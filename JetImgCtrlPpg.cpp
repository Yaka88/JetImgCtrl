// JetImgCtrlPpg.cpp : Implementation of the CJetImgCtrlPropPage property page class.
// �ļ���	: JetImgCtrlPpg.h
// ������Ŀ	: ������Ŀ
// �汾��	: 1.0
// ����		: ��ʾ�ؼ�����ҳʵ���ļ�
// ��������	: 2001/02/01
// ����		: yaka
// ��ע 		: 
#include "stdafx.h"
#include "JetImgCtrl.h"
#include "JetImgCtrlPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CJetImgCtrlPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CJetImgCtrlPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CJetImgCtrlPropPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CJetImgCtrlPropPage, "JETIMGCTRL.JetImgCtrlPropPage.1",
	0x969fb304, 0x8193, 0x4adb, 0x9b, 0x9e, 0xd4, 0x11, 0x87, 0x1b, 0xe6, 0xad)


/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlPropPage::CJetImgCtrlPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CJetImgCtrlPropPage

BOOL CJetImgCtrlPropPage::CJetImgCtrlPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_JETIMGCTRL_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlPropPage::CJetImgCtrlPropPage - Constructor
// ��������	: ����ҳ�๹��
// ����		: 
// ����ֵ	: 
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
CJetImgCtrlPropPage::CJetImgCtrlPropPage() :
	COlePropertyPage(IDD, IDS_JETIMGCTRL_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CJetImgCtrlPropPage)
	m_bMagnifer = FALSE;
	m_nCol = 0;
	m_nRow = 0;
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlPropPage::DoDataExchange - Moves data between page and properties
// ��������	: ����ҳ���ݽ���
// ����		: CDataExchange* pDX
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CJetImgCtrlPropPage)
	DDP_Check(pDX, IDC_Magnify, m_bMagnifer, _T("Magnify") );
	DDX_Check(pDX, IDC_Magnify, m_bMagnifer);
	DDP_Text(pDX, IDC_EDITCOL, m_nCol, _T("Col") );
	DDX_Text(pDX, IDC_EDITCOL, m_nCol);
	DDV_MinMaxInt(pDX, m_nCol, 1, 100);
	DDP_Text(pDX, IDC_EDITROW, m_nRow, _T("Row") );
	DDX_Text(pDX, IDC_EDITROW, m_nRow);
	DDV_MinMaxInt(pDX, m_nRow, 1, 100);
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlPropPage message handlers
