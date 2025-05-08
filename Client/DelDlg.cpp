// DelDlg.cpp: 实现文件
//

#include "pch.h"
#include "saveMoneysys.h"
#include "DelDlg.h"
#include "InfoFile.h"


// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(IDD_DIALOG_DEL)
	, m_price(0)
	, m_number(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_number);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON4, &CDelDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDelDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDelDlg 诊断

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg 消息处理程序


void CDelDlg::OnInitialUpdate()
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


void CDelDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
		if (CString(it->name.c_str()) == name) {
			m_price = it->price;
			break;
		}
	}
	UpdateData(FALSE);
}


void CDelDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int index = m_combo.GetCurSel();
	CString name;
	m_combo.GetLBText(index, name);
	int num = 0;
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
		if (CString(it->name.c_str()) == name) {
			num = it->num;
			break;
		}
	}
	if (m_number <= 0 || m_number > num) {
		MessageBox(TEXT("删除数量需大于0且不超过当前库存"));
	}
	else {
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
			if (CString(it->name.c_str()) == name) {
				it->num -= m_number;
				m_number = 0;
				UpdateData(FALSE);
				file.WirteDocline();
				MessageBox(TEXT("删除成功"));
				break;
			}
		}
	}
}


void CDelDlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	m_number = 0;
	UpdateData(FALSE);
}
