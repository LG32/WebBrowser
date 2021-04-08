// DlgProxySet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WebBrowser.h"
#include "DlgProxySet.h"


// CDlgProxySet �Ի���

IMPLEMENT_DYNAMIC(CDlgProxySet, CDialog)

CDlgProxySet::CDlgProxySet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProxySet::IDD, pParent)
	, m_IP(0)
	, m_port(0)
{

}

CDlgProxySet::~CDlgProxySet()
{
}

void CDlgProxySet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_IPAddress(pDX, IDC_IPADDRESS, m_IP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
}


BEGIN_MESSAGE_MAP(CDlgProxySet, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgProxySet::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgProxySet ��Ϣ�������

void CDlgProxySet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	BYTE b1, b2, b3, b4;
	((CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS))->GetAddress(b1, b2, b3, b4);
	csIP.Format(_T("%d.%d.%d.%d"), b1, b2, b3, b4);
	OnOK();
}
