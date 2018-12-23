#include <iostream>
#include <memory>

#include <boost/date_time.hpp>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/placeholders.hpp>

void func1(const boost::system::error_code& ec)
{
	std::cout << "func1  " << ec.message() << std::endl;
}
void func2(const boost::system::error_code& ec)
{
	std::cout << "func2" << ec.message() << std::endl;
}

int main()
{
	boost::asio::io_context io_context;
	std::shared_ptr<boost::asio::steady_timer> timer = 
		std::make_shared<boost::asio::steady_timer>(io_context);

	timer->expires_from_now(boost::asio::chrono::milliseconds(4000));
	timer->async_wait(&func1);
	timer->expires_from_now(boost::asio::chrono::milliseconds(5000));
	timer->async_wait(&func2);

	io_context.run();
	return 0;
}

/*
	1
	10
	11
	100
*/