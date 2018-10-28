#pragma once
#include <string>

#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/record_ostream.hpp>

enum severity_levels
{
	slog_emergency = 0,                //slog_emerg
	slog_alert = 1,                    //slog_alert
	slog_critical = 2,                 //slog_crit
	slog_error = 3,                    //slog_error 大于slog_error的log不会在console显示 并且不会马上写入文件
	slog_warning = 4,                  //slog_warning
	slog_notice = 5,                   //slog_notice
	slog_info = 6,                     //slog_info
	slog_debug = 7                     //slog_debug
};

class SLog
{
public:
	SLog(void);
	~SLog(void);

	static boost::log::sources::severity_logger<severity_levels> slg;

	static void InitLog(const std::string& filename);

	static void SetLevel(severity_levels sl);
};

#define BOOST_SLOG(slog_lvl) BOOST_LOG_FUNCTION();BOOST_LOG_SEV(SLog::slg, slog_lvl)

#define SLOG_EMERGENCY BOOST_SLOG(slog_emergency)
#define SLOG_ALERT BOOST_SLOG(slog_alert)
#define SLOG_CRITICAL BOOST_SLOG(slog_critical)
#define SLOG_ERROR BOOST_SLOG(slog_error)
#define SLOG_WARNING BOOST_SLOG(slog_warning)
#define SLOG_NOTICE BOOST_SLOG(slog_notice)
#define SLOG_INFO BOOST_SLOG(slog_info)
#define SLOG_DEBUG BOOST_SLOG(slog_debug)