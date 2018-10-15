#ifndef __MSG_H__
#define __MSG_H__
#include <cstddef>
#include <cstdint>

struct proto_header
{ 
	uint32_t m_cmd = 0;
	union { uint32_t m_mid = 0; };
	unsigned int m_length = 0;

	bool check_msg(unsigned int max_body_length);
};

struct proto_msg : public proto_header
{
	proto_msg() {}
	proto_msg(uint32_t cmd) { m_cmd = cmd; }

	size_t size() {
		return sizeof(proto_header) + m_length;
	}

	template<class T>
	int serialize_msg(const T& msg)
	{
		int c = msg.ByteSize();
		if (c < msg_data_length)
		{
			m_length = c;
			msg.SerializeToArray(data, c);
			return c;
		}
		return 0;
	}

	enum {
		msg_data_length = 1024 * 64
	};
	char data[msg_data_length];
};

enum cmd_enum
{
	cmd_login_request = 1,

	cmd_module_logon
};


#endif