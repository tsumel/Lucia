// MeasureDlg.cpp : implementation file
//

#include "stdafx.h"

#include "Defines.h"
#include "Lucia.h"
#include "MeasureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeasureDlg dialog

CMeasureDlg::CMeasureDlg(CObservate* pObs, CWnd* pParent /*=NULL*/)
	: CDialog(CMeasureDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMeasureDlg)
	m_SumCont = _T("");
	m_OneMsr = _T("");
	m_OneSeria = _T("");
	//}}AFX_DATA_INIT
	m_pObservate = pObs;
}


void CMeasureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeasureDlg)
	DDX_Text(pDX, IDC_IN_SERIA_DELAY, m_InSeriaDelay);
	DDX_Text(pDX, IDC_SERIA_DELAY, m_SeriaDelay);
	DDX_Text(pDX, IDC_MEASURE_DELAY, m_MeasureDelay);
	DDX_Text(pDX, IDC_SERIA_COUNT, m_SeriaCount);
	DDX_Text(pDX, IDC_MEASURE_COUNT, m_MeasureCount);
	DDX_Text(pDX, IDC_IN_SERIA_COUNT, m_InSeriaCount);
	DDX_Text(pDX, IDC_SUM_CONT, m_SumCont);
	DDX_Text(pDX, IDC_ONE_MSR_CONT, m_OneMsr);
	DDX_Text(pDX, IDC_ONE_SERIA_CONT, m_OneSeria);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMeasureDlg, CDialog)
	//{{AFX_MSG_MAP(CMeasureDlg)
	ON_EN_CHANGE(IDC_IN_SERIA_COUNT, OnChangeInSeriaCount)
	ON_EN_CHANGE(IDC_IN_SERIA_DELAY, OnChangeInSeriaDelay)
	
	ON_EN_CHANGE(IDC_MEASURE_COUNT, OnChangeMeasureCount)
	ON_EN_CHANGE(IDC_MEASURE_DELAY, OnChangeMeasureDelay)

	ON_EN_CHANGE(IDC_SERIA_COUNT, OnChangeSeriaCount)
	ON_EN_CHANGE(IDC_SERIA_DELAY, OnChangeSeriaDelay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeasureDlg message handlers

BOOL CMeasureDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

//In Seria settings
	m_InSeriaCount = m_pObservate->m_InSeriaCount;
	m_InSeriaDelay = m_pObservate->m_InSeriaDelay;

////Seria settings	
	m_SeriaCount = m_pObservate->m_SeriaCount;
	m_SeriaDelay = m_pObservate->m_SeriaDelay;

//Measure settings
	m_MeasureCount = m_pObservate->m_MsrCount;
	m_MeasureDelay = m_pObservate->m_MsrDelay;

	UpdateData(FALSE);

	ReCalculate();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMeasureDlg::OnOK() 
{
	if(m_pObservate->m_ValList.GetSize() == NULL)
	{
		UpdateData(TRUE);

		m_pObservate->m_MsrCount = m_MeasureCount;
		m_pObservate->m_MsrDelay = m_MeasureDelay;

		m_pObservate->m_SeriaCount = m_SeriaCount;
		m_pObservate->m_SeriaDelay = m_SeriaDelay;

		m_pObservate->m_InSeriaCount = m_InSeriaCount;
		m_pObservate->m_InSeriaDelay = m_InSeriaDelay;

		ReCalculate();
	}

	CDialog::OnOK();
}


void CMeasureDlg::ReCalculate()
{
	UpdateData(TRUE);
	
//	DWORD cont = (m_InSeriaCount)*m_InSeriaDelay;
//
//	char buffer[1024] = { 0 };
//	DWORD rem = 0;		
////one seria continue	
//	rem = cont/(60 * 1000);
//	_itoa_s(rem, buffer, 10);
//	m_OneSeria = buffer;
//	m_OneSeria += " min. ";
//	
//	rem = cont - 60*1000*rem;
//	_itoa_s(rem, buffer, 10);
//	m_OneSeria += buffer;
//	m_OneSeria += " sec.";
//
////one measure continue
//	cont = cont*m_SeriaCount + (m_SeriaCount)*m_SeriaDelay;
//	
//	rem = cont/(3600 * 1000);
//	_itoa_s(rem, buffer, 10);
//	m_OneMsr = buffer;
//	m_OneMsr += " h. ";
//
//	DWORD TMPcont = cont;
//	cont = cont - rem*3600*1000;
//	rem = cont/(60 *1000);
//	_itoa_s(rem, buffer, 10);
//	m_OneMsr += buffer;
//	m_OneMsr += " min. ";
//	
//	rem = cont - 60*1000*rem;
//	_itoa_s(rem, buffer, 10);
//	m_OneMsr += buffer;
//	m_OneMsr += " sec.";
//
////All measure
//	cont = TMPcont;
//	cont = cont*m_MeasureCount + (m_MeasureCount)*m_MeasureDelay;
//
//	m_pObservate->m_MsrContinue = cont;
//
//	rem = cont/(3600 * 1000);
//	_itoa_s(rem, buffer, 10);
//	m_SumCont = buffer;
//	m_SumCont += " h. ";
//
//	cont = cont - rem*3600*1000;
//	rem = cont/(60 * 1000);
//	_itoa_s(rem, buffer, 10);
//	m_SumCont += buffer;
//	m_SumCont += " min. ";
//		
//	rem = cont - 60*1000*rem;
//	_itoa_s(rem, buffer, 10);
//	m_SumCont += buffer;
//	m_SumCont += " sec.";

	UpdateData(FALSE);
}


void CMeasureDlg::OnChangeInSeriaCount() 
{
	ReCalculate();
}

void CMeasureDlg::OnChangeInSeriaDelay() 
{
	ReCalculate();
	
}

void CMeasureDlg::OnChangeMeasureCount() 
{
	ReCalculate();
	
}

void CMeasureDlg::OnChangeMeasureDelay() 
{
	ReCalculate();
	
}

void CMeasureDlg::OnChangeSeriaCount() 
{
	ReCalculate();
}

void CMeasureDlg::OnChangeSeriaDelay() 
{
	ReCalculate();
}
