#include <iostream>
#include <list>

#include "user_client.h"
#include "main_start.h"


int main(int argc, char* argv[])
{
	try
	{
		SLOG_INFO << "client start.";
		boost::asio::io_context io_context;
		main_start(io_context);
		//SLOG_ERROR << "client start1.";
		config_settings& config_reader = config_settings::instance();
		std::string remote_ip = config_reader.get_remote_ip();
		std::string remote_port = std::to_string(config_reader.get_remote_port());
		std::string ports[4] = {"21000", "21001", "21002", "21003"};
		std::size_t tids[4] = { 0, 100000, 200000, 300000 };
		std::list<std::shared_ptr<user_client>> users;
		int uid_max = 14000;
		for (int i = 10000; i < uid_max; ++i)
		{
			auto client = std::make_shared<user_client>(io_context, remote_ip, ports[0/*i % 4*/]);
			client->set_reconnect_time(3000);
			client->init(std::shared_ptr<base_server>());
			client->set_active_type(module_gateway_type);
			client->set_user_info(i / 2 + tids[(i - 10000) / ((uid_max - 10000) / 4)], i);
			client->set_tmp_send_msg();
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