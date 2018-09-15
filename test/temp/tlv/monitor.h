#ifndef __MONITOR_H__
#define __MONITOR_H__
#include "MsgProto.h"
namespace protocol{

	MSG_BEGIN(logReq)
		Int cmd;
		void init()
		{
			loc(cmd);
		}
		void parse(){}
		int size()const
		{
			return cmd.size();
		}
		MSG_END()

	


	// MSG_BEGIN(users_routes)
	// 	Int mid;
	// 	Int uid;
	// 	Int type;
	// 	Int fd;
	// 	void init()
	// 	{
	// 		loc(mid);
	// 		loc(uid);
	// 		loc(type);
	// 		loc(fd);
	// 	}
	// 	void parse(){}
	// 	int size()const
	// 	{
	// 		return mid.size()
	// 			+ uid.size()
	// 			+ type.size()
	// 			+ fd.size();
	// 	}
	// MSG_END()

	// MSG_BEGIN(modules_routes)
	// 	Int mid;
	// 	Int vid;
	// 	Int type;
	// 	Int fd;
	// 	void init()
	// 	{
	// 		loc(mid);
	// 		loc(vid);
	// 		loc(type);
	// 		loc(fd);
	// 	}
	// 	void parse(){}
	// 	int size()const
	// 	{
	// 		return mid.size()
	// 			+ vid.size()
	// 			+ type.size()
	// 			+ fd.size();
	// 	}
	// MSG_END()

	// MSG_BEGIN(tables_routes)
	// 	Int mid;
	// 	Int tid;
	// 	Int uid;
	// 	void init()
	// 	{
	// 		loc(mid);
	// 		loc(tid);
	// 		loc(uid);
	// 	}
	// 	void parse(){}
	// 	int size()const
	// 	{
	// 		return mid.size()
	// 			+ tid.size()
	// 			+ uid.size();
	// 	}
	// MSG_END()

	MSG_BEGIN(module_info)
		Int port;
		IP ip;
		void init()
		{
			loc(port);
			loc(ip);
		}
		void parse(){}
		int size()const
		{
			return port.size()
				+ ip.size();
		}
	MSG_END()


	struct balance_ref
	{
		int mid;
		int ref;
	};
	struct balance_sort
	{
		int type;
		int ref;
		int mid;
	};
	


	MSG_BEGIN(balance_info)
		PTLV<balance_ref,1> m_ref;
		PTLV<balance_sort,2> m_sort;
		void init(){}
		void parse()
		{
			pop(m_ref);
			pop(m_sort);
		}
		int size()const
		{
			return m_ref.size()
				+ m_sort.size();
		}
	MSG_END()
	struct users_routes
	{
		int mid;
		int uid;
		int type;
		int fd;
	};
	struct modules_routes
	{
		int mid;
		int vid;
		int type;
		int fd;
	};
	struct tables_routes
	{
		int mid;
		int tid;
		int uid;
	};
	
	MSG_BEGIN(logAck)
		PTLV<users_routes,1> users;
		PTLV<modules_routes,2> modules;
		PTLV<tables_routes,3> tables;
		PTLV<balance_ref,4> m_ref;
		PTLV<balance_sort,5> m_sort;

		void init(){}
		void parse()
		{
			pop(users);
			pop(modules);
			pop(tables);
			pop(m_ref);
			pop(m_sort);
		}
		int size()const
		{
			return users.size()
				+ modules.size()
				+ tables.size()
				+ m_ref.size()
				+ m_sort.size();
		}
	MSG_END()
};
#endif