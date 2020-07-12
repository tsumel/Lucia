// MeterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lucia.h"
#include "MeterDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeterDlg dialog


CMeterDlg::CMeterDlg(CMeter* pMeter, CWnd* pParent /*=NULL*/)
	: CDialog(CMeterDlg::IDD, pParent)
{
	m_pMeter = pMeter;
	//{{AFX_DATA_INIT(CMeterDlg)
	//}}AFX_DATA_INIT
}


void CMeterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeterDlg)
	DDX_Control(pDX, IDC_RATE, m_cmbRate);
	DDX_Control(pDX, IDC_RANGE, m_cmbRange);

	DDX_Text(pDX, IDC_EDIT_READ_INTERVAL_TIMEOUT, m_pMeter->m_PortReadIntervalTimeout);
	DDX_Text(pDX, IDC_EDIT_READ_TOTAL_TIMEOUT_MULTIPLIER, m_pMeter->m_PortReadTotalTimeoutMultiplier);
	DDX_Text(pDX, IDC_EDIT_READ_TOTAL_TIMEOUT_CONSTANT, m_pMeter->m_PortReadTotalTimeoutConstant);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMeterDlg, CDialog)
	//{{AFX_MSG_MAP(CMeterDlg)
	ON_BN_CLICKED(IDC_RB_CAC, OnRbCac)
	ON_BN_CLICKED(IDC_RB_CDC, OnRbCdc)
	ON_BN_CLICKED(IDC_RB_FREQ, OnRbFreq)
	ON_BN_CLICKED(IDC_RB_RES, OnRbRes)
	ON_BN_CLICKED(IDC_RB_VAC, OnRbVac)
	ON_BN_CLICKED(IDC_RB_VDC, OnRbVdc)
	ON_CBN_SELCHANGE(IDC_RATE, OnSelchangeRate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeterDlg message handlers

BOOL CMeterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CheckRadioButton(IDC_RB_VDC, IDC_RB_FREQ, m_pMeter->m_MsrType);

	SetDlgItemText(IDC_PORT_NAME, m_pMeter->m_PortName);
	SetDlgItemText(IDC_BOUD_RATE, m_pMeter->m_BoudRate);
	
	SetDlgItemText(IDC_RATE, m_pMeter->m_Rate);

	CheckDlgButton(IDC_PARITY, m_pMeter->m_bParity);
	
	CheckDlgButton(IDC_ECHO, m_pMeter->m_bEcho);

	if(m_pMeter->m_Rate == "Fast" || m_pMeter->m_Rate == "Medium" )
	{
		switch(m_pMeter->m_MsrType)
		{
		case IDC_RB_VDC:
			FillComboBox(1);
			break;
		case IDC_RB_VAC:
			FillComboBox(8);
			break;
		case IDC_RB_CDC:
			FillComboBox(2);
			break;
		case IDC_RB_CAC:
			FillComboBox(2);
			break;
		case IDC_RB_RES:
			FillComboBox(3);
			break;
		case IDC_RB_FREQ:
			FillComboBox(4);
			break;
		}
	}
	else
	{
		switch(m_pMeter->m_MsrType)
		{
		case IDC_RB_VDC:
			FillComboBox(5);
			break;
		case IDC_RB_VAC:
			FillComboBox(9);
			break;
		case IDC_RB_CDC:
			FillComboBox(6);
			break;
		case IDC_RB_CAC:
			FillComboBox(6);
			break;
		case IDC_RB_RES:
			FillComboBox(7);
			break;
		case IDC_RB_FREQ:
			FillComboBox(4);
			break;
		}
	}	

	m_cmbRange.SetCurSel(m_pMeter->m_Range);				
				
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMeterDlg::OnOK() 
{
	// TODO: Add extra validation here
	m_pMeter->m_MsrType = GetCheckedRadioButton(IDC_RB_VDC, IDC_RB_FREQ);

	GetDlgItemText(IDC_PORT_NAME, m_pMeter->m_PortName);
	GetDlgItemText(IDC_BOUD_RATE, m_pMeter->m_BoudRate);
	
	GetDlgItemText(IDC_RATE, m_pMeter->m_Rate);

	m_pMeter->m_bParity = IsDlgButtonChecked(IDC_PARITY);
	m_pMeter->m_bEcho = IsDlgButtonChecked(IDC_ECHO);

	m_pMeter->m_Range = m_cmbRange.GetCurSel();

	CDialog::OnOK();
}

void CMeterDlg::FillComboBox(UINT iPar)
{
	switch(iPar)
	{
	case 1:
			m_cmbRange.AddString("300 mV");
			m_cmbRange.AddString("3 V");
			m_cmbRange.AddString("30 V");
			m_cmbRange.AddString("300 V");
			m_cmbRange.AddString("1000 V");
		break;
	case 2:
			m_cmbRange.AddString("30 mA");
			m_cmbRange.AddString("100 mA");
			m_cmbRange.AddString("10 A");
		break;
	case 3:
			m_cmbRange.AddString("300 Om");
			m_cmbRange.AddString("3 kOm");
			m_cmbRange.AddString("30 kOm");
			m_cmbRange.AddString("300 kOm");
			m_cmbRange.AddString("3 MOm");
			m_cmbRange.AddString("30 MOm");
			m_cmbRange.AddString("300 MOm");
		break;
	case 4:
			m_cmbRange.AddString("1000 Hz");
			m_cmbRange.AddString("10 kHz");
			m_cmbRange.AddString("100  kHz");
			m_cmbRange.AddString("1000 kHz");
			m_cmbRange.AddString("1 MHz");
		break;
	case 5:
			m_cmbRange.AddString("100 mV");
			m_cmbRange.AddString("1000 mV");
			m_cmbRange.AddString("10 V");
			m_cmbRange.AddString("100 V");
			m_cmbRange.AddString("1000 V");
		break;
	case 6:
			m_cmbRange.AddString("10 mA");
			m_cmbRange.AddString("100 mA");
			m_cmbRange.AddString("10 A");
		break;
	case 7:
			m_cmbRange.AddString("100 Om");
			m_cmbRange.AddString("1000 Om");
			m_cmbRange.AddString("10 kOm");
			m_cmbRange.AddString("100  kOm");
			m_cmbRange.AddString("1000 kOm");
			m_cmbRange.AddString("10 MOm");
			m_cmbRange.AddString("100 MOm");
		break;
	case 8:
			m_cmbRange.AddString("300 mV");
			m_cmbRange.AddString("3 V");
			m_cmbRange.AddString("30 V");
			m_cmbRange.AddString("300 V");
			m_cmbRange.AddString("750 V");
		break;
	case 9:
			m_cmbRange.AddString("100 mV");
			m_cmbRange.AddString("1000 mV");
			m_cmbRange.AddString("10 V");
			m_cmbRange.AddString("100 V");
			m_cmbRange.AddString("750 V");
		break;

	}

}

void CMeterDlg::OnRbCac() 
{
	int CurSel = m_cmbRate.GetCurSel();	

	m_cmbRange.ResetContent();

	if(CurSel == 0 || CurSel == 1 )
	{
		FillComboBox(2);
	}
	else
		FillComboBox(6);
	m_cmbRange.SetCurSel(0);				

}

void CMeterDlg::OnRbCdc() 
{
	int CurSel = m_cmbRate.GetCurSel();	

	m_cmbRange.ResetContent();

	if(CurSel == 0 || CurSel == 1 )
	{
		FillComboBox(2);
	}
	else
		FillComboBox(6);
	m_cmbRange.SetCurSel(0);				

}

void CMeterDlg::OnRbFreq() 
{
	int CurSel = m_cmbRate.GetCurSel();	

	m_cmbRange.ResetContent();

	if(CurSel == 0 || CurSel == 1 )
	{
		FillComboBox(4);
	}
	else
		FillComboBox(4);
	m_cmbRange.SetCurSel(0);				

}

void CMeterDlg::OnRbRes() 
{
	int CurSel = m_cmbRate.GetCurSel();	

	m_cmbRange.ResetContent();

	if(CurSel == 0 || CurSel == 1 )
	{
		FillComboBox(3);
	}
	else
		FillComboBox(7);
	m_cmbRange.SetCurSel(0);				
}

void CMeterDlg::OnRbVac() 
{
	int CurSel = m_cmbRate.GetCurSel();	

	m_cmbRange.ResetContent();

	if(CurSel == 0 || CurSel == 1 )
	{
		FillComboBox(8);
	}
	else
		FillComboBox(9);
	m_cmbRange.SetCurSel(0);				
}

void CMeterDlg::OnRbVdc() 
{
	int CurSel = m_cmbRate.GetCurSel();	

	m_cmbRange.ResetContent();

	if(CurSel == 0 || CurSel == 1 )
	{
		FillComboBox(1);
	}
	else
	{
		FillComboBox(5);
	}
		m_cmbRange.SetCurSel(0);				

}

void CMeterDlg::OnSelchangeRate() 
{
	int CurSel = m_cmbRate.GetCurSel();	

	m_cmbRange.ResetContent();

	if(CurSel == 0 || CurSel == 1 )
	{
		switch(GetCheckedRadioButton(IDC_RB_VDC, IDC_RB_FREQ))
		{
		case IDC_RB_VDC:
			FillComboBox(1);
			break;
		case IDC_RB_VAC:
			FillComboBox(8);
			break;
		case IDC_RB_CDC:
			FillComboBox(2);
			break;
		case IDC_RB_CAC:
			FillComboBox(2);
			break;
		case IDC_RB_RES:
			FillComboBox(3);
			break;
		case IDC_RB_FREQ:
			FillComboBox(4);
			break;
		}
	}
	else
	{
		switch(GetCheckedRadioButton(IDC_RB_VDC, IDC_RB_FREQ))
		{
		case IDC_RB_VDC:
			FillComboBox(5);
			break;
		case IDC_RB_VAC:
			FillComboBox(9);
			break;
		case IDC_RB_CDC:
			FillComboBox(6);
			break;
		case IDC_RB_CAC:
			FillComboBox(6);
			break;
		case IDC_RB_RES:
			FillComboBox(7);
			break;
		case IDC_RB_FREQ:
			FillComboBox(4);
			break;
		}
	}	
	m_cmbRange.SetCurSel(m_pMeter->m_Range);				

}
