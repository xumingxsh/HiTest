#pragma once

#include <afxwin.h>         // MFC 核心和标准组件

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