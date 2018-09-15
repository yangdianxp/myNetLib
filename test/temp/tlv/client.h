#ifndef __CLIENT_H__
#define __CLIENT_H__
#include "MsgProto.h"
namespace protocol
{
	MSG_BEGIN(EmotionRequest)
		Int shooter;
		Int target;
		Int type;
		void init()
		{
			loc(shooter);
			loc(target);
			loc(type);
		}
		void parse(){}
		int size()const
		{
			return shooter.size()
				+ target.size()
				+ type.size();
		}
	MSG_END()
	/*
	MSG_BEGIN(ChatBroadcast)
		Int seatid;
		String<1> msg;
		void init()
		{
			loc(seatid);
		}
		void parse()
		{
			pop(msg);
		}
		int size()const
		{
			return seatid.size()
				+ msg.size();
		}
	MSG_END()
	*/
	enum client_type
	{
		player_client = 1,
		player_transfer = 2,
	};
	MSG_BEGIN(ConnectInfo)
		Int type;
		Int port;
		Int fd;
		String<1> ip;
		void init()
		{
			loc(type);
			loc(port);
			loc(fd);
		}
		void parse()
		{
			pop(ip);
		}
		int size()const
		{
			return type.size()
				+ port.size()
				+ fd.size()
				+ ip.size();
		}
	MSG_END()

	MSG_BEGIN(notify_type)
		Int type;
		void init()
		{
			loc(type);
			
		}
		void parse(){}
		int size()const
		{
			return type.size();
		}
	MSG_END()

};
#endif