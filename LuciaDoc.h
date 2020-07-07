// LuciaDoc.h : interface of the CLuciaDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LUCIADOC_H__86C7200E_903C_11D2_AA4C_B82F490C6469__INCLUDED_)
#define AFX_LUCIADOC_H__86C7200E_903C_11D2_AA4C_B82F490C6469__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Meter.h"
#include "Observate.h"

class CLuciaDoc : public CDocument
{
protected: // create from serialization only
	CLuciaDoc();
	DECLARE_DYNCREATE(CLuciaDoc)

// Attributes
public:
	CMeter* m_pMeter;
	CObservate* m_pObser;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLuciaDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLuciaDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLuciaDoc)
	afx_msg void OnCommentar();
	afx_msg void OnMeasure();
	afx_msg void OnMeter();
	afx_msg void OnOperator();
	afx_msg void OnSaveAsText();
	afx_msg void OnExcelConvert();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LUCIADOC_H__86C7200E_903C_11D2_AA4C_B82F490C6469__INCLUDED_)
