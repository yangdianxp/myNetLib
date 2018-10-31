#include <iostream>
#include <sstream>
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
	while (true)
	{
		std::string line;
		getline(std::cin, line, '\n');
		emit(line);
	}
}

void cmd_thread::emit(std::string str)
{
	boost::asio::post(m_io_context, 
		[this, str]() 
		{
			proto_msg msg(cmd_monitor_instruction);
			pb::monitor::cmd cmd;
			cmd.set_content(str);
			msg.serialize_msg(cmd);
			write((char *)&msg, msg.size());
		});
}