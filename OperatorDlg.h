#if !defined(AFX_OPERATORDLG_H__D613CF60_911C_11D2_AA4C_EB353B85A36A__INCLUDED_)
#define AFX_OPERATORDLG_H__D613CF60_911C_11D2_AA4C_EB353B85A36A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OperatorDlg.h : header file
//
#include "Observate.h"
/////////////////////////////////////////////////////////////////////////////
// COperatorDlg dialog

class COperatorDlg : public CDialog
{
// Construction
public:
	COperatorDlg(CObservate * pObs, CWnd * pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COperatorDlg)
	enum { IDD = IDD_OPERATOR_DLG };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COperatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COperatorDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CObservate* m_pObs;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATORDLG_H__D613CF60_911C_11D2_AA4C_EB353B85A36A__INCLUDED_)
