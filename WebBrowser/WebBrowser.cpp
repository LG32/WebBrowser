
// WebBrowser.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "WebBrowser.h"
#include "WebBrowserDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CWebBrowserApp

BEGIN_MESSAGE_MAP(CWebBrowserApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWebBrowserApp ����

CWebBrowserApp::CWebBrowserApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CWebBrowserApp ����

CWebBrowserApp theApp;


// CWebBrowserApp ��ʼ��

BOOL CWebBrowserApp::InitInstance()
{
	CWinAppEx::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	wkeSetWkeDllPath(L"node.dll");

	wkeInitialize();
	CWebBrowserDlg dlg = new CWebBrowserDlg();
	//dlg->Create(IDD_WEBBROWSER_DIALOG);
	m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg->ShowWindow(SW_SHOW);
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	
	//MSG msg = { 0 };
	//while (GetMessage(&msg, NULL, 0, 0)) 
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessageW(&msg);
	//}

	//delete dlg;
	wkeFinalize();
	return FALSE;
}