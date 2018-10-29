#include <iostream>
#include "cmd_thread.h"

cmd_thread::cmd_thread(boost::asio::io_context& io_context,
	std::string remote_ip, std::string remote_port)
	: base_client(io_context, remote_ip, remote_port),
	m_thread(std::bind(&cmd_thread::routine, this))
{
}

cmd_thread::~cmd_thread()
{
}

void cmd_thread::routine()
{
	std::cout << "cmd_thread routine start." << std::endl;
}

void cmd_thread::emit(std::string cmd)
{
	boost::asio::post(m_io_context, )
}