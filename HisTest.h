// HisTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	//#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif


#include <afxwin.h>         // MFC ���ĺͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����

#include <afxdtctl.h>		// Internet Explorer 4 �����ؼ��� MFC ֧��

#include "resource.h"		// ������


// CHisTestApp:
// �йش����ʵ�֣������ HisTest.cpp
//

class CHisTestApp : public CWinApp
{
public:
	CHisTestApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHisTestApp theApp;
