#ifndef __COMMON_H__
#define __COMMON_H__
#include <memory>
#include <string>
#include <map>

#include "proc.pb.h"
#include "msg.h"
#include "log.h"
#include "config_settings.h"

//全局模块类型
enum g_module_type
{
	module_none_type,
	module_gateway_type,
	module_login_type,
	module_central_type,
	module_balance_type,

	module_media_type = 16,
	module_end_type
};

#endif