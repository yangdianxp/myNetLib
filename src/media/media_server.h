#ifndef __MEDIA_SERVER_H__
#define __MEDIA_SERVER_H__
#include "middleware_server.h"
#include "media_client.h"

class media_server : public middleware_server<media_client>
{
	using tcp = boost::asio::ip::tcp;
public:
	media_server(boost::asio::io_context& io_context, short port);

private:

};


#endif
