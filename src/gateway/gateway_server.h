#ifndef __GATEWAY_SERVER_H__
#define __GATEWAY_SERVER_H__
#include "middleware_server.h"
#include "gateway_client.h"
#include "unique_code.h"

class gateway_server : public middleware_server<gateway_client>
{
	using tcp = boost::asio::ip::tcp;
public:
	gateway_server(boost::asio::io_context& io_context, short port);
	void handle_accept_succ(tcp::socket& socket);

	void set_vid_range(uint32_t min, uint32_t max);
	void del_vid(uint32_t id);
	std::map<std::size_t, range_manage::pair>& get_balance_list();
	/*获取对应房间号区间的balance mid*/
	std::size_t get_balance(std::size_t tid);
private:
	unique_code m_vid_range;
	/*可以接受客户端连接了*/
	bool m_ready = false;
	std::map<std::size_t, range_manage::pair> m_balance_list;
};


#endif
