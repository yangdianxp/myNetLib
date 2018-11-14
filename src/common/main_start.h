#ifndef __MAIN_START_H__
#define __MAIN_START_H__
#include <boost/asio.hpp>
#include "signal_process.h"
#include "common.h"

void main_start(boost::asio::io_service& io_context, bool console = false)
{
	config_settings& config_reader = config_settings::instance();
	config_reader.load("conf/net.xml");
	config_reader.print();
	SLog::InitLog(config_reader.get_log_filename(), console);
	SLog::SetLevel(severity_levels(config_reader.get_log_level()));
	signal_init(io_context);
}

#endif
