#include <iostream>
#include <boost/asio.hpp>

#include "common.h"
#include "base_server.h"
#include "config_settings.h"

int main(int argc, char* argv[])
{
	try
	{
		config_settings& config_reader = config_settings::instance();
		config_reader.load("conf/net.xml");
		config_reader.print();
		SLog::InitLog(config_reader.get_log_filename());
		SLog::SetLevel(slog_debug);

		SLOG_INFO << "server start.";
		boost::asio::io_service io_context;
		base_server s(io_context, config_reader.get_local_port());

		io_context.run();
	}
	catch (std::exception& e)
	{
		SLOG_ERROR << "Exception: " << e.what();
	}

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}

