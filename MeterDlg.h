#if !defined(AFX_METERDLG_H__D613CF62_911C_11D2_AA4C_EB353B85A36A__INCLUDED_)
#define AFX_METERDLG_H__D613CF62_911C_11D2_AA4C_EB353B85A36A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MeterDlg.h : header file
//
#include "Meter.h"
/////////////////////////////////////////////////////////////////////////////
// CMeterDlg dialog

class CMeterDlg : public CDialog
{
	CMeter* m_pMeter;
// Construction
public:
	void FillComboBox(UINT iPar);
	CMeterDlg(CMeter* pMeter, CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CMeterDlg)
	enum { IDD = IDD_METER_DLG };
	CComboBox	m_cmbRate;
	CComboBox	m_cmbRange;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMeterDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnRbCac();
	afx_msg void OnRbCdc();
	afx_msg void OnRbFreq();
	afx_msg void OnRbRes();
	afx_msg void OnRbVac();
	afx_msg void OnRbVdc();
	afx_msg void OnSelchangeRate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_METERDLG_H__D613CF62_911C_11D2_AA4C_EB353B85A36A__INCLUDED_)
