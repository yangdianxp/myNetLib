#include <iostream>

#include "central_server.h"
#include "main_start.h"

int main(int argc, char* argv[])
{
	try
	{
		SLOG_INFO << "server start.";
		boost::asio::io_service io_context;
		main_start(io_context);
		config_settings& config_reader = config_settings::instance();
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

