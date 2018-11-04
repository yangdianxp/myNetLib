#ifndef __MSG_H__
#define __MSG_H__
#include <cstddef>
#include <cstdint>

struct proto_header
{ 
	uint32_t m_cmd = 0;
	uint32_t m_type = 0;
	uint32_t m_tid = 0;
	uint32_t m_uid = 0;
	union {
		uint32_t m_mid; uint32_t m_vid;
	};
	unsigned int m_length = 0;

	bool check_msg();
};

struct proto_msg : public proto_header
{
	proto_msg() {}
	proto_msg(uint32_t cmd) { m_cmd = cmd; }
	proto_msg(uint32_t cmd, uint32_t vid) { m_cmd = cmd; m_vid = vid; }
	proto_msg(uint32_t cmd, uint32_t type, uint32_t tid, uint32_t uid)
	{
		m_cmd = cmd; m_type = type; m_tid = tid; m_uid = uid;
	}

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

	cmd_module_logon,                //��¼central������
	cmd_module_logon_ack,
	cmd_broadcast_module_logon,
	cmd_broadcast_module_logon_ack,
	cmd_register_info,					//ע��ģ����Ϣ
	cmd_register_info_ack,
	cmd_request_vid_range,				//gateway����vid��Χ
	cmd_request_vid_range_ack,
	cmd_update_balance_list,			//����balance�б�
	cmd_update_balance_list_ack,

	cmd_create_channel,					//����ͨ��
	cmd_create_channel_ack,
	cmd_user_disconnection,
	cmd_user_disconnection_ack,
	/*������Ϣ����*/
	cmd_interchannel_broadcast,			//ͨ���ڹ㲥
	cmd_interchannel_broadcast_ack,

	cmd_monitor_instruction,			//monitor����ָ��
	cmd_monitor_instruction_ack,
	cmd_monitor_route,					//����·����Ϣ
	cmd_monitor_route_ack,
	cmd_monitor_vid_manage,				//����central��vid������Ϣ
	cmd_monitor_vid_manage_ack,
	cmd_end
};


#endif