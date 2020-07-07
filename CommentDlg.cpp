// CommentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lucia.h"
#include "CommentDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommentDlg dialog


CCommentDlg::CCommentDlg(CObservate * pObs, CWnd* pParent /*=NULL*/)
	: CDialog(CCommentDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCommentDlg)
	//}}AFX_DATA_INIT
	m_pObs = pObs;
}


void CCommentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCommentDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCommentDlg, CDialog)
	//{{AFX_MSG_MAP(CCommentDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommentDlg message handlers

void CCommentDlg::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItemText(IDC_COMMENT, m_pObs->m_Comment);
	CDialog::OnOK();
}

BOOL CCommentDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetDlgItemText(IDC_COMMENT, m_pObs->m_Comment);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
