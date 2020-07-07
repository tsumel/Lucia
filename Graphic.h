// Graphic.h: interface for the CGraphic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHIC_H__49AC5302_959D_11D2_AA4C_ECA596079E69__INCLUDED_)
#define AFX_GRAPHIC_H__49AC5302_959D_11D2_AA4C_ECA596079E69__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CGraphic  
{
public:
	void SetYType(CString YType);
	void SetCaption(CString caption);
	void SetCellW(UINT count);
	void Erase(UINT NumFrom, UINT NumTo);
	DWORD GetVolume();
	bool DrawItm(DWORD ItmNum, double ItmVal, bool IsActive);
	void Create(CStatic* pFrame);
	CGraphic(CString caption, CString XType, CString YType, UINT border);
	virtual ~CGraphic();
	void DrawAxisX();
	void DrawAxisY();

private:
	DWORD m_NullLev;
	DWORD Transform(double y);
	void ShowLegend(double Value);
	void ShowCaption();
	CStatic* m_pFrame;
	CString m_Caption;
	CString m_XType;
	CString m_YType;
	
	CPoint m_pNull;
	CRect m_Rect;
	UINT m_brd;
	
	double m_cellH;
	DWORD m_cellW;
	double m_MinVal;
	double m_MaxVal;
	bool m_IsFirst;

	CClientDC* m_pDC;
protected:
};

#endif // !defined(AFX_GRAPHIC_H__49AC5302_959D_11D2_AA4C_ECA596079E69__INCLUDED_)
