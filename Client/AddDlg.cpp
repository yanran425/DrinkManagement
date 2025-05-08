// AddDlg.cpp: 实现文件
//

#include "pch.h"
#include "saveMoneysys.h"
#include "AddDlg.h"
#include "InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(IDD_DIALOG_ADD)
	, m_price1(0.0)
	, m_number1(0)
	, m_name2(_T(""))
	, m_price2(0.0)
	, m_number2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price1);
	DDX_Text(pDX, IDC_EDIT2, m_number1);
	DDX_Text(pDX, IDC_EDIT7, m_name2);
	DDX_Text(pDX, IDC_EDIT6, m_price2);
	DDX_Text(pDX, IDC_EDIT4, m_number2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON5, &CAddDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CAddDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CAddDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CAddDlg 诊断

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg 消息处理程序



void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
		m_combo.AddString(CString(it->name.c_str()));
	}
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
}

void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
		if (CString(it->name.c_str()) == name) {
			m_price1 = it->price;
			break;
		}
	}
	UpdateData(FALSE);
}

void CAddDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_number1 <= 0) {
		MessageBox(TEXT("添加数量需大于0"));
	}
	else {
		int index = m_combo.GetCurSel();
		CString name;
		m_combo.GetLBText(index, name);
		CInfoFile file;
		file.ReadDocline();
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
			if (CString(it->name.c_str()) == name) {
				it->num += m_number1;
				m_number1 = 0;
				UpdateData(FALSE);
				file.WirteDocline();
				MessageBox(TEXT("添加成功"));
				break;
			}
		}
	}

}

void CAddDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_number1 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_name2.IsEmpty() || m_number2 <= 0 || m_price2 <= 0) {
		MessageBox(TEXT("输入信息有误"));
		return;
	}
	CInfoFile file;
	file.ReadDocline();
	file.Addline(m_name2, m_number2, m_price2);
	file.WirteDocline();

	m_combo.InsertString(0, m_name2);
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
	MessageBox(TEXT("新商品添加成功"));

	m_name2.Empty();
	m_price2 = 0;
	m_number2 = 0;
	UpdateData(FALSE);

}


void CAddDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_name2.Empty();
	m_price2 = 0;
	m_number2 = 0;
	UpdateData(FALSE);
}
