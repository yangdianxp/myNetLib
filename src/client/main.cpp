#include <iostream>
#include <set>
#include <memory>
#include <boost/asio.hpp>

#include "base_client.h"
#include "config_settings.h"

int main(int argc, char* argv[])
{
	using tcp = boost::asio::ip::tcp;
	try
	{
		config_settings& config_reader = config_settings::instance();
		config_reader.load("conf/net.xml");
		config_reader.print();
		SLog::InitLog(config_reader.get_log_filename());
		SLog::SetLevel(slog_debug);

		boost::asio::io_context io_context;
		tcp::resolver resolver(io_context);
		std::string remote_ip = config_reader.get_remote_ip();
		std::string remote_port = std::to_string(config_reader.get_remote_port());
		auto endpoints = resolver.resolve(remote_ip, remote_port);
		std::set<std::shared_ptr<base_client>> client_set;
		client_set.insert(std::make_shared<base_client>(io_context, endpoints));
		std::shared_ptr<boost::asio::io_service::work> work
			= std::make_shared<boost::asio::io_service::work>(io_context);
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