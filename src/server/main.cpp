#include <iostream>
#include <boost/asio.hpp>

#include "common.h"
#include "base_server.h"

int main(int argc, char* argv[])
{
	SLog::InitLog("common");
	SLog::SetLevel(slog_debug);
	using tcp = boost::asio::ip::tcp;
	try
	{
		if (argc != 2)
		{
			SLOG_ERROR << "Usage: main <port>";
			return 1;
		}
		SLOG_INFO << "server start.";
		boost::asio::io_context io_context;
		base_server s(io_context, std::atoi(argv[1]));

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

