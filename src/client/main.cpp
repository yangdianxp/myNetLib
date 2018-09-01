#include <iostream>
#include <set>
#include <memory>
#include <boost/asio.hpp>

#include "base_client.h"

int main(int argc, char* argv[])
{
	using tcp = boost::asio::ip::tcp;
	try
	{
		if (argc != 3)
		{
			std::cerr << "Usage: chat_client <host> <port>\n";
			return 1;
		}
		/*boost::asio::io_context io_context;
		std::string ip = argv[1];
		std::string port = argv[2];
		boost::asio::ip::tcp::resolver resolver(io_context);
		boost::asio::ip::tcp::resolver::query query(ip, port);
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		base_client c(io_context, endpoint_iterator);*/
		boost::asio::io_context io_context;

		tcp::resolver resolver(io_context);
		auto endpoints = resolver.resolve(argv[1], argv[2]);
		std::set<std::shared_ptr<base_client>> client_set;
		client_set.insert(std::make_shared<base_client>(io_context, endpoints, client_set));
		std::shared_ptr<boost::asio::io_service::work> work
			= std::make_shared<boost::asio::io_service::work>(io_context);
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