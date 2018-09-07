// log_test.cpp : 定义控制台应用程序的入口点。
//
#include <windows.h>

#include "SLog.h"
#include <boost/timer.hpp>

void test2()
{
	BOOST_SLOG(slog_notice) << "A normal severity message, test2";
}

void test1()
{
	BOOST_SLOG(slog_notice) << "A normal severity message, test1";
	test2();
}

void test1(int)
{
	BOOST_SLOG(slog_notice) << "A normal severity message, test1 int";
}

int main(int argc, char* argv[])
{
	SLog::InitLog("testapp");

	//SLog::SetLevel(slog_notice);

	SLOG_ALERT << "A normal severity message, will not pass to the file";

	SLOG_WARNING << "A warning severity message, will pass to the file";

	SLOG_NOTICE << "An error severity message, will pass to the file";

	//printf("start:\n");
	test1();
	test1(0);
	//SLog::SetLevel(slog_emergency);
	int _count = 10000;
	boost::timer tt;
	for (int i = 0; i < _count; i++)
	{
		SLOG_INFO << "An slog_warning severity message, count:" << i;
		Sleep(1000);
	}
	printf("count:%d time:%lf(s)\n", _count, tt.elapsed());

	getchar();
	return 0;
}