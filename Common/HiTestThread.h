#pragma once

#include <afxwin.h>         // MFC ���ĺͱ�׼���

#include <functional>

class HiTestThread
{
public:
	typedef std::function<void()> ThreadFunc;
public:
	explicit HiTestThread(const ThreadFunc& fun);
	~HiTestThread();
public:
	bool start();
	void join();
	bool isNeedExit();
public:
	void on_run();
private:
	ThreadFunc fun_;
	HANDLE handle_;
	bool is_stoped_;
};