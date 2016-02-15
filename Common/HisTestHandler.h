#pragma once
#include <functional>
#include <map>
#include <string>

class TestInfo;

class HisTestHandler
{
public:
	typedef std::function<void(std::function<void(TestInfo&)>&)> TestObject;
public:
	HisTestHandler();
	void Run(std::string key, std::function<void(TestInfo&)>& fun);
public:
	std::map<std::string,  TestObject> list;


	template<typename T>
	static void OnTest_i(std::function<void(TestInfo&)>& fun)
	{
		T t;
		t.OnTest(fun);
	}
};
