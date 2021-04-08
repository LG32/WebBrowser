
// WebBrowserDlg.h : ͷ�ļ�
//

#pragma once
#include "WebView.h"
#include "DlgProxySet.h"

// CWebBrowserDlg �Ի���
class CWebBrowserDlg : public CDialog
{
// ����
public:
	CWebBrowserDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
	enum { IDD = IDD_WEBBROWSER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void WaitForClose();
	WebView m_web;
//	wkeWebView m_web;
// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnBack();
	afx_msg void OnBnClickedBtnForward();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnRefresh();
	afx_msg void OnBnClickedBtnGo();
	afx_msg void OnBnClickedBtnProxy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};

void _cdecl wkeOnTitleChangedCallBack(wkeWebView webView, void* param, const wkeString title);
void _cdecl wkeOnURLChangedCallBack(wkeWebView webView, void* param, const wkeString url);
bool _cdecl wkeOnNavigationCallBack(wkeWebView webView, void* param, wkeNavigationType navigationType, const wkeString url);
wkeWebView _cdecl onBrowserCreateView(wkeWebView webView, void* param, wkeNavigationType navType, const wkeString urlStr, const wkeWindowFeatures* features);
char* _cdecl CreateUTF8TextInitWithString(CString strValue);