#include "log.h"

#include <stdexcept>
#include <iostream>
#include <boost/smart_ptr.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>

#define BOOST_LOG_DYN_LINK

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

using namespace boost;

boost::log::sources::severity_logger<severity_levels> SLog::slg;

SLog::SLog(void)
{
}


SLog::~SLog(void)
{
}

template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
	std::basic_ostream< CharT, TraitsT >& strm, severity_levels lvl)
{
	static const char* const str[] =
	{
		"emergency",
		"alert",
		"critical",
		"error",
		"warning",
		"notice",
		"info",
		"debug"
	};
	if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
		strm << str[lvl];
	else
		strm << static_cast<int>(lvl);
	return strm;
};

BOOST_LOG_ATTRIBUTE_KEYWORD(_severity, "Severity", severity_levels);
BOOST_LOG_ATTRIBUTE_KEYWORD(_timestamp, "TimeStamp", boost::posix_time::ptime);
BOOST_LOG_ATTRIBUTE_KEYWORD(_uptime, "Uptime", attrs::timer::value_type);
BOOST_LOG_ATTRIBUTE_KEYWORD(_scope, "Scope", attrs::named_scope::value_type);

void SLog::InitLog(const std::string& filename)
{
	//auto asink = logging::add_console_log(std::clog, keywords::format = expr::stream
	//	<< expr::format_date_time(_timestamp, "[%Y-%m-%d,%H:%M:%S.%f]")
	//	<< " <" << _severity
	//	<< ">: " << expr::message);

	//asink->set_filter(expr::attr< severity_levels >("Severity") <= slog_error);

	//logging::core::get()->add_sink(asink);

	//for (int i = slog_emergency; i <= slog_debug; i++)
	//{
		std::stringstream allfilename;
#ifdef _WIN32
		//allfilename << "logs\\" << filename << "_" << (severity_levels)i << "_%Y%m%d_%H%M%S.log";
		allfilename << "logs\\" << filename << "_%Y%m%d_%H%M%S.log";
#else 
		allfilename << "logs/" << filename << "_%Y%m%d_%H%M%S.log";
#endif
		auto sink = logging::add_file_log(
			keywords::file_name = allfilename.str(),
			keywords::rotation_size = 1 * 1024 * 1024 * 1024,
			keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
			keywords::open_mode = std::ios::app,
			keywords::auto_flush = true
		);


		sink->locked_backend()->set_file_collector(sinks::file::make_collector(
			keywords::target = "logs",
			keywords::max_size = 30 * 1024 * 1024,
			keywords::min_free_space = 100 * 1024 * 1024
		));

		sink->locked_backend()->scan_for_files();

		//if (i <= slog_error)
		//{
			//sink->locked_backend()->auto_flush();
		//}

		//sink->set_filter(expr::attr< severity_levels >("Severity") == (severity_levels)i);

		sink->set_formatter
		(
			expr::format("[%1%](%2%)<%3%_%4%>{%5%}: %6%")
			% expr::attr< severity_levels >("Severity")
			% expr::attr< attrs::current_thread_id::value_type >("ThreadID")
			% expr::format_date_time(_timestamp, "%Y-%m-%d,%H:%M:%S.%f")
			% expr::attr< boost::posix_time::time_duration >("Uptime")
			% expr::format_named_scope(_scope, keywords::format = "%n[%f:%l]", keywords::depth = 1)
			% expr::smessage
		);

		logging::core::get()->add_sink(sink);
	//}

	logging::add_common_attributes();
	logging::core::get()->add_thread_attribute("Scope", attrs::named_scope());
	logging::core::get()->add_thread_attribute("Uptime", attrs::timer());
}

void SLog::SetLevel(severity_levels sl)
{
	logging::core::get()->set_filter(expr::attr< severity_levels >("Severity") <= sl);
}