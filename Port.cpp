// Port.cpp: implementation of the CPort class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lucia.h"
#include "Port.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPort::CPort():
	m_ReadIntervalTimeout(DefaultReadIntervalTimeout.count()),
	m_ReadTotalTimeoutMultiplier(DefaultReadTotalTimeoutMultiplier.count()),
	m_ReadTotalTimeoutConstant(DefaultReadTotalTimeoutConstant.count())
{
	m_hPort = NULL;
}

CPort::~CPort()
{
	if(m_hPort)
	{
//return port in old state
		SetCommState(m_hPort, &m_oldDCB);
		SetCommTimeouts(m_hPort, &m_oldTimeOut);
		CloseHandle(m_hPort);
	}
}

bool CPort::Create(const char* name, const char* str)
{
	m_PortName = name;
	DWORD dwError;
	CString errorMsg;
	
	if(m_hPort)
	{
		SetCommState(m_hPort, &m_oldDCB);
		SetCommTimeouts(m_hPort, &m_oldTimeOut);
		CloseHandle(m_hPort);
	}

	m_hPort = CreateFile(m_PortName, GENERIC_READ | GENERIC_WRITE,0, NULL,OPEN_EXISTING, 0,NULL );
		
	if (m_hPort == INVALID_HANDLE_VALUE) 
	{   
		dwError = GetLastError();    
		errorMsg = "	Error!\n";
		errorMsg += "\nPort ";
		errorMsg += m_PortName;
		dwError = GetLastError();
		switch(dwError)
		{
		case 2:
			errorMsg += " is not found in Your PC";
			break;
		case 5:
			errorMsg += " is not available";
			break;
		}
		AfxMessageBox(errorMsg);
		m_hPort = NULL;
		return FALSE;
	}

	GetCommTimeouts(m_hPort, &m_oldTimeOut);
	GetCommState(m_hPort, &m_oldDCB);

//	m_TimeOut.ReadIntervalTimeout = 100;
//	m_TimeOut.ReadTotalTimeoutMultiplier =100; 
//	m_TimeOut.ReadTotalTimeoutConstant = 100;
//	m_TimeOut.WriteTotalTimeoutMultiplier = 0; 
//	m_TimeOut.WriteTotalTimeoutConstant = 0; 

	m_DCB = m_oldDCB;
	m_TimeOut = m_oldTimeOut;
//	m_DCB.BaudRate    = 9600;
//  m_DCB.ByteSize    = 8;
//  m_DCB.Parity      = NOPARITY;
//  m_DCB.StopBits    = ONESTOPBIT;
	if(BuildCommDCB(str, &m_DCB))
	{
		if (SetCommState(m_hPort, &m_DCB))
		{
			if (SetCommTimeouts(m_hPort, &m_TimeOut))
			{
				return TRUE;
			}
			else
			{
				return FALSE;
			}
			//ClearCommError(m_hPort, &dwError, &m_PortStat);
		}
	}
	else
	{
		dwError = GetLastError();
		if (dwError == 87)
		{
			errorMsg = "Wrong parametrs";
		}
		AfxMessageBox(errorMsg);
		return FALSE;
	}
	return FALSE;
}

bool CPort::WriteStr(CString cmd)
{
	DWORD written = cmd.GetLength();
	DWORD dwError = NULL;

	if (WriteFile(m_hPort, cmd, written, &written, 0))
	{
		return TRUE;
	}

	dwError = GetLastError();
	ClearCommError(m_hPort, &dwError, &m_PortStat);
	return FALSE;
}

CString CPort::ReadStr()
{
	// TODO: why setup COMM on every READ?
	m_TimeOut.ReadIntervalTimeout = m_ReadIntervalTimeout.count();
	m_TimeOut.ReadTotalTimeoutMultiplier = m_ReadTotalTimeoutMultiplier.count(); 
	m_TimeOut.ReadTotalTimeoutConstant = m_ReadTotalTimeoutConstant.count(); // ms

	CString result = _T("");

	if(SetCommTimeouts(m_hPort, &m_TimeOut))
	{
		// TODO: ReadFile with 0 and buffer? DON'T READ BYTE BY BYTE!

		DWORD read = NULL;
		char ch = 0;
		
		if(ReadFile(m_hPort, &ch, 1, &read, 0)&& read)
		{
			result += ch;
			while(ch != '\r')
			{
				if (ReadFile(m_hPort, &ch, 1, &read, 0) && read)
				{
					result += ch;
				}
				else
				{
					ch = '\r';
				}
			}
		}
	}
	return result;
}