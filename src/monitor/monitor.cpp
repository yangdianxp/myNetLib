#include <iostream>

#include "monitor_server.h"
#include "cmd_thread.h"
#include "main_start.h"

int main(int argc, char* argv[])
{
	try
	{
		SLOG_INFO << "server start.";
		boost::asio::io_service io_context;
		main_start(io_context, true);
		config_settings& config_reader = config_settings::instance();
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

