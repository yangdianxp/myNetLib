#ifndef __MSG_H__
#define __MSG_H__
#include <cstddef>
#include <cstdint>

struct proto_header
{ 
	uint32_t m_cmd = 0;
	union { uint32_t m_mid = 0; };
	unsigned int m_length = 0;

	bool check_msg();
};

struct proto_msg : public proto_header
{
	proto_msg() {}
	proto_msg(uint32_t cmd) { m_cmd = cmd; }

	size_t size() {
		return sizeof(proto_header) + m_length;
	}

	template<class T>
	int parse(T& proto)
	{
		return proto.ParseFromArray(m_data, m_length);
	}

	template<class T>
	int serialize_msg(const T& msg)
	{
		int c = msg.ByteSize();
		if (c < msg_data_length)
		{
			m_length = c;
			msg.SerializeToArray(m_data, c);
			return c;
		}
		return 0;
	}

	enum {
		msg_data_length = 1024 * 64
	};
	char m_data[msg_data_length];
};

enum cmd_enum
{
	cmd_login_request = 1,

	cmd_module_logon,                //登录central服务器
	cmd_module_logon_ack,
	cmd_broadcast_module_logon,
	cmd_broadcast_module_logon_ack,
	cmd_register_info,					//注册模块信息
	cmd_register_info_ack,
	cmd_request_vid_range,				//gateway请求vid范围
	cmd_request_vid_range_ack,
	cmd_end
};


#endif