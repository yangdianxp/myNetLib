#ifndef __CENTRAL_SERVER_H__
#define __CENTRAL_SERVER_H__
#include "middleware_server.h"
#include "central_client.h"
#include "unique_code.h"
#include "range_manage.h"

class central_server : public middleware_server<central_client>
{
public:
	central_server(boost::asio::io_context& io_context, short port);

	uint32_t get_unique_mid();
	void del_unique_mid(std::size_t mid);
	range_manage::vid_pair get_vid_range(std::size_t mid);
	range_manage& get_vid_manage();
private:
	unique_code m_unique_mid;
	range_manage m_vid_manage;
};


#endif
