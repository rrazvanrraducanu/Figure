
// FigureView.cpp : implementation of the CFigureView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Figure.h"
#endif

#include "FigureDoc.h"
#include "FigureView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFigureView

IMPLEMENT_DYNCREATE(CFigureView, CView)

BEGIN_MESSAGE_MAP(CFigureView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFigureView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CFigureView construction/destruction

CFigureView::CFigureView() noexcept
{
	// TODO: add construction code here
	m_color = RGB(0, 0, 255);
}

CFigureView::~CFigureView()
{
}

BOOL CFigureView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CFigureView drawing

void CFigureView::OnDraw(CDC* /*pDC*/)
{
	CFigureDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CFigureView printing


void CFigureView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFigureView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFigureView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFigureView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFigureView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFigureView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFigureView diagnostics

#ifdef _DEBUG
void CFigureView::AssertValid() const
{
	CView::AssertValid();
}

void CFigureView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFigureDoc* CFigureView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFigureDoc)));
	return (CFigureDoc*)m_pDocument;
}
#endif //_DEBUG


// CFigureView message handlers


void CFigureView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	RedrawWindow();
	CClientDC dc(this);
	CPen pen(PS_SOLID, 2, RGB(100, 100, 100));
	dc.SelectObject(&pen);
	CBrush penson(m_color);
	dc.SelectObject(&penson);
	dc.Rectangle(10, 10, 300, 300);
	CView::OnLButtonDown(nFlags, point);
}


void CFigureView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CColorDialog dlg;
	dlg.DoModal();
	m_color = dlg.GetColor();
	OnLButtonDown(nFlags, point);
	CView::OnRButtonDown(nFlags, point);
}
