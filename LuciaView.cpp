// LuciaView.cpp : implementation of the CLuciaView class
//
#include "stdafx.h"
#include "Lucia.h"

#include "LuciaDoc.h"
#include "LuciaView.h"

#include "OperatorDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

UINT ExMeasure(LPVOID WinObjPtr);
/////////////////////////////////////////////////////////////////////////////
// CLuciaView
IMPLEMENT_DYNCREATE(CLuciaView, CFormView)

BEGIN_MESSAGE_MAP(CLuciaView, CFormView)
	//{{AFX_MSG_MAP(CLuciaView)
	ON_COMMAND(ID_BREAK_MEASURING, OnBreak)
	ON_COMMAND(ID_START_STOP_MSR, OnStartStopMsr)
	ON_NOTIFY(TVN_SELCHANGED, IDC_MEASURE_TREE, OnSelchangedMeasureTree)
	ON_NOTIFY(TVN_SELCHANGING, IDC_MEASURE_TREE, OnSelchangingMeasureTree)
	ON_NOTIFY(TVN_DELETEITEM, IDC_MEASURE_TREE, OnDeleteitemMeasureTree)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLuciaView construction/destruction

CLuciaView::CLuciaView()
	: CFormView(CLuciaView::IDD)
{
	//{{AFX_DATA_INIT(CLuciaView)
	m_ElapsedTime = _T("00:00:00");
	//}}AFX_DATA_INIT
	m_IsContinue = TRUE;
	m_ActivePos = NULL;
	m_DelTree = FALSE;
	m_CurPos = NULL;
}

CLuciaView::~CLuciaView()
{
}

void CLuciaView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLuciaView)
	DDX_Control(pDX, IDC_MEASURE_TREE, m_MsrTree);
	DDX_Control(pDX, IDC_GRAPH_FRAME, m_GraphFrame);
	DDX_Control(pDX, IDC_PROSESS, m_Progress);
	DDX_Text(pDX, IDC_ELAPSED_TIME, m_ElapsedTime);
	//}}AFX_DATA_MAP
}

BOOL CLuciaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CFormView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLuciaView printing

BOOL CLuciaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
//	pInfo->SetMaxPage(5);
	return DoPreparePrinting(pInfo);
}

void CLuciaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLuciaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLuciaView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	/*

	if(GetDocument()->m_pObser->m_ValList.GetSize())
	{
		const UINT x = 20;
		const UINT y = 50;
		CString str = _T("");
		char buffer[10]; 

//Title page
		if(pInfo->m_nCurPage == 1)
		{
			str = "";
			_itoa(pInfo->m_nCurPage, buffer, 10);
			str += buffer;
			pDC->TextOut(pInfo->m_rectDraw.BottomRight().x/2, 10, str , str.GetLength());

			str = ConstructCaption();
			pDC->TextOut(x, y, str, str.GetLength());
	
			str	= "Operator: ";
			str += GetDocument()->m_pObser->m_Operator;
			pDC->TextOut(x, 2*y, str, str.GetLength());

			str = "Comment: ";
			str += GetDocument()->m_pObser->m_Comment;
			pDC->TextOut(x, 3*y, str, str.GetLength());
			str = "Total was maked ";
			_itoa(GetDocument()->m_pObser->m_RealSize, buffer, 10);
			str += buffer;
			str += " takes"; 
			pDC->TextOut(x, 4*y, str, str.GetLength());
	
			m_CurM = NULL;
		//	m_CurS = NULL;
		//	m_CurV = NULL;
			pInfo->m_nCurPage++;
			pInfo->SetMaxPage(pInfo->m_nCurPage);
			return;

		}

		UINT curY = 5*y;
		int pos = 0;

		float min_val = GetDocument()->m_pObser->m_ValList[0];
		float max_val = GetDocument()->m_pObser->m_ValList[0];
		short par = 0;

		for(int i = 1; i < GetDocument()->m_pObser->m_ValList.GetSize(); i++)
		{
			if(GetDocument()->m_pObser->m_ValList[i] > max_val)
				max_val = GetDocument()->m_pObser->m_ValList[i];

			if(GetDocument()->m_pObser->m_ValList[i] < min_val)
				min_val = GetDocument()->m_pObser->m_ValList[i];

			if(min_val == max_val)
				par = (pInfo->m_rectDraw.Width() - x - 550)/min_val;
			else
				par = (pInfo->m_rectDraw.Width() - x - 550)/(max_val-min_val);
		}

		//draw ox axe
		pDC->MoveTo(x + 495, curY);
		pDC->LineTo(x + 495, curY+(y+50)*GetDocument()->m_pObser->m_SeriaCount*GetDocument()->m_pObser->m_InSeriaCount);


		for(int m = m_CurM; m < GetDocument()->m_pObser->m_MsrCount; m++)
		{
			if((curY + y*GetDocument()->m_pObser->m_SeriaCount*GetDocument()->m_pObser->m_InSeriaCount) > pInfo->m_rectDraw.BottomRight().y)
			{
			//	m_CurV = v;
			//	m_CurS = s;
				m_CurM = m;
				pInfo->m_nCurPage++;
				pInfo->SetMaxPage(pInfo->m_nCurPage);
				return;
			}

			str = "";
			_itoa(pInfo->m_nCurPage, buffer, 10);
			str += buffer;
//			pDC->TextOut(x, curY+50, str , str.GetLength());
			pDC->TextOut(pInfo->m_rectDraw.BottomRight().x/2, 10, str , str.GetLength());

			str = "Measure ";
			_itoa(m+1, buffer, 10);
			str += buffer;
			pDC->TextOut(x, curY, str, str.GetLength());
			for(int s = m_CurS; s < GetDocument()->m_pObser->m_SeriaCount; s++)
			{
				curY += 50;
				str = "Seria ";
				_itoa(s+1, buffer, 10);
				str += buffer;
				pDC->TextOut(2*x, curY, str, str.GetLength());
				for(int v = m_CurV; v < GetDocument()->m_pObser->m_InSeriaCount; v++)
				{
					curY += 50;
					pos = GetDocument()->m_pObser->m_InSeriaCount*(m*(GetDocument()->m_pObser->m_SeriaCount)+s)+v;
					//float!!!!
					_itoa(GetDocument()->m_pObser->m_ValList[pos], buffer, 10);
					str = buffer;
					str += " ";
					str += GetDocument()->m_pObser->GetMsrType();
					pDC->TextOut(3*x, curY, str, str.GetLength());
				
					pDC->MoveTo(x + 500, curY+25);
					CPen* oldPen;
					CPen newPen;
					newPen.CreatePen(PS_SOLID, 3, RGB(0,0,0));
					oldPen = (CPen*)pDC->SelectObject(&newPen);
					pDC->LineTo((x+500+(GetDocument()->m_pObser->m_ValList[pos]-min_val)*par), curY+25);
					pDC->SelectObject(oldPen);
					newPen.DeleteObject();
				}
			}
			curY += 50;
		}
	
		//str = "*END*";
	}
	*/
}

/////////////////////////////////////////////////////////////////////////////
// CLuciaView diagnostics

#ifdef _DEBUG
void CLuciaView::AssertValid() const
{
	CFormView::AssertValid();
}

void CLuciaView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CLuciaDoc* CLuciaView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLuciaDoc)));
	return (CLuciaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLuciaView message handlers

void CLuciaView::OnDraw(CDC* pDC) 
{
	if(GetDocument()->m_pObser->m_ValList.GetSize())
	{
		GetDocument()->m_pObser->m_pGraphic->DrawAxisY();
		GetDocument()->m_pObser->m_pGraphic->DrawAxisX();

		GetDocument()->m_pObser->Redraw(0, GetDocument()->m_pObser->m_pGraphic->GetVolume(), 0);

		HTREEITEM hSelItm;
		hSelItm = m_MsrTree.GetSelectedItem( );
		if(!m_MsrTree.ItemHasChildren(hSelItm))
		{
			m_ActivePos = m_MsrTree.GetItemData(hSelItm);
			GetDocument()->m_pObser->ShowValInGraph(m_ActivePos, TRUE);
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// CLuciaView commands

void CLuciaView::OnBreak() 
{
	if(MessageBox( "Are You realy want break Measuring?", "Warning", MB_YESNO) == IDYES)
	{
		m_IsContinue = FALSE;
		m_pThread->ResumeThread();

		CMenu * m_pMainMenu;
		m_pMainMenu = GetParentFrame()->GetMenu();

		m_pMainMenu->RemoveMenu(ID_BREAK_MEASURING, MF_BYCOMMAND); 
		m_pMainMenu->ModifyMenu(ID_START_STOP_MSR, MF_BYCOMMAND|MF_STRING, ID_START_STOP_MSR, "&Start" );
		GetParentFrame()->DrawMenuBar();

		MessageBox("Break Measure","Info");
	}
}

UINT ExMeasure(LPVOID WinObjPtr)
{
	CLuciaView* ptr = (CLuciaView*)WinObjPtr;
	if (ptr == nullptr)
	{
		return -1;
	}

	DWORD pos = 0;
	HTREEITEM hTreeItm[2];
	CObservate* pObs = ptr->GetDocument()->m_pObser;
	if (pObs == nullptr)
	{
		return -1;
	}

	pObs->m_pGraphic->Create((CStatic*)ptr->m_GraphFrame.FromHandle(ptr->m_GraphFrame));

	DWORD RealSize = 0;
	DWORD delay = 0;
	for(DWORD m = 0; m < pObs->m_MsrCount; m++)
	{
		hTreeItm[0] = pObs->ShowMsrInTree(&ptr->m_MsrTree, m);
		for(DWORD s = 0; s < pObs->m_SeriaCount; s++)
		{
			hTreeItm[1] = pObs->ShowSeriaInTree(&ptr->m_MsrTree, s, hTreeItm[0]);
			for (DWORD v = 0; v < pObs->m_InSeriaCount; v++)
			{
				pos = pObs->m_InSeriaCount * (m * (pObs->m_SeriaCount) + s) + v;

				pObs->m_timestapms.InsertAt(pos, std::chrono::system_clock::now().time_since_epoch().count());

				pObs->m_ValList.InsertAt(pos, ptr->GetDocument()->m_pMeter->GetVal());

				pObs->ShowValInTree(&ptr->m_MsrTree, pos, hTreeItm[1]);

				pObs->ShowValInGraph(pos, TRUE);
				if (pos)
				{
					pObs->ShowValInGraph(pos - 1, FALSE);
				}

				if(!ptr->m_IsContinue)
				{
					pObs->m_RealSize = RealSize;
					UINT stat = 0;
//Menu modify???
					ptr->GetDocument()->m_pMeter->Initialise(FALSE);
					ptr->KillTimer(1);
//					pObs->m_RealSize = RealSize;
				
					ptr->GetDocument()->SetModifiedFlag(TRUE);

					AfxEndThread(stat);
				}

				ptr->m_Progress.StepIt();
			
				RealSize++;

				::Sleep(pObs->m_InSeriaDelay);
			}
			ptr->m_MsrTree.Expand(hTreeItm[1], TVE_EXPAND);
			::Sleep(pObs->m_SeriaDelay);
		}
		ptr->m_MsrTree.Expand(hTreeItm[0], TVE_EXPAND);
		::Sleep(pObs->m_MsrDelay);
	}
	ptr->InvalidateRect(NULL, TRUE);

	pObs->m_RealSize = RealSize;

	ptr->GetDocument()->SetModifiedFlag(TRUE);
	ptr->MessageBox("Measuring is complete", "Info" );

	ptr->GetDocument()->m_pMeter->Initialise(FALSE);
/*
	CMenu* m_pMainMenu;
	m_pMainMenu = ptr->GetParentFrame()->GetMenu();
	m_pMainMenu->ModifyMenu(ID_START_STOP_MSR, MF_BYCOMMAND|MF_STRING, ID_START_STOP_MSR, "&Start" );
	ptr->GetParentFrame()->DrawMenuBar();
*/
	ptr->KillTimer(1);
	return 0;
}
/*
void CLuciaView::OnFileClose() 
{
	GetDocument()->DeleteContents();
	OnUpdate(NULL,NULL,NULL);
	GetDocument()->OnNewDocument();
	
}
*/
void CLuciaView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if(m_MsrTree.GetCount() != NULL)
		m_MsrTree.DeleteAllItems();

	m_DelTree = FALSE;

	m_ElapsedTime.Format("%i:%i:%i", 0, 0, 0);

	UpdateData(FALSE);

	InvalidateRect(NULL, TRUE);

	m_Progress.SetPos(0);

	CObservate* pObs = GetDocument()->m_pObser;
	
	if(pObs->m_ValList.GetSize())
	{
		m_Progress.SetRange(0, pObs->m_MsrCount*pObs->m_SeriaCount*pObs->m_InSeriaCount);
		m_Progress.SetStep(1);
		m_Progress.SetPos(0);


		unsigned int pos = NULL;
		HTREEITEM hTreeItm[2];

		pObs->m_pGraphic->Create((CStatic*)m_GraphFrame.FromHandle(m_GraphFrame));
//		GetDocument()->m_pObser->Redraw(0, GetDocument()->m_pObser->m_pGraphic->GetVolume(), 0);
		pObs->m_pGraphic->SetCellW(pObs->m_ValList.GetSize());
//		GetDocument()->m_pObser->m_pGraphic->SetCaption(ConstructCaption());
		pObs->m_pGraphic->SetYType(pObs->GetMsrType());

		for(unsigned char m = 0; m < pObs->m_MsrCount; m++)
		{
			hTreeItm[0] = pObs->ShowMsrInTree(&m_MsrTree, m);
			for(unsigned char s = 0; s < pObs->m_SeriaCount; s++)
			{
				hTreeItm[1] = pObs->ShowSeriaInTree(&m_MsrTree, s, hTreeItm[0]);
				for(unsigned char v = 0; v < pObs->m_InSeriaCount; v++)
				{
					pos = pObs->m_InSeriaCount*(m*(pObs->m_SeriaCount)+s)+v;
					pObs->ShowValInTree(&m_MsrTree, pos, hTreeItm[1]);
					pObs->ShowValInGraph(pos, FALSE);
					m_Progress.StepIt();
				}
				m_MsrTree.Expand(hTreeItm[1], TVE_EXPAND);
			}
			m_MsrTree.Expand(hTreeItm[0], TVE_EXPAND);
		}
//cintinue
		m_TimeElapsed = pObs->GetContinue();

		DWORD cont = m_TimeElapsed;
		DWORD rem[3] = { 0 };

		rem[0] = cont/(60 * 60 * 1000);
	
		cont = cont - rem[0]*(60 * 60 * 1000);
		rem[1] = cont/(60 * 1000);
	
		rem[2] = cont - (60 * 1000)*rem[1];

		m_ElapsedTime.Format("%i:%i:%i", rem[0], rem[1], rem[2]);

		UpdateData(FALSE);

		InvalidateRect(NULL, TRUE);
	}
}

void CLuciaView::OnSelchangedMeasureTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(!m_DelTree)
	{
		HTREEITEM hSelItm;

		hSelItm = m_MsrTree.GetSelectedItem( );
		if(!m_MsrTree.ItemHasChildren(hSelItm))
		{
			m_ActivePos = m_MsrTree.GetItemData(hSelItm);
			GetDocument()->m_pObser->ShowValInGraph(m_ActivePos, TRUE);
//			InvalidateRect(NULL, TRUE);
		}
	}
	*pResult = 0;
}

void CLuciaView::OnSelchangingMeasureTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	if(!m_DelTree)
	{
		HTREEITEM hSelItm;

		hSelItm = m_MsrTree.GetSelectedItem( );
		if(!m_MsrTree.ItemHasChildren(hSelItm))
		{
			m_ActivePos = m_MsrTree.GetItemData(hSelItm);
			GetDocument()->m_pObser->ShowValInGraph(m_ActivePos, FALSE);
//			InvalidateRect(NULL, TRUE);
		}	
	}
	*pResult = 0;
}

void CLuciaView::OnDeleteitemMeasureTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	m_DelTree = TRUE;
	*pResult = 0;
}

CString CLuciaView::ConstructCaption()
{
	CString caption = "Date: ";
	caption += GetDocument()->m_pObser->m_MsrTime.Format( "%d %B, %Y" );
	caption += " Meter: ";
	caption += GetDocument()->m_pObser->m_Meter;
	return caption;
}

void CLuciaView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	DWORD cont = m_TimeElapsed--;
	unsigned char rem[3];

	rem[0] = cont/(60 * 60 * 1000);
	
	cont = cont - rem[0]*(60 * 60 * 1000);
	rem[1] = cont/(60 * 1000);
	
	rem[2] = cont - (60 * 1000)*rem[1];

	m_ElapsedTime.Format("%i:%i:%i", rem[0], rem[1], rem[2]);

	UpdateData(FALSE);

	if(rem[0] == 0 && rem[1] == 0 && rem[2] <= 100)
	{
		CMenu* m_pMainMenu;
		m_pMainMenu = GetParentFrame()->GetMenu();
		m_pMainMenu->ModifyMenu(ID_START_STOP_MSR, MF_BYCOMMAND|MF_STRING, ID_START_STOP_MSR, "&Start" );
		GetParentFrame()->DrawMenuBar();
		KillTimer(1);
		m_ElapsedTime.Format("%i:%i:%i", 0,0,0);
	}

	CFormView::OnTimer(nIDEvent);
}

void CLuciaView::OnStartStopMsr() 
{
	CMenu * m_pMainMenu;
	CString str = _T("");
	m_pMainMenu = GetParentFrame()->GetMenu();
	m_pMainMenu->GetMenuString(ID_START_STOP_MSR, str, MF_BYCOMMAND);

	CObservate* pObs = GetDocument()->m_pObser;

	if(	str == "&Start")
	{
/*
		m_pMainMenu->ModifyMenu(ID_START_STOP_MSR, MF_BYCOMMAND|MF_STRING, ID_START_STOP_MSR, "&Stop" );
		GetParentFrame()->DrawMenuBar();		
*/
		if(MessageBox( "Are You realy want start Measuring?", "Warning", MB_YESNO) == IDYES)
		{
			if(pObs->m_ValList.GetSize() != NULL)
			{
				if(!pObs->m_IsSaved)
				{
					unsigned int answer;
					answer = MessageBox("You now have a non saved Measure!\n Do You want save old measure befor to start new?", "Warning",  MB_YESNOCANCEL|MB_ICONQUESTION);
					switch(answer)
					{
						case IDCANCEL:
							return;
						break;
						case IDYES:
							if(pObs->Record(FALSE))
							{
								m_MsrTree.DeleteAllItems();
								m_DelTree = FALSE;
								pObs->Clear();
							}
							else
							{
								MessageBox("Recording is failed", "Error");
								return;
							}
						break;
						case IDNO:
							m_MsrTree.DeleteAllItems();
							m_DelTree = FALSE;
							pObs->Clear();
						break;
					}
				}
			}
			if(GetDocument()->m_pMeter->ConnectExp())
			{
				MessageBox( "Connection is success", "Info" );
				if(!GetDocument()->m_pMeter->Initialise(TRUE))
				{
					MessageBox("Can not initialise Meter", "Error" );
					return;
				}

				if(!pObs->Initialise())
				{
					MessageBox("Can not initialise Measure", "Error" );
					return;
				}
			
				pObs->SetMeter(GetDocument()->m_pMeter->GetName());
				pObs->SetMsrType(GetDocument()->m_pMeter->GetMsrType());
				pObs->SetMsrTime(CTime::GetCurrentTime());
		
				m_Progress.SetRange(0, pObs->m_MsrCount*pObs->m_SeriaCount*pObs->m_InSeriaCount);
				m_Progress.SetStep(1);
				m_Progress.SetPos(0);
//run Measure Thread
				m_IsContinue = TRUE;
	
				pObs->m_pGraphic->Create((CStatic*)m_GraphFrame.FromHandle(m_GraphFrame));
				pObs->m_pGraphic->SetCellW(pObs->m_ValList.GetSize());
				pObs->m_pGraphic->SetYType(pObs->GetMsrType());
				//pObs->m_pGraphic->SetCaption(ConstructCaption());

		m_pMainMenu->ModifyMenu(ID_START_STOP_MSR, MF_BYCOMMAND|MF_STRING, ID_START_STOP_MSR, "&Stop" );
		GetParentFrame()->DrawMenuBar();		


				m_TimeElapsed = pObs->GetContinue() + 3000;
				SetTimer(1, 1, NULL);

				m_pThread = AfxBeginThread(ExMeasure, this, THREAD_PRIORITY_HIGHEST);
			}
		}
	}
	if(str == "&Stop")
	{
		m_pThread->SuspendThread();		
		KillTimer(1);
		
		m_pMainMenu->ModifyMenu(ID_START_STOP_MSR, MF_BYCOMMAND|MF_STRING, ID_START_STOP_MSR, "&Continue" );

		m_pMainMenu->AppendMenu(MF_ENABLED|MF_STRING, ID_BREAK_MEASURING, "&Break");
		MessageBox("Measure is stopped","Info");
		GetParentFrame()->DrawMenuBar();
	}
	if(str == "&Continue")
	{
		m_pThread->ResumeThread();
		SetTimer(1, 1, NULL);

		m_pMainMenu->ModifyMenu(ID_START_STOP_MSR, MF_BYCOMMAND|MF_STRING, ID_START_STOP_MSR, "&Stop" );
		m_pMainMenu->RemoveMenu(ID_BREAK_MEASURING, MF_BYCOMMAND);
		GetParentFrame()->DrawMenuBar();
	}
}

