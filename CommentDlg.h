#if !defined(AFX_COMMENTDLG_H__D613CF61_911C_11D2_AA4C_EB353B85A36A__INCLUDED_)
#define AFX_COMMENTDLG_H__D613CF61_911C_11D2_AA4C_EB353B85A36A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// CommentDlg.h : header file
//
#include "Observate.h"
/////////////////////////////////////////////////////////////////////////////
// CCommentDlg dialog

class CCommentDlg : public CDialog
{
	CObservate * m_pObs;
// Construction
public:
	CCommentDlg(CObservate * pObs, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCommentDlg)
	enum { IDD = IDD_COMMENT_DLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommentDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommentDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMENTDLG_H__D613CF61_911C_11D2_AA4C_EB353B85A36A__INCLUDED_)
