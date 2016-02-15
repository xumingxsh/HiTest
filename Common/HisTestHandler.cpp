//#include "StdAfx.h"
#include "..\Common\HisTest.h"
#include ".\histesthandler.h"
#include "..\HisTestDlg.h"

using namespace std;
/*
template<typename T>
static void OnTest_i(function<void(TestInfo&)>& fun)
{
	T t;
	t.OnTest(fun);
}*/

extern void add_test_fun(std::map<std::string,  HisTestHandler::TestObject>& lst);

HisTestHandler::HisTestHandler()
{
	add_test_fun(list);
}

void  HisTestHandler::Run(std::string key, function<void(TestInfo&)>& fun)
{
	if (key == "All")
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			it->second(fun);
		}
		return;
	}
	auto it = list.find(key);
	if (it != list.end())
	{
		it->second(fun);
	}
}
