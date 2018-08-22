#include <iostream>
#include <boost/asio.hpp>
#include "common.h"
#include "base_server.h"

int main(int argc, char* argv[])
{
	using tcp = boost::asio::ip::tcp;
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: main <port>\n";
			return 1;
		}

		boost::asio::io_context io_context;
		base_server s(io_context, std::atoi(argv[1]));

		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

#ifdef _WIN32
	system("pause");
#endif
	return 0;
}

