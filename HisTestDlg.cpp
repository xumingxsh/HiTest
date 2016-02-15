// HisTestDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CHisTestDlg 对话框



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
	ON_NOTIFY( NM_CUSTOMDRAW, IDC_LST_RESULT, OnDrawColorForMyList) //为改变颜色添加的消息
END_MESSAGE_MAP()


// CHisTestDlg 消息处理程序

BOOL CHisTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

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
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHisTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CHisTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CHisTestDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

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
		int    nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec);//获得子项

		if( nItem%2 ==0 )//设置背景色
		{
			clrNewBkColor = RGB( 240, 240, 240 ); //偶数行背景色为灰色

			//clrNewTextColor = RGB( 255, 0, 0 );
		}
		else
		{
			clrNewBkColor = RGB( 255, 255, 255 ); //奇数行背景色为白色

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
