// HisTest.cpp : ����Ӧ�ó��������Ϊ��
//

//#include "stdafx.h"
#include "HisTest.h"
#include "HisTestDlg.h"

#include <io.h>
#include <fstream>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHisTestApp

BEGIN_MESSAGE_MAP(CHisTestApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CHisTestApp ����

CHisTestApp::CHisTestApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CHisTestApp ����

CHisTestApp theApp;


// CHisTestApp ��ʼ��

BOOL CHisTestApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//_CrtSetBreakAlloc(31052);
	//_CrtSetBreakAlloc(8798);
	//_CrtSetBreakAlloc(58673);
	AllocConsole( ); 
	// setup stdout
	{
		int fd = _open_osfhandle( (long)GetStdHandle( /*STD_OUTPUT_HANDLE*/STD_ERROR_HANDLE ), 0);
		FILE* fp = _fdopen( fd, "w" );
		        //FILE* fp = fopen( "log.txt", "w" );

		*stdout = *fp;
		setvbuf( /*stdout*/stderr, NULL, _IONBF, 0 );
	}
	/*
	std::ofstream ferr("error.txt");
	std::cerr.rdbuf(ferr.rdbuf());


	std::ofstream fout("out.txt");
	std::cout.rdbuf(fout.rdbuf());


	std::ofstream flog("log.txt");
	std::clog.rdbuf(flog.rdbuf()); */

	CHisTestDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

