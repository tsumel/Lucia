// Observate.cpp: implementation of the CObservate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Lucia.h"

#include "MeasureDlg.h"
#include "OperatorDlg.h"
#include "CommentDlg.h"

#include <ctime>
#include <chrono>
#include <string>
#include <sstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DEFAULT_MSR_COUNT 5
#define DEFAULT_MSR_DELAY 1

#define DEFAULT_SERIA_COUNT 5
#define DEFAULT_SERIA_DELAY 1

#define DEFAULT_IN_SERIA_COUNT 20
#define DEFAULT_IN_SERIA_DELAY 1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObservate::CObservate(CString meter)
{
	m_Meter = meter;	

	m_Operator = _T("Unknown");
	m_Comment = _T("none");

	m_MsrCount = DEFAULT_MSR_COUNT;
	m_MsrDelay = DEFAULT_MSR_DELAY;
	
	m_InSeriaCount = DEFAULT_IN_SERIA_COUNT;
	m_InSeriaDelay = DEFAULT_IN_SERIA_DELAY;
	
	m_SeriaCount = DEFAULT_SERIA_COUNT;
	m_SeriaDelay = DEFAULT_SERIA_DELAY;

	m_IsSaved = FALSE;
	m_ValList.SetSize(NULL);

	m_pGraphic = NULL;
	m_pGraphic = new CGraphic(" ", "Num.", " ", 20);

	m_DecKoef = NULL;
	m_MsrType = "none";
}

CObservate::~CObservate()
{
	Clear();
	if(m_pGraphic)
		delete m_pGraphic;
}

void CObservate::SetObservate()
{
	CMeasureDlg dlg(this, NULL);
	dlg.DoModal();
}

bool CObservate::Initialise()
{
	m_ValList.SetSize(m_MsrCount*m_SeriaCount*m_InSeriaCount);
	return TRUE;
	//return FALSE;
}

HTREEITEM CObservate::ShowMsrInTree(CTreeCtrl* pTreeCtrl, DWORD MsrNum)
{	
	char buffer[256] = { 0 };
	_itoa_s(MsrNum+1, buffer, 10);

	TV_INSERTSTRUCT treeItem;
	treeItem.hParent = TVI_ROOT;
	treeItem.hInsertAfter = TVI_LAST;

	TV_ITEM tvi;
	tvi.mask = TVIF_CHILDREN|TVIF_PARAM|TVIF_TEXT|TVIF_STATE;
	//tvi.hItem
	strcat(buffer," Measure");
	tvi.pszText = buffer;
	tvi.lParam = -2;
	tvi.cChildren = 1;
	tvi.state = TVIS_EXPANDED;

	treeItem.item = tvi;

	return pTreeCtrl->InsertItem(&treeItem);
}

HTREEITEM CObservate::ShowSeriaInTree(CTreeCtrl* pTreeCtrl, DWORD SerNum, HTREEITEM hParItm)
{

	char buffer[256] = { 0 };
	_itoa_s(SerNum+1, buffer, 10);
	
	TV_INSERTSTRUCT treeItem;
	treeItem.hParent = hParItm;
	treeItem.hInsertAfter = TVI_LAST;

	TV_ITEM tvi;
	tvi.mask = TVIF_CHILDREN|TVIF_PARAM|TVIF_TEXT|TVIF_STATE;
	//tvi.hItem

	strcat(buffer," Seria");
	tvi.pszText = buffer;
	tvi.lParam = -1;
	tvi.cChildren = 1;
	tvi.state = TVIS_EXPANDED;

	treeItem.item = tvi;

	return pTreeCtrl->InsertItem(&treeItem);

}

void CObservate::ShowValInTree(CTreeCtrl* pTreeCtrl, DWORD ValNum, HTREEITEM hParItm)
{
	char buffer[256] = { 0 };
//	int pos = ValNum - ((int)ValNum/m_InSeriaCount)*m_InSeriaCount;
	_gcvt( m_ValList[ValNum], 5, buffer );
//	char* buffer;
//	int a, b;
//	buffer = fcvt(m_ValList[ValNum], 5, &a, &b);

	TV_INSERTSTRUCT treeItem;
	treeItem.hParent = hParItm;
	treeItem.hInsertAfter = TVI_LAST;

	TV_ITEM tvi;
	tvi.mask = TVIF_PARAM|TVIF_TEXT;
	//tvi.hItem
	tvi.pszText = buffer;
	tvi.lParam = ValNum;

	treeItem.item = tvi;

	pTreeCtrl->InsertItem(&treeItem);
}

bool CObservate::Record(bool forExcel)
{
	if(m_ValList.GetSize() != NULL)
	{
		CString strFilePath = _T("");

		CFileDialog fileDlg(FALSE, "txt", "Record001", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "Text Files (*.txt)|*.txt");
		
		if(fileDlg.DoModal() == IDOK)
		{
			CStdioFile file;
			strFilePath = fileDlg.GetPathName();
			try
			{
				file.Open(strFilePath, CFile::modeCreate |
						/*CFile::modeNoTruncate  |*/ CFile::modeReadWrite | CFile::typeText );
			}
			catch( CFileException* e )
			{  
				TRACE0(e);	
				return FALSE;
			}
		
			if(file.m_pStream)
			{
				WriteToFile(&file);

				if(forExcel)
				{
					char buf[1024] = { 0 };
					char prog[1024] = { 0 };
					long sz = sizeof(buf);

					if(RegQueryValue(HKEY_LOCAL_MACHINE, _T("Software\\CLASSES\\Excel.Application\\CLSID"), buf, &sz) == ERROR_SUCCESS)
					{
					CString cmd = "CLSID\\";
					cmd += buf;
					cmd += "\\Localserver";
					//strcpy(but, "CLSID\\");
					//strcat(but, buf);
					//strcat(but,"\\Localserver");
									
					sz = sizeof(prog);
						if(RegQueryValue(HKEY_CLASSES_ROOT, cmd, prog, &sz) == ERROR_SUCCESS)
						{
							//char path[255];
						
							CString path = _T("");
							for(DWORD i = 0; i < sz; i++)
							{
								if(prog[i] != '/')
									path += prog[i];
								else
									i = sz;
							}
							path += " ";
							path += strFilePath;

							//_execl(path, path, strFilePath , NULL, NULL);
							//system(path);
							
						    PROCESS_INFORMATION piProcInfo;
						    STARTUPINFO siStartupInfo;

						    siStartupInfo.cb = sizeof(STARTUPINFO);
						    siStartupInfo.lpReserved = NULL;
							siStartupInfo.lpDesktop = NULL;
							siStartupInfo.lpTitle = NULL;
							siStartupInfo.dwFlags = STARTF_USESHOWWINDOW;
							siStartupInfo.wShowWindow = SW_SHOWNORMAL;
							siStartupInfo.cbReserved2 = 0;
							siStartupInfo.lpReserved2 = NULL;

							LPTSTR lpsz = new TCHAR[path.GetLength()+1];
							_tcscpy(lpsz, path);
							if(CreateProcess( NULL, lpsz, 
								NULL, NULL, FALSE,
								NORMAL_PRIORITY_CLASS ,
								NULL, NULL, 
					            &siStartupInfo, 
						        &piProcInfo))
					//			AfxMessageBox("Excel is running");
							delete lpsz;

							//path = "c:\\Windows\\Notepad.exe " + strFilePath;
							//_execl(path, path, strFilePath , NULL, NULL);
						}
					}
					return TRUE;
				}
				return TRUE;
			}
			return FALSE;
		}
		return FALSE;
	}
	else
	{
		AfxMessageBox("You have not a samthing save");
		return FALSE;
	}
}

DWORD CObservate::PosCal(DWORD m, DWORD s, DWORD v)
{
	return (m*(m_SeriaCount)+s)*(m_InSeriaCount)+v;
}

void CObservate::Clear()
{
	m_ValList.RemoveAll();
	m_ValList.FreeExtra();
	Initialise();
	m_IsSaved = FALSE;
}

void CObservate::SetOperator()
{
	COperatorDlg dlg(this, NULL);
	dlg.DoModal();
}

void CObservate::SetComment()
{
	CCommentDlg dlg(this, NULL);
	dlg.DoModal();
}

void CObservate::SetMeter(CString name)
{
	m_Meter = name;
}

void CObservate::Serialize(CArchive & ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		ar<<m_Operator;
		ar<<m_Comment;
		ar<<m_Meter;
		ar<<m_RealSize;
		ar<<m_MsrType;
		ar<<m_MsrTime;

		ar<<(DWORD)m_MsrCount;
		ar<<(DWORD)m_MsrDelay;

		ar<<(DWORD)m_SeriaCount;
		ar<<(DWORD)m_SeriaDelay;

		ar<<(DWORD)m_InSeriaCount;
		ar<<(DWORD)m_InSeriaDelay;

		m_timestapms.Serialize(ar);
		m_ValList.Serialize(ar);
	}
	else
	{
		// TODO: add loading code here
		ar>>m_Operator;
		ar>>m_Comment;
		ar>>m_Meter;
		ar>>m_RealSize;
		ar>>m_MsrType;
		ar>>m_MsrTime;

		ar>>(DWORD)m_MsrCount;
		ar>>(DWORD)m_MsrDelay;

		ar>>(DWORD)m_SeriaCount;
		ar>>(DWORD)m_SeriaDelay;

		ar>>(DWORD)m_InSeriaCount;
		ar>>(DWORD)m_InSeriaDelay;

		m_timestapms.SetSize(m_MsrCount * m_SeriaCount * m_InSeriaCount);
		m_timestapms.Serialize(ar);

		m_ValList.SetSize(m_MsrCount*m_SeriaCount*m_InSeriaCount);
		m_ValList.Serialize(ar);
	}
}


void CObservate::ShowValInGraph(unsigned int pos, bool active)
{
	DWORD max_pos = m_pGraphic->GetVolume();

	if(pos <= max_pos)
	{
		if(m_pGraphic->DrawItm(pos, m_ValList[pos], active))
		{
			if(pos != NULL)
			{
				Redraw(0, pos, 0);
				//Redraw(pos+1, max_pos, 0);
			}
		}
	}	
	else
	{
		m_pGraphic->DrawItm(max_pos, m_ValList[pos], active);
		if(pos != NULL)
			Redraw(0, max_pos, pos - max_pos);
	}
}

void CObservate::Redraw(UINT NumFrom, UINT NumTo, UINT Move)
{
	m_pGraphic->Erase(NumFrom, NumTo);

	for(DWORD pos = NumFrom; pos < NumTo; pos++)
	{
		if(m_pGraphic->GetVolume() > m_ValList.GetSize())
		{
			if(pos < m_ValList.GetSize())
				m_pGraphic->DrawItm(pos, m_ValList[pos + Move], FALSE);
		}
		else
			m_pGraphic->DrawItm(pos, m_ValList[pos + Move], FALSE);
	}
}


void CObservate::SetMsrType(CString type)
{
	m_MsrType = type;

	if(m_MsrType[0] == 'm')
		m_DecKoef = 3;
	if(m_MsrType[0] == 'k')
		m_DecKoef = -3;
	if(m_MsrType[0] == 'M')
		m_DecKoef = -6;
/*
	if(m_MsrType[0] == "p")
		m_DecKoef = 12;
	if(m_MsrType[0] == "n")
		m_DecKoef = 9;
	if(m_MsrType[0] == "m"&&m_MsrType[1] == "k")
		m_DecKoef = 6;
*/
	if(m_MsrType[0] == 'm')
		m_DecKoef = 3;
/*
	if(m_MsrType[0] == "c")
		m_DecKoef = 2;

	if(m_MsrType[0] == "d")
		m_DecKoef = 1;
	if(m_MsrType[0] == "d"&&m_MsrType[1] == "a")
		m_DecKoef = -1;
	if(m_MsrType[0] == "h")
		m_DecKoef = -2;
*/
	if(m_MsrType[0] == 'k')
		m_DecKoef = -3;
	if(m_MsrType[0] == 'M')
		m_DecKoef = -6;
/*	if(m_MsrType[0] == "G")
		m_DecKoef = -9;
	if(m_MsrType[0] == "T")
		m_DecKoef = -12;
	if(m_MsrType[0] == "P")
		m_DecKoef = -15;
*/
}

CString CObservate::GetMsrType()
{
	return m_MsrType;
}

void CObservate::SetMsrTime(CTime time)
{
	m_MsrTime = time;
}

DWORD CObservate::GetContinue()
{
	DWORD cont = (m_InSeriaCount-1) * m_InSeriaDelay;
	cont = cont * m_SeriaCount;
	cont = cont + (m_SeriaCount-1) * m_SeriaDelay;
	cont = cont * m_MsrCount;
	cont = cont + (m_MsrCount-1) * m_MsrDelay;
	return cont;
}

void CObservate::WriteToFile(CStdioFile * pFile)
{
	pFile->SeekToEnd();
				
	char buffer[128] = { 0 };
	CTime time = CTime::GetCurrentTime();
//Begin Caption				
	pFile->WriteString("\"");
	pFile->WriteString(time.Format( "%d %B, %Y" ));
	pFile->WriteString("\"");

	pFile->WriteString("\n\"Operator: ");
	pFile->WriteString(m_Operator);
	pFile->WriteString("\"");

	pFile->WriteString("\n\"Comment: ");
	pFile->WriteString(m_Comment);
	pFile->WriteString("\"");
				
	pFile->WriteString("\n\"Meter: ");
	pFile->WriteString(m_Meter);
	pFile->WriteString("\"");

	pFile->WriteString("\n\"Total was maked ");
	pFile->WriteString(_itoa(m_RealSize, buffer, 10));
	pFile->WriteString(" taking.\"\n\n");

	/////////////////
//End Caption
//Begin Values record
	DWORD pos = NULL;

	for(DWORD m = 0; m < m_MsrCount; m++)
	{
		for(DWORD s = 0; s < m_SeriaCount; s++)
		{
			ZeroMemory(buffer, 128);
			pFile->WriteString("\"Measure:");
			pFile->WriteString(_itoa(m+1, buffer, 10));
			pFile->WriteString(" - ");
					
			ZeroMemory(buffer, 128);
			pFile->WriteString("Seria:");
			pFile->WriteString(_itoa(s+1, buffer, 10));
			pFile->WriteString("\"");
				
			for(DWORD v = 0; v < m_InSeriaCount; v++)
			{
				pos = (m*m_SeriaCount+s)*m_InSeriaCount+v;
				if(pos > m_RealSize)
				{
					//m_ValList[pos] = NULL;
					ZeroMemory(buffer, 128);
					pFile->WriteString("\n\"Was successeful maked ");
					pFile->WriteString(_itoa(m, buffer, 10));
					pFile->WriteString(" measures.\"\n");

					pFile->WriteString("\n\"<<< End >>>\"\n");
					pFile->Close();
					m_IsSaved = TRUE;
					return;
				}

				auto ms = std::chrono::milliseconds(m_timestapms[pos]);
				std::time_t seconds_since_epoch = std::chrono::duration_cast<std::chrono::seconds>(ms).count();
				auto fractional_seconds = ms.count() % 1000;
				auto fractional_ms = ms.count() - seconds_since_epoch * 1000;
				std::stringstream ss;
				ss << std::ctime(&seconds_since_epoch) << " " << fractional_seconds << "." << fractional_ms;
				pFile->WriteString("\t");
				pFile->WriteString(ss.str().c_str());

				auto timestamp = std::to_string(m_timestapms[pos]);
				pFile->WriteString("\t");
				pFile->WriteString(timestamp.c_str());

				ZeroMemory(buffer, 128);
				_gcvt( m_ValList[pos], 10, buffer );
				for(DWORD p = 0; p < sizeof(buffer); p++)
				{
					if(buffer[p] == '.')
					{
						buffer[p] = ',';
						p = sizeof(buffer);
					}
				}

				pFile->WriteString("\t");
				pFile->WriteString(buffer);
				pFile->WriteString("\t");
				pFile->WriteString(m_MsrType);
				pFile->WriteString("\n");
			}

		}
	}
	pFile->WriteString("\n\"<<< End >>>\"");
//End Values record
	pFile->Close();
	m_IsSaved = TRUE;

}
/*
				for(int i = 0; i < m_MsrCount; i++)
				{
					file.WriteString("Measure: ");
					file.WriteString(_itoa_s(i+1, buffer, 10));
					file.WriteString("      ");
				}
				
				file.WriteString("\n");
				
				int s;
				for(s = 0; s < m_SeriaCount; s++)
				{
					for(int i = 0; i < m_MsrCount; i++)
					{
						file.WriteString("Seria: ");
						file.WriteString(_itoa_s(s+1, buffer, 10));
						file.WriteString("        ");
					}
					file.WriteString("\n");
					for(int k = 0; k < m_InSeriaCount; k++)
					{
						for(int l = 0; l < m_MsrCount; l++)
						{
							pos = (l*(m_SeriaCount)+s)*(m_InSeriaCount)+k;
							if(pos > m_RealSize)
							{
								file.WriteString("\nWas successeful maked ");
								file.WriteString(_itoa_s(m, buffer, 10));
								file.WriteString(" measures.\n");
								//m_ValList[pos] = NULL;
								file.WriteString("\n<<< End >>>\n");
								file.Close();
								m_IsSaved = TRUE;
								return TRUE;
							}
							_gcvt( m_ValList[pos], 7, buffer );
//							int a, b;
//							buffer = fcvt(m_ValList[pos], 5, &a, &b);

							file.WriteString(buffer);
							file.WriteString("           ");
						}
						file.WriteString("\n");
					
					}
				}
				*/

