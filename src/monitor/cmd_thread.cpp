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
		// 以换行为结束，允许行内有空格
		int num = 0;
		std::stringstream ss1(line);
		std::string cmd;
		ss1 >> cmd;
		std::size_t index = line.find_first_of("0123456789");
		if (index != std::string::npos)
		{
			std::string num_str(line, index);
			std::stringstream ss(num_str);
			ss >> num;
		}
		
		std::cout << cmd << " " << num << std::endl;
		//emit(line);
	}
}

void cmd_thread::emit(std::string cmd)
{
	boost::asio::post(m_io_context, 
		[this, cmd]() 
		{
			write(cmd.c_str(), cmd.size());
		});
}