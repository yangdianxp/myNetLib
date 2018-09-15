#ifndef __VOICE_H__
#define __VOICE_H__
#include "MsgProto.h"
namespace protocol{

	MSG_BEGIN(VoiceData)
		Int uid;
		Int tid;
		Int time_flag;
		Int frame_cnt;
		String<1> data;
		void init()
		{
			loc(uid);
			loc(tid);
			loc(time_flag);
			loc(frame_cnt);
		}
		void parse()
		{
			pop(data);
		}
		int size()const
		{
			return uid.size()
				+ tid.size()
				+ time_flag.size()
				+ frame_cnt.size()
				+ data.size();
		}
	MSG_END()

	MSG_BEGIN(DownlineVoice2Central)
		Int mid;
		void init()
		{
			loc(mid);
		}
		void parse(){}
		int size()const
		{
			return mid.size();
		}
	MSG_END()


	MSG_BEGIN(DownlineVoice2CentralAck)
		Int mid;
		void init()
		{
			loc(mid);
		}
		void parse(){}
		int size()const
		{
			return mid.size();
		}
	MSG_END()

	MSG_BEGIN(VoiceDynRecvPackage)
		Int uid;
		Int tid;
		Int recv_package_prob;
		void init()
		{
			loc(uid);
			loc(tid);
			loc(recv_package_prob);
		}
		void parse(){}
		int size()const
		{
			return uid.size()
				+ tid.size()
				+ recv_package_prob.size();
		}
	MSG_END()
};
#endif