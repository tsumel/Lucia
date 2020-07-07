// Graphic.cpp: implementation of the CGraphic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lucia.h"
#include "Graphic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphic::CGraphic(CString caption,  CString XType,  CString YType, UINT border)
{
	m_Caption = caption;
	
	m_XType = XType;
	m_YType = YType;

	m_brd = border;
	m_cellH = NULL;
	//m_cellW = NULL;

	m_pDC = NULL;

	m_cellW = 1;
	m_cellH = NULL;

	m_MinVal = NULL;
	m_MaxVal = NULL;

	m_NullLev = 5;
	m_IsFirst = TRUE;
}

CGraphic::~CGraphic()
{
	if(m_pDC)
		delete m_pDC;
}

void CGraphic::Create(CStatic * pFrame)
{
	m_pFrame = pFrame;
	m_pNull.x = m_brd;
	m_pFrame->GetClientRect(&m_Rect);
	m_pNull.y = m_Rect.Height() - m_brd;

	if(!m_pDC)
		m_pDC = new CClientDC(m_pFrame);
	
	//m_pDC->FillSolidRect(&m_Rect, ::GetSysColor(COLOR_WINDOW));

	DrawAxisX();
	DrawAxisY();

//	m_cellW = 1;
//	m_cellH = NULL;

	m_MinVal = NULL;
	m_MaxVal = NULL;

	m_NullLev = 5;
	m_IsFirst = TRUE;
}

void CGraphic::DrawAxisX()
{
//	CPen* pOldPen = DC.GetCurrentPen();
//Draw axisX
	m_pDC->MoveTo(m_pNull);
	m_pDC->LineTo(m_Rect.Width()-m_brd, m_pNull.y);
	m_pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
	m_pDC->TextOut(m_Rect.Width()-2*m_brd+5, m_pNull.y, "     ", 5);	
	m_pDC->TextOut(m_Rect.Width()-2*m_brd+5, m_pNull.y, m_XType, m_XType.GetLength());	
	
//	ShowCaption();
}

void CGraphic::DrawAxisY()
{
//	CPen* pOldPen = DC.GetCurrentPen();
//Draw axisY
	m_pDC->MoveTo(m_brd, m_Rect.Height() - m_brd);
	m_pDC->LineTo(m_brd,m_brd);
	m_pDC->TextOut(m_brd/2, m_brd/2, "     ",  5);	
	m_pDC->TextOut(m_brd/2, m_brd/2, m_YType,  m_YType.GetLength());	

//	ShowCaption();
}

bool CGraphic::DrawItm(DWORD ItmNum, double ItmVal, bool IsActive)
{
	const DWORD Ylen = m_pNull.y - 2*m_brd;

	if(m_IsFirst)
	{
		m_MaxVal = ItmVal;
		m_MinVal = ItmVal;
		if(ItmVal)
			m_cellH = Ylen/(2*m_MaxVal);
		m_IsFirst = FALSE;
	}

	bool IsChange = FALSE;
	if(IsActive)
		ShowLegend(ItmVal);
	DWORD x = m_brd+1+m_cellW*ItmNum;
	DWORD y = NULL;
	
	if(ItmVal > 0)
	{
		if(ItmVal > m_MaxVal)
		{
			m_MaxVal = ItmVal;
			IsChange = TRUE;
		}
	
		if(ItmVal < m_MinVal)
		{
			m_MinVal = ItmVal;
			IsChange = TRUE;
		}

		if(m_MinVal != m_MaxVal)
			m_cellH = Ylen/(m_MaxVal - m_MinVal);
		else
		{
			if(m_MaxVal != 0)
				m_cellH = Ylen/(2*m_MaxVal);
//			else
//				m_cellH = 0;
		}
		y = Transform(m_cellH*(ItmVal - m_MinVal));

		CRect rct(x, y, x+m_cellW, m_pNull.y);
//	CRect rct((m_brd+m_cellW*ItmNum+1),m_Rect.Height()-m_brd - ItmVal*m_cellH,(m_brd+m_cellW*(ItmNum+1)+1), m_Rect.Height()-m_brd);
		if(IsActive)
		{
			m_pDC->FillSolidRect(&rct, RGB(0,225,225));
		}
		else
			m_pDC->FillSolidRect(&rct, GetSysColor(COLOR_ACTIVECAPTION));

	}
/*
	if(ItmVal == 0)
	{

		m_MinVal = ItmVal;
		IsChange = TRUE;
		if(m_MinVal != m_MaxVal)
			m_cellH = Ylen/(m_MaxVal - m_MinVal);
		else
			m_cellH = Ylen/(2*m_MaxVal);

		y = Transform(m_cellH*(ItmVal - m_MinVal));

		//y = Transform(0);
	}
	if(ItmVal < 0)
	{
	//	ItmVal = 0;
		m_pNull.y = m_Rect.Height()/2;
		DrawAxisX();
	}
*/
/*
	int tmpH = m_cellH;

	if(ItmVal != NULL)
		tmpH = (m_Rect.Height()*4/5 - 2*m_brd)/ItmVal;
	if(tmpH < m_cellH)
	{
		m_cellH = tmpH;
		IsChange = TRUE;
	}
*/
/*
	CRect rct(x, y, x+m_cellW, m_pNull.y);
//	CRect rct((m_brd+m_cellW*ItmNum+1),m_Rect.Height()-m_brd - ItmVal*m_cellH,(m_brd+m_cellW*(ItmNum+1)+1), m_Rect.Height()-m_brd);
	if(IsActive)
	{
		m_pDC->FillSolidRect(&rct, RGB(0,225,225));
	}
	else
		m_pDC->FillSolidRect(&rct, GetSysColor(COLOR_ACTIVECAPTION));

//	m_pDC->LineTo((m_brd + ItmNum*m_cellW), ItmVal*m_cellH);
*/
	return IsChange;
	
}

DWORD CGraphic::GetVolume()
{
	return (m_Rect.Width()-2*m_brd)/m_cellW;
}

void CGraphic::ShowLegend(double Value)
{
	char buffer[256] = { 0 };
	_gcvt(Value, 5 , buffer);
//	char* buffer;
//	int a, b;
//	buffer = fcvt(Value, 5, &a, &b);

	CString Legend = "Val: ";
	Legend += buffer;
	Legend += "  ";
	Legend += m_YType;
	m_pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
	m_pDC->TextOut(m_Rect.Width()/6, m_brd/2, "                                                       ", 50);	
	m_pDC->TextOut(m_Rect.Width()/6, m_brd/2, Legend,Legend.GetLength());	
}

void CGraphic::ShowCaption()
{
	m_pDC->SetBkColor(GetSysColor(COLOR_WINDOW));
	m_pDC->TextOut(m_Rect.Width()/6, m_brd/2, "                                             ", 30);	
	m_pDC->TextOut(m_Rect.Width()/6, m_brd/2, m_Caption, m_Caption.GetLength());	
}

void CGraphic::Erase(UINT NumFrom, UINT NumTo)
{
	CRect rct(m_brd+NumFrom*m_cellW, 2*m_brd, m_brd+NumTo*m_cellW, m_Rect.Height()-m_brd);
	m_pDC->FillSolidRect(&rct, ::GetSysColor(COLOR_WINDOW));
	if(NumFrom == NULL)
		DrawAxisY();
	DrawAxisX();
}


void CGraphic::SetCellW(UINT count)
{
	m_cellW = (m_Rect.Width() - 2*m_brd)/count;
	if(!m_cellW)
		m_cellW = 1;
}

void CGraphic::SetCaption(CString caption)
{
	m_Caption = caption;
}

void CGraphic::SetYType(CString YType)
{
	m_YType = YType;
}

DWORD CGraphic::Transform(double y)
{
	return (DWORD)(m_pNull.y - y);
}
