#ifndef __CENTRAL_SERVER_H__
#define __CENTRAL_SERVER_H__
#include "middleware_server.h"
#include "central_client.h"
#include "unique_code.h"
#include "vid_manage.h"

class central_server : public middleware_server<central_client>
{
public:
	central_server(boost::asio::io_context& io_context, short port);

	uint32_t get_unique_mid();
	void del_unique_mid(std::size_t mid);
	vid_manage::vid_pair get_vid_range(std::size_t mid);
	vid_manage& get_vid_manage();
private:
	unique_code m_unique_mid;
	vid_manage m_vid_manage;
};


#endif
