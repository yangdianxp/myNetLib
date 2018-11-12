#include <iostream>
#include <boost/asio.hpp>

#include "signal_process.h"
#include "common.h"
#include "central_server.h"

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
		signal_init(io_context);
		std::shared_ptr<central_server> server = 
			std::make_shared<central_server>(io_context, config_reader.get_local_port());
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

