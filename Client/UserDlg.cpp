// UserDlg.cpp: 实现文件
//

#include "pch.h"
#include "saveMoneysys.h"
#include "UserDlg.h"
#include "InfoFile.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(IDD_DIALOG_USER)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newpsd(_T(""))
	, m_surepsd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT3, m_name);
	DDX_Text(pDX, IDC_EDIT4, m_newpsd);
	DDX_Text(pDX, IDC_EDIT5, m_surepsd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_user = TEXT("销售员");

	CInfoFile file;
	CString name, psd;
	file.ReadLogin(name, psd);
	m_name = name;

	UpdateData(FALSE);


	// TODO: 在此添加专用代码和/或调用基类
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	if (m_newpsd.IsEmpty() || m_surepsd.IsEmpty()) {
		MessageBox(TEXT("输入密码不能为空！"));
		return;
	}
	if (m_newpsd != m_surepsd) {
		MessageBox(TEXT("输入密码不一致！"));
		return;
	}
	CInfoFile file;
	CString name, psd;
	file.ReadLogin(name, psd);
	if (m_newpsd == m_surepsd && m_newpsd == psd) {
		MessageBox(TEXT("新密码与旧密码一致！"));
		return;
	}
	if (m_newpsd == m_surepsd && m_newpsd != psd) {
		CStringA tmp(name);
		CStringA tmp2(name);
		file.WritePwd(tmp.GetBuffer(), tmp2.GetBuffer());
		MessageBox(TEXT("密码设置成功！"));

		m_newpsd.Empty();
		m_surepsd.Empty();
		UpdateData(FALSE);

		return;
	}
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_newpsd.Empty();
	m_surepsd.Empty();
	UpdateData(FALSE);
	return;

}
