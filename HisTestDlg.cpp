// HisTestDlg.cpp : ʵ���ļ�
//

//#include "stdafx.h"
#include "HisTest.h"
#include "HisTestDlg.h"
#include ".\histestdlg.h"

#include "Common\histesthandler.h"
#include "string/hiString.h"

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static HisTestHandler handler;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CHisTestDlg �Ի���



CHisTestDlg::CHisTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHisTestDlg::IDD, pParent)
	, m_SelVal(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHisTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_RESULT, m_lstResult);
	DDX_Control(pDX, IDC_CMB_TEST, cmbTestList);
	DDX_CBString(pDX, IDC_CMB_TEST, m_SelVal);
}

BEGIN_MESSAGE_MAP(CHisTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_NOTIFY( NM_CUSTOMDRAW, IDC_LST_RESULT, OnDrawColorForMyList) //Ϊ�ı���ɫ��ӵ���Ϣ
END_MESSAGE_MAP()


// CHisTestDlg ��Ϣ�������

BOOL CHisTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��\������...\���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	this->m_lstResult.SetExtendedStyle(
		this->m_lstResult.GetExtendedStyle()
		|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	this->m_lstResult.InsertColumn(0, _T("result"), 0, 50);
	this->m_lstResult.InsertColumn(1, _T("function"), 0, 100);
	this->m_lstResult.InsertColumn(2, _T("script"), 0, 150);
	this->m_lstResult.InsertColumn(3, _T("exception"), 0, 200);
	this->m_lstResult.InsertColumn(4, _T("remark"), 0, 300);

	cmbTestList.AddString(_T("All"));
	for (auto it = handler.list.begin(); it != handler.list.end(); ++it)
	{
		cmbTestList.AddString(Hi::u82uc(it->first.c_str()).c_str());
	}

	cmbTestList.SetCurSel(1);

	this->UpdateData(false);
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

void CHisTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CHisTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CHisTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHisTestDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//HisDBTest test;
	this->UpdateData();
	this->m_lstResult.DeleteAllItems();

	using namespace std::tr1::placeholders;
	std::function<void(TestInfo&)> fun = std::bind(&CHisTestDlg::OnTestResult, this, _1);
	//cmbTestList.getGetCurSel()
	handler.Run(Hi::uc2u8((LPCTSTR)m_SelVal), fun);
	
	//std::function<void(TestInfo&)> fun =std::bind( &CHisTestDlg::OnTestResult), this);
	/*using namespace std::tr1::placeholders;
	HisStrTest test;
	test.OnTest(std::bind(&CHisTestDlg::OnTestResult, this, _1));*/
	/*handler.GetTest()->OnTest();
	this->m_lstResult.DeleteAllItems();
	handler.GetTest()->ForEachInfo(*this, &CHisTestDlg::OnTestResult);*/

	int count = this->m_lstResult.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < count; i++)
	{
		this->m_lstResult.SendMessage(LVM_SETCOLUMNWIDTH,
			i, MAKELPARAM(LVSCW_AUTOSIZE_USEHEADER, 0));
	}
}

void CHisTestDlg::OnTestResult(TestInfo& info)
{
	int count = this->m_lstResult.GetItemCount();

	LV_ITEM curItem;
	curItem.mask = LVIF_TEXT | LVIF_STATE;
	curItem.state = 0;
	curItem.stateMask = 0;

	curItem.iItem = count;
	curItem.iSubItem = 0;
	const TCHAR* result = _T("OK");
	if (!info.isOK)
	{
		result = _T("NO");
	}
	if (info.is_unsport)
	{
		result = _T("HL");
	}
	curItem.pszText = (LPWSTR)result;
	this->m_lstResult.InsertItem(&curItem);
	this->m_lstResult.SetItemText(count, 1, (LPWSTR)Hi::u82uc(info.name.c_str()).c_str());
	this->m_lstResult.SetItemText(count, 2, (LPWSTR)Hi::u82uc(info.subName.c_str()).c_str());
	this->m_lstResult.SetItemText(count, 3, (LPWSTR)Hi::u82uc(info.exception.c_str()).c_str());
	this->m_lstResult.SetItemText(count, 4, (LPWSTR)Hi::u82uc(info.remark.c_str()).c_str());
}

void CHisTestDlg::OnDrawColorForMyList(NMHDR *pNmHdr, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNmHdr);

	*pResult = CDRF_DODEFAULT;

	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	} 
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		//COLORREF clrNewTextColor, clrNewBkColor;   
		COLORREF clrNewBkColor;  
		int    nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec);//�������

		if( nItem%2 ==0 )//���ñ���ɫ
		{
			clrNewBkColor = RGB( 240, 240, 240 ); //ż���б���ɫΪ��ɫ

			//clrNewTextColor = RGB( 255, 0, 0 );
		}
		else
		{
			clrNewBkColor = RGB( 255, 255, 255 ); //�����б���ɫΪ��ɫ

			//clrNewTextColor = RGB( 0, 0, 0 );
		}

		CString txt = this->m_lstResult.GetItemText(nItem, 0);

		if (txt == "NO")
		{
			clrNewBkColor = RGB( 255, 0, 0 );
		}

		if (txt == "HL")
		{
			clrNewBkColor = RGB( 255, 255, 0 );
		}

		//pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;

		*pResult = CDRF_DODEFAULT;
	}
}
