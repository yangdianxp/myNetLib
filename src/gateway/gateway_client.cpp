#include <set>
#include "gateway_client.h"
#include "gateway_server.h"
gateway_client::gateway_client(boost::asio::io_context& io_context, \
	std::string remote_ip, std::string remote_port) :
	common_client(io_context, remote_ip, remote_port)
{

}

gateway_client::gateway_client(boost::asio::io_context& io_context, tcp::socket socket) :
	common_client(io_context, std::move(socket))
{

}

void gateway_client::handle_error_aux()
{
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		if (m_type == module_user_type)
		{
			auto route = server->get_route();
			std::set<std::size_t> tids;
			auto self(shared_from_this());
			auto fn = [self, &tids](const std::size_t vid, const route::node& n)
			{
				tids.insert(n.tid);
			};
			route->for_each_vid_node(m_id, fn);
			std::set<std::shared_ptr<common_client>> balances;
			for (auto n : tids)
			{
				auto id = server->get_balance(n);
				auto balance = route->get_client(id);
				if (balance)
				{
					balances.insert(balance);
				}
			}
			proto_msg msg(cmd_user_disconnection, m_id);
			for (auto n : balances)
			{
				n->write((char *)&msg, msg.size());
			}
			route->delete_node(m_id);
			server->del_vid(m_id);
			/*做完所有工作，最后再删自己*/
			route->delete_vid(std::dynamic_pointer_cast<common_client>(shared_from_this()));
		}
		else {
			if (m_type == module_balance_type)
			{
				auto& balance_list = server->get_balance_list();
				balance_list.erase(m_id);
			}
			common_client::handle_error_aux();
		}
	}
}

void gateway_client::handle_module_logon_ack(proto_msg& msg)
{
	SLOG_DEBUG << "handle_module_logon_ack";
	common_client::handle_module_logon_ack(msg);
	proto_msg req(cmd_request_vid_range);
	write((char *)&req, req.size());
}

void gateway_client::handle_request_vid_range_ack(proto_msg& msg)
{
	pb::internal::range range;
	msg.parse(range);
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] << ", vid range begin:" << range.begin()
		<< ", end:" << range.end();
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		server->set_vid_range(range.begin(), range.end());
	}
}
void gateway_client::handle_update_balance_list(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		pb::internal::balance_list list;
		msg.parse(list);
		for (int i = 0; i < list.range_size(); ++i)
		{
			const pb::internal::mid_range& mid_range = list.range(i);
			const pb::internal::range& range = mid_range.range();
			auto& balance_list = server->get_balance_list();
			balance_list.insert(std::make_pair(mid_range.mid(), std::make_pair(range.begin(), range.end())));
		}
	}
}
void gateway_client::handle_create_channel(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		pb::external::modify_channel modify;
		msg.parse(modify);
		modify.set_vid(m_id);
		modify.set_src(server->get_id());
		SLOG_DEBUG << modify.DebugString();
		proto_msg r_msg;
		memcpy(&r_msg, &msg, sizeof(proto_header));
		route::node n(modify.type(), modify.tid(), modify.uid(), modify.vid());
		if (!route->find_node(n))
		{
			route->add_node(std::shared_ptr<common_client>(), n);
			r_msg.serialize_msg(modify);
			auto id = server->get_balance(modify.tid());
			auto balance = route->get_client(id);
			if (balance)
			{
				balance->write((char *)&r_msg, r_msg.size());
			}
		}
		else {
			SLOG_WARNING << "this channel already exists. type:" << modify.type() << " tid:" << modify.tid()
				<< " uid:" << modify.uid() << " vid:" << modify.vid();
			modify.set_rslt(pb::external::modify_channel::rslt_already_exist);
			r_msg.serialize_msg(modify);
			write((char *)&r_msg, r_msg.size());
		}
	}
}
void gateway_client::handle_create_channel_ack(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		pb::external::modify_channel modify;
		msg.parse(modify);
		SLOG_DEBUG << modify.DebugString();
		proto_msg r_msg;
		memcpy(&r_msg, &msg, msg.size());
		route::node n(modify.type(), modify.tid(), modify.uid(), modify.vid());
		if (route->find_node(n))
		{
			route->delete_node(n);
			if (modify.rslt() == pb::external::modify_channel::rslt_succ)
			{
				auto media = route->get_client(modify.src());
				if (media)
				{
					route->add_node(media, n);
				}
			}
		}
		else {
			modify.set_rslt(pb::external::modify_channel::rslt_not_exist);
			r_msg.serialize_msg(modify);
		}
		auto client = route->get_vid(modify.vid());
		if (client)
		{
			client->write((char *)&r_msg, r_msg.size());
		}
	}
}
void gateway_client::handle_delete_channel(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	pb::external::modify_channel modify;
	msg.parse(modify);
	proto_msg r_msg;
	memcpy(&r_msg, &msg, sizeof(proto_header));
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		modify.set_vid(m_id);
		modify.set_src(server->get_id());
		SLOG_DEBUG << modify.DebugString();
		route::node n(modify.type(), modify.tid(), modify.uid(), modify.vid());
		if (route->find_node(n))
		{
			r_msg.serialize_msg(modify);
			/*向balance发送*/
			auto id = server->get_balance(modify.tid());
			auto balance = route->get_client(id);
			if (balance)
			{
				balance->write((char *)&r_msg, r_msg.size());
			}
			//删除通道
			route->delete_node(n);
			modify.set_rslt(pb::external::modify_channel::rslt_succ);
		}
		else {
			SLOG_WARNING << "this channel does not exist.";
			modify.set_rslt(pb::external::modify_channel::rslt_not_exist);
		}
		r_msg.m_cmd = cmd_delete_channel_ack;
		r_msg.serialize_msg(modify);
		write((char *)&r_msg, r_msg.size());
	}
}
void gateway_client::handle_delete_channel_ack(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd] 
		<< ", mid:" << m_id << ", type info:" << config_settings::instance().get_module_name(m_type);
}
void gateway_client::handle_interchannel_broadcast(proto_msg& msg)
{
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		msg.m_vid = m_id;
		auto route = server->get_route();
		route::node n(msg.m_type, msg.m_tid, msg.m_uid, msg.m_vid);
		auto media = route->get_node(n);
		if (media)
		{
			media->write((char *)&msg, msg.size());
		}
	}
}
void gateway_client::handle_interchannel_broadcast_ack(proto_msg& msg)
{
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		auto route = server->get_route();
		route::ttnode ttn(msg.m_type, msg.m_tid);
		std::set<std::size_t> vids;
		auto self = shared_from_this();
		auto fn = [self, &vids, msg](std::shared_ptr<common_client> client, const route::node& n)
		{
			/*如果client为空，则表示通道还没有完全建立好*/
			if (client && n.vid != msg.m_vid)
			{
				vids.insert(n.vid);
			}
		};
		route->for_each_ttnode(ttn, fn);
		for (auto n : vids)
		{
			auto client = route->get_vid(n);
			client->write((char *)&msg, msg.size());
		}
	}
}
void gateway_client::handle_monitor_tid_manage(proto_msg& msg)
{
	SLOG_INFO << "cmd:" << msg.m_cmd << ", info:" << m_cmd_desc[msg.m_cmd];
	auto server = std::dynamic_pointer_cast<gateway_server>(m_server);
	if (server)
	{
		auto& list = server->get_balance_list();
		pb::monitor::range_manage manage;
		for (auto n : list)
		{
			pb::internal::mid_range* m_r = manage.add_already_assigned();
			m_r->set_mid(n.first);
			pb::internal::range* r = m_r->mutable_range();
			r->set_begin(n.second.first);
			r->set_end(n.second.second);
		}
		proto_msg ack_msg(cmd_monitor_tid_manage_ack);
		ack_msg.serialize_msg(manage);
		write((char *)&ack_msg, ack_msg.size());
	}
}

void gateway_client::init(std::shared_ptr<base_server> server)
{
	common_client::init(server);
	std::shared_ptr<gateway_client> client = std::dynamic_pointer_cast<gateway_client>(shared_from_this());
	if (client)
	{
		m_function_set[cmd_module_logon_ack] = std::bind(&gateway_client::handle_module_logon_ack, this, std::placeholders::_1);
		m_function_set[cmd_request_vid_range_ack] = std::bind(&gateway_client::handle_request_vid_range_ack, this, std::placeholders::_1);
		m_function_set[cmd_update_balance_list] = std::bind(&gateway_client::handle_update_balance_list, this, std::placeholders::_1);
		m_function_set[cmd_create_channel] = std::bind(&gateway_client::handle_create_channel, this, std::placeholders::_1);
		m_function_set[cmd_create_channel_ack] = std::bind(&gateway_client::handle_create_channel_ack, this, std::placeholders::_1);
		m_function_set[cmd_delete_channel] = std::bind(&gateway_client::handle_delete_channel, this, std::placeholders::_1);
		m_function_set[cmd_delete_channel_ack] = std::bind(&gateway_client::handle_delete_channel_ack, this, std::placeholders::_1);
		m_function_set[cmd_interchannel_broadcast] = std::bind(&gateway_client::handle_interchannel_broadcast, this, std::placeholders::_1);
		m_function_set[cmd_interchannel_broadcast_ack] = std::bind(&gateway_client::handle_interchannel_broadcast_ack, this, std::placeholders::_1);
		m_function_set[cmd_monitor_tid_manage] = std::bind(&gateway_client::handle_monitor_tid_manage, this, std::placeholders::_1);
	}
}
