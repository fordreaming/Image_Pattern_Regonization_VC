// DSPLITView.cpp : implementation of the CDSPLITView class
// 2005.1.13��16��02 By Superman 


#include "stdafx.h"
#include "DSPLIT.h"

#include "DSPLITDoc.h"
#include "DSPLITView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDSPLITView

IMPLEMENT_DYNCREATE(CDSPLITView, CView)

BEGIN_MESSAGE_MAP(CDSPLITView, CView)
	//{{AFX_MSG_MAP(CDSPLITView)
	ON_COMMAND(ID_BUTTON_CLEAR, OnButtonClear)
	ON_COMMAND(ID_BUTTONDISPLAY, OnButtondisplay)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDSPLITView construction/destruction

CDSPLITView::CDSPLITView()
{
	lbtDown=FALSE;
	rbtDown=FALSE;
}

CDSPLITView::~CDSPLITView()
{
}

BOOL CDSPLITView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDSPLITView drawing

void CDSPLITView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	pDC->TextOut(10,250,"1.����д�淶���ֲ�Ҫ̫С��");
	pDC->TextOut(10,270,"2.д�ֵ�ʱ�����϶���������");
	pDC->TextOut(10,290,"3.�϶�����Ҽ������Բ����ʻ���");
	pDC->TextOut(10,310,"4.��������ͼ����[����]��ť���������ͼ��");
	pDC->TextOut(10,330,"5.��������ͼ��ѡ��ģʽʶ��˵�������б�");
	pDC->TextOut(10,350,"6.�б����ʱ��˵������Ʒ��������д��̫�٣�");
	pDC->TextOut(10,370,"  ��[����]��ť�������ִ�����Ʒ���У���ʶ��");
	pDC->TextOut(10,390,"  ���߻�һ�ַ�ʽд��");

	CRect cr(0,0,240,240);
	pDC->FillSolidRect(cr,RGB(220,220,220));

	if(state==1)
	{
        BYTE* pBitmapData = classify->GetData();
        LPBITMAPINFO pBitmapInfo = classify->GetInfo();
        int bitmapHeight = classify->GetHeight();
        int bitmapWidth = classify->GetWidth();
		
		if (classify->GetRGB()) // Has a color table
		{
			CPalette * hPalette1=CreateBitmapPalette(classify);
            CPalette * hOldPalette =
                pDC->SelectPalette(hPalette1, true);
            pDC->RealizePalette();
			::StretchDIBits(pDC->GetSafeHdc(),0,0, bitmapWidth, bitmapHeight,
				0, 0, bitmapWidth , bitmapHeight ,
				pBitmapData, pBitmapInfo,
				DIB_RGB_COLORS, SRCCOPY);
            pDC->SelectPalette(hOldPalette, true);
            hPalette.DeleteObject();
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDSPLITView diagnostics

#ifdef _DEBUG
void CDSPLITView::AssertValid() const
{
	CView::AssertValid();
}

CPalette* CDSPLITView::CreateBitmapPalette(CDib *pBitmap)
{
	struct
	{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];
	} palette = { 0x300, 256 };
	
	LPRGBQUAD pRGBTable = pBitmap->GetRGB();
	UINT numberOfColors = pBitmap->GetNumberOfColors();
	
	for(UINT x=0; x<numberOfColors; ++x)
	{
		palette.aEntries[x].peRed =
			pRGBTable[x].rgbRed;
		palette.aEntries[x].peGreen =
			pRGBTable[x].rgbGreen;
		palette.aEntries[x].peBlue =
			pRGBTable[x].rgbBlue;
		palette.aEntries[x].peFlags = 0;
	}
	
	hPalette.CreatePalette((LPLOGPALETTE)&palette);
	return &hPalette;
}

void CDSPLITView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDSPLITDoc* CDSPLITView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDSPLITDoc)));
	return (CDSPLITDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDSPLITView message handlers

void CDSPLITView::clearmem()
{
	CDSPLITDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
    classify=&pDoc->classify;
}

void CDSPLITView::OnButtonClear() 
{
	clearmem();
	m_pData=classify->m_pData;
	wide=classify->GetWidth();
	LineBytes=(wide*8+31)/32*4;
	height=classify->GetHeight();
	memset(m_pData,220,(wide)*(height-3));
 	state=1;
	Invalidate();	
}

void CDSPLITView::OnButtondisplay() 
{
	

	clearmem();
	m_pData=classify->m_pData;	
	wide=classify->GetWidth();
	LineBytes=(wide*8+31)/32*4;
	height=classify->GetHeight();
 	state=1;
	Invalidate();	
}

void CDSPLITView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(state==1)
	{
		if(rbtDown)
		{
			SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR2));
			CRect rc;
			rc.left=point.x-3;
			rc.right=point.x+3;
			rc.top=point.y-3;
			rc.bottom=point.y+3;
			for(int x=point.x-3;x<point.x+3;x++)
				for(int y=point.y-3;y<point.y+3;y++)
					if((x-point.x)*(x-point.x)+(y-point.y)*(y-point.y)<9)
						*(m_pData+LineBytes*(height-y)+x)=220;
			InvalidateRect(rc,TRUE);
		}
		else
		{
			SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR1));
			if (lbtDown)
			{
				CRect rc;
				rc.left=point.x-5;
				rc.right=point.x+5;
				rc.top=point.y-5;
				rc.bottom=point.y+5;
				for(int x=point.x-5;x<point.x+5;x++)
					for(int y=point.y-5;y<point.y+5;y++)
						if((x-point.x)*(x-point.x)+(y-point.y)*(y-point.y)<16)
							*(m_pData+LineBytes*(height-y)+x)=0;
				InvalidateRect(rc,TRUE);
			}
		}
	}	
	CView::OnMouseMove(nFlags, point);
}

void CDSPLITView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	OnButtondisplay();
	lbtDown=TRUE;
	CRect cr;
	cr.left =3;
	cr.right =wide-3;
	cr.top =8;
	cr.bottom =height;
	ClientToScreen(&cr);
	ClipCursor(&cr);
	CView::OnLButtonDown(nFlags, point);
}

void CDSPLITView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	lbtDown=FALSE;
	ClipCursor(NULL);
	CView::OnLButtonUp(nFlags, point);
}

void CDSPLITView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	rbtDown=TRUE;
	CView::OnRButtonDown(nFlags, point);
}

void CDSPLITView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	rbtDown=FALSE;
	CView::OnRButtonUp(nFlags, point);
}

