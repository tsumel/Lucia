// Meter.cpp: implementation of the CMeter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lucia.h"
#include "MeterDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace std::chrono;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMeter::CMeter()
{
	m_strName = "FLUKE 45";
	m_strInterface = "RS-232";
	
	m_PortName = "COM1";

	m_BoudRate = "9600";
	m_bParity = FALSE;

	m_pPort = NULL;
	m_pPort = new CPort();

	m_PortReadIntervalTimeout = m_pPort->m_ReadIntervalTimeout.count();
	m_PortReadTotalTimeoutMultiplier = m_pPort->m_ReadTotalTimeoutMultiplier.count();
	m_PortReadTotalTimeoutConstant = m_pPort->m_ReadTotalTimeoutConstant.count();

	m_bEcho = FALSE;
	
	m_MsrType = IDC_RB_VDC;
	m_Range = NULL;
	m_Rate = "Medium";


	m_strEcho = _T("");
	m_strPrompt = _T("");
	m_strAnswer = _T("");

	m_DecKoef = NULL;
}

CMeter::~CMeter()
{
	if (m_pPort)
	{
		delete m_pPort;
	}
}

bool CMeter::ConnectExp()
{
	CString strDCB = m_PortName + ":";
	strDCB += " baud=";
	strDCB += m_BoudRate;
	strDCB += " parity=";
	if (m_bParity)
	{
		strDCB += "1";
	}
	else
	{
		strDCB += "N";
	}
	strDCB += " data=8";
	strDCB += " stop=1";

	if (m_pPort->Create(LPCTSTR(m_PortName), LPCSTR(strDCB)))
	{
		return TRUE;
	}
	return FALSE;
}

double CMeter::GetVal()
{
//	return Simulate();
	m_strAnswer = _T("");
	double val = 0.0;
	if (SendQuery("MEAS1?\r"))
	{
		val = atof(m_strAnswer) * pow(10, m_DecKoef);
	}
	return val;
	
}

void CMeter::SetMeter()
{
	CMeterDlg dlg(this,NULL);
	dlg.DoModal();

	m_pPort->m_ReadIntervalTimeout = milliseconds(m_PortReadIntervalTimeout);
	m_pPort->m_ReadTotalTimeoutMultiplier = milliseconds(m_PortReadTotalTimeoutMultiplier);
	m_pPort->m_ReadTotalTimeoutConstant = milliseconds(m_PortReadTotalTimeoutConstant);
}

bool CMeter::Initialise(bool mode)
{
	CString cmd = _T("");

	if(mode)
	{	
		if (SendQuery("*IDN?\r"))
		{
			m_strName = m_strAnswer;
		}
		else
		{
			return FALSE;
		}

		if(m_strPrompt == "\n=>\r")
		{
		//strcat(cmd,"REMS; ");
			cmd += "REMS; ";
			switch(m_MsrType)
			{
				case IDC_RB_VDC:
			//strcat(cmd, "VDC; ");
					cmd += "VDC; ";
				break;
				case IDC_RB_VAC:
			//strcat(cmd, "VAC; ");
					cmd += "VAC; ";
				break;
				case IDC_RB_CDC:
			//strcat(cmd, "ADC; ");
					cmd += "ADC; ";
				break;
				case IDC_RB_CAC:
			//strcat(cmd, "AAC; ");
					cmd += "AAC; ";
				break;
				case IDC_RB_RES:
			//strcat(cmd, "OHMS; ");
					cmd += "OHMS; ";
				break;
				case IDC_RB_FREQ:
			//strcat(cmd, "FREQ; ");
					cmd += "FREQ; ";
				break;
			}

			if(m_Rate == "Medium")
			//strcat(cmd, "RATE M; ");
				cmd += "RATE M; ";
			if(m_Rate == "Slow")
			//strcat(cmd, "RATE S; ");
				cmd += "RATE S; ";
			if(m_Rate == "Fast")
			//strcat(cmd, "RATE F; ");
				cmd += "RATE F; ";

			//strcat(cmd, "RANGE ");
			cmd += "RANGE ";

			char buf[5];
			itoa(m_Range+1, buf, 10);
		//strcat(buf, "; ");
		//strcat(cmd, buf);
			cmd += buf;
			cmd += "; ";

		//strcat(cmd, "FORMAT1;");
			cmd += " FORMAT 1;\r";
		
			SendCmd(cmd);
			if( m_strPrompt == "\n=>\r")
				return TRUE;
			return FALSE;
		}
		return FALSE;
	}
	else
	{
		SendCmd("LOCS\r");
		if( m_strPrompt == "\n=>\r")
			return TRUE;
		return FALSE;
	}
}

bool CMeter::SendCmd(CString cmd)
{
	if(m_pPort->WriteStr(cmd))
	{
		if (m_bEcho)
		{
			m_strEcho = m_pPort->ReadStr();
		}
		m_strPrompt = m_pPort->ReadStr();

		return TRUE;	
	}
	else
	{
		AfxMessageBox("Can not write to Port!");
	}
	return FALSE;
}

CString CMeter::GetName()
{
	return m_strName;
}

double CMeter::Simulate()
{
	char buf[20];
	srand((unsigned int)time(0));
	_itoa((BYTE)rand(),buf,10);
	CString str = buf;
	srand((unsigned int)time(0));
	_itoa((BYTE)rand(),buf,10);
	str += '.';
	str += buf;
	double val = atof(str);
	return val;
}


bool CMeter::SendQuery(CString query)
{
	if(m_pPort->WriteStr(query))
	{
		if(m_bEcho)
		{
			m_strEcho = m_pPort->ReadStr();
			if(m_strEcho == "")
			{
				AfxMessageBox("Not detected a Meter FLUKE 45!");
				return FALSE;
			}

		}
		
		m_strAnswer = m_pPort->ReadStr();
		if(m_strAnswer == "")
		{
			AfxMessageBox("Not detected a Meter FLUKE 45!");
			return FALSE;
		}
		m_strPrompt = m_pPort->ReadStr();
		if(m_strPrompt == "\n=>\r")
		{
			return TRUE;
		}
		else
		{
			AfxMessageBox("Was detected Command or Execution Error!");
		}
		return FALSE;
	}
	else
	{
		AfxMessageBox("Can not write to Port!");
	}
	return FALSE;
}

CString CMeter::GetMsrType()
{
	CString type = _T("");

	
	if(m_MsrType == IDC_RB_VDC || m_MsrType == IDC_RB_VAC)
	{
		if(m_Rate == "Fast" || m_Rate == "Medium")
		{
			if(m_Range == 0)
			{
				type = "mV";
				m_DecKoef = 3;
			}
			else
			{
				type = "V";
				m_DecKoef = 0;
			}
		}
		else
		{
			if(m_Range == 0 || m_Range == 1)
			{
				type = "mV";
				m_DecKoef = 3;
			}
			else
			{
				type = "V";
				m_DecKoef = 0;
			}

		}
	}


	if(m_MsrType == IDC_RB_CDC || m_MsrType == IDC_RB_CAC)
	{
		
		if(m_Range == 0 || m_Range == 1)
		{
			type = "mA";
			m_DecKoef = 3;
		}
		else
		{
			type = "A";
			m_DecKoef = 0;
		}
		
//			type = "A";

	}

	if(m_MsrType == IDC_RB_RES)
	{
		
		if(m_Rate == "Fast" || m_Rate == "Medium")
		{
			if(m_Range == 0)
			{
				type = "Om";
				m_DecKoef = 0;
			}
			if(m_Range > 0 || m_Range < 4)
			{
				type = "kOm";
				m_DecKoef = -3;
			}
			if(m_Range > 3)
			{
				type = "MOm";
				m_DecKoef = -6;
			}
		}
		else
		{
			if(m_Range < 2)
			{
				type = "Om";
				m_DecKoef = 0;
			}
			if(m_Range > 1 || m_Range < 5)
			{
				type = "kOm";
				m_DecKoef = -3;
			}
			if(m_Range > 4)
			{
				type = "MOm";
				m_DecKoef = -6;
			}
		}
		//		type = "Om";
	}

	if(m_MsrType == IDC_RB_FREQ)
	{
		if(m_Range == 0)
		{
			type = "Hz";
			m_DecKoef = 0;
		}
		if(m_Range == 4)
		{
			type = "MHz";
			m_DecKoef = -6;
		}
		if(m_Range < 4 && m_Range > 0)
		{
			type = "kHz";
			m_DecKoef = -3;
		}
		//type = "Hz";
	}
	
	return type;
}
