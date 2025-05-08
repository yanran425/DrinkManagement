// SellDlg.cpp: 实现文件
//

#include "pch.h"
#include "saveMoneysys.h"
#include "SellDlg.h"
#include "InfoFile.h"


// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(IDD_DIALOG_SELL)
	, m_price(0)
	, m_leave(0)
	, m_number(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT5, m_leave);
	DDX_Text(pDX, IDC_EDIT2, m_number);
	DDX_Text(pDX, IDC_EDIT3, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSellDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CSellDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++){
		m_combo.AddString(CString(it->name.c_str()));
	}
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();

}


void CSellDlg::OnCbnSelchangeCombo1()
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
			m_leave = it->num;
			break;
		}
	}
	UpdateData(FALSE);
}


void CSellDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_number <= 0) {
		MessageBox(TEXT("购买数量需大于零"));
	}
	else if (m_number > m_leave) {
		MessageBox(TEXT("库存不足"));
	}
	else {
		int index = m_combo.GetCurSel();
		CString name;
		m_combo.GetLBText(index, name);

		CInfoFile file;
		file.ReadDocline();
		for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++) {
			if (CString(it->name.c_str()) == name) {
				it->num -= m_number;
				m_leave -= m_number;
				break;
			}
		}
		CString str;
		str.Format(TEXT("商品：%s \r\n单价：%.2f \r\n个数：%d \r\n总价：%.2f \r\n购买成功。"), name,m_price,m_number,m_price*m_number);
		m_sellInfo = str;
		UpdateData(FALSE);
		file.WirteDocline();
		MessageBox(TEXT("卖出成功"));

		m_number = 0;
		m_sellInfo.Empty();
		UpdateData(FALSE);
	}
}


void CSellDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	m_number = 0;
	m_combo.SetCurSel(0);
	OnCbnSelchangeCombo1();
	UpdateData(FALSE);
}
