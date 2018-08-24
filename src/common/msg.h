#ifndef __MSG_H__
#define __MSG_H__

struct proto_header
{
	unsigned short cmd = 0;
	unsigned int length = 0;

	bool check_msg(unsigned int max_body_length);
};

struct proto_msg : public proto_header
{
	enum {
		msg_data_length = 0x1000
	};
	char data[msg_data_length];

	size_t size() {
		return sizeof(proto_header) + length;
	}

	template<class T>
	int serialize_msg(const T& msg)
	{
		int c = msg.ByteSize();
		if (c < msg_data_length)
		{
			length = c;
			msg.SerializeToArray(data, c);
			return c;
		}
		return 0;
	}
};

enum cmd_enum
{
	cmd_login_request = 1,
};


#endif