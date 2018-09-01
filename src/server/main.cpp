#include <iostream>
#include <boost/asio.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace logging = boost::log;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

#include "common.h"
#include "base_server.h"

void init()
{
	boost::log::add_common_attributes();
	logging::add_file_log
	(
		keywords::file_name = "sample_%N.log",
		keywords::rotation_size = 10 * 1024 * 1024,
		keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
		keywords::format = "[%TimeStamp%]: %Message%",
		keywords::auto_flush = true
	);

	logging::core::get()->set_filter
	(
		logging::trivial::severity >= logging::trivial::info
	);
}

int main(int argc, char* argv[])
{
	using tcp = boost::asio::ip::tcp;
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: main <port>\n";
			return 1;
		}
		init();

		BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
		BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
		BOOST_LOG_TRIVIAL(info) << "An informational severity message";
		BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
		BOOST_LOG_TRIVIAL(error) << "An error severity message";
		BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";

		boost::asio::io_context io_context;
		base_server s(io_context, std::atoi(argv[1]));

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

