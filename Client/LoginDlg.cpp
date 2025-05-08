// LoginDlg.cpp: 实现文件
//

#include "pch.h"
#include "saveMoneysys.h"
#include "afxdialogex.h"
#include "LoginDlg.h"
#include "InfoFile.h"


// LoginDlg 对话框

IMPLEMENT_DYNAMIC(LoginDlg, CDialogEx)

LoginDlg::LoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, edit_user(_T(""))
	, edit_psd(_T(""))
{

}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, edit_user);
	DDX_Text(pDX, IDC_EDIT2, edit_psd);
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &LoginDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &LoginDlg::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// LoginDlg 消息处理程序


void LoginDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (edit_user.IsEmpty() || edit_psd.IsEmpty()) {
		MessageBox(TEXT("账号或密码不能为空"));
		return;
	}
	CInfoFile file;
	CString name, psd;
	file.ReadLogin(name, psd);
	if (name == edit_user && psd == edit_psd) {
		CDialog::OnCancel();
	}
	else if (name != edit_user) {
		MessageBox(TEXT("用户名不存在"));
	}
	else {
		MessageBox(TEXT("密码错误"));
	}
}


BOOL LoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CInfoFile file;
	CString name, psd;
	file.ReadLogin(name, psd);
	edit_user = name;
	edit_psd = psd;
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void LoginDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void LoginDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void LoginDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
}


void LoginDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CDialogEx::OnClose();
	exit(0);
}
