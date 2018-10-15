#include "msg.h"

bool proto_header::check_msg(unsigned int max_body_length)
{
	if (m_cmd == 0 || m_length > max_body_length)
		return false;
	return true;
}