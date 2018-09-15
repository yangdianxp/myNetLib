#ifndef __REGISTER_H__
#define __REGISTER_H__
#include "MsgProto.h"
namespace protocol{

	enum RegisterError
	{
		error_success = 0,
		error_register_1 = 1,
	};

	MSG_BEGIN(ModuleLogonReq)
		Int type;
		Int port;
		IP ip;
		//String<1> ip;
		void init()
		{
			loc(type);
			loc(port);
			loc(ip);
		}
		void parse()
		{
			//pop(ip);
		}
		int size()const
		{
			return type.size()
				+ port.size()
				+ ip.size();
		}
	MSG_END()

	MSG_BEGIN(ModuleLogonAck)
		Int id;
		Int type;
		Int code;
		Int central_id;
		Int vid_begin;
		Int vid_end;
		void init()
		{
			loc(id);
			loc(type);
			loc(code);
			loc(central_id);
			loc(vid_begin);
			loc(vid_end);
		}
		void parse(){}
		int size()const
		{
			return id.size()
				+ type.size()
				+ code.size()
				+ central_id.size()
				+ vid_begin.size()
				+ vid_end.size();
		}
	MSG_END()

	MSG_BEGIN(ModuleInfo)
		Int type;
		Int port;
		IP ip;
		void init()
		{
			loc(type);
			loc(port);
			loc(ip);
		}
		void parse(){ }
		int size()const
		{
			return type.size()
				+ port.size()
				+ ip.size();
		}
		MSG_END()

	struct Module_Info
	{
		int port;
		int type;
		char ip[20];
	};
	MSG_BEGIN(ModuleBroadcast)
		PTLV<Module_Info,1> info;
		void init(){ }
		void parse()
		{
			pop(info);
		
		}
		int size()const
		{
			return info.size();
		}
	MSG_END()

	MSG_BEGIN(UpdateChannelReq)
		Int uid;
		Int tid;
		Int left_id;
		Int left_type;
		Int right_id;
		Int right_type;
		void init()
		{
			loc(uid);
			loc(tid);
			loc(left_id);
			loc(left_type);
			loc(right_id);
			loc(right_type);
		}
		void parse(){ }
		int size()const
		{
			return uid.size()
				+ tid.size()
				+ left_id.size()
				+ left_type.size()
				+ right_id.size()
				+ right_type.size();
		}
	MSG_END()

	enum UpdateChannelAckStatus
	{
		create_channel_success = 0,
		create_channel_fail = 1,
	};


	MSG_BEGIN(UpdateChannelAck)
		Int uid;
		Int tid;
		Int status;
		void init()
		{
			loc(uid);
			loc(tid);
			loc(status);
		}
		void parse(){ }
		int size()const
		{
			return uid.size()
				+ tid.size()
				+ status.size();
		}
	MSG_END()

};
#endif