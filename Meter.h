// Meter.h: interface for the CMeter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_METER_H__D6F5DEE0_9104_11D2_AA4C_C0037FC18168__INCLUDED_)
#define AFX_METER_H__D6F5DEE0_9104_11D2_AA4C_C0037FC18168__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Port.h"

class CMeter 
{
	CPort* m_pPort;

	CString m_strEcho;
	CString m_strPrompt;
	CString m_strAnswer;

public:
	CString m_strName;
	CString m_strInterface;
	CString m_PortName;

	CString m_BoudRate;
	BOOL m_bParity;
	BOOL m_bEcho;

	DWORD m_PortReadIntervalTimeout;
	DWORD m_PortReadTotalTimeoutMultiplier;
	DWORD m_PortReadTotalTimeoutConstant;

	CString m_Rate;
	unsigned short m_Range;
	unsigned short m_MsrType;

protected:
	bool SendCmd(CString str);
	bool SendQuery(CString query);
	
public:
	short m_DecKoef;
	CString GetMsrType();
	CString GetName();
	CMeter();
	virtual ~CMeter();

	bool ConnectExp();
	bool Initialise(bool mode);
	double GetVal();
	void SetMeter();

private:
	double	Simulate();
};

#endif // !defined(AFX_METER_H__D6F5DEE0_9104_11D2_AA4C_C0037FC18168__INCLUDED_)
