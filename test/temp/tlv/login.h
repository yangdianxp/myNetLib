#ifndef __LOGIN_H__
#define __LOGIN_H__
#include "MsgProto.h"
//using namespace protocol;
namespace protocol{

	MSG_BEGIN(LoginRequest)
		Int uid;
		String<1> password;
		String<2> token;
		String<3> deviceid;
		void init()
		{
			loc(uid);
		}
		void parse()
		{
			pop(password);
			pop(token);
			pop(deviceid);
		}
		int size()const
		{
			return uid.size()
				+ password.size()
				+ token.size()
				+ deviceid.size();
		}
	MSG_END()

		//��¼����������LoginAck statusö��
	enum LoginAckStatus
	{
		login_success = 0,
		login_fail = 1,
	};

	MSG_BEGIN(LoginAck)
		Int uid;
		Int status;
		Int code;
		Int vid;
		String<1> token;
		void init()
		{
			loc(uid);
			loc(status);
			loc(code);
			loc(vid);
		}
		void parse()
		{
			pop(token);
		}
		int size()const
		{
			return uid.size()
				+ status.size()
				+ code.size()
				+ vid.size()
				+ token.size();
		}
	MSG_END()

	MSG_BEGIN(LoginNotice)
		String<1> uid;
		void init(){}
		void parse()
		{
			pop(uid);
		}
		int size()const
		{
			return uid.size();
		}
	MSG_END()

	MSG_BEGIN(DownlineNotice)
		Int uid;
		void init()
		{
			loc(uid);
		}
		void parse(){}
		int size()const
		{
			return uid.size();
		}
	MSG_END()

	MSG_BEGIN(LogoutReq)
		Int vid;
		Int uid;
		String<1> skey;
		void init()
		{
			loc(vid);
			loc(uid);
		}
		void parse()
		{
			pop(skey);
		}
		int size()const
		{
			return vid.size()
				+ uid.size()
				+ skey.size();
		}
	MSG_END()

	enum LogoutAckStatus
	{
		logout_success = 0,
		logout_fail = 1,
	};

	MSG_BEGIN(LogoutAck)
		Int vid;
		Int uid;
		Int status;
		Int code;
		void init()
		{
			loc(vid);
			loc(uid);
			loc(status);
			loc(code);
		}
		void parse(){}
		int size()const
		{
			return vid.size()
				+ uid.size()
				+ status.size()
				+ code.size();
		}
	MSG_END()

	MSG_BEGIN(ClientDisconnect)
		Int uid;
		Int vid;
		void init()
		{
			loc(uid);
			loc(vid);
		}
		void parse(){}
		int size()const
		{
			return uid.size()
				+ vid.size();
		}
	MSG_END()

	MSG_BEGIN(ClientDisconnectAck)
		Int uid;
		Int vid;
		void init()
		{
			loc(uid);
			loc(vid);
		}
		void parse(){}
		int size()const
		{
			return uid.size()
				+ vid.size();
		}
	MSG_END()

	MSG_BEGIN(ClientLogout)
		Int vid;
		Int uid;
		String<1> skey;
		void init()
		{
			loc(vid);
			loc(uid);
		}
		void parse()
		{
			pop(skey);
		}
		int size()const
		{
			return vid.size()
				+ uid.size()
				+ skey.size();
		}
	MSG_END()

	MSG_BEGIN(ClientLogoutAck)
		Int uid;
		Int vid;
		void init()
		{
			loc(uid);
			loc(vid);
		}
		void parse(){}
		int size()const
		{
			return uid.size()
				+ vid.size();
		}
	MSG_END()

	

	MSG_BEGIN(HeartBeat)
		Int state;
		Int localtime;
		void init()
		{
			loc(state);
			loc(localtime);
		}
		void parse(){}
		int size()const
		{
			return state.size()
				+ localtime.size();
		}
	MSG_END()

		
		/*
		MSG_BEGIN(UserInfo)
		Int uid;
	Int seatid;
	Int coin;
	Int gold;
	Int rmb;
	Int exp;
	Int sex;
	Int vip;
	Int level;
	String<1> avatar;
	String<2> name;
	void init()
	{
		loc(uid);
		loc(seatid);
		loc(coin);
		loc(gold);
		loc(rmb);
		loc(exp);
		loc(sex);
		loc(vip);
		loc(level);

	}
	void parse()
	{
		pop(avatar);
		pop(name);
	}
	int size()const
	{
		return uid.size()
			+ seatid.size()
			+ coin.size()
			+ gold.size()
			+ rmb.size()
			+ exp.size()
			+ sex.size()
			+ vip.size()
			+ level.size()
			+ avatar.size()
			+ name.size();
	}
	MSG_END()
	*/

};
#endif