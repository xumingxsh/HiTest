// HisTestDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "resource.h"		// ������
#include "Common\HisTest.h"
#include "afxwin.h"


// CHisTestDlg �Ի���
class CHisTestDlg : public CDialog
{
// ����
public:
	CHisTestDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HISTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDrawColorForMyList(NMHDR *pNmHdr, LRESULT *pResult);

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_lstResult;
	afx_msg void OnBnClickedOk();
public:
	void OnTestResult(TestInfo&);
	CComboBox cmbTestList;
	CString m_SelVal;
};
