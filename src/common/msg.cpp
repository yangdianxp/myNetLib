#include "msg.h"
#include "log.h"

bool proto_header::check_msg()
{
	if (m_cmd == 0 || m_cmd >= cmd_end || m_length > proto_msg::msg_data_length)
	{
		SLOG_ERROR << "msg error, m_cmd:" << m_cmd << ", m_length:" << m_length;
		return false;
	}
	return true;
}