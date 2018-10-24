#include <iostream>
#include <boost/asio.hpp>

#include "common.h"
#include "login_server.h"

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
		std::shared_ptr<login_server> server =
			std::make_shared<login_server>(io_context, config_reader.get_local_port());
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

