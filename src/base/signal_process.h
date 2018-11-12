#ifndef __SIGNAL_PROCESS__
#define __SIGNAL_PROCESS__
#include <signal.h>
#include <functional>
#include <boost/asio.hpp>
#include "log.h"

// 通过这个参数获取当前触发的信号值
void signal_handler(const boost::system::error_code& ec, int signal_number)
{
	SLOG_ERROR << "signal_number:" << " " << signal_number << ec.message();
}

void signal_init(boost::asio::io_context& io_context)
{
	signal(SIGPIPE, SIG_IGN);
	boost::asio::signal_set signals(io_context, SIGPIPE, SIGHUP, SIGINT);
	signals.async_wait(std::bind(signal_handler, std::placeholders::_1, std::placeholders::_2));
}

#endif