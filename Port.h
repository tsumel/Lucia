// Port.h: interface for the CPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PORT_H__24FC1740_9424_11D2_AA4C_85373E25B168__INCLUDED_)
#define AFX_PORT_H__24FC1740_9424_11D2_AA4C_85373E25B168__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <chrono>
using namespace std::chrono_literals;

class CPort  
{
public:
	static constexpr std::chrono::milliseconds DefaultReadIntervalTimeout			= 1000ms;
	static constexpr std::chrono::milliseconds DefaultReadTotalTimeoutMultiplier	= 1000ms;
	static constexpr std::chrono::milliseconds DefaultReadTotalTimeoutConstant		= 1000ms;

public:
	CString m_PortName;
	HANDLE m_hPort;

	DCB m_DCB;
	DCB m_oldDCB;

	COMSTAT m_PortStat;
	
	COMMTIMEOUTS m_TimeOut;
	COMMTIMEOUTS m_oldTimeOut;

	COMMCONFIG	m_Config;
	COMMCONFIG	m_oldConfig;

	std::chrono::milliseconds m_ReadIntervalTimeout;
	std::chrono::milliseconds m_ReadTotalTimeoutMultiplier;
	std::chrono::milliseconds m_ReadTotalTimeoutConstant;

public:
	CPort();
	virtual ~CPort();

	bool Create(const char * name, const char* str);

	CString ReadStr();
	bool WriteStr(CString cmd);
};

#endif // !defined(AFX_PORT_H__24FC1740_9424_11D2_AA4C_85373E25B168__INCLUDED_)
