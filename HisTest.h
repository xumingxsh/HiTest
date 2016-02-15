// HisTest.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	//#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif


#include <afxwin.h>         // MFC 核心和标准组件
#include <afxext.h>         // MFC 扩展
#include <afxdisp.h>        // MFC 自动化类

#include <afxdtctl.h>		// Internet Explorer 4 公共控件的 MFC 支持

#include "resource.h"		// 主符号


// CHisTestApp:
// 有关此类的实现，请参阅 HisTest.cpp
//

class CHisTestApp : public CWinApp
{
public:
	CHisTestApp();

// 重写
	public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CHisTestApp theApp;
