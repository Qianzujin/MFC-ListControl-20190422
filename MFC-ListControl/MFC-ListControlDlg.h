
// MFC-ListControlDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include <afx.h>//CFile文件读写需要的头文件



// CMFCListControlDlg 对话框
class CMFCListControlDlg : public CDialogEx
{

	struct SInfo
	{
		TCHAR nInt[8]=_T("");
		TCHAR sStr[8] = _T("");
		TCHAR fFlo[8] = _T("");
		TCHAR tTime[16] = _T("");
		
		//CString nInt;
		//CString Sstr;
		//CString fFlo;
		//CString tTime;

	};
// 构造
public:
	CMFCListControlDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCLISTCONTROL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	CListCtrl m_List;
	// 整型数据// 整型数据
	CString m_IntValue;
	// 字符数据
	CString m_StrValue;
	// 字符数据
	CString m_FloValue;
	// 时间数据// 时间数据
	CString m_DateValue;
	afx_msg void OnBnClickedDell();
	afx_msg BOOL CheckNull();
	// 隐藏的窗口// 隐藏的窗口
	CEdit m_Hide;
	int m_Row = -1;
	int m_Col = -1;
	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusHide();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
};
