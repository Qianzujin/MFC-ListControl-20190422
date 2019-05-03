
// MFC-ListControlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC-ListControl.h"
#include "MFC-ListControlDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCListControlDlg �Ի���



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


// CMFCListControlDlg ��Ϣ�������

BOOL CMFCListControlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//���ر༭��,�������Ĵ����,����ListControl���޸ı༭����
	m_Hide.ShowWindow(SW_HIDE);

	//��ͷĬ��ֵ���ô���
	m_IntValue = TEXT("1");
	m_StrValue = TEXT("100");
	m_FloValue = TEXT("100.1");
	UpdateData(FALSE);

	//ListControl�б�ؼ����ƴ���
	CRect rect;
	m_List.GetClientRect(&rect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_List.InsertColumn(0, _T("��������"), LVCFMT_CENTER, rect.Width() / 4, 0);
	m_List.InsertColumn(1, _T("�ַ�������"), LVCFMT_CENTER, rect.Width() / 4, 1);
	m_List.InsertColumn(2, _T("��������"), LVCFMT_CENTER, rect.Width() / 4, 2);
	m_List.InsertColumn(3, _T("ʱ������"), LVCFMT_CENTER, rect.Width() / 4, 3);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCListControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCListControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�Զ����ͷĬ��ֵ�Ƿ�Ϊ��
BOOL CMFCListControlDlg::CheckNull() {
	if (m_IntValue.IsEmpty())
	{
		AfxMessageBox(TEXT("��������δ���룡"));
		return TRUE;
	}
	if (m_StrValue.IsEmpty())
	{
		AfxMessageBox(TEXT("�ַ�����δ���룡"));
		return TRUE;
	}
	if (m_FloValue.IsEmpty())
	{
		AfxMessageBox(TEXT("��������δ���룡"));
		return TRUE;
	}
}

//��������ʵ�ֺ���
void CMFCListControlDlg::OnBnClickedAdd()
{
	UpdateData(TRUE);
	if (CheckNull())
	{
		return;
	}

	//�˴��ǽ�w_char�������ݱ��浽int�ͱ�����
	int ListCountStart = m_List.GetItemCount();
	//��intת����CString
	CString TempListCount;
	TempListCount.Format(_T("%d"), ListCountStart);
	//��CStringת����int
	int ListCountEnd;
	ListCountEnd = _ttoi(TempListCount);

	m_List.InsertItem(ListCountEnd, m_IntValue);
	m_List.SetItemText(ListCountEnd, 1, m_StrValue);
	m_List.SetItemText(ListCountEnd, 2, m_FloValue);
	m_List.SetItemText(ListCountEnd, 3, m_DateValue);
	/*ԭ��������������Ͳ���ʶ�����޷���������Ϊʶ����������󾭲���ȷʵ���������͵�����*/

}

//ɾ����ť����ʵ�ִ����
void CMFCListControlDlg::OnBnClickedDell()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CRect rect;
	m_List.GetClientRect(&rect);

	if (AfxMessageBox(TEXT("ȷ��Ҫɾ������������?"), MB_OKCANCEL) == IDOK)
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
Listcontrol�༭����
�ó���μ���һ����θ���ListControl�ؼ��ı༭���֣��ο��������ӽ��б༭
https://blog.csdn.net/weixin_41485242/article/details/80601588
https://blog.csdn.net/xianglifighter/article/details/17592209#commentBox
*/
void CMFCListControlDlg::OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult)
{

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRect rc;
	CString strTemp;
	NM_LISTVIEW *pNMListView = (NM_LISTVIEW *)pNMHDR;
	m_Row = pNMListView->iItem;
	m_Col = pNMListView->iSubItem;

	if (pNMListView->iItem == -1)	//ѡ��հ״������һ�У������ý���Ϊ���һ�У��ڶ���
	{
		m_Row = m_List.GetItemCount();//�õ�ListControl������
		strTemp.Format(_T("%d"), m_Row + 1);
		//m_List.InsertItem(m_Row, strTemp); //�˾����岻��
		m_List.SetItemState(m_Row, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		m_List.EnsureVisible(m_Row, FALSE);
		//m_Col = 1;
	}

	if (m_Col != 0 & m_Col != 3)	// ���жϲ����ڵ�����ֵΪ�����޸ĵ�����
	{
		m_List.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);
		m_Hide.SetParent(&m_List);
		m_Hide.MoveWindow(rc);
		//m_Hide.SetWindowTextW(m_List.GetItemText(m_Row, m_Col));
		m_Hide.ShowWindow(SW_SHOW);
		m_Hide.SetFocus();//����Edit����
		m_Hide.ShowCaret();//��ʾ���
		m_Hide.SetSel(0, -1);//ȫѡ
	}

	*pResult = 0;

}

/*
�ó���μ���һ����θ���ListControl�ؼ��ı༭���֣��ο��������ӽ��б༭
https://blog.csdn.net/weixin_41485242/article/details/80601588
https://blog.csdn.net/xianglifighter/article/details/17592209#commentBox
*/

void CMFCListControlDlg::OnKillfocusHide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString str;
	//m_Hide.GetWindowTextW(str);
	m_List.SetItemText(m_Row, m_Col, str);
	m_Hide.ShowWindow(SW_HIDE);

}


void CMFCListControlDlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��������
	//���Ҫ�����ļ�����Ҫ��һ���ļ�����

	CFile file;
	if (!file.Open(TEXT(".\\test.txt"), CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox(TEXT("�����ļ�ʧ��"));
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
			�˴��Ľṹ��info�����û�н��г�ʼ���ڴ������������ļ��д洢����Ϣ�����̣�Ҫ���г�ʼ���ڴ�Ĳ���Ϊ��ֵ_T("");
			����û�б������ֽڵĿռ�ᱻ�ո����
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
		AfxMessageBox(TEXT("���ݱ���ɹ�"));
		file.Close();
	}

}



void CMFCListControlDlg::OnBnClickedLoad()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//AfxMessageBox(_TEXT("hello"));
	CFile file;
	if (!file.Open(TEXT(".\\test.txt"), CFile::modeRead))
	{
		AfxMessageBox(TEXT("���ļ�ʧ�ܣ�"));
		return;
	}
	CListCtrl *pList = (CListCtrl*)GetDlgItem(IDC_LIST);
	int i = 0;
	CString str;
	SInfo info;
	pList->DeleteAllItems();//�ڽ��м�������֮ǰ����ListCtrl���������ݽ�����ղ�����
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
