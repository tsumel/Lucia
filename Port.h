// Port.h: interface for the CPort class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PORT_H__24FC1740_9424_11D2_AA4C_85373E25B168__INCLUDED_)
#define AFX_PORT_H__24FC1740_9424_11D2_AA4C_85373E25B168__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CPort  
{
	CString m_PortName;
	HANDLE m_hPort;

	DCB m_DCB;
	DCB m_oldDCB;

	COMSTAT m_PortStat;
	
	COMMTIMEOUTS m_TimeOut;
	COMMTIMEOUTS m_oldTimeOut;

	COMMCONFIG	m_Config;
	COMMCONFIG	m_oldConfig;

public:
	CPort();
	virtual ~CPort();

	bool Create(const char * name, const char* str);

	CString ReadStr();
	bool WriteStr(CString cmd);

};

#endif // !defined(AFX_PORT_H__24FC1740_9424_11D2_AA4C_85373E25B168__INCLUDED_)
