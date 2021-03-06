// test_lamda.cpp: 定义控制台应用程序的入口点。
//
#include <windows.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unordered_map>
#include "MsgProto.h"
#include "MsgValue.h"
#include "Aristotle.h"

using namespace protocol;

MSG_BEGIN(LoginReq)
	Int uid;
	Int tid;
	String<1> password;
	String<2> token;
	void init()
	{
		loc(uid);
		loc(tid);
	}
	void parse()
	{
		analysis();
		pop(password);
		pop(token);
	}
	int size()const
	{
		return uid.size()
			+ tid.size()
			+ password.size()
			+ token.size();
	}	
MSG_END()


int test()
{	
	char buffer[100] = { 0 };
	LoginReq q(buffer, sizeof(buffer));		

	q.uid = 100;	
	q.tid = 200;
	TLV_BEGIN(q, token);
	q.token.push_back("hello", 6);
	//q.tlv_end();
	TLV_END(q);
	TLV_BEGIN(q, password);
	q.password.push_back("hello", 6);
	q.password.push_back("hello", 6);
	TLV_END(q);

	LoginReq  req(buffer, q.size());
	req.parse();
	

//	req.uid = 100;
		
    return 0;
}
inline size_t calc_hash(const int * _First, const int * const _Last, size_t _Val)
{	
	static const size_t _FNV_prime = 16777619U;
	for (; _First != _Last; ++_First)
	{
		_Val ^= static_cast<size_t>(*_First);
		_Val *= _FNV_prime;
	}
	return (_Val);
}
inline size_t calc_hash(const int * _First,const int * const _Last)
{	
	static const size_t _Val = 2166136261U;
	return calc_hash(_First, _Last, _Val);
}

int main()
{
		
	test();
	system("pause");
	return 0;
}
