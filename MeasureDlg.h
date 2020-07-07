#if !defined(AFX_MEASUREDLG_H__A9A46920_91B8_11D2_AA4C_CFC085E0EC65__INCLUDED_)
#define AFX_MEASUREDLG_H__A9A46920_91B8_11D2_AA4C_CFC085E0EC65__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MeasureDlg.h : header file
//
#include "Observate.h"

/////////////////////////////////////////////////////////////////////////////
// CMeasureDlg dialog

class CMeasureDlg : public CDialog
{
	CObservate* m_pObservate;

// Construction
public:
	CMeasureDlg(CObservate* pObs, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CMeasureDlg)
	enum { IDD = IDD_MEASURE_DLG };
	DWORD	m_InSeriaDelay;
	DWORD	m_SeriaDelay;
	DWORD	m_MeasureDelay;
	DWORD	m_SeriaCount;
	DWORD	m_MeasureCount;
	DWORD	m_InSeriaCount;
	CString	m_SumCont;
	CString	m_OneMsr;
	CString	m_OneSeria;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeasureDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeasureDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	
	afx_msg void OnChangeInSeriaCount();
	afx_msg void OnChangeInSeriaDelay();
	
	afx_msg void OnChangeMeasureCount();
	afx_msg void OnChangeMeasureDelay();

	afx_msg void OnChangeSeriaCount();
	afx_msg void OnChangeSeriaDelay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ReCalculate();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEASUREDLG_H__A9A46920_91B8_11D2_AA4C_CFC085E0EC65__INCLUDED_)
