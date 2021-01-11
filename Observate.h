// Observate.h: interface for the CObservate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OBSERVATE_H__A9A46921_91B8_11D2_AA4C_CFC085E0EC65__INCLUDED_)
#define AFX_OBSERVATE_H__A9A46921_91B8_11D2_AA4C_CFC085E0EC65__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Graphic.h"

#include <tuple>
#include <chrono>

class CObservate  
{
public:
	void WriteToFile(CStdioFile * pFile);
	DWORD GetContinue();
	DWORD m_MsrContinue;
	void SetMsrTime(CTime time);
	void SetMsrType(CString type);
	void SetMeter(CString name);
	void SetComment();
	void SetOperator();
	void SetObservate();

	CString GetMsrType();

	void Redraw(UINT NumFrom, UINT NumTo, UINT Move);
	void ShowValInGraph(unsigned int pos, bool active);

	void Serialize(CArchive& ar);
	bool Record(bool forExcel);

	void ShowValInTree(CTreeCtrl* pTreeCtrl, DWORD ValNum, HTREEITEM hParItm);
	HTREEITEM ShowSeriaInTree(CTreeCtrl* pTreeCtrl, DWORD SerNum, HTREEITEM hParItm);
	HTREEITEM ShowMsrInTree(CTreeCtrl* pTreeCtrl, DWORD MsrNum);
	
	void Clear();
	DWORD PosCal(DWORD m, DWORD s, DWORD v);
	bool Initialise();
	
	CObservate(CString meter);
	virtual ~CObservate();

	CTime m_MsrTime;

	CString m_MsrType;
	DWORD m_DecKoef;
	CString m_Comment;
	CString m_Operator;
	CString m_Meter;

	CGraphic* m_pGraphic;

	bool m_IsSaved;
	
	DWORD m_MsrCount;
	DWORD m_MsrDelay;

	DWORD m_SeriaCount;
	DWORD m_SeriaDelay;
	
	DWORD m_InSeriaCount;
	DWORD m_InSeriaDelay;

	DWORD m_RealSize;
	CArray < unsigned long long > m_timestapms;
	CArray < double > m_ValList;

};

#endif // !defined(AFX_OBSERVATE_H__A9A46921_91B8_11D2_AA4C_CFC085E0EC65__INCLUDED_)
