#ifndef __CMD_THREAD_H__
#define __CMD_THREAD_H__
#include <thread>
#include <string>
#include "base_client.h"

class cmd_thread : public base_client
{
public:
	cmd_thread(boost::asio::io_context& io_context,
		std::string remote_ip, std::string remote_port);
	~cmd_thread();

	void routine();
	
private:
	void emit(std::string cmd);
	std::thread m_thread;
};


#endif
