#include <iostream>
#include <set>
#include <boost/asio.hpp>

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
		auto client = std::make_shared<user_client>(io_context, remote_ip, remote_port);
		client->set_reconnect_time(3000);
		client->init(std::shared_ptr<base_server>());
		client->set_active_type(module_user_type);
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