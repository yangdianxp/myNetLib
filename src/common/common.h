#ifndef __COMMON_H__
#define __COMMON_H__
#include <memory>

#include "proc.pb.h"
#include "msg.h"
#include "log.h"
#include "config_settings.h"

//ȫ��ģ������
enum g_module_type
{
	module_none_type,
	module_gateway_type,
	module_login_type,
	module_central_type,

	module_media_type = 16,
	module_end_type
};


#endif