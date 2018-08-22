#include "msg.h"

bool proto_header::check_msg(unsigned int max_body_length)
{
	if (cmd == 0 || length > max_body_length)
		return false;
	return true;
}