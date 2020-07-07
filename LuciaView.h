// LuciaView.h : interface of the CLuciaView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LUCIAVIEW_H__86C72010_903C_11D2_AA4C_B82F490C6469__INCLUDED_)
#define AFX_LUCIAVIEW_H__86C72010_903C_11D2_AA4C_B82F490C6469__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CLuciaView : public CFormView
{
	bool m_DelTree;
	unsigned int m_ActivePos;
	bool m_IsBreak;

public:
//	bool m_PropActive;
//	bool m_RecActive;
//	bool m_MsrActive;
//	bool m_StopActive;
	//bool m_DelTree;
	bool m_IsContinue;
	CWinThread* m_pThread;
	//int m_ActivePos;

protected: // create from serialization only
	CLuciaView();
	DECLARE_DYNCREATE(CLuciaView)

public:
	//{{AFX_DATA(CLuciaView)
	enum { IDD = IDD_LUCIA_FORM };
	CTreeCtrl	m_MsrTree;
	CStatic	m_GraphFrame;
	CProgressCtrl	m_Progress;
	CString	m_ElapsedTime;
	//}}AFX_DATA

// Attributes
public:
	CLuciaDoc* GetDocument();
	//UINT ExMeasure(LPVOID WinObjPtr);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLuciaView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo*);
	virtual void OnDraw(CDC* pDC);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	DWORD m_TimeElapsed;
//	int m_ActivePos;
	virtual ~CLuciaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CLuciaView)
	afx_msg void OnBreak();
	afx_msg void OnStartStopMsr();
	afx_msg void OnSelchangedMeasureTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangingMeasureTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteitemMeasureTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	unsigned short m_CurPos;
	CString ConstructCaption();
};

#ifndef _DEBUG  // debug version in LuciaView.cpp
inline CLuciaDoc* CLuciaView::GetDocument()
   { return (CLuciaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LUCIAVIEW_H__86C72010_903C_11D2_AA4C_B82F490C6469__INCLUDED_)
