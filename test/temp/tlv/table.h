#ifndef __TABLE_H__
#define __TABLE_H__
#include "MsgProto.h"
namespace protocol{
	enum TableErrorCode
	{
		// ����/ɾ��  ���Ӵ�����
		error_no_login = 101,   // �������� ��δ��¼
		error_table_exist = 102,     // uid =1001 , tid =1001 �Ѿ����ڣ�   uid =1001 �������������� 
		error_user_is_already_in_table = 103,   // uid=1001 , tid=1001 ,�ڷ����С���  uid=1001 Ҫ���� tid=1002 �����ӡ�	
		error_not_in_table = 104,    // ������������ 
		error_table_no_exist = 105,  // ���Ӳ����� ��
		error_voice_downline = 106,	  // voice��������
	};

	//��������
	MSG_BEGIN(CreateTableReq)
		Int uid;	// �������ӵ�������û�id 
		Int tid;	// ����������id  client ��������
		Int type;
		void init()
		{
			loc(uid);
			loc(tid);
			loc(type);
		}
		void parse(){}
		int size()const
		{
			return uid.size()
				+ tid.size()
				+ type.size();
		}
	MSG_END()

	MSG_BEGIN(CreateTableAck)
		Int uid;	
		Int tid;	
		Int result;// �������� ���
		Int errorcode;//  ʧ��code ���� 101δ��¼     102�������Ѿ�����   103���Ѿ���������
		void init()
		{
			loc(uid);
			loc(tid);
			loc(result);
			loc(errorcode);
		}
		void parse(){}
		int size()const
		{
			return uid.size()
				+ tid.size()
				+ result.size()
				+ errorcode.size();
		}
	MSG_END()

	MSG_BEGIN(DeleteTableReq)
		Int uid;	
		Int tid;	
		Int type;
		void init()
		{
			loc(uid);
			loc(tid);
			loc(type);
		}
		void parse(){}
		int size()const
		{
			return uid.size()
				+ tid.size()
				+ type.size();
		}
	MSG_END()

	MSG_BEGIN(DeleteTableAck)
		Int uid;
		Int tid;
		Int result;
		Int errorcode;
		void init()
		{
			loc(uid);
			loc(tid);
			loc(result);
			loc(errorcode);
		}
		void parse(){}
		int size()const
		{
			return uid.size()
				+ tid.size()
				+ result.size()
				+ errorcode.size();
		}
	MSG_END()

	MSG_BEGIN(DeleteTableVoiceToCentral)
		Int tid;
		void init()
		{
			loc(tid);
		}
		void parse(){}
		int size()const
		{
			return tid.size();
		}
	MSG_END()
		
};
#endif