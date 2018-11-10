#include <iostream>
#include <boost/asio.hpp>
#include <list>

#include "user_client.h"

int main(int argc, char* argv[])
{
	try
	{
		config_settings& config_reader = config_settings::instance();
		config_reader.load("conf/net.xml");
		config_reader.print();
		SLog::InitLog(config_reader.get_log_filename());
		SLog::SetLevel(slog_debug);

		SLOG_INFO << "client start.";
		boost::asio::io_context io_context;
		std::string remote_ip = config_reader.get_remote_ip();
		std::string remote_port = std::to_string(config_reader.get_remote_port());
		std::string ports[4] = {"21000", "21001", "21002", "21003"};
		std::list<std::shared_ptr<user_client>> users;
		for (int i = 10000; i < 40000; ++i)
		{
			auto client = std::make_shared<user_client>(io_context, remote_ip, ports[i % 4]);
			client->set_reconnect_time(3000);
			client->init(std::shared_ptr<base_server>());
			client->set_active_type(module_gateway_type);
			client->set_user_info(i / 3, i);
			users.push_back(client);
		}
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