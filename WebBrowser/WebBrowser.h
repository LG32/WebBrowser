
// WebBrowser.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CWebBrowserApp:
// �йش����ʵ�֣������ WebBrowser.cpp
//

class CWebBrowserApp : public CWinAppEx
{
public:
	CWebBrowserApp();

// ��д
	public:
	virtual BOOL InitInstance();
	HHOOK m_hHook;
// ʵ��
	
	DECLARE_MESSAGE_MAP()
};

extern CWebBrowserApp theApp;