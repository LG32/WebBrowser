#pragma once


// CDlgProxySet �Ի���

class CDlgProxySet : public CDialog
{
	DECLARE_DYNAMIC(CDlgProxySet)

public:
	CDlgProxySet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgProxySet();
	CString csIP;
// �Ի�������
	enum { IDD = IDD_DLG_PROXY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	DWORD m_IP;
	UINT m_port;
};
