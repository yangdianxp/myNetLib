#include "user_client.h"

user_client::user_client(boost::asio::io_context& io_context,
	std::string remote_ip, std::string remote_port) :
	common_client(io_context, remote_ip, remote_port)
{

}
user_client::user_client(boost::asio::io_context& io_context, tcp::socket socket) :
	common_client(io_context, std::move(socket))
{

}
void user_client::handle_connect_succ()
{
	pb::external::modify_channel modify;
	modify.set_type(module_media_type);
	modify.set_tid(1000);
	modify.set_uid(10000);
	proto_msg msg(cmd_create_channel);
	write((char *)&msg, msg.size());
}
