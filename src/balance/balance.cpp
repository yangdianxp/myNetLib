#include <iostream>

#include "balance_server.h"
#include "main_start.h"

int main(int argc, char* argv[])
{
	try
	{
		SLOG_INFO << "server start.";
		boost::asio::io_service io_context;
		main_start(io_context);
		config_settings& config_reader = config_settings::instance();
		std::shared_ptr<balance_server> server =
			std::make_shared<balance_server>(io_context, config_reader.get_local_port());
		server->connect_remote(config_reader.get_remote_ip(), std::to_string(config_reader.get_remote_port()),
			module_central_type);
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

