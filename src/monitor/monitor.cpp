#include <iostream>
#include <boost/asio.hpp>

#include "common.h"
#include "monitor_server.h"
#include "cmd_thread.h"

int main(int argc, char* argv[])
{
	try
	{
		config_settings& config_reader = config_settings::instance();
		config_reader.load("conf/net.xml");
		config_reader.print();
		SLog::InitLog(config_reader.get_log_filename(), true);
		SLog::SetLevel(slog_debug);

		SLOG_INFO << "server start.";
		boost::asio::io_service io_context;
		std::shared_ptr<monitor_server> server =
			std::make_shared<monitor_server>(io_context, config_reader.get_local_port());
		server->connect_remote(config_reader.get_remote_ip(), std::to_string(config_reader.get_remote_port()),
			module_central_type);
		std::shared_ptr<cmd_thread> cmd_routine =
			std::make_shared<cmd_thread>(io_context, config_reader.get_local_ip(),
				std::to_string(config_reader.get_local_port()));
		cmd_routine->set_reconnect_time(3000);
		cmd_routine->init(std::shared_ptr<base_server>());
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

