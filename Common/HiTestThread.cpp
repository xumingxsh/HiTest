#include "HiTestThread.h"

using namespace std;

HiTestThread::HiTestThread(const ThreadFunc& fun): fun_(fun), is_stoped_(false), handle_(NULL)
{

}

HiTestThread::~HiTestThread()
{
	if (handle_ != NULL)
	{
		CloseHandle(handle_);
		handle_ = NULL;
	}
}

void HiTestThread::on_run()
{
	try
	{
		is_stoped_ = false;
		fun_();
	}
	catch (...)
	{
		
	}
	if (!handle_)
	{
		return;
	}

	CloseHandle(handle_);

	handle_ = NULL;
}

static DWORD WINAPI RunProc(LPVOID param)
{
	HiTestThread* thread = static_cast<HiTestThread*>(param);
	thread->on_run();
	return 0;
}

bool HiTestThread::isNeedExit()
{
	return is_stoped_;
}

void HiTestThread::join()
{
	if (!handle_)
	{
		return;
	}
	is_stoped_ = true;
	while (handle_ != NULL)
	{
		Sleep(10);
	}

	//CloseHandle(handle_);

	//handle_ = NULL;
}

bool HiTestThread::start()
{
	if (handle_)
	{
		return false;
	}
	handle_ = ::CreateThread(NULL, 0,  ::RunProc, this, 0, 0);
	return true;
}