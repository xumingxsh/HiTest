#pragma once

/**
*    @defgroup 测试框架程序
*    @brief    测试框架程序，包括测试数据，测试命令对象，测试基类，测试案例等。
*	 @author  徐敏荣
*    @date    2012-06-14
*
* @par 修订历史
*    @version v0.5 \n
*	 @author  徐敏荣
*    @date    2012-06-24
*    @li 初始版本
* @{
*/ 


#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <functional> 
#include <algorithm> 
#include <stdarg.h>

#pragma warning (disable: 4996)


#if !defined(HITEST_ON_VARLIST)
#define HITEST_ON_VARLIST(x, y) \
	char chArr[2048] = {0};\
	char* pchar = &chArr[0];\
	va_list pArgList;\
	va_start(pArgList, y);\
	::_vsnprintf(chArr, 2047, x, pArgList);	\
	va_end(pArgList) ;
#endif

/**
* @brief 测试信息对象，保存测试信息及测试结果。
*
*/
class TestInfo
{
public:
	TestInfo()
	{
		level = 1;
		name = "";
		subName = "";
		isOK = false;
		isWantException = false;
		exception = "";
		remark = "";
		is_unsport = false;
	}

	void append_remark(const char* fmt, ...)
	{
		HITEST_ON_VARLIST(fmt, fmt);
		remark += chArr;
	}
public:
	int		level;		/**< 测试用例级别 */
	std::string	name;		/**< 测试接口名称 */
	std::string	subName;	/**< 测试接口名称具体描述 */
	bool	isOK;		/**< 测试结果 */
	bool	isWantException;	/**< 是否期望异常发生 */
	std::string	exception;	/**< 异常信息 */
	std::string remark;		/**< 备注信息 */
	bool is_unsport;		/**< 改接口是否暂时不支持 */
};

class TestBaseEX
{
public:
	typedef std::function<bool(TestInfo&)> TestFun;

	typedef std::vector<TestFun> TestList;
	typedef TestList::iterator TestItor; 

	void OnTest(std::function<void(TestInfo&)> testShow)
	{
		for (TestItor it = m_Tests.begin(); it != m_Tests.end();
			++it)
		{
			TestInfo info;			
			try
			{
				bool result = (*it)(info);
				if (info.isWantException)
				{
					info.isOK = false;
				}
				else
				{
					info.isOK = result;
				}
			}
			catch (...)
			{
				info.exception = "有异常，但是没有异常描述信息";

				if (info.isWantException)
				{
					info.isOK = true;
				}
			}

			CoutInfo(info);
			testShow(info);
		}
	}
	
private:
	void CoutInfo(TestInfo& info)
	{
		std::cout<<"\n"<<std::endl;
		std::cout<<"test name:"<<info.name<<std::endl;
		std::cout<<"\tsub name:"<<info.subName<<std::endl;
		std::cout<<"\tis want exception:"<<(info.isWantException?"yes":"no")<<std::endl;
		std::cout<<"\tremark:"<<info.remark<<std::endl;
		std::cout<<"\texecute result:"<<info.isOK<<std::endl;
		std::cout<<"\texception:"<<info.exception<<std::endl;
		if (info.is_unsport)
		{
			std::cout<<"\tthis function is not supprt,you can neglect this test result"<<std::endl;
		}
		std::cout<<"\n"<<std::endl;
	}
public:
	std::vector<TestFun> m_Tests;
};


#define TEST_INIT(info, sub) {\
	ostringstream oss;\
	oss<<"position:"<<__FILE__<<"-"<<__LINE__<<"-"<<__FUNCTION__<<endl;\
	info.name = __FUNCTION__;/*oss.str();*/\
}\
	info.subName = sub;\
	info.remark = "";\
	info.isOK = true;

#define TESTFUN_INIT(name) m_Tests.push_back(std::bind(&name, this, std::tr1::placeholders::_1))\

/**//** @}*/ // 测试框架