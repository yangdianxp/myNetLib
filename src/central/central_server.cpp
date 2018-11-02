#include "central_server.h"
#include "central_client.h"

central_server::central_server(boost::asio::io_context& io_context, short port) :
	middleware_server(io_context, port)
{
	config_settings& config_reader = config_settings::instance();
	int mid_begin = config_reader.get_mid_begin();
	int mid_end = config_reader.get_mid_end();
	m_unique_mid.init(mid_begin, mid_end);
	m_id = get_unique_mid();
	m_vid_manage.set_unit_size(config_reader.get_vid_unit_size());
}

uint32_t central_server::get_unique_mid()
{
	return m_unique_mid.get();
}
void central_server::del_unique_mid(std::size_t mid)
{
	m_unique_mid.del(mid);
}

vid_manage::vid_pair central_server::get_vid_range(std::size_t mid)
{
	return m_vid_manage.get(mid);
}
vid_manage& central_server::get_vid_manage()
{
	return m_vid_manage;
}
