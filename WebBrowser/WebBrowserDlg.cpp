
// WebBrowserDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WebBrowser.h"
#include "WebBrowserDlg.h"
#include "WebView.h"
#include <iostream>
#include <atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CWebBrowserDlg �Ի���
CWebBrowserDlg::CWebBrowserDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWebBrowserDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWebBrowserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWebBrowserDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	//ON_BN_CLICKED(IDC_BTN_BACK, &CWebBrowserDlg::OnBnClickedBtnBack)
	//ON_BN_CLICKED(IDC_BTN_FORWARD, &CWebBrowserDlg::OnBnClickedBtnForward)
	//ON_BN_CLICKED(IDC_BTN_STOP, &CWebBrowserDlg::OnBnClickedBtnStop)
	//ON_BN_CLICKED(IDC_BTN_REFRESH, &CWebBrowserDlg::OnBnClickedBtnRefresh)
	//ON_BN_CLICKED(IDC_BTN_GO, &CWebBrowserDlg::OnBnClickedBtnGo)
	//ON_BN_CLICKED(IDC_BTN_PROXY, &CWebBrowserDlg::OnBnClickedBtnProxy)
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CWebBrowserDlg ��Ϣ�������

BOOL CWebBrowserDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	RECT rtClient;
	GetClientRect(&rtClient);
	rtClient.top += 24;
	m_web.Create(rtClient.left, rtClient.top, rtClient.right - rtClient.left, rtClient.bottom - rtClient.top, *this);
//	m_web = wkeCreateWebWindow(WKE_WINDOW_TYPE_CONTROL, *this, rtClient.left, rtClient.top, rtClient.right - rtClient.left, rtClient.bottom - rtClient.top);
	wkeOnTitleChanged(m_web, wkeOnTitleChangedCallBack, this);
	wkeOnURLChanged(m_web, wkeOnURLChangedCallBack, this);
	wkeOnNavigation(m_web, wkeOnNavigationCallBack, this);
	wkeOnCreateView(m_web, onBrowserCreateView, this);
	
	
	//CString sCmdline = ::GetCommandLine();
	//AfxMessageBox(sCmdline);
	
	CString sCmdParam = AfxGetApp()->m_lpCmdLine;
	//AfxMessageBox(sCmdParam);
	char* utfParam = CreateUTF8TextInitWithString(sCmdParam);
	wkeLoadURL(m_web, utfParam);
	wkeShowWindow(m_web, TRUE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CWebBrowserDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CWebBrowserDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWebBrowserDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DestroyWindow();
	//CDialog::OnClose();
}

void CWebBrowserDlg::OnBnClickedBtnBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (wkeCanGoBack(m_web))
	{
		wkeGoBack(m_web);
	}
}

void CWebBrowserDlg::OnBnClickedBtnForward()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (wkeCanGoForward(m_web))
	{
		wkeGoForward(m_web);
	}
}

void CWebBrowserDlg::OnBnClickedBtnStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	wkeStopLoading(m_web);
}

void CWebBrowserDlg::OnBnClickedBtnRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	wkeReload(m_web);
}

void CWebBrowserDlg::OnBnClickedBtnGo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString csurl;
	//GetDlgItem(IDC_EDIT_URL)->GetWindowText(csurl);
	wkeLoadURLW(m_web, csurl);
}

void CWebBrowserDlg::OnBnClickedBtnProxy()
{
	CDlgProxySet dlgProxySet;
	dlgProxySet.DoModal();
	wkeProxy proxy;
	proxy.type = WKE_PROXY_HTTP;
	USES_CONVERSION;
	strcpy_s(proxy.hostname, sizeof(proxy.hostname), T2A(dlgProxySet.csIP));

	proxy.port = dlgProxySet.m_port;
	wkeSetProxy(&proxy);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

void _cdecl wkeOnTitleChangedCallBack(wkeWebView webView, void* param, const wkeString title)
{
	CWebBrowserDlg *pDlg = (CWebBrowserDlg*)param;
	if (NULL != pDlg)
	{
		pDlg->SetWindowText(wkeGetStringW(title));
	}
}

void _cdecl wkeOnURLChangedCallBack(wkeWebView webView, void* param, const wkeString url)
{
	CWebBrowserDlg *pDlg = (CWebBrowserDlg*)param;
	if (NULL != pDlg)
	{
	//	pDlg->GetDlgItem(IDC_EDIT_URL)->SetWindowTextW(wkeGetStringW(url));
	}
}

bool _cdecl wkeOnNavigationCallBack(wkeWebView webView, void* param, wkeNavigationType navigationType, const wkeString url)
{
	const wchar_t* urlStr = wkeGetStringW(url);
	if (wcsstr(urlStr, L"exec://") == urlStr) {
		PROCESS_INFORMATION processInfo = { 0 };
		STARTUPINFOW startupInfo = { 0 };
		startupInfo.cb = sizeof(startupInfo);
		BOOL succeeded = CreateProcessW(NULL, (LPWSTR)urlStr + 7, NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo);
		if (succeeded) {
			CloseHandle(processInfo.hProcess);
			CloseHandle(processInfo.hThread);
		}
		return false;
	}

	return true;
}

wkeWebView _cdecl onBrowserCreateView(wkeWebView webView, void* param, wkeNavigationType navType, const wkeString urlStr, const wkeWindowFeatures* features)
{
	const wchar_t* url = wkeGetStringW(urlStr);

	wkeWebView newWindow = wkeCreateWebWindow(WKE_WINDOW_TYPE_POPUP, NULL, features->x, features->y, features->width, features->height);
	wkeShowWindow(newWindow, true);
	return newWindow;
}

void CWebBrowserDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	unsigned int flags = 0;
	if (nFlags & KF_REPEAT)
		flags |= WKE_REPEAT;
	if (nFlags & KF_EXTENDED)
		flags |= WKE_EXTENDED;

	wkeFireKeyPressEvent(m_web, nChar, flags, false);
	CDialog::OnChar(nChar, nRepCnt, nFlags);
}


char* _cdecl::CreateUTF8TextInitWithString(CString strValue)
{
	char* buffer = NULL;
	int  length;

#ifdef _UNICODE
	length = WideCharToMultiByte(CP_UTF8, 0, strValue, -1, NULL, 0, NULL, NULL);
#else
	return NULL;
#endif
	if (length <= 0)
	{
		return NULL;
	}

	buffer = new char[length];
	if (buffer == NULL)
	{
		return NULL;
	}

	ZeroMemory(buffer, length);

#ifdef _UNICODE
	WideCharToMultiByte(CP_UTF8, 0, strValue, -1, buffer, length, NULL, NULL);
#else
	strcpy_s(buffer, length, strValue);
#endif

	return buffer;
}