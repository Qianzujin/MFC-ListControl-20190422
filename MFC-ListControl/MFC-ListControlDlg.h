
// MFC-ListControlDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include <afx.h>//CFile�ļ���д��Ҫ��ͷ�ļ�



// CMFCListControlDlg �Ի���
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
// ����
public:
	CMFCListControlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCLISTCONTROL_DIALOG };
#endif

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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAdd();
	CListCtrl m_List;
	// ��������// ��������
	CString m_IntValue;
	// �ַ�����
	CString m_StrValue;
	// �ַ�����
	CString m_FloValue;
	// ʱ������// ʱ������
	CString m_DateValue;
	afx_msg void OnBnClickedDell();
	afx_msg BOOL CheckNull();
	// ���صĴ���// ���صĴ���
	CEdit m_Hide;
	int m_Row = -1;
	int m_Col = -1;
	afx_msg void OnDblclkList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnKillfocusHide();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
};
