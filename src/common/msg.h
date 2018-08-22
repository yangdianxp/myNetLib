#ifndef __MSG_H__
#define __MSG_H__

struct proto_header
{
	unsigned short cmd;
	unsigned int length;

	bool check_msg(unsigned int max_body_length);
};

enum cmd_enum
{
	cmd_login_request
};


#endif