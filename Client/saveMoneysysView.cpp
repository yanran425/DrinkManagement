
// saveMoneysysView.cpp: CsaveMoneysysView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "saveMoneysys.h"
#endif

#include "saveMoneysysDoc.h"
#include "saveMoneysysView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsaveMoneysysView

IMPLEMENT_DYNCREATE(CsaveMoneysysView, CView)

BEGIN_MESSAGE_MAP(CsaveMoneysysView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CsaveMoneysysView 构造/析构

CsaveMoneysysView::CsaveMoneysysView() noexcept
{
	// TODO: 在此处添加构造代码

}

CsaveMoneysysView::~CsaveMoneysysView()
{
}

BOOL CsaveMoneysysView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CsaveMoneysysView 绘图

void CsaveMoneysysView::OnDraw(CDC* /*pDC*/)
{
	CsaveMoneysysDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CsaveMoneysysView 打印

BOOL CsaveMoneysysView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CsaveMoneysysView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CsaveMoneysysView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CsaveMoneysysView 诊断

#ifdef _DEBUG
void CsaveMoneysysView::AssertValid() const
{
	CView::AssertValid();
}

void CsaveMoneysysView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CsaveMoneysysDoc* CsaveMoneysysView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsaveMoneysysDoc)));
	return (CsaveMoneysysDoc*)m_pDocument;
}
#endif //_DEBUG


// CsaveMoneysysView 消息处理程序
