#pragma once

/**
*    @defgroup ���Կ�ܳ���
*    @brief    ���Կ�ܳ��򣬰����������ݣ�����������󣬲��Ի��࣬���԰����ȡ�
*	 @author  ������
*    @date    2012-06-14
*
* @par �޶���ʷ
*    @version v0.5 \n
*	 @author  ������
*    @date    2012-06-24
*    @li ��ʼ�汾
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
* @brief ������Ϣ���󣬱��������Ϣ�����Խ����
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
	int		level;		/**< ������������ */
	std::string	name;		/**< ���Խӿ����� */
	std::string	subName;	/**< ���Խӿ����ƾ������� */
	bool	isOK;		/**< ���Խ�� */
	bool	isWantException;	/**< �Ƿ������쳣���� */
	std::string	exception;	/**< �쳣��Ϣ */
	std::string remark;		/**< ��ע��Ϣ */
	bool is_unsport;		/**< �Ľӿ��Ƿ���ʱ��֧�� */
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
				info.exception = "���쳣������û���쳣������Ϣ";

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

/**//** @}*/ // ���Կ��