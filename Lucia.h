// Lucia.h : main header file for the LUCIA application
//

#if !defined(AFX_LUCIA_H__86C72008_903C_11D2_AA4C_B82F490C6469__INCLUDED_)
#define AFX_LUCIA_H__86C72008_903C_11D2_AA4C_B82F490C6469__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLuciaApp:
// See Lucia.cpp for the implementation of this class
//

class CLuciaApp : public CWinApp
{
public:
	CLuciaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLuciaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLuciaApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LUCIA_H__86C72008_903C_11D2_AA4C_B82F490C6469__INCLUDED_)
