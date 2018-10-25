#ifndef __MEDIA_SERVER_H__
#define __MEDIA_SERVER_H__
#include "module.h"

class media_server : public module
{
	using tcp = boost::asio::ip::tcp;
public:
	media_server(boost::asio::io_context& io_context, short port);

private:

};


#endif
