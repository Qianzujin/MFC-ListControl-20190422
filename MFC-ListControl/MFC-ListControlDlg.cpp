
// MFC-ListControlDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC-ListControl.h"
#include "MFC-ListControlDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCListControlDlg 对话框



CMFCListControlDlg::CMFCListControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCLISTCONTROL_DIALOG, pParent)
	, m_IntValue(_T(""))
	, m_StrValue(_T(""))
	, m_FloValue(_T(""))
	, m_DateValue(_T(""))

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCListControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Text(pDX, IDC_EDIT1, m_IntValue);
	DDX_Text(pDX, IDC_EDIT2, m_StrValue);
	DDX_Text(pDX, IDC_EDIT3, m_FloValue);
	DDX_Text(pDX, IDC_DATE1, m_DateValue);
	DDX_Control(pDX, IDC_HIDE, m_Hide);
}

BEGIN_MESSAGE_MAP(CMFCListControlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ADD, &CMFCListControlDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DELL, &CMFCListControlDlg::OnBnClickedDell)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CMFCListControlDlg::OnDblclkList)
	ON_EN_KILLFOCUS(IDC_HIDE, &CMFCListControlDlg::OnKillfocusHide)
	ON_BN_CLICKED(IDC_SAVE, &CMFCListControlDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_LOAD, &CMFCListControlDlg::OnBnClickedLoad)
END_MESSAGE_MAP()


// CMFCListControlDlg 消息处理程序

BOOL CMFCListControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//隐藏编辑框,配合下面的代码段,进行ListControl的修改编辑功能
	m_Hide.ShowWindow(SW_HIDE);

	//表头默认值设置代码
	m_IntValue = TEXT("1");
	m_StrValue = TEXT("100");
	m_FloValue = TEXT("100.1");
	UpdateData(FALSE);

	//ListControl列表控件绘制代码
	CRect rect;
	m_List.GetClientRect(&rect);

	// 为列表视图控件添加全行选中和栅格风格   
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_List.InsertColumn(0, _T("整型数据"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_List.InsertColumn(1, _T("字符串数据"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_List.InsertColumn(2, _T("浮点数据"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_List.InsertColumn(3, _T("时间数据"), LVCFMT_CENTER, rect.Width() / 4, 3);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCListControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCListControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCListControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//自定义表头默认值是否为空
BOOL CMFCListControlDlg::CheckNull() {
	if (m_IntValue.IsEmpty())
	{
		AfxMessageBox(TEXT("整型数据未输入！"));
		return TRUE;
	}
	if (m_StrValue.IsEmpty())
	{
		AfxMessageBox(TEXT("字符数据未输入！"));
		return TRUE;
	}
	if (m_FloValue.IsEmpty())
	{
		AfxMessageBox(TEXT("浮点数据未输入！"));
		return TRUE;
	}
}

//新增函数实现函数
void CMFCListControlDlg::OnBnClickedAdd()
{
	UpdateData(TRUE);
	if (CheckNull())
	{
		return;
	}

	//此处是将w_char类型数据保存到int型变量中
	int ListCountStart = m_List.GetItemCount();
	//将int转换成CString
	CString TempListCount;
	TempListCount.Format(_T("%d"), ListCountStart);
	//将CString转换成int
	int ListCountEnd;
	ListCountEnd = _ttoi(TempListCount);

	m_List.InsertItem(ListCountEnd, m_IntValue);
	m_List.SetItemText(ListCountEnd, 1, m_StrValue);
	m_List.SetItemText(ListCountEnd, 2, m_FloValue);
	m_List.SetItemText(ListCountEnd, 3, m_DateValue);
	/*原因可能是数据类型不被识别导致无法将参数变为识别的整数，后经测试确实是数据类型的问题*/

}

//删除按钮功能实现代码段
void CMFCListControlDlg::OnBnClickedDell()
{
	// TODO: 在此添加控件通知处理程序代码

	CRect rect;
	m_List.GetClientRect(&rect);

	if (AfxMessageBox(TEXT("确定要删除此条内容吗?"), MB_OKCANCEL) == IDOK)
	{
		int iItem;
		for (iItem = m_List.GetItemCount() - 1; iItem >= 0; iItem--)
		{
			//AfxMessageBox(m_List.GetItemText(1, 1));

			if (m_List.GetItemState(iItem, LVIS_SELECTED) == LVIS_SELECTED)
				m_List.DeleteItem(iItem);
		}
	}
		
	

}



/*
Listcontrol编辑代码
该程序段及下一程序段负责ListControl控件的编辑部分，参考下面链接进行编辑
https://blog.csdn.net/weixin_41485242/article/details/80601588
https://blog.csdn.net/xianglifighter/article/details/17592209#commentBox
*/
void CMFCListControlDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CRect rc;
	CString strTemp;
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	m_Row = pNMListView->iItem;
	m_Col = pNMListView->iSubItem;

	if (pNMListView->iItem == -1)	//选择空白处，添加一行，并设置焦点为最后一行，第二列
	{
		m_Row = m_List.GetItemCount();//得到ListControl的行数
		strTemp.Format(_T("%d"), m_Row + 1);
		//m_List.InsertItem(m_Row, strTemp); //此句意义不明
		m_List.SetItemState(m_Row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_List.EnsureVisible(m_Row, FALSE);
		//m_Col = 1;
	}

	if (m_Col != 0 & m_Col != 3)	// 该判断不等于的列数值为不可修改的列数
	{
		m_List.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);
		m_Hide.SetParent(&m_List);
		m_Hide.MoveWindow(rc);
		//m_Hide.SetWindowTextW(m_List.GetItemText(m_Row, m_Col));
		m_Hide.ShowWindow(SW_SHOW);
		m_Hide.SetFocus();//设置Edit焦点
		m_Hide.ShowCaret();//显示光标
		m_Hide.SetSel(0, -1);//全选
	}

	*pResult = 0;

}

/*
该程序段及上一程序段负责ListControl控件的编辑部分，参考下面链接进行编辑
https://blog.csdn.net/weixin_41485242/article/details/80601588
https://blog.csdn.net/xianglifighter/article/details/17592209#commentBox
*/

void CMFCListControlDlg::OnKillfocusHide()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str;
	//m_Hide.GetWindowTextW(str);
	m_List.SetItemText(m_Row, m_Col, str);
	m_Hide.ShowWindow(SW_HIDE);

}


void CMFCListControlDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
	// 处理数据
	//如果要保存文件首先要打开一个文件对象

	CFile file;
	if (!file.Open(TEXT(".\\test.txt"), CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox(TEXT("保存文件失败"));
		return;
	}
	else
	{
		SInfo info;
		CListCtrl *pList = (CListCtrl*)GetDlgItem(IDC_LIST);
		int i = 0, nCount = pList->GetItemCount();
		while (i < nCount)
		{
			/*
			此处的结构体info，如果没有进行初始化内存操作，会造成文件中存储的信息出现烫，要进行初始化内存的操作为赋值_T("");
			另外没有被分配字节的空间会被空格代替
			*/
			_tcscpy(info.nInt, pList->GetItemText(i, 0));
			_tcscpy(info.sStr, pList->GetItemText(i, 1));
			_tcscpy(info.fFlo, pList->GetItemText(i, 2));
			_tcscpy(info.tTime, pList->GetItemText(i, 3));
			//info.nInt = pList->GetItemText(i, 0);			
			//info.Sstr = pList->GetItemText(i, 1);
			//info.fFlo = pList->GetItemText(i, 2);
			//info.tTime= pList->GetItemText(i, 3);
			//_tcscpy(info.nInt, pList->GetItemText(i, 0));
			file.Write(&info, sizeof(info));
			++i;
		 }
		AfxMessageBox(TEXT("数据保存成功"));
		file.Close();
	}

}



void CMFCListControlDlg::OnBnClickedLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	//AfxMessageBox(_TEXT("hello"));
	CFile file;
	if (!file.Open(TEXT(".\\test.txt"), CFile::modeRead))
	{
		AfxMessageBox(TEXT("打开文件失败！"));
		return;
	}
	CListCtrl *pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	int i = 0;
	CString str;
	SInfo info;
	pList->DeleteAllItems();//在进行加载数据之前，对ListCtrl中所有数据进行清空操作；
	while (file.Read(&info,sizeof(info)) == sizeof(info))
	{
		
		pList->InsertItem(i, info.nInt);
		//MessageBox(info.nInt);
		pList->SetItemText(i, 1, info.sStr);
		pList->SetItemText(i, 2, info.fFlo);
		pList->SetItemText(i, 3, info.tTime);
		++i;
	}
	file.Close();


}
