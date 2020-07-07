// LuciaDoc.cpp : implementation of the CLuciaDoc class
//
#include "stdafx.h"
#include "Lucia.h"

#include "LuciaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLuciaDoc

IMPLEMENT_DYNCREATE(CLuciaDoc, CDocument)

BEGIN_MESSAGE_MAP(CLuciaDoc, CDocument)
	//{{AFX_MSG_MAP(CLuciaDoc)
	ON_COMMAND(ID_COMMENTAR, OnCommentar)
	ON_COMMAND(ID_MEASURE, OnMeasure)
	ON_COMMAND(ID_METER, OnMeter)
	ON_COMMAND(ID_OPERATOR, OnOperator)
	ON_COMMAND(ID_SAVE_AS_TEXT, OnSaveAsText)
	ON_COMMAND(ID_EXCEL_CONVERT, OnExcelConvert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLuciaDoc construction/destruction

CLuciaDoc::CLuciaDoc()
{
	m_pMeter = NULL;
	m_pObser = NULL;
}

CLuciaDoc::~CLuciaDoc()
{
	if(m_pMeter)
		delete m_pMeter;
	if(m_pObser)
		delete m_pObser;
}

BOOL CLuciaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	if(m_pMeter)
		delete m_pMeter;
	m_pMeter = new CMeter;

	if(m_pObser)
		delete m_pObser;
	m_pObser = new CObservate(m_pMeter->GetName());
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLuciaDoc serialization

void CLuciaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
//		UpdateAllViews(NULL, 0, NULL);
	}
	else
	{
//		UpdateAllViews(NULL, 0, NULL);
	}
	m_pObser->Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CLuciaDoc diagnostics

#ifdef _DEBUG
void CLuciaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CLuciaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLuciaDoc commands

BOOL CLuciaDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	return TRUE;
}

void CLuciaDoc::DeleteContents() 
{
	CDocument::DeleteContents();
}

void CLuciaDoc::OnCommentar() 
{
	if(m_pObser->m_ValList.GetSize() != NULL)
		if(m_pObser->m_IsSaved != TRUE)
			AfxMessageBox("You can lost Datas");
	m_pObser->SetComment();
}

void CLuciaDoc::OnMeasure() 
{
	m_pObser->SetObservate();
}

void CLuciaDoc::OnMeter() 
{
	m_pMeter->SetMeter();
}

void CLuciaDoc::OnOperator() 
{
	if(m_pObser->m_ValList.GetSize() != NULL)
		if(m_pObser->m_IsSaved != TRUE)
			AfxMessageBox("You can lost Datas");
	m_pObser->SetOperator();	
}

void CLuciaDoc::OnSaveAsText() 
{
	if(m_pObser->Record(FALSE))
		AfxMessageBox( "Record is complete successful");
	else
		AfxMessageBox("Recording is failed");
}

void CLuciaDoc::OnExcelConvert() 
{
	if(!m_pObser->Record(TRUE))
		AfxMessageBox("Recording is failed");
}
