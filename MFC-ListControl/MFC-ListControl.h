
// MFC-ListControl.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCListControlApp: 
// �йش����ʵ�֣������ MFC-ListControl.cpp
//

class CMFCListControlApp : public CWinApp
{
public:
	CMFCListControlApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCListControlApp theApp;