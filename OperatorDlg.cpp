// OperatorDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lucia.h"
#include "OperatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COperatorDlg dialog


COperatorDlg::COperatorDlg(CObservate* pObs, CWnd* pParent /*=NULL*/)
	: CDialog(COperatorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COperatorDlg)
	//}}AFX_DATA_INIT
	m_pObs = pObs;
}


void COperatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COperatorDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COperatorDlg, CDialog)
	//{{AFX_MSG_MAP(COperatorDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COperatorDlg message handlers

void COperatorDlg::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItemText(IDC_OPERATOR_NAME, m_pObs->m_Operator);
	CDialog::OnOK();
}

BOOL COperatorDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetDlgItemText(IDC_OPERATOR_NAME, m_pObs->m_Operator);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
