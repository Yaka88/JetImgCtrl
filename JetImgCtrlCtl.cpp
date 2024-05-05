// JetImgCtrlCtl.cpp : Implementation of the CJetImgCtrlCtrl ActiveX Control class.

// �ļ���	: JetImgCtrlCtl.h
// ������Ŀ	: ������Ŀ
// �汾��	: 1.0
// ����		: ��ʾ�ؼ�ʵ���ļ�
// ��������	: 2001/02/01
// ����		: yaka
// ��ע 		: 
#include "stdafx.h"
#include "JetImgCtrl.h"
#include "JetImgCtrlCtl.h"
#include "JetImgCtrlPpg.h"
#include "JetImgSeeApi.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern int g_nDrawState;
extern int g_nShowState;
extern CSize g_nMagOffset;
extern CSize g_nMagSize;
CEdit* g_pEdit = NULL;
CComboBox* g_pCombobox = NULL;
CListBox* g_pListbox = NULL;

IMPLEMENT_DYNCREATE(CJetImgCtrlCtrl, COleControl)
/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CJetImgCtrlCtrl, COleControl)
	//{{AFX_MSG_MAP(CJetImgCtrlCtrl)
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_CREATE()
	ON_WM_NCACTIVATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map
BEGIN_DISPATCH_MAP(CJetImgCtrlCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CJetImgCtrlCtrl)
	DISP_PROPERTY_NOTIFY(CJetImgCtrlCtrl, "OutLineColor", m_outLineColor, OnOutLineColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY(CJetImgCtrlCtrl, "ImgBackColor", m_imgBackColor, OnImgBackColorChanged, VT_COLOR)
	DISP_PROPERTY_NOTIFY(CJetImgCtrlCtrl, "Magnify", m_bMagnify, OnMagnifyChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CJetImgCtrlCtrl, "Col", m_nCol, OnColChanged, VT_I2)
	DISP_PROPERTY_NOTIFY(CJetImgCtrlCtrl, "Row", m_nRow, OnRowChanged, VT_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetMaxImg", SetMaxImg, VT_EMPTY, VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetDrawState", GetDrawState, VT_I2, VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetMaxImg", GetMaxImg, VT_I2, VTS_NONE)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetCurImgNum", GetCurImgNum, VT_I2, VTS_NONE)
	DISP_FUNCTION(CJetImgCtrlCtrl, "CoverImgFile", CoverImgFile, VT_I2, VTS_BSTR VTS_I4)
	DISP_FUNCTION(CJetImgCtrlCtrl, "AddImgFile", AddImgFile, VT_I2, VTS_BSTR VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "AddImgDib", AddImgDib, VT_I2, VTS_I4 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "CoverImgDib", CoverImgDib, VT_I2, VTS_I4 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetFocus", SetFocus, VT_I2, VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetFocus", GetFocus, VT_I2, VTS_NONE)
	DISP_FUNCTION(CJetImgCtrlCtrl, "ClearAllImg", ClearAllImg, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetReferPoint", SetReferPoint, VT_I2, VTS_I4 VTS_I4 VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetElementColor", SetElementColor, VT_I2, VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "ShowLine", ShowLine, VT_I2, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "ShowPoint", ShowPoint, VT_I2, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "ShowRect", ShowRect, VT_I2, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "ShowText", ShowText, VT_I2, VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BSTR VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetItemData", GetItemData, VT_I2, VTS_PI4 VTS_I2 VTS_I4 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetDrawPoint", GetDrawPoint, VT_I2, VTS_I4 VTS_PI4 VTS_PI4 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetDrawLine", GetDrawLine, VT_I2, VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetDrawRect", GetDrawRect, VT_I2, VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetMousePosition", GetMousePosition, VT_I2, VTS_I4 VTS_I4)
	DISP_FUNCTION(CJetImgCtrlCtrl, "DeleteElement", DeleteElement, VT_I2, VTS_I4 VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetItemData", SetItemData, VT_I2, VTS_I4 VTS_I2 VTS_I4 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "EnsureElementVisible", EnsureElementVisible, VT_I2, VTS_I4 VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetShowRuler", SetShowRuler, VT_I2, VTS_BOOL VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetShowState", SetShowState, VT_I2, VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetShowState", GetShowState, VT_I2, VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetDrawState", SetDrawState, VT_I2, VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "RefreshImg", RefreshImg, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetElementNum", GetElementNum, VT_I2, VTS_PI2 VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "GetDrawText", GetDrawText, VT_I2, VTS_I4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_PI4 VTS_BSTR VTS_PI2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "RotateImg", RotateImg, VT_I2, VTS_I2 VTS_R8 VTS_I2 VTS_BOOL VTS_BOOL)
	DISP_FUNCTION(CJetImgCtrlCtrl, "StretchImg", StretchImg, VT_I2, VTS_I2 VTS_R8 VTS_BOOL)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetShowRatio", SetShowRatio, VT_EMPTY, VTS_PR4 VTS_PR4)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetMagnifer", SetMagnifer, VT_EMPTY, VTS_BOOL VTS_I2 VTS_I2 VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetText", SetText, VT_EMPTY, VTS_BOOL VTS_I2 VTS_PVARIANT VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "SetTextNeedBack", SetTextNeedBack, VT_EMPTY, VTS_BOOL)
	DISP_FUNCTION(CJetImgCtrlCtrl, "PrintImg", PrintImg, VT_I2, VTS_I2 VTS_R4 VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "PrintImage", PrintImage, VT_I2, VTS_I2 VTS_I4 VTS_I4 VTS_I2 VTS_I2)
	DISP_FUNCTION(CJetImgCtrlCtrl, "RotateImage", RotateImage, VT_I2, VTS_I2 VTS_I2 VTS_I2)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CJetImgCtrlCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CJetImgCtrlCtrl, COleControl)
	//{{AFX_EVENT_MAP(CJetImgCtrlCtrl)
	EVENT_CUSTOM("ClickImg", FireClickImg, VTS_I4  VTS_I4)
	EVENT_CUSTOM("ElementGetFocus", FireElementGetFocus, VTS_I4  VTS_I2)
	EVENT_CUSTOM("ElementLoseFocus", FireElementLoseFocus, VTS_I4  VTS_I2)
	EVENT_CUSTOM("BeginModify", FireBeginModify, VTS_I4  VTS_I2)
	EVENT_CUSTOM("BeginDrawNew", FireBeginDrawNew, VTS_I2)
	EVENT_CUSTOM("EndDrawNew", FireEndDrawNew, VTS_I4  VTS_I2)
	EVENT_CUSTOM("EndModify", FireEndModify, VTS_I4  VTS_I2)
	EVENT_CUSTOM("OnDrawing", FireOnDrawing, VTS_I2)
	EVENT_CUSTOM("OnModifying", FireOnModifying, VTS_I4  VTS_I2)
	EVENT_CUSTOM("OnDraw", FireOnDraw, VTS_I4)
	EVENT_STOCK_DBLCLICK()
	//}}AFX_EVENT_MAP
END_EVENT_MAP()

/////////////////////////////////////////////////////////////////////////////
// Property pages
// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CJetImgCtrlCtrl, 2)
	PROPPAGEID(CJetImgCtrlPropPage::guid)
	PROPPAGEID(CLSID_CColorPropPage)
END_PROPPAGEIDS(CJetImgCtrlCtrl)

/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CJetImgCtrlCtrl, "JETIMGCTRL.JetImgCtrlCtrl.1",
	0xc51f7b20, 0x3d4a, 0x483e, 0xb6, 0x98, 0x4, 0xb2, 0x25, 0x31, 0x89, 0xd3)
/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CJetImgCtrlCtrl, _tlid, _wVerMajor, _wVerMinor)
/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DJetImgCtrl =
		{ 0x9991e755, 0x7afa, 0x4e3b, { 0x80, 0x56, 0xcf, 0x72, 0x3d, 0x97, 0x8f, 0x3f } };
const IID BASED_CODE IID_DJetImgCtrlEvents =
		{ 0xe9686592, 0x11f0, 0x41f2, { 0xbb, 0xcd, 0xe8, 0xd3, 0x3c, 0x8f, 0x92, 0x63 } };

/////////////////////////////////////////////////////////////////////////////
// Control type information
static const DWORD BASED_CODE _dwJetImgCtrlOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CJetImgCtrlCtrl, IDS_JETIMGCTRL, _dwJetImgCtrlOleMisc)
/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlCtrl::CJetImgCtrlCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CJetImgCtrlCtrl
#define SHOWIMG_CLASSNAME _T("SHOWIMG")

BOOL RegisterWindowClass()
{
    WNDCLASS wndcls;
    HINSTANCE hInst = AfxGetInstanceHandle();
    if (!(::GetClassInfo(hInst, SHOWIMG_CLASSNAME, &wndcls)))
    {
        // otherwise we need to register a new class
        wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
        wndcls.lpfnWndProc      = ::DefWindowProc;
        wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
        wndcls.hInstance        = hInst;
        wndcls.hIcon            = NULL;
        wndcls.hCursor          = NULL;
        wndcls.hbrBackground    = (HBRUSH)(COLOR_3DFACE);//COLOR_3DSHADOW
        wndcls.lpszMenuName     = NULL;
        wndcls.lpszClassName    = SHOWIMG_CLASSNAME;
        if (!AfxRegisterClass(&wndcls)) {//����ʹ��RegisterClass������DLL����ʱ�����ͷţ�
            AfxThrowResourceException();
            return FALSE;
        }
    }
    return TRUE;
}
BOOL CJetImgCtrlCtrl::CJetImgCtrlCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_JETIMGCTRL,
			IDB_JETIMGCTRL,
			afxRegApartmentThreading,
			_dwJetImgCtrlOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}

/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlCtrl::CJetImgCtrlCtrl - Constructor
// ��������	: ��ʼ���ؼ�
// ����		: 
// ����ֵ	: 
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
CJetImgCtrlCtrl::CJetImgCtrlCtrl()
{
	InitializeIIDs(&IID_DJetImgCtrl, &IID_DJetImgCtrlEvents);
/*	m_hHeap = HeapCreate(0,0,0);
	if(m_hHeap == NULL){
		AfxMessageBox("CSingleImg:�ڴ治��!");
		exit(-1);
	}*/
	RegisterWindowClass();
	m_pFocusImg = NULL;
	m_sizeLine.cy = m_sizeLine.cx = 0;
	m_iRectState = MOUSE_RECT_NULL;
	m_iLineState = MOUSE_LINE_NULL;
	m_iTextState = MOUSE_TEXT_NULL;
	m_iPointState = MOUSE_POINT_NULL;
	m_rtClientRect.SetRectEmpty();
	m_rtCurTotalRect.SetRectEmpty();

	m_rtTempRect.SetElementEmpty();
	m_liTempLine.SetElementEmpty();
	m_rtTempText.SetElementEmpty();
	m_rtTempPoint.SetElementEmpty();
	m_rtTempRect.SetFocus(TRUE);
	m_liTempLine.SetFocus(TRUE);
	m_rtTempText.SetFocus(TRUE);
	m_rtTempPoint.SetFocus(TRUE);
	m_prtDocRect = &m_rtTempRect;
	m_pliDocLine = &m_liTempLine;
	m_prtDocText = &m_rtTempText;
	m_prtDocPoint = &m_rtTempPoint;
	m_nLineFocus=m_nRectFocus=m_nTextFocus=m_nPointFocus=-1;
	m_rtCurShowRect.SetRectEmpty();
	m_nImgFocus = -1;
	m_ImgArray.RemoveAll();
	m_nMaxImg = -1;
//	m_bMagnify = FALSE;
}
/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlCtrl::~CJetImgCtrlCtrl - Destructor
// ��������	: �����ؼ�
// ����		: 
// ����ֵ	: 
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
CJetImgCtrlCtrl::~CJetImgCtrlCtrl()
{
	vClearVarible();
}
/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlCtrl::OnDraw - Drawing function
// ��������	: ˢ��ͼ��
// ����		: const CRect& p_Rect,BOOL bErase,CRect* p_ValidRect
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
inline void CJetImgCtrlCtrl::RefreshByParent(const CRect& p_Rect,BOOL bErase,CRect* p_ValidRect) 
{
	if(GetParent()->GetSafeHwnd() != NULL){
		CRect myRect = p_Rect;	
		ClientToScreen(myRect);
		GetParent()->ScreenToClient(myRect);
		::InvalidateRect(GetParent()->m_hWnd,&myRect,bErase);
		if(p_ValidRect)
			::ValidateRect(GetParent()->m_hWnd,p_ValidRect);
		GetParent()->UpdateWindow();
	}

}
// ��������	: ���ؼ�
// ����		: CDC* pdc,�豸������ const CRect& rcBounds, const CRect& rcInvalid
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{	
	FireOnDraw((long)pdc);
	GetScrollPosition(m_ScrollPoint);
	pdc->DrawEdge(m_rtClientRect, EDGE_SUNKEN, BF_RECT);
	for(int ii=0; ii<m_ImgArray.GetSize(); ii++)
		m_ImgArray.GetAt(ii)->ShowSingleImg(pdc,m_ScrollPoint.x,m_ScrollPoint.y);
	//add by yaka 20010509
	// DRAW Background
	CRect Recttemp;
	for (ii = m_ImgArray.GetSize(); ii < m_nMaxImg;ii++)
	{
		Recttemp = GetSingleTotalRect(ii);
//		pdc->FillRect(&Recttemp, &CBrush(m_imgBackColor));

	}
	//add end

	//���������֮������DRAGRECT��DRAGLINEʱ���ӣ�����Ϊ�������ShowSingleImg���Ѿ�����һ���ˡ�����DRAWRECT��DRAWLINE
	//��û�У�
	if(m_iRectState & DRAWRECT)
		vShowRectOrLine(RECT_SET);
	else if(m_iLineState & DRAWLINE)
		vShowRectOrLine(LINE_SET);
	else if(m_iTextState & DRAWTEXT)
		vShowRectOrLine(TEXT_SET);
	else if(m_iPointState & DRAWPOINT)
		vShowRectOrLine(POINT_SET);
}

/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlCtrl::DoPropExchange - Persistence support
// ��������	: �������ݽ���
// ����		: CPropExchange* pPX��������
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

void CJetImgCtrlCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	PX_Color(pPX,"OutLineColor",m_outLineColor,RGB(255,0,0));
	PX_Color(pPX,"ImgBackColor",m_imgBackColor,COLOR_3DFACE);
	PX_Bool(pPX,"Magnify",m_bMagnify,FALSE);
	PX_Short(pPX,"Col",m_nCol,1);
	PX_Short(pPX,"Row",m_nRow,1);
	COleControl::DoPropExchange(pPX);
}
/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlCtrl::OnResetState - Reset control to default state
void CJetImgCtrlCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange
}

// ��������	: ��ʾ���ڶԻ���
// ����		: 
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

void CJetImgCtrlCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_JETIMGCTRL);
	dlgAbout.DoModal();
}


// ��������	: ���һЩ�����ڴ�
// ����		: 
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

void CJetImgCtrlCtrl::vClearVarible()
{
	vClearElementAll();
	for(int i=0; i<m_ImgArray.GetSize(); i++)
	{
		delete m_ImgArray[i];
		m_ImgArray[i]=NULL;
	}
	m_pFocusImg = NULL;
	m_nImgFocus = -1;
	m_ImgArray.RemoveAll();
}


// ��������	: ����ĳ��ͼ������������ø�ͼ���������ʾ����
// ����		: short p_nIndexͼ������
// ����ֵ	: CRect ������ʾ����
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
CRect CJetImgCtrlCtrl::GetSingleTotalRect(int p_nIndex)
{
	//modify by yaka 20010416
	float tempx= 0,tempy = 0;
	short i;
	int left,top,right,bottom;
	int nx,ny;//��ʱ���������ת�������������λ�ã�
	nx = p_nIndex % m_nCol;			//λ�ڵ�nx�У�
	ny = (p_nIndex - nx) / m_nCol;	//λ�ڵ�ny�У�

	for (i = 0 ; i< nx; i++)
		tempx += m_aWidthRatio[i];
	for (i = 0 ; i< ny; i++)
		tempy += m_aHeightRatio[i];
	left = (int)(m_rtClientRect.Width() * tempx);
	right = left + (int)(m_rtClientRect.Width() * m_aWidthRatio[nx]);
	top = (int)(m_rtClientRect.Height() * tempy);
	bottom = top + (int)(m_rtClientRect.Height() * m_aHeightRatio[ny]);
	return CRect(left ,top ,right ,bottom);
	//modify end 
}
// ��������	: �������Ԫ��
// ����		: BOOL p_ClearState
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

void CJetImgCtrlCtrl::vClearElementAll(BOOL p_ClearState)
{
	vClearElement(RECT_SET,p_ClearState);
	vClearElement(LINE_SET,p_ClearState);
	vClearElement(POINT_SET,p_ClearState);
	vClearElement(TEXT_SET,p_ClearState);
}





// ��������	: ���һ������Ԫ�أ�
// ����		: int pa_iFlag,BOOL p_ClearState
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

void CJetImgCtrlCtrl::vClearElement(int pa_iFlag,BOOL p_ClearState)
{
	switch(pa_iFlag){
	case RECT_SET:
		if(p_ClearState)
			m_iRectState &= (~NEED_DRAWRECT);
		m_prtDocRect = &m_rtTempRect;
		m_prtDocRect->SetElementEmpty();
		m_rtViewRect.SetElementEmpty();
		m_nRectFocus = -1;
		break;
	case LINE_SET:
		if(p_ClearState)
			m_iLineState &= (~NEED_DRAWLINE);
		m_pliDocLine = &m_liTempLine;
		m_pliDocLine->SetElementEmpty();
		m_liViewLine.SetElementEmpty();
		m_nLineFocus = -1;
		break;
	case TEXT_SET:
		if(p_ClearState)
			m_iTextState &= (~NEED_DRAWTEXT);
		m_prtDocText = &m_rtTempText;
		m_prtDocText->SetElementEmpty();
		m_rtViewText.SetElementEmpty();
		m_nTextFocus = -1;
	break;
	case POINT_SET:
		if(p_ClearState)
			m_iPointState &= (~NEED_DRAWPOINT);
		m_prtDocPoint = &m_rtTempPoint;
		m_prtDocPoint->SetElementEmpty();
		m_rtViewPoint.SetElementEmpty();
		m_nPointFocus = -1;
	break;
	}
}
// ��������	: ��ȡ������λ��
// ����		: CPoint& p_ScrollPoint������λ��
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::GetScrollPosition(CPoint& p_ScrollPoint)
{
	p_ScrollPoint.x = GetScrollPos32(SB_HORZ);
	p_ScrollPoint.y = GetScrollPos32(SB_VERT);
}


// ��������	: ��ȡ������λ��
// ����		: int nBar, BOOL bGetTrackPos
// ����ֵ	: int λ��
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
int CJetImgCtrlCtrl::GetScrollPos32(int nBar, BOOL bGetTrackPos /* = FALSE */)
{
    SCROLLINFO si;
    si.cbSize = sizeof(SCROLLINFO);
    if (bGetTrackPos){
        if (GetScrollInfo(nBar, &si, SIF_TRACKPOS))
            return si.nTrackPos;
	}
    else {
        if (GetScrollInfo(nBar, &si, SIF_POS))
            return si.nPos;
	}
    return 0;
}
// ��������	: ���ù�����λ��
// ����		: int nBar, int nPos, BOOL bRedraw
// ����ֵ	: BOOL�Ƿ�ɹ�
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
BOOL CJetImgCtrlCtrl::SetScrollPos32(int nBar, int nPos, BOOL bRedraw /* = TRUE */)
{
    SCROLLINFO si;
    si.cbSize = sizeof(SCROLLINFO);
    si.fMask  = SIF_POS;
    si.nPos   = nPos;
    return SetScrollInfo(nBar, &si, bRedraw);
}
// ��������	: ��ʾԪ��
// ����		: CDrawElement& p_Element
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע
void CJetImgCtrlCtrl::vShowElement(CDrawElement& p_Element)
{
	CDC *m_pDC = GetDC();
	p_Element.ShowElement(m_rtCurShowRect,m_pDC);//ShowElement��һ������ָ���˻�ͼ�Ľ��ޣ�
	ReleaseDC(m_pDC);
}

//����ʵ��ѡȡ��Ĵ�С�������Ӧ����ʾ�Ĵ�С��p_x��p_y�ǹ���������Ե�ǰ��ʾ���򣩵�λ�ã�
inline void CJetImgCtrlCtrl::vGetViewElement(CDrawElement& p_Element,int p_x, int p_y)
{
	/*CRuntimeClass* pRunClass = NULL;
	pRunClass = p_Element.GetRuntimeClass();
	if(pRunClass != NULL)	AfxMessageBox(pRunClass->m_lpszClassName);*/
	p_Element.StretchElement(m_pFocusImg->m_fzoomx,m_pFocusImg->m_fzoomy);
	p_Element.OffsetElement(-p_x,-p_y);//�۳���������λ�ã�
	p_Element.OffsetElement(m_rtCurShowRect.left,m_rtCurShowRect.top);//�÷�ͼ��ʵ����ʾ���������������е�λ�ã�
	p_Element.NormalizeElement();
}

inline void CJetImgCtrlCtrl::vGetViewElement(CDrawElement* p_pElement,int p_x, int p_y)
{
	p_pElement->StretchElement(m_pFocusImg->m_fzoomx,m_pFocusImg->m_fzoomy);
	p_pElement->OffsetElement(-p_x,-p_y);//�۳���������λ�ã�
	p_pElement->OffsetElement(m_rtCurShowRect.left,m_rtCurShowRect.top);//�÷�ͼ��ʵ����ʾ���������������е�λ�ã�
	p_pElement->NormalizeElement();
}

void CJetImgCtrlCtrl::vShowRectOrLine(int pa_iState)
{
	switch(pa_iState){
	case RECT_SET:
		m_rtViewRect = *m_prtDocRect;
		vGetViewElement(m_rtViewRect,m_ScrollPoint.x,m_ScrollPoint.y);
		vShowElement(m_rtViewRect);
		break;
	case LINE_SET:
		m_liViewLine = *m_pliDocLine;
		vGetViewElement(m_liViewLine,m_ScrollPoint.x,m_ScrollPoint.y);
		vShowElement(m_liViewLine);
		break;
	case TEXT_SET:
		//add by yaka 20010420
		m_rtViewText = *m_prtDocText;
		vGetViewElement(m_rtViewText,m_ScrollPoint.x,m_ScrollPoint.y);
		vShowElement(m_rtViewText);
		//add end
		break;
	case POINT_SET:
		//add by yaka 20010428
		m_rtViewPoint = *m_prtDocPoint;
		vGetViewElement(m_rtViewPoint,m_ScrollPoint.x,m_ScrollPoint.y);
		vShowElement(m_rtViewPoint);
		//add end
		break;
	}
}
// ��������	: ���λ���Ƿ��ھ�����
// ����		: CPoint& point���ָ�룬CRect& pa_Rect����Ԫ��
// ����ֵ	: BOOL �Ƿ�ɹ�
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
inline BOOL CJetImgCtrlCtrl::bPointInRect(CPoint& pa_Point, CRect& pa_Rect)
{
	if((pa_Point.x<pa_Rect.right) && (pa_Point.x >= pa_Rect.left) && (pa_Point.y < pa_Rect.bottom) && (pa_Point.y >= pa_Rect.top))
		return TRUE;
	return FALSE;
}
// ��������	: ���λ���Ƿ���������
// ����		: CPoint& point���ָ�룬CMyLine& pa_Line����Ԫ��
// ����ֵ	: BOOL �Ƿ�ɹ�
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
inline BOOL CJetImgCtrlCtrl::bPointInLine(CPoint& pa_Point, CMyLine& pa_Line)
{
	CRect rect(pa_Line.m_Begin.x,pa_Line.m_Begin.y,pa_Line.m_End.x,pa_Line.m_End.y);
	rect.NormalizeRect();
	rect.InflateRect(6,6);
	return bPointInRect(pa_Point, rect);
}

// ��������	: ����p1���Ƿ���p2��ĸ�����ָ������
// ����		: CPoint& p1, CPoint& p2,�� int iFlagָ������
// ����ֵ	: BOOL �Ƿ�ɹ�
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
inline BOOL CJetImgCtrlCtrl::bPointNearAnother(CPoint& p1, CPoint& p2, int iFlag)
{
	if(iFlag==0){//ˮƽ����
		if( (p1.x<=(p2.x+6)) && (p1.x>=(p2.x-6)) && (p1.y<=(p2.y+2)) && (p1.y>=(p2.y-2)) && (p1.x != p2.x) ){
			SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
			return TRUE;
		}
		else	return FALSE;
	}
	else if(iFlag==1){//��ֱ����
		if( (p1.y<=(p2.y+6)) && (p1.y>=(p2.y-6)) && (p1.x<=(p2.x+2)) && (p1.x>=(p2.x-2)) && (p1.y != p2.y) ){
			SetCursor(::LoadCursor(NULL, IDC_SIZENS));
			return TRUE;
		}
		else 	return FALSE;
	}
	return FALSE;
}
// ��������	: ����
// ����		: CPoint& point
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע
inline void CJetImgCtrlCtrl::vScroll(CPoint& point) 
{
	if(point.x >= m_rtCurShowRect.right)
		SendMessage(WM_HSCROLL, SB_LINERIGHT, 0); 
	if(point.y >= m_rtCurShowRect.bottom)
		SendMessage(WM_VSCROLL, SB_LINEDOWN, 0); 
	if(point.x <= m_rtCurShowRect.left)
		SendMessage(WM_HSCROLL, SB_LINELEFT, 0); 
	if(point.y <= m_rtCurShowRect.top)
		SendMessage(WM_VSCROLL, SB_LINEUP, 0); 
	GetScrollPosition(m_ScrollPoint);

	//�����Ի����λ�ã���֤ת��������λ���ڸ÷�ͼ����ʾ�����ڣ�λ�ò��ܱ䣻
	point.x = max(m_rtCurShowRect.left,min(point.x,m_rtCurShowRect.right))-m_rtCurShowRect.left;
	point.y = max(m_rtCurShowRect.top,min(point.y,m_rtCurShowRect.bottom))-m_rtCurShowRect.top;
	point.x += m_ScrollPoint.x;
	point.y += m_ScrollPoint.y;
	point.x = (int)(point.x*(m_pFocusImg->m_fzoomx));
	point.y = (int)(point.y*(m_pFocusImg->m_fzoomy));
}

// ��������	: ��Ӧ��Ϣ
// ����		: BOOL bActive
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
BOOL CJetImgCtrlCtrl::OnNcActivate(BOOL bActive) 
{
	for(int ii=0; ii<m_ImgArray.GetSize(); ii++)
		m_ImgArray.GetAt(ii)->RepaintNotChange();
	Invalidate(FALSE);
	return COleControl::OnNcActivate(bActive);
}
// ��������	: ˮƽ����
// ����		: UINT nSBCode, UINT nPos, CScrollBar* pScrollBar
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    int scrollPos = GetScrollPos32(SB_HORZ);
    CRect rect=m_rtCurShowRect;  
    switch (nSBCode)
    {
        case SB_LINERIGHT:
            if (scrollPos < m_nHScrollMax)
            {
                int xScroll = m_sizeLine.cx;
                SetScrollPos32(SB_HORZ, scrollPos + xScroll);
                if (GetScrollPos32(SB_HORZ) == scrollPos) break;          // didn't work
                /*rect.left = xScroll;
                ScrollWindow(-xScroll, 0, rect);
                rect.left = rect.right - xScroll;
				InvalidateRect(rect)*/
                InvalidateRect(rect,FALSE);
            }
            break;
        case SB_LINELEFT:
            if (scrollPos > 0 )
            {
                int xScroll = m_sizeLine.cx;
                SetScrollPos32(SB_HORZ, max(0,scrollPos - xScroll));
                /*ScrollWindow(xScroll, 0, rect);
                rect.right = rect.left + xScroll;InvalidateRect(rect)*/
                InvalidateRect(rect,FALSE);
            }
            break;
        case SB_PAGERIGHT:
            if (scrollPos < m_nHScrollMax)
            {
                int offset = rect.Width();
                int pos = min(m_nHScrollMax, scrollPos + offset);
                SetScrollPos32(SB_HORZ, pos);
                InvalidateRect(rect,FALSE);
            }
            break;
        case SB_PAGELEFT:
            if (scrollPos > 0)
            {
                int offset = -rect.Width();
                int pos = max(0, scrollPos + offset);
                SetScrollPos32(SB_HORZ, pos);
                InvalidateRect(rect,FALSE);
            }
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            {
				int iCurPosition = GetScrollPos32(SB_HORZ, TRUE);
                SetScrollPos32(SB_HORZ, iCurPosition);
                /*int xScroll = iCurPosition-m_ixOffset;
                ScrollWindow(-xScroll, 0, rect);
				if(xScroll > 0)
					rect.left = rect.right-xScroll;
				else
					rect.right = rect.left - xScroll;
                InvalidateRect(rect);UpdateWindow();*/
				InvalidateRect(rect,FALSE);
            }
            break;
        case SB_LEFT:
            if (scrollPos > 0)
            {
                SetScrollPos32(SB_HORZ, 0);
                Invalidate(FALSE);
            }
            break;
        case SB_RIGHT:
            if (scrollPos < m_nHScrollMax)
            {
                SetScrollPos32(SB_HORZ, m_nHScrollMax);
                Invalidate(FALSE);
            }
            break;
        default: break;
    }	
	if(m_pFocusImg != NULL)	m_pFocusImg->SetShowDib(TRUE);
	COleControl::OnHScroll(nSBCode, nPos, pScrollBar);
}

// ��������	: ������õ�ǰ����ͼƬ�Ľ���Ԫ�أ�
// ����		: CPoint& point���ָ��
// ����ֵ	: BOOL �Ƿ�ɹ�
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
BOOL CJetImgCtrlCtrl::bGetFocusElement(CPoint& point) 
{
	int ii;
	switch(m_pFocusImg->GetDrawState()){
	case POINT_SET:
	{
		CMyPoint TempPoint;//��ʱ����
		for(ii=0; ii<m_pFocusImg->m_DocPointArray.GetSize(); ii++)
		{
			TempPoint = *(m_pFocusImg->m_DocPointArray.GetAt(ii));
			vGetViewElement(&TempPoint,m_ScrollPoint.x,m_ScrollPoint.y);
			if(TempPoint.bPointInElement(point))
			{
				m_prtDocPoint->SetFocus(FALSE);
				FireElementLoseFocus(m_nPointFocus,POINT_SET);//�����¼�;
				m_prtDocPoint = m_pFocusImg->m_DocPointArray.GetAt(ii);
				m_prtDocPoint->SetFocus(TRUE);
				m_nPointFocus = ii;
				FireElementGetFocus(m_nPointFocus,POINT_SET);//�����¼�;
				m_pFocusImg->SetShowDib(TRUE);
				InvalidateRect(&m_rtCurShowRect,FALSE);
				return TRUE;
			}
		}
		break;
	}
	case LINE_SET:
	{
		CMyLine TempLine;//��ʱ����
		for(ii=0; ii<m_pFocusImg->m_DocLineArray.GetSize(); ii++)
		{
			TempLine = *(m_pFocusImg->m_DocLineArray.GetAt(ii));
			vGetViewElement(&TempLine,m_ScrollPoint.x,m_ScrollPoint.y);
			if(TempLine.bPointInElement(point))
			{
				m_pliDocLine->SetFocus(FALSE);
				FireElementLoseFocus(m_nLineFocus,LINE_SET);//�����¼�;
				m_pliDocLine = m_pFocusImg->m_DocLineArray.GetAt(ii);
				m_pliDocLine->SetFocus(TRUE);
				m_nLineFocus = ii;
				FireElementGetFocus(m_nLineFocus,LINE_SET);//�����¼�;
				m_pFocusImg->SetShowDib(TRUE);
				InvalidateRect(&m_rtCurShowRect,FALSE);
				return TRUE;
			}
		}
		break;
	}
	case RECT_SET:
	{
		CMyRect TempRect;//��ʱ����
		for(ii=0; ii<m_pFocusImg->m_DocRectArray.GetSize(); ii++)
		{
			TempRect = *(m_pFocusImg->m_DocRectArray.GetAt(ii));
			vGetViewElement(&TempRect,m_ScrollPoint.x,m_ScrollPoint.y);
			if(TempRect.bPointInElement(point))
			{
				m_prtDocRect->SetFocus(FALSE);
				FireElementLoseFocus(m_nRectFocus,RECT_SET);//�����¼�;
				m_prtDocRect = m_pFocusImg->m_DocRectArray.GetAt(ii);
				m_prtDocRect->SetFocus(TRUE);
				m_nRectFocus = ii;
				FireElementGetFocus(m_nRectFocus,RECT_SET);//�����¼�;
				m_pFocusImg->SetShowDib(TRUE);
				InvalidateRect(&m_rtCurShowRect,FALSE);
				return TRUE;
			}
		}
		break;
	}
	case TEXT_SET:
	{
		CMyText TempText;//��ʱ����
		for(ii=0; ii<m_pFocusImg->m_DocTextArray.GetSize(); ii++)
		{
			TempText = *(m_pFocusImg->m_DocTextArray.GetAt(ii));
			vGetViewElement(&TempText,m_ScrollPoint.x,m_ScrollPoint.y);
			if(TempText.bPointInElement(point))
			{
				if (m_nTextFocus != ii) //add by yaka 20010427
				{
					m_prtDocText->SetFocus(FALSE);
					FireElementLoseFocus(m_nTextFocus,TEXT_SET);//�����¼�;
					m_prtDocText = m_pFocusImg->m_DocTextArray.GetAt(ii);
					m_prtDocText->SetFocus(TRUE);
					m_nTextFocus = ii;
					FireElementGetFocus(m_nTextFocus,TEXT_SET);//�����¼�;
					m_pFocusImg->SetShowDib(TRUE);
					
				}
				InvalidateRect(&m_rtCurShowRect,FALSE);
				m_prtDocText->CreateEdit(this);//test 
				return TRUE;
			}
		}
		break;
	}
	default:break;
	}
	return FALSE;
}

// ��������	: �жϵ�ǰ����ܷ����½��㣻
// ����		: CPoint& point
// ����ֵ	: BOOL �Ƿ�ɹ�
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
inline BOOL CJetImgCtrlCtrl::bSetFocusByMouse(CPoint& point) 
{
	//��Ȼ�ڵ�ǰͼ��ֱ���˳���
	if((m_nImgFocus>0) && (bPointInRect(point,m_ImgArray.GetAt(m_nImgFocus-1)->m_rtTotalRect)))
		return FALSE;
	for(int ii=0; ii<m_ImgArray.GetSize(); ii++){
		if(bPointInRect(point,m_ImgArray.GetAt(ii)->m_rtTotalRect)){
			SetFocus(ii+1);
			return TRUE;
		}
	}
	return FALSE;
}
// ��������	: ��������������
// ����		: UINT nFlags, CPoint point���λ��
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	COleControl::OnLButtonDown(nFlags, point);
	//֧�����ѡȡ���㣻���ڷ��ڻص�������.
	/*if(bSetFocusByMouse(point))
		return;*/
	//�����¼������û�ѡ���Ƿ����ý��㣻�û����¼��ؿ����ڵ���GetMousePosition(CPoint& p_Point);�ٵ���SetFocus()������
	CSingleImg* pTempFocus = m_pFocusImg;
	FireClickImg(point.x,point.y);
	if(pTempFocus != m_pFocusImg)
		return;
	if(m_pFocusImg == NULL)
		return;
	GetScrollPosition(m_ScrollPoint);//�п��ܹ������Ѿ������仯��
	switch (m_pFocusImg->GetDrawState())
	{
	case RECT_SET:
	{//������������״̬��������С����
		if(bGetFocusElement(point))
			return;
		if(m_iRectState & NEED_DRAGRECT){
			m_iRectState |= DRAGRECT;//������ϣ���ʼ΢����
			FireBeginModify(m_nRectFocus,RECT_SET);//�����¼�
			SetCapture();
		}
		else if(m_iRectState & NEED_DRAWRECT){
			if(bPointInRect(point,m_rtCurShowRect)){
				m_iRectState |= DRAWRECT;//������껭��
				if(m_nRectFocus>-1){
					m_prtDocRect->SetFocus(FALSE);
					m_prtDocRect = &m_rtTempRect;
					m_prtDocRect->SetFocus(TRUE);
					m_nRectFocus = -1;
					m_pFocusImg->SetShowDib(TRUE);
					InvalidateRect(&m_rtCurShowRect,FALSE);
				}
				m_prtDocRect->left=m_prtDocRect->right = (int)(m_pFocusImg->m_fzoomx * (point.x + m_ScrollPoint.x-m_rtCurShowRect.left));
				m_prtDocRect->top=m_prtDocRect->bottom = (int)(m_pFocusImg->m_fzoomy * (point.y + m_ScrollPoint.y-m_rtCurShowRect.top));
				FireBeginDrawNew(RECT_SET);
				SetCapture();
			}
		}
		break;
	}
	case LINE_SET:
	{//������������״̬��
		if(bGetFocusElement(point))
			return;
		if(m_iLineState & NEED_DRAGLINE){
			m_iLineState |= DRAGLINE;//������ϣ���ʼ΢����
			FireBeginModify(m_nLineFocus,LINE_SET);//�����¼�
			SetCapture();
		}
		else if(m_iLineState & NEED_DRAWLINE){
			if(bPointInRect(point,m_rtCurShowRect)){
				m_iLineState |= DRAWLINE;//������껭�ߣ�
				if(m_nLineFocus>-1){
					m_pliDocLine->SetFocus(FALSE);
					m_pliDocLine = &m_liTempLine;
					m_pliDocLine->SetFocus(TRUE);
					m_nLineFocus = -1;
					m_pFocusImg->SetShowDib(TRUE);
					InvalidateRect(&m_rtCurShowRect,FALSE);
				}
				m_pliDocLine->m_Begin.x = m_pliDocLine->m_End.x = (int)(m_pFocusImg->m_fzoomx * (point.x + m_ScrollPoint.x-m_rtCurShowRect.left));
				m_pliDocLine->m_Begin.y = m_pliDocLine->m_End.y = (int)(m_pFocusImg->m_fzoomy * (point.y + m_ScrollPoint.y-m_rtCurShowRect.top));
	
				FireBeginDrawNew(LINE_SET);
				SetCapture();
			}
		}
		break;
	}	//add by yaka 20010420
	case TEXT_SET:
	{//���������ı�״̬��������С����
		if(bGetFocusElement(point))
			return;
		if(m_iTextState & NEED_DRAGTEXT){
			m_iTextState |= DRAGTEXT;//�ı���ϣ���ʼ΢����
			FireBeginModify(m_nTextFocus,TEXT_SET);//�����¼�
			SetCapture();
		}
		else if(m_iTextState & NEED_DRAWTEXT){
			if(bPointInRect(point,m_rtCurShowRect)){
				m_iTextState |= DRAWTEXT;//������껭��
				if(m_nTextFocus>-1){
					m_prtDocText->SetFocus(FALSE);
					m_prtDocText = &m_rtTempText;
					m_prtDocText->SetFocus(TRUE);
					m_nTextFocus = -1;
					m_pFocusImg->SetShowDib(TRUE);
					InvalidateRect(&m_rtCurShowRect,FALSE);
				}
				m_prtDocText->left=m_prtDocText->right = (int)(m_pFocusImg->m_fzoomx * (point.x + m_ScrollPoint.x-m_rtCurShowRect.left));
				m_prtDocText->top=m_prtDocText->bottom = (int)(m_pFocusImg->m_fzoomy * (point.y + m_ScrollPoint.y-m_rtCurShowRect.top));
				FireBeginDrawNew(TEXT_SET);
				SetCapture();
			}
		}
		break;
	}
	//add by yaka 20010428
	case POINT_SET:
	{//�������õ�״̬
		if(bGetFocusElement(point))
			return;
		if(m_iPointState & NEED_DRAGPOINT){
			m_iPointState |= DRAGPOINT;//�ı���ϣ���ʼ΢����
			FireBeginModify(m_nPointFocus,POINT_SET);//�����¼�
			SetCapture();
		}
		else if(m_iPointState & NEED_DRAWPOINT){
			if(bPointInRect(point,m_rtCurShowRect)){
				m_iPointState |= DRAWPOINT;//������껭��
				if(m_nPointFocus>-1){
					m_prtDocPoint->SetFocus(FALSE);
					m_prtDocPoint = &m_rtTempPoint;
					m_prtDocPoint->SetFocus(TRUE);
					m_nPointFocus = -1;
					m_pFocusImg->SetShowDib(TRUE);
					InvalidateRect(&m_rtCurShowRect,FALSE);
				}
				m_prtDocPoint->m_Point.x = (int)(m_pFocusImg->m_fzoomx * (point.x + m_ScrollPoint.x-m_rtCurShowRect.left));
				m_prtDocPoint->m_Point.y = (int)(m_pFocusImg->m_fzoomy * (point.y + m_ScrollPoint.y-m_rtCurShowRect.top));
				m_prtDocPoint->m_lradii = 0;
				FireBeginDrawNew(POINT_SET);
				SetCapture();
			}
		}
		break;
	}
	}
	//add end
	//add by yaka 20010416
	if (m_nMaxImg <= 1)
		return;
	if ((point.x > m_pFocusImg->m_rtTotalRect.BottomRight().x -4) && (point.x < m_pFocusImg->m_rtTotalRect.BottomRight().x) 
		&& (point.y > m_pFocusImg->m_rtTotalRect.TopLeft().y) && (point.y < m_pFocusImg->m_rtTotalRect.BottomRight().y) && (m_nImgFocus % m_nCol != 0 ))
	{
		m_pFocusImg->m_nDrag = DRAGEAST;
	}
	else if ((point.y > m_pFocusImg->m_rtTotalRect.BottomRight().y -4 )&& (point.y < m_pFocusImg->m_rtTotalRect.BottomRight().y) 
		&& (point.x > m_pFocusImg->m_rtTotalRect.TopLeft().x) && (point.x < m_pFocusImg->m_rtTotalRect.BottomRight().x) && ((m_nImgFocus - 1) / m_nCol != (m_nRow -1)))
	{
		m_pFocusImg->m_nDrag = DRAGSOUTH;
	}
	else if ((point.x > m_pFocusImg->m_rtTotalRect.TopLeft().x ) && (point.x < m_pFocusImg->m_rtTotalRect.TopLeft().x + 4) 
		&& (point.y > m_pFocusImg->m_rtTotalRect.TopLeft().y) && (point.y < m_pFocusImg->m_rtTotalRect.BottomRight().y) && (m_nImgFocus % m_nCol != 1 ))
	{
		m_pFocusImg->m_nDrag = DRAGWEST;
	}
	else if ((point.y > m_pFocusImg->m_rtTotalRect.TopLeft().y ) && (point.y < m_pFocusImg->m_rtTotalRect.TopLeft().y + 4) 
		&& (point.x > m_pFocusImg->m_rtTotalRect.TopLeft().x) && (point.x < m_pFocusImg->m_rtTotalRect.BottomRight().x) && ((m_nImgFocus - 1) / m_nCol != 0 ))
	{
		m_pFocusImg->m_nDrag = DRAGNORTH;
	}
	


	//add end
}
// ��������	: �����������ͷ�
// ����		: UINT nFlags, CPoint point���λ��
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	COleControl::OnLButtonUp(nFlags, point);
	ReleaseCapture();
	if(m_pFocusImg == NULL)
		return;
	if(m_pFocusImg->GetDrawState() == RECT_SET){//������������״̬
		if((m_iRectState & DRAWRECT) || (m_iRectState & DRAGRECT)){
			m_prtDocRect->NormalizeElement();	 //���ܶ�������OnDraw()�е��ж���ʱ�������⣨if (!m_prtDocRect.IsRectEmpty())����
 			int iFocus;
			if (m_iRectState & DRAWRECT){
				m_iRectState &= (~DRAWRECT);//������NEED_DRAWRECT;
				if(m_pFocusImg->bAddRect(m_prtDocRect,iFocus)){
					m_nRectFocus = iFocus;
					FireEndDrawNew(iFocus,RECT_SET);
				}
			}
			else if(m_iRectState & DRAGRECT){
				m_iRectState &= (~DRAGRECT);//������NEED_DRAGRECT;
				FireEndModify(m_nRectFocus,RECT_SET);
				//m_pFocusImg->bModifyRect(m_prtDocRect);//����Ҫ�޸ģ���Ϊm_prtDocRect�Ѿ�ֱ��ָ���Ԫ���ڴ棻
			}
		}
	}
	else if(m_pFocusImg->GetDrawState()==LINE_SET){//������������״̬��
		if ((m_iLineState & DRAWLINE)||(m_iLineState & DRAGLINE)) {
			m_pliDocLine->NormalizeElement();
			int iFocus;
			if (m_iLineState & DRAWLINE){
				m_iLineState &= (~DRAWLINE);//������NEED_DRAWLINE;
				if(m_pFocusImg->bAddLine(m_pliDocLine,iFocus)){
					m_nLineFocus = iFocus;
					FireEndDrawNew(iFocus,LINE_SET);
				}
			}
			else if(m_iLineState & DRAGLINE){
				m_iLineState &= (~DRAGLINE);//������NEED_DRAGLINE;
				FireEndModify(m_nLineFocus,LINE_SET);
				//m_pFocusImg->bModifyLine(m_pliDocLine);//����Ҫ�޸ģ���Ϊm_prtDocRect�Ѿ�ֱ��ָ���Ԫ���ڴ棻
			}
		}
	}	//add by yaka 20010420
	else if(m_pFocusImg->GetDrawState()==TEXT_SET)
	{//���������ı�״̬��
		if((m_iTextState & DRAWTEXT) || (m_iTextState & DRAGTEXT)){
			m_prtDocText->NormalizeElement();	
 			int iFocus;
			if (m_iTextState & DRAWTEXT){
				m_iTextState &= (~DRAWTEXT);//������NEED_DRAWTEXT;
				m_prtDocText->m_strText = "  "; 
			//	m_prtDocText->m_bNeedBack = m_bTextNeedBack;
				if(m_pFocusImg->bAddText(m_prtDocText,iFocus)){
					m_nTextFocus = iFocus;
					InvalidateRect(&m_rtCurShowRect,FALSE);
					FireEndDrawNew(iFocus,TEXT_SET);
				}
			}
			else if(m_iTextState & DRAGTEXT){
				m_iTextState &= (~DRAGTEXT);//������NEED_DRAGTEXT;
				InvalidateRect(&m_rtCurShowRect,FALSE);
				FireEndModify(m_nTextFocus,TEXT_SET);
			}
		}
	}	//add end
	else if(m_pFocusImg->GetDrawState()==POINT_SET)
	{//�������õ�״̬��//add by yaka 20010428
	if((m_iPointState & DRAWPOINT) || (m_iPointState & DRAGPOINT)){
 			int iFocus;
			if (m_iPointState & DRAWPOINT){
				m_iPointState &= (~DRAWPOINT);
				if(m_pFocusImg->bAddPoint(m_prtDocPoint,iFocus)){
					m_nPointFocus = iFocus;
					FireEndDrawNew(iFocus,POINT_SET);
				}
			}
			else if(m_iPointState & DRAGPOINT){
				m_iPointState &= (~DRAGPOINT);//������NEED_DRAGRECT;
				InvalidateRect(&m_rtCurShowRect,FALSE);
				FireEndModify(m_nPointFocus,POINT_SET);
			}
		}//add end
	}

	//add by yaka 20010416
	CRect TempRect;
	switch (m_pFocusImg->m_nDrag)
	{
	case DRAGEAST:
		TempRect = GetSingleTotalRect(m_nImgFocus);
		m_aWidthRatio[(m_nImgFocus - 1) % m_nCol] *= (float)(point.x - m_pFocusImg->m_rtTotalRect.TopLeft().x) / (float)(m_pFocusImg->m_rtTotalRect.Width());
		m_aWidthRatio[(m_nImgFocus - 1) % m_nCol + 1] *= (float)(TempRect.BottomRight().x - point.x ) / (float)(TempRect.Width());
		break;
	case DRAGSOUTH:
		TempRect = GetSingleTotalRect(m_nImgFocus - 1 + m_nCol);
		m_aHeightRatio[(m_nImgFocus - 1) / m_nCol] *= (float)(point.y - m_pFocusImg->m_rtTotalRect.TopLeft().y) / (float)(m_pFocusImg->m_rtTotalRect.Height());
		m_aHeightRatio[(m_nImgFocus - 1) / m_nCol + 1] *= (float)(TempRect.BottomRight().y - point.y ) / (float)(TempRect.Height());
		break;
	case DRAGWEST:
		TempRect = GetSingleTotalRect(m_nImgFocus - 2);
		m_aWidthRatio[(m_nImgFocus - 1) % m_nCol] *= (float)(m_pFocusImg->m_rtTotalRect.BottomRight().x - point.x) / (float)(m_pFocusImg->m_rtTotalRect.Width());
		m_aWidthRatio[(m_nImgFocus - 1) % m_nCol - 1] *= (float)(point.x - TempRect.TopLeft().x ) / (float)(TempRect.Width());
		break;
	case DRAGNORTH:
		TempRect = GetSingleTotalRect(m_nImgFocus - 1 - m_nCol);
		m_aHeightRatio[(m_nImgFocus - 1) / m_nCol] *= (float)(m_pFocusImg->m_rtTotalRect.BottomRight().y - point.y) / (float)(m_pFocusImg->m_rtTotalRect.Height());
		m_aHeightRatio[(m_nImgFocus - 1) / m_nCol - 1] *= (float)(point.y - TempRect.TopLeft().y ) / (float)(TempRect.Height());
		break;
	}


	if (m_pFocusImg->m_nDrag != NOTDRAG)
	{
		for(short iTemp=0; iTemp<m_ImgArray.GetSize(); iTemp++)
		m_ImgArray.GetAt(iTemp)->SetTotalRect(GetSingleTotalRect(iTemp));
		RefreshByParent(m_rtClientRect,TRUE);	
		m_pFocusImg->m_nDrag = NOTDRAG;
		m_Dashrect = CRect(0,0,0,0); 
	}
	//add end
}
// ��������	: ��������ƶ�
// ����		: UINT nFlags, CPoint point���λ��
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint OldPoint = point;
	if(m_pFocusImg == NULL)
		return;
	switch (m_pFocusImg->GetDrawState())
	{
	case RECT_SET:
	{//������������״̬
		if ((m_iRectState & DRAWRECT) || (m_iRectState & DRAGRECT)) 
		{
			vShowRectOrLine(RECT_SET);
			vScroll(point);
			if(m_iRectState & DRAWRECT)
			{
				m_prtDocRect->right = point.x;
				m_prtDocRect->bottom = point.y;
				FireOnDrawing(RECT_SET);
			}
			else
			{//΢����
				if(m_iRotation == 0)
					m_prtDocRect->left = point.x;
				else if(m_iRotation == 1)
					m_prtDocRect->right = point.x;
				else if(m_iRotation == 2)
					m_prtDocRect->top = point.y;
				else if(m_iRotation == 3)
					m_prtDocRect->bottom = point.y;
				FireOnModifying(m_nRectFocus,RECT_SET);
			}
			vShowRectOrLine(RECT_SET);
		}	
		else {
			if(!m_prtDocRect->IsElementEmpty())
			{//��ʱ�Ѿ��п�
				m_rtViewRect = *m_prtDocRect;
				vGetViewElement(m_rtViewRect,m_ScrollPoint.x,m_ScrollPoint.y);
				m_iRectState |= NEED_DRAGRECT;
				if( ( (point.x<(m_rtViewRect.left+2)) && (point.x>(m_rtViewRect.left-2))) && 
					( (point.y>m_rtViewRect.top) && (point.y<m_rtViewRect.bottom) ) ){
					m_iRotation = 0; 
					SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
				}
				else if( ( (point.x<(m_rtViewRect.right+2)) && (point.x>(m_rtViewRect.right-2))) && 
					( (point.y>m_rtViewRect.top) && (point.y<m_rtViewRect.bottom) ) ){
					m_iRotation = 1; 
					SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
				}

				else if( ( (point.y<(m_rtViewRect.top+2)) && (point.y>(m_rtViewRect.top-2))) && 
					( (point.x>m_rtViewRect.left) && (point.x<m_rtViewRect.right) ) ){
					m_iRotation = 2;
					SetCursor(::LoadCursor(NULL, IDC_SIZENS));
				}
				else if( ( (point.y<(m_rtViewRect.bottom+2)) && (point.y>(m_rtViewRect.bottom-2)) ) && 
					( (point.x>m_rtViewRect.left) && (point.x<m_rtViewRect.right) ) ){
					m_iRotation = 3;
					SetCursor(::LoadCursor(NULL, IDC_SIZENS));
				}
				else{
					m_iRectState &= (~NEED_DRAGRECT);
					SetCursor(::LoadCursor(NULL, IDC_ARROW));
				}
			}
			else{
				m_iRectState &= (~NEED_DRAGRECT);
				SetCursor(::LoadCursor(NULL, IDC_ARROW));
			}
		}
		break;
	}
	case LINE_SET:
	{//������������״̬��
		if ((m_iLineState & DRAWLINE)||(m_iLineState & DRAGLINE)) {
			vShowRectOrLine(LINE_SET);
			vScroll(point);
			if(m_iLineState & DRAWLINE){
				m_pliDocLine->m_End.x = point.x;
				m_pliDocLine->m_End.y = point.y;
				FireOnDrawing(LINE_SET);
			}
			else{//΢����
				if(m_iRotation == 0)
					m_pliDocLine->m_Begin.x = point.x;
				else if(m_iRotation == 1)
					m_pliDocLine->m_End.x = point.x;
				else if(m_iRotation == 2)
					m_pliDocLine->m_Begin.y = point.y;
				else if(m_iRotation == 3)
					m_pliDocLine->m_End.y = point.y;
				FireOnModifying(m_nLineFocus,LINE_SET);
			}
			vShowRectOrLine(LINE_SET);
		}
		else{
			if(!m_pliDocLine->IsElementEmpty()){//��ʱ�Ѿ����ߣ�
				m_liViewLine = *m_pliDocLine;
				vGetViewElement(m_liViewLine,m_ScrollPoint.x,m_ScrollPoint.y);
				m_iLineState |= NEED_DRAGLINE;
				if(bPointNearAnother(point, m_liViewLine.m_Begin, 0))
					m_iRotation = 0; 
				else if(bPointNearAnother(point, m_liViewLine.m_Begin, 1))
					m_iRotation = 2;
				else if(bPointNearAnother(point, m_liViewLine.m_End, 0))
					m_iRotation = 1; 
				else if(bPointNearAnother(point, m_liViewLine.m_End, 1))
					m_iRotation = 3;
				else{
					m_iLineState &= (~NEED_DRAGLINE);
					SetCursor(::LoadCursor(NULL, IDC_ARROW));
				}
			}
			else{//΢����
				m_iLineState &= (~NEED_DRAGLINE);
				SetCursor(::LoadCursor(NULL, IDC_ARROW));
			}
		}
		break;
	}	//add by yaka 20010420
	case TEXT_SET:
	{//���������ı�״̬��
		if ((m_iTextState & DRAWTEXT) || (m_iTextState & DRAGTEXT)) 
		{
			vShowRectOrLine(TEXT_SET);
			vScroll(point);
			if(m_iTextState & DRAWTEXT)
			{
				m_prtDocText->right = point.x;
				m_prtDocText->bottom = point.y;
				FireOnDrawing(TEXT_SET);
			}
			else
			{//΢����
				if(m_iRotation == 0)
					m_prtDocText->left = point.x;
				else if(m_iRotation == 1)
					m_prtDocText->right = point.x;
				else if(m_iRotation == 2)
					m_prtDocText->top = point.y;
				else if(m_iRotation == 3)
					m_prtDocText->bottom = point.y;
				FireOnModifying(m_nTextFocus,TEXT_SET);
			}
			vShowRectOrLine(TEXT_SET);
		}	
		else {
			if(!m_prtDocText->IsElementEmpty())
			{//��ʱ�Ѿ����ı���
				m_rtViewText = *m_prtDocText;
				vGetViewElement(m_rtViewText,m_ScrollPoint.x,m_ScrollPoint.y);
				m_iTextState |= NEED_DRAGTEXT;
				if( ( (point.x<(m_rtViewText.left+2)) && (point.x>(m_rtViewText.left-2))) && 
					( (point.y>m_rtViewText.top) && (point.y<m_rtViewText.bottom) ) ){
					m_iRotation = 0; 
					SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
				}
				else if( ( (point.x<(m_rtViewText.right+2)) && (point.x>(m_rtViewText.right-2))) && 
					( (point.y>m_rtViewText.top) && (point.y<m_rtViewText.bottom) ) ){
					m_iRotation = 1; 
					SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
				}

				else if( ( (point.y<(m_rtViewText.top+2)) && (point.y>(m_rtViewText.top-2))) && 
					( (point.x>m_rtViewText.left) && (point.x<m_rtViewText.right) ) ){
					m_iRotation = 2;
					SetCursor(::LoadCursor(NULL, IDC_SIZENS));
				}
				else if( ( (point.y<(m_rtViewText.bottom+2)) && (point.y>(m_rtViewText.bottom-2)) ) && 
					( (point.x>m_rtViewText.left) && (point.x<m_rtViewText.right) ) ){
					m_iRotation = 3;
					SetCursor(::LoadCursor(NULL, IDC_SIZENS));
				}
				else{
					m_iTextState &= (~NEED_DRAGTEXT);
					SetCursor(::LoadCursor(NULL, IDC_ARROW));
				}
			}
			else{
				m_iTextState &= (~NEED_DRAGTEXT);
				SetCursor(::LoadCursor(NULL, IDC_ARROW));
			}
		}
		break;
	}//add end
	//add by yaka 20010428
	case POINT_SET:
		{//�������õ�״̬
		if ((m_iPointState & DRAWPOINT) || (m_iPointState & DRAGPOINT)) 
		{
			vShowRectOrLine(POINT_SET);
			vScroll(point);
			if(m_iPointState & DRAWPOINT)
			{
				m_prtDocPoint->m_lradii = (long)sqrt((m_prtDocPoint->m_Point.x - point.x) * (m_prtDocPoint->m_Point.x - point.x) +
					(m_prtDocPoint->m_Point.y - point.y) * (m_prtDocPoint->m_Point.y - point.y));
				FireOnDrawing(POINT_SET);
			}
			else
			{//΢����
				if(m_iRotation == 0 || m_iRotation == 1)
					m_prtDocPoint->m_lradii = abs(point.x - m_prtDocPoint->m_Point.x);
				else if(m_iRotation == 2 || m_iRotation == 3)
					m_prtDocPoint->m_lradii = abs(point.y - m_prtDocPoint->m_Point.y);
				else 
					m_prtDocPoint->m_lradii = (long)sqrt((m_prtDocPoint->m_Point.x - point.x) * (m_prtDocPoint->m_Point.x - point.x) +
				(m_prtDocPoint->m_Point.y - point.y) * (m_prtDocPoint->m_Point.y - point.y));
			
				FireOnModifying(m_nPointFocus,POINT_SET);
			}
			vShowRectOrLine(POINT_SET);
		}	
		else {
			if(!m_prtDocPoint->IsElementEmpty())
			{//��ʱ�Ѿ��п�
				m_rtViewPoint = *m_prtDocPoint;
				vGetViewElement(m_rtViewPoint,m_ScrollPoint.x,m_ScrollPoint.y);
				m_iPointState |= NEED_DRAGPOINT;
				if( ( (point.x<(m_rtViewPoint.m_Point.x - m_rtViewPoint.m_lradii+2)) && (point.x>(m_rtViewPoint.m_Point.x - m_rtViewPoint.m_lradii-2))) && 
					( (point.y > m_rtViewPoint.m_Point.y -4 ) && (point.y<m_rtViewPoint.m_Point.y +4) ) ){
					m_iRotation = 0; 
					SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
				}
				else if( ( (point.x<(m_rtViewPoint.m_Point.x + m_rtViewPoint.m_lradii+2)) && (point.x>(m_rtViewPoint.m_Point.x + m_rtViewPoint.m_lradii-2))) && 
					( (point.y > m_rtViewPoint.m_Point.y -4 ) && (point.y<m_rtViewPoint.m_Point.y +4) ) ){
					m_iRotation = 1; 
					SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
				}

				else if( ( (point.y<(m_rtViewPoint.m_Point.y - m_rtViewPoint.m_lradii+2)) && (point.y>(m_rtViewPoint.m_Point.y - m_rtViewPoint.m_lradii-2))) && 
					( (point.x > m_rtViewPoint.m_Point.x -4 ) && (point.x<m_rtViewPoint.m_Point.x +4) ) ){
					m_iRotation = 2;
					SetCursor(::LoadCursor(NULL, IDC_SIZENS));
				}
				else if( ( (point.y<(m_rtViewPoint.m_Point.y + m_rtViewPoint.m_lradii+2)) && (point.y>(m_rtViewPoint.m_Point.y + m_rtViewPoint.m_lradii-2))) && 
					( (point.x > m_rtViewPoint.m_Point.x -4 ) && (point.x<m_rtViewPoint.m_Point.x +4) ) ){
					m_iRotation = 3;
					SetCursor(::LoadCursor(NULL, IDC_SIZENS));
				}
				else
				{
					long ltemp = (long)sqrt((m_rtViewPoint.m_Point.x - point.x) * (m_rtViewPoint.m_Point.x - point.x) +
					(m_rtViewPoint.m_Point.y - point.y) * (m_rtViewPoint.m_Point.y - point.y));
					if ((ltemp >= m_rtViewPoint.m_lradii -2) && (ltemp <= m_rtViewPoint.m_lradii + 2))
					{
						if ((point.x > m_rtViewPoint.m_Point.x) == ( point.y > m_rtViewPoint.m_Point.y))
							SetCursor(::LoadCursor(NULL, IDC_SIZENWSE));
						else
							SetCursor(::LoadCursor(NULL, IDC_SIZENESW));
						m_iRotation = 5;
					}
					else
					{
						m_iPointState &= (~NEED_DRAGPOINT);
						SetCursor(::LoadCursor(NULL, IDC_ARROW));
					}
				}
			}
			else{
				m_iPointState &= (~NEED_DRAGPOINT);
				SetCursor(::LoadCursor(NULL, IDC_ARROW));
			}
		}
		break;
		}
	}

	//add by yaka 20010416
	switch (m_pFocusImg->m_nDrag)
	{
	case NOTDRAG:
		if (m_nMaxImg <= 1)
			break;
		if ((point.x > m_pFocusImg->m_rtTotalRect.BottomRight().x -4) && (point.x < m_pFocusImg->m_rtTotalRect.BottomRight().x)
			&& (point.y > m_pFocusImg->m_rtTotalRect.TopLeft().y) && (point.y < m_pFocusImg->m_rtTotalRect.BottomRight().y) && (m_nImgFocus % m_nCol != 0 ))
			SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		else if ((point.y > m_pFocusImg->m_rtTotalRect.BottomRight().y -4 )&& (point.y < m_pFocusImg->m_rtTotalRect.BottomRight().y)
			&& (point.x > m_pFocusImg->m_rtTotalRect.TopLeft().x) && (point.x < m_pFocusImg->m_rtTotalRect.BottomRight().x) && ((m_nImgFocus - 1) / m_nCol != (m_nRow -1)))
			SetCursor(::LoadCursor(NULL, IDC_SIZENS));
		else if ((point.x > m_pFocusImg->m_rtTotalRect.TopLeft().x ) && (point.x < m_pFocusImg->m_rtTotalRect.TopLeft().x + 4)
			&& (point.y > m_pFocusImg->m_rtTotalRect.TopLeft().y) && (point.y < m_pFocusImg->m_rtTotalRect.BottomRight().y) && (m_nImgFocus % m_nCol != 1 ))
			SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		else if ((point.y > m_pFocusImg->m_rtTotalRect.TopLeft().y )&& (point.y < m_pFocusImg->m_rtTotalRect.TopLeft().y + 4)
			&& (point.x > m_pFocusImg->m_rtTotalRect.TopLeft().x) && (point.x < m_pFocusImg->m_rtTotalRect.BottomRight().x) && ((m_nImgFocus - 1) / m_nCol != 0 ))
			SetCursor(::LoadCursor(NULL, IDC_SIZENS));
		break;
	case DRAGEAST:
	 	SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		DrawDashLine(CPoint(point.x , 0) , CPoint(point.x , m_rtClientRect.Height()));
		if (point.x <= m_pFocusImg->m_rtTotalRect.TopLeft().x + 20)
		{
			point.x = m_pFocusImg->m_rtTotalRect.TopLeft().x + 20;
			ClientToScreen(& point);
			SetCursorPos(point.x,point.y);
		}
		else if(point.x >= GetSingleTotalRect(m_nImgFocus).BottomRight().x - 20 )
		{
			point.x = GetSingleTotalRect(m_nImgFocus).BottomRight().x - 20 ;
			ClientToScreen(& point);
			SetCursorPos(point.x,point.y);
		}
		break;
	case DRAGSOUTH:
		SetCursor(::LoadCursor(NULL, IDC_SIZENS));
		DrawDashLine(CPoint(0 , point.y) , CPoint(m_rtClientRect.Width(), point.y));
		if (point.y <= m_pFocusImg->m_rtTotalRect.TopLeft().y + 20)
		{
			point.y = m_pFocusImg->m_rtTotalRect.TopLeft().y + 20;
			ClientToScreen(& point);
			SetCursorPos(point.x,point.y);
		}
		else if(point.y >= GetSingleTotalRect(m_nImgFocus - 1 + m_nCol).BottomRight().y - 20 )
		{
			point.y = GetSingleTotalRect(m_nImgFocus - 1 + m_nCol).BottomRight().y - 20 ;
			ClientToScreen(& point);
			SetCursorPos(point.x,point.y);
		}
		break;	
	case DRAGWEST:
	 	SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		DrawDashLine(CPoint(point.x , 0) , CPoint(point.x , m_rtClientRect.Height()));
		if (point.x >= m_pFocusImg->m_rtTotalRect.BottomRight().x - 20)
		{
			point.x = m_pFocusImg->m_rtTotalRect.BottomRight().x - 20;
			ClientToScreen(& point);
			SetCursorPos(point.x,point.y);
		}
		else if(point.x <= GetSingleTotalRect(m_nImgFocus - 2).TopLeft().x + 20 )
		{
			point.x = GetSingleTotalRect(m_nImgFocus - 2).TopLeft().x + 20 ;
			ClientToScreen(& point);
			SetCursorPos(point.x,point.y);
		}
		break;
	case DRAGNORTH:
		SetCursor(::LoadCursor(NULL, IDC_SIZENS));
		DrawDashLine(CPoint(0 , point.y) , CPoint(m_rtClientRect.Width(), point.y));
		if (point.y >= m_pFocusImg->m_rtTotalRect.BottomRight().y - 20)
		{
			point.y = m_pFocusImg->m_rtTotalRect.BottomRight().y - 20;
			ClientToScreen(& point);
			SetCursorPos(point.x,point.y);
		}
		else if(point.y <= GetSingleTotalRect(m_nImgFocus - 1 - m_nCol).TopLeft().y + 20 )
		{
			point.y = GetSingleTotalRect(m_nImgFocus - 1 - m_nCol).TopLeft().y + 20 ;
			ClientToScreen(& point);
			SetCursorPos(point.x,point.y);
		}
		break;	
	}
		//add end
	//add by yaka 20010418
//	m_bMagnify =TRUE;
	if (m_bMagnify && m_pFocusImg->m_nDrag == NOTDRAG && bPointInRect(OldPoint,m_rtCurShowRect))
	{
		if (m_pFocusImg->SetMouse(OldPoint))
		{
			CRect rect=m_rtCurShowRect;
			InvalidateRect(rect,FALSE);
		//hCursor = ::LoadCursor(theApp.m_hInstance, MAKEINTRESOURCE(IDC_Magnifer));
		}
	}
	else if (m_pFocusImg->m_bShowMagnifer)
	{
		m_pFocusImg->m_bShowMagnifer = FALSE;
		CRect rect=m_rtCurShowRect;
		InvalidateRect(rect,FALSE);
	}
	//add end
	COleControl::OnMouseMove(nFlags, point);
}
// ��������	: ������С
// ����		: UINT nType, int cx, int cy
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::OnSize(UINT nType, int cx, int cy) 
{
	COleControl::OnSize(nType, cx, cy);
	//���µ���ͼ�����ʾλ�ã���ʱ�����ò�ͬ���㵼����ʱ�й���������ʱ�޹�������Ҳ�ᴥ�����¼���
	GetClientRect(&m_rtClientRect);
	for(int iTemp=0; iTemp<m_ImgArray.GetSize(); iTemp++)
		m_ImgArray.GetAt(iTemp)->SetTotalRect(GetSingleTotalRect(iTemp));
}
// ��������	: ����ֱ������
// ����		: UINT nSBCode, UINT nPos, CScrollBar* pScrollBar
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    int scrollPos = GetScrollPos32(SB_VERT);
    CRect rect=m_rtCurShowRect;
    switch (nSBCode)
    {
        case SB_LINEDOWN:
            if (scrollPos < m_nVScrollMax){
                int yScroll = m_sizeLine.cy;
                SetScrollPos32(SB_VERT, scrollPos + yScroll);
                if (GetScrollPos32(SB_VERT) == scrollPos) 
					break;          // didn't work
                InvalidateRect(rect,FALSE);
	        }
            break;
        case SB_LINEUP:
            if (scrollPos > 0){
                int yScroll = m_sizeLine.cy;
                SetScrollPos32(SB_VERT, max(0, scrollPos - yScroll));
                InvalidateRect(rect,FALSE);
            }
            break;
        case SB_PAGEDOWN:
            if (scrollPos < m_nVScrollMax){
                scrollPos = min(m_nVScrollMax, scrollPos + rect.Height());
                SetScrollPos32(SB_VERT, scrollPos);
                InvalidateRect(rect,FALSE);
            }
            break;
        case SB_PAGEUP:
            if (scrollPos > 0){
                int offset = -rect.Height();
                int pos = max(0, scrollPos + offset);
                SetScrollPos32(SB_VERT, pos);
                InvalidateRect(rect,FALSE);
            }
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:{
				int iCurPosition = GetScrollPos32(SB_VERT, TRUE);
                SetScrollPos32(SB_VERT, iCurPosition);
                InvalidateRect(rect,FALSE);
            }
            break;
        case SB_TOP:
            if (scrollPos > 0){
                SetScrollPos32(SB_VERT, 0);
                Invalidate(FALSE);
            }
            break;
        case SB_BOTTOM:
            if (scrollPos < m_nVScrollMax){
                SetScrollPos32(SB_VERT, m_nVScrollMax);
                Invalidate(FALSE);
            }
        default: break;
    }	
	if(m_pFocusImg != NULL)	m_pFocusImg->SetShowDib(TRUE);
	COleControl::OnVScroll(nSBCode, nPos, pScrollBar);
}
// ��������	: Ԥ�����ؼ�
// ����		: CREATESTRUCT &cs�������ṹ
// ����ֵ	: BOOL �Ƿ�ɹ�
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
BOOL CJetImgCtrlCtrl::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= WS_HSCROLL | WS_VSCROLL;
	cs.lpszClass = SHOWIMG_CLASSNAME;
	return COleControl::PreCreateWindow(cs);
}
// ��������	: �����ؼ�
// ����		: LPCREATESTRUCT lpCreateStruct�������ṹָ��
// ����ֵ	: int �Ƿ�ɹ�
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
int CJetImgCtrlCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	lpCreateStruct->lpszClass = SHOWIMG_CLASSNAME;
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetMaxImg(m_nRow,m_nCol); //add  by yaka 20010430
	ShowScrollBar(SB_BOTH,TRUE);
	GetClientRect(&m_rtClientRect);	
	return 0;
}

//********************************************************************************
//�ⲿ�ӿڣ�
//********************************************************************************
// CJetImgCtrlCtrl message handlers
// ��������	: �������ͼ����
// ����		: short p_nRow, short p_nCol����
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::SetMaxImg(short p_nRow, short p_nCol) 
{

	int iTemp = p_nRow*p_nCol;
	if (iTemp <= 0) //add by yaka 20010430
		return;
	if(m_nMaxImg != -1){//���ǵ�һ�����ã���Ҫ���µ����ڴ棻
		for(int ii=iTemp; ii<m_ImgArray.GetSize(); ii++)
			delete m_ImgArray[ii];
		if(ii>iTemp)
			m_ImgArray.RemoveAt(iTemp,ii-iTemp);
		if((m_nImgFocus>iTemp) && (m_nImgFocus<=ii)){
			vClearFocus();
		}
	}
	m_nRow = p_nRow;
	m_nCol = p_nCol;
	m_nMaxImg = iTemp;

	//add by yaka 20010416
	m_aWidthRatio.SetSize(m_nCol);
	for (short i = 0 ; i < m_nCol ;i++)
		m_aWidthRatio[i] = 1 / (float)m_nCol;
	m_aHeightRatio.SetSize(m_nRow);
	for (i = 0 ; i < m_nRow ;i++)
		m_aHeightRatio[i] = 1 / (float)m_nRow;
	//add end

	//���µ���ʣ�µ�ͼ��
	for(iTemp=0; iTemp<m_ImgArray.GetSize(); iTemp++)
		m_ImgArray.GetAt(iTemp)->SetTotalRect(GetSingleTotalRect(iTemp));
	//ˢ����Ļ��
	RefreshByParent(m_rtClientRect,TRUE);
}

// ��������	: ���ͼ��
// ����		: BOOL pa_bFlag,���ļ���ʽ�����ڴ淽ʽ��HDIB p_hdib, LPCTSTR lpszFileName,long p_nPosition,λ��BOOL p_bIsAdd��׷�ӻ��Ǹ��Ƿ�ʽ��
// ����ֵ	: CRect ������ʾ����
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
inline short CJetImgCtrlCtrl::InnerAddImgFile(BOOL pa_bFlag,HDIB p_hdib, LPCTSTR lpszFileName,long p_nPosition,BOOL p_bIsAdd) 
{
	if((p_nPosition<0) || (p_nPosition>m_nMaxImg))
		return -1203;
	int iCurImgNum = m_ImgArray.GetSize();
	if(p_nPosition>(iCurImgNum+1))//ֻ�����������ӣ�ע��������ADD����COVER��ʽ��������ͼ��
		return -1203;
	if(pa_bFlag){//From File
		p_hdib = OpenImgFile(lpszFileName,NULL);
		if(p_hdib == NULL)
			return -1209;
	}
	CSingleImg* pImg = new CSingleImg();
	if(pImg == NULL)
		return -1201;
	int iIndex;
	if(p_bIsAdd)
	{
		if(p_nPosition == 0){//׷����ĩβ��
			iIndex = m_ImgArray.Add(pImg);//iIndex��0��ʼ;
			if(iIndex==m_nMaxImg){//�Ѿ�Խ�磻
				iIndex -= 1;
				delete m_ImgArray.GetAt(0);
				m_ImgArray.RemoveAt(0);
				//���µ������ʣ�µ�ͼ��
				for(int iTemp=0; iTemp<m_ImgArray.GetSize()-1; iTemp++)
					m_ImgArray.GetAt(iTemp)->SetTotalRect(GetSingleTotalRect(iTemp));
			}
			pImg->SetShowWindow(this,&m_sizeLine,&m_nHScrollMax,&m_nVScrollMax);
			pImg->SetTotalRect(GetSingleTotalRect(iIndex));
			if(!pImg->bSetImgDib(p_hdib,iIndex))
				return -1202;
		}
		else{//��ĳ��ͼ��ǰ����÷�ͼ��
			iIndex = p_nPosition-1;
			m_ImgArray.InsertAt(iIndex,pImg);//iIndex��0��ʼ;
			//add by yaka 20010517
			if(m_nImgFocus > iIndex )
    			m_nImgFocus += 1;
			//add end
			pImg->SetShowWindow(this,&m_sizeLine,&m_nHScrollMax,&m_nVScrollMax);
			pImg->SetTotalRect(GetSingleTotalRect(iIndex));
			if(!pImg->bSetImgDib(p_hdib,iIndex))
				return -1202;
			if(m_ImgArray.GetSize()>m_nMaxImg){
				delete m_ImgArray.GetAt(m_nMaxImg);
				m_ImgArray.RemoveAt(m_nMaxImg);
			}
			//���µ������ʣ�µ�ͼ��
			for(int iTemp=iIndex+1; iTemp<m_ImgArray.GetSize(); iTemp++)
				m_ImgArray.GetAt(iTemp)->SetTotalRect(GetSingleTotalRect(iTemp));
		}
		SetFocus(iIndex+1);
	}
	else{
		if(p_nPosition == 0){//cover�����һ��ͼ��
			p_nPosition = iCurImgNum;
			if(p_nPosition == 0)	p_nPosition += 1;
		}
		iIndex = p_nPosition-1;
		if(p_nPosition <= iCurImgNum){//�Ǹ�����ĳ��ͼ��
			delete m_ImgArray.GetAt(iIndex);
			m_ImgArray.SetAt(iIndex,pImg);//iIndex��0��ʼ;
			pImg->SetShowWindow(this,&m_sizeLine,&m_nHScrollMax,&m_nVScrollMax);
			pImg->SetTotalRect(GetSingleTotalRect(iIndex));
			if(!pImg->bSetImgDib(p_hdib,iIndex))
				return -1202;
		}
		else{//��׷����ĩβ��
			iIndex = m_ImgArray.Add(pImg);
			pImg->SetShowWindow(this,&m_sizeLine,&m_nHScrollMax,&m_nVScrollMax);
			pImg->SetTotalRect(GetSingleTotalRect(iIndex));
			if(!pImg->bSetImgDib(p_hdib,iIndex))
				return -1202;
		}
		SetFocus(iIndex+1);
	}
	RefreshByParent(pImg->m_rtTotalRect,TRUE);
	if(pa_bFlag)
		pImg->m_bNeedFreeMemory = TRUE;
	else
		pImg->m_bNeedFreeMemory = FALSE;
	return 0;
}
// ��������	: ���ͼ���ļ�
// ����		: LPCTSTR lpszFileName,ͼ���ļ� short p_nPositionͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

short CJetImgCtrlCtrl::AddImgFile(LPCTSTR lpszFileName, short p_nPosition) 
{
	return InnerAddImgFile(TRUE,NULL,lpszFileName,p_nPosition,TRUE);
}
// ��������	: ���ͼ����
// ����		: long p_hdib,ͼ���� short p_nPositionͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::AddImgDib(long p_hdib, short p_nPosition) 
{
	return InnerAddImgFile(FALSE,(HDIB)p_hdib,NULL,p_nPosition,TRUE);
}
// ��������	: ����ͼ���ļ�
// ����		: LPCTSTR lpszFileName,ͼ���ļ� short p_nPositionͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

short CJetImgCtrlCtrl::CoverImgFile(LPCTSTR lpszFileName, long p_nPosition) 
{
	return InnerAddImgFile(TRUE,NULL,lpszFileName,p_nPosition,FALSE);
}
// ��������	: ����ͼ����
// ����		: long p_hdib,ͼ���� short p_nPositionͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::CoverImgDib(long p_hdib, short p_nPosition) 
{
	return InnerAddImgFile(FALSE,(HDIB)p_hdib,NULL,p_nPosition,FALSE);
}
// ��������	: ���ý���
// ����		: short p_nFocus,��������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::SetFocus(short p_nFocus) 
{
	//�л�������
	if((p_nFocus<1) || (p_nFocus > m_ImgArray.GetSize()))
		return -1203;

	if((m_nImgFocus == p_nFocus) && (m_pFocusImg == m_ImgArray.GetAt(p_nFocus-1)))
		return 0;
	if(m_pFocusImg != NULL){
		GetScrollPosition(m_ScrollPoint);
		m_pFocusImg->SetLoseFocus(m_ScrollPoint.x,m_ScrollPoint.y);
		vClearFocus();
	}
	m_nImgFocus = p_nFocus;

	m_pFocusImg = m_ImgArray.GetAt(p_nFocus-1);
	if(m_pFocusImg->m_bCanSetRect)
		m_iRectState |= NEED_DRAWRECT;//������
	if(m_pFocusImg->m_bCanSetLine)
		m_iLineState |= NEED_DRAWLINE;//�����ߣ�
	if(m_pFocusImg->m_bCanSetText)
		m_iTextState |= NEED_DRAWTEXT;//�����ı�;
	if(m_pFocusImg->m_bCanSetPoint)
		m_iPointState |= NEED_DRAWPOINT;//�����ı�;
	//�ڴ����ý��㣬ע��˳���ܱ䣻
	m_pFocusImg->SetFocus();
	Invalidate(FALSE);
	return 0;
}
// ��������	: ��ȡ����ͼ������
// ����		: 
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetFocus() 
{
	return m_nImgFocus;
}
// ��������	: ���ƻ�Ԫ������
// ����		: short p_nDrawState,״̬ short p_nNoͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::SetDrawState(short p_nDrawState, short p_nNo) 
{
	if((p_nNo<0) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	if(p_nNo == 0){//�������еģ�
		for(int ii=0; ii<m_ImgArray.GetSize(); ii++)
			m_ImgArray.GetAt(ii)->SetDrawState(p_nDrawState);
		g_nDrawState = p_nDrawState;
	}
	else
		m_ImgArray.GetAt(p_nNo-1)->SetDrawState(p_nDrawState);
	return 0;
}
// ��������	: ��ȡ����״̬
// ����		: short p_nNoͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetDrawState(short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	return m_ImgArray.GetAt(p_nNo-1)->GetDrawState();
}
// ��������	: ������ʾ״̬
// ����		: short p_nShowState, short p_nNo
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::SetShowState(short p_nShowState, short p_nNo) 
{
	if((p_nNo<0) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	if(p_nNo == 0){//�������еģ�
		for(int ii=0; ii<m_ImgArray.GetSize(); ii++){
			if(m_ImgArray.GetAt(ii)->GetShowState() != p_nShowState){
				m_ImgArray.GetAt(ii)->SetShowState(p_nShowState);
				RefreshByParent(m_ImgArray.GetAt(ii)->m_rtTotalRect,TRUE);
			}
		}
		g_nShowState = p_nShowState;
	}
	else{
		if(m_ImgArray.GetAt(p_nNo-1)->GetShowState() != p_nShowState){
			m_ImgArray.GetAt(p_nNo-1)->SetShowState(p_nShowState);
			RefreshByParent(m_ImgArray.GetAt(p_nNo-1)->m_rtTotalRect,TRUE);
		}
	}
	return 0;
}

// ��������	: ˢ��ͼ��
// ����		: 
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::RefreshImg() 
{
	for(int ii=0; ii<m_ImgArray.GetSize(); ii++)
		m_ImgArray.GetAt(ii)->RepaintNotChange();
	//Invalidate(FALSE);
	RefreshByParent(m_rtClientRect,TRUE);
}
// ��������	: ��ȡ��ʾ״̬
// ����		: short p_nNoͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetShowState(short p_nNo) 
{
	if((p_nNo<0) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	return m_ImgArray.GetAt(p_nNo-1)->GetShowState();
}

// ��������	: ��ȡ���ͼ����
// ����		:
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetMaxImg() 
{
	return m_nMaxImg;
}
// ��������	: ��ȡ��ǰͼ����
// ����		:
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetCurImgNum() 
{
	return m_ImgArray.GetSize();
}
// ��������	: ɾ������ͼ��
// ����		: 
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::ClearAllImg() 
{
	vClearVarible();
	Invalidate();
}

short CJetImgCtrlCtrl::SetReferPoint(long p_nReferx, long p_nRefery, short p_nKind, short p_nNo) 
{
	return -1299;
}

short CJetImgCtrlCtrl::SetElementColor(short ColorR, short ColorG, short ColorB, short p_nKind, short p_nNo) 
{
	return -1299;
}
// ��������	: ��ʾ����
// ����		: long p_nStartx, long p_nStarty, long p_nEndx, long p_nEndy, long p_lpData, short p_nNo)
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

short CJetImgCtrlCtrl::ShowLine(long p_nStartx, long p_nStarty, long p_nEndx, long p_nEndy, long p_lpData, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	CMyLine* lpTempEle = new CMyLine;
	CMyLine* lpTempEle1 = lpTempEle;
	int nTemp;//��ʱ������
	lpTempEle->SetItemDate((LPVOID)p_lpData);
	lpTempEle->m_Begin.x = p_nStartx;	lpTempEle->m_Begin.y = p_nStarty;
	lpTempEle->m_End.x = p_nEndx;	lpTempEle->m_End.y = p_nEndy;
	if(!m_ImgArray.GetAt(p_nNo-1)->bAddLine(lpTempEle,nTemp))
		return -1204;
	delete lpTempEle1;//ע�ⲻ����lpTempEle��
	return 0;
}
// ��������	: ��ʾ��
// ����		: long p_nx, long p_ny, long p_nDia, long p_lpData, short p_nNo
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

short CJetImgCtrlCtrl::ShowPoint(long p_nx, long p_ny, long p_nDia, long p_lpData, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	CMyPoint* lpTempEle = new CMyPoint;
	CMyPoint* lpTempEle1 = lpTempEle;
	int nTemp;//��ʱ������
	lpTempEle->SetItemDate((LPVOID)p_lpData);
	lpTempEle->m_Point = CPoint(p_nx,p_ny);
	lpTempEle->m_lradii = p_nDia /2 ;
	if(!m_ImgArray.GetAt(p_nNo-1)->bAddPoint(lpTempEle,nTemp))//ע�⣺bAddRect�е�lpTempEle�Ѿ��ı��ˡ�
		return -1206;
	delete lpTempEle1;//ע�ⲻ����lpTempEle��
	return 0;
}
// ��������	: ��ʾ����
// ����		: long p_nOriginx, long p_nOriginy, long p_nWidth, long p_nHeight, long p_lpData, short p_nNo
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

short CJetImgCtrlCtrl::ShowRect(long p_nOriginx, long p_nOriginy, long p_nWidth, long p_nHeight, long p_lpData, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	CMyRect* lpTempEle = new CMyRect;
	CMyRect* lpTempEle1 = lpTempEle;
	int nTemp;//��ʱ������
	lpTempEle->SetItemDate((LPVOID)p_lpData);
	lpTempEle->left = p_nOriginx;	lpTempEle->top = p_nOriginy;
	lpTempEle->right = p_nOriginx+p_nWidth;	lpTempEle->bottom = p_nOriginy+p_nHeight;
	if(!m_ImgArray.GetAt(p_nNo-1)->bAddRect(lpTempEle,nTemp))//ע�⣺bAddRect�е�lpTempEle�Ѿ��ı��ˡ�
		return -1205;
	delete lpTempEle1;//ע�ⲻ����lpTempEle��
	return 0;
}
// ��������	: ��ʾ�ı���
// ����		: long p_nOriginx, long p_nOriginy, long p_nWidth, long p_nHeight, long p_lpData, LPCTSTR pa_lpszText, short p_nNo
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

short CJetImgCtrlCtrl::ShowText(long p_nOriginx, long p_nOriginy, long p_nWidth, long p_nHeight, long p_lpData, LPCTSTR pa_lpszText, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	CMyText* lpTempEle = new CMyText;
	CMyText* lpTempEle1 = lpTempEle;
	int nTemp;//��ʱ������
	lpTempEle->SetItemDate((LPVOID)p_lpData);
	lpTempEle->left = p_nOriginx;	lpTempEle->top = p_nOriginy;
	lpTempEle->right = p_nOriginx+p_nWidth;	lpTempEle->bottom = p_nOriginy+p_nHeight;
	lpTempEle->m_strText = pa_lpszText;
	//add by yaka 20010426
	lpTempEle->m_bNeedBack = m_rtTempText.m_bNeedBack;
	lpTempEle->m_nEditType = m_rtTempText.m_nEditType ;
	lpTempEle->ma_lpTextIn.Copy(m_rtTempText.ma_lpTextIn);
	lpTempEle->m_iCount = m_rtTempText.m_iCount;
	//add end
	if(!m_ImgArray.GetAt(p_nNo-1)->bAddText(lpTempEle,nTemp))//ע�⣺bAddRect�е�lpTempEle�Ѿ��ı��ˡ�
		return -1207;
	delete lpTempEle1;//ע�ⲻ����lpTempEle��
	return 0;
}
// ��������	: ��ȡԪ������
// ����		: long FAR* p_pOutData,���� short p_nKind,����long p_nItem,���, short p_nNoͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetItemData(long FAR* p_pOutData, short p_nKind, long p_nItem, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	switch(p_nKind){
	case LINE_SET:        //modify by yaka 20010423
		if((p_nItem<1) || (p_nItem > m_ImgArray.GetAt(p_nNo-1)->m_DocLineArray.GetSize()))
			return -1208;
		*p_pOutData = (long)m_ImgArray.GetAt(p_nNo-1)->m_DocLineArray.GetAt(p_nItem)->GetItemDate();
		break;
	case RECT_SET:
		if((p_nItem<1) || (p_nItem > m_ImgArray.GetAt(p_nNo-1)->m_DocRectArray.GetSize()))
			return -1208;
		*p_pOutData = (long)m_ImgArray.GetAt(p_nNo-1)->m_DocRectArray.GetAt(p_nItem)->GetItemDate();
		break;
	case TEXT_SET:
		if((p_nItem<1) || (p_nItem > m_ImgArray.GetAt(p_nNo-1)->m_DocTextArray.GetSize()))
			return -1208;
		*p_pOutData = (long)m_ImgArray.GetAt(p_nNo-1)->m_DocTextArray.GetAt(p_nItem)->GetItemDate();
		break;
					//modify end
	case POINT_SET://add by yaka 20010429
		if((p_nItem<1) || (p_nItem > m_ImgArray.GetAt(p_nNo-1)->m_DocPointArray.GetSize()))
			return -1208;
		*p_pOutData = (long)m_ImgArray.GetAt(p_nNo-1)->m_DocPointArray.GetAt(p_nItem)->GetItemDate();
		break;
			//add end
	default:return -1299;
	}
	return 0;
}
// ��������	: ����Ԫ������
// ����		: long p_pData, short p_nKind, long p_nItem, short p_nNo
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::SetItemData(long p_pData, short p_nKind, long p_nItem, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	switch(p_nKind){
	case LINE_SET:
		if((p_nItem<1) || (p_nItem > m_ImgArray.GetAt(p_nNo-1)->m_DocLineArray.GetSize()))
			return -1208;
		m_ImgArray.GetAt(p_nNo-1)->m_DocLineArray.GetAt(p_nItem)->m_lpDate = (LPVOID)p_pData;
		break;
	case RECT_SET:
		if((p_nItem<1) || (p_nItem > m_ImgArray.GetAt(p_nNo-1)->m_DocRectArray.GetSize()))
			return -1208;
		m_ImgArray.GetAt(p_nNo-1)->m_DocRectArray.GetAt(p_nItem)->m_lpDate = (LPVOID)p_pData;
		break;
	case TEXT_SET:
		if((p_nItem<1) || (p_nItem > m_ImgArray.GetAt(p_nNo-1)->m_DocTextArray.GetSize()))
			return -1208;
		m_ImgArray.GetAt(p_nNo-1)->m_DocTextArray.GetAt(p_nItem)->m_lpDate = (LPVOID)p_pData;
		break;
	case POINT_SET:
		if((p_nItem<1) || (p_nItem > m_ImgArray.GetAt(p_nNo-1)->m_DocPointArray.GetSize()))
			return -1208;
		m_ImgArray.GetAt(p_nNo-1)->m_DocPointArray.GetAt(p_nItem)->m_lpDate = (LPVOID)p_pData;
		break;
	default:return -1299;
	}
	return 0;
}

short CJetImgCtrlCtrl::GetDrawPoint(long p_nItem, long FAR* p_pnOutx, long FAR* p_pnOuty, short p_nNo) 
{//add by yaka 20010429
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	if((p_nItem<0) || (p_nItem>=m_ImgArray.GetAt(p_nNo-1)->m_DocPointArray.GetSize()))
		return -1208;
	CMyPoint* pTempEle = m_ImgArray.GetAt(p_nNo-1)->m_DocPointArray.GetAt(p_nItem);
	*p_pnOutx = pTempEle->m_Point.x;
	*p_pnOuty = pTempEle->m_Point.y;
	return 0;
}
//add end
// ��������	: ��ȡ��������
// ����		: long p_nItem,��� long FAR* p_pnOStartx, long FAR* p_pnOStarty, long FAR* p_pnOEndx, long FAR* p_pnOEndy, short p_nNoͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetDrawLine(long p_nItem, long FAR* p_pnOStartx, long FAR* p_pnOStarty, long FAR* p_pnOEndx, long FAR* p_pnOEndy, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	if((p_nItem<0) || (p_nItem>=m_ImgArray.GetAt(p_nNo-1)->m_DocLineArray.GetSize()))
		return -1208;
	CMyLine* pTempEle = m_ImgArray.GetAt(p_nNo-1)->m_DocLineArray.GetAt(p_nItem);
	*p_pnOStartx = pTempEle->m_Begin.x;
	*p_pnOStarty = pTempEle->m_Begin.y;
	*p_pnOEndx = pTempEle->m_End.x;
	*p_pnOEndy = pTempEle->m_End.y;
	return 0;
}
// ��������	: ��ȡ���β���
// ����		: long p_nItem, long FAR* p_pnOOriginx, long FAR* p_pnOOriginy, long FAR* p_pnOWidth, long FAR* p_pnOHeightshort p_nNoͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetDrawRect(long p_nItem, long FAR* p_pnOOriginx, long FAR* p_pnOOriginy, long FAR* p_pnOWidth, long FAR* p_pnOHeight, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	if((p_nItem<0) || (p_nItem>=m_ImgArray.GetAt(p_nNo-1)->m_DocRectArray.GetSize()))
		return -1208;
	CMyRect* pTempEle = m_ImgArray.GetAt(p_nNo-1)->m_DocRectArray.GetAt(p_nItem);
	*p_pnOOriginx = pTempEle->left;
	*p_pnOOriginy = pTempEle->top;
	*p_pnOWidth = pTempEle->right - pTempEle->left;
	*p_pnOHeight = pTempEle->bottom - pTempEle->top;
	return 0;
}
// ��������	: ��ȡ�ı������
// ����		: long p_nItem,��� long FAR* p_pnOOriginx, long FAR* p_pnOOriginy, long FAR* p_pnOWidth, long FAR* p_pnOHeight, LPCTSTR p_lpOText, short FAR* p_pnLen�� short p_nNoͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetDrawText(long p_nItem, long FAR* p_pnOOriginx, long FAR* p_pnOOriginy, long FAR* p_pnOWidth, long FAR* p_pnOHeight, LPCTSTR p_lpOText, short FAR* p_pnLen, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	if((p_nItem<0) || (p_nItem>=m_ImgArray.GetAt(p_nNo-1)->m_DocTextArray.GetSize()))
		return -1208;
	CMyText* pTempEle = m_ImgArray.GetAt(p_nNo-1)->m_DocTextArray.GetAt(p_nItem);
	*p_pnOOriginx = pTempEle->left;
	*p_pnOOriginy = pTempEle->top;
	*p_pnOWidth = pTempEle->right - pTempEle->left;
	*p_pnOHeight = pTempEle->bottom - pTempEle->top;
	int iLen = pTempEle->m_strText.GetLength();
	if(*p_pnLen < (iLen+1))
		return -1211;
	_stprintf((LPTSTR)p_lpOText,TEXT("%s"),pTempEle->m_strText);
	return 0;
}
// ��������	: ��ȡ���λ�õ�ͼ������
// ����		: long p_x, long p_y���λ��
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetMousePosition(long p_x, long p_y)
{
	CPoint point(p_x,p_y);
	for(int ii=0; ii<m_ImgArray.GetSize(); ii++){
		if(bPointInRect(point,m_ImgArray.GetAt(ii)->m_rtTotalRect))
			return (ii+1);
	}
	return -1;
}
// ��������	: ɾ��Ԫ��
// ����		: long p_nItem,Ԫ����� short p_nDrawState,Ԫ������ short p_nNoͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::DeleteElement(long p_nItem, short p_nDrawState, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	if(p_nItem<0)
		return -1208;
	if(p_nItem == -1){
		p_nNo = m_nImgFocus;
		switch(p_nDrawState){
		case LINE_SET:p_nItem = m_nLineFocus;break;
		case RECT_SET:p_nItem = m_nRectFocus;break;
		case TEXT_SET:p_nItem = m_nTextFocus;break; //add by yaka 20010420
		case POINT_SET:p_nItem = m_nPointFocus;break;
		default:break;
		}
	}
	int nTempFocus;
	CSingleImg* pImg = m_ImgArray.GetAt(p_nNo-1);
	switch(p_nDrawState)
	{
		case LINE_SET:
			if(p_nItem>=pImg->m_DocLineArray.GetSize())
				return -1208;
			nTempFocus=m_nLineFocus;
			delete pImg->m_DocLineArray.GetAt(p_nItem);pImg->m_DocLineArray.RemoveAt(p_nItem);
			break;
		case RECT_SET:
			if(p_nItem>=pImg->m_DocRectArray.GetSize())
				return -1208;
			nTempFocus=m_nRectFocus;
			delete pImg->m_DocRectArray.GetAt(p_nItem);pImg->m_DocRectArray.RemoveAt(p_nItem);
			break;
		case TEXT_SET:
			if(p_nItem>=pImg->m_DocTextArray.GetSize())
				return -1208;
			nTempFocus=m_nTextFocus;
			delete pImg->m_DocTextArray.GetAt(p_nItem);pImg->m_DocTextArray.RemoveAt(p_nItem);
			break;
		case POINT_SET:
			if(p_nItem>=pImg->m_DocPointArray.GetSize())
				return -1208;
			nTempFocus=m_nPointFocus;
			delete pImg->m_DocPointArray.GetAt(p_nItem);pImg->m_DocPointArray.RemoveAt(p_nItem);
			break;
		default:break;
	}
	if(p_nItem == nTempFocus)//ɾ�����ǵ�ǰ���н����Ԫ�أ���..
		vClearElementAll(FALSE);
	pImg->SetShowDib(TRUE);
	InvalidateRect(&pImg->m_rtShowRect,FALSE);
	return 0;
}


// ��������	: ȷ��ͼ���ϻ���Ԫ�ؿɼ�
// ����		:long p_nItem,Ԫ�����short p_nKind,���� short p_nNo��ͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

short CJetImgCtrlCtrl::EnsureElementVisible(long p_nItem,short p_nKind, short p_nNo)
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	if(p_nNo != m_nImgFocus)
		SetFocus(p_nNo);
	if(m_ImgArray.GetAt(p_nNo-1)->bEnsurePartVisible(p_nItem,p_nKind,m_sizeLine.cx,m_sizeLine.cy))
		return 0;
	else
		return -1210;
}

// ��������	: ���ñ��
// ����		: BOOL p_bShowRuler, short p_nNo
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::SetShowRuler(BOOL p_bShowRuler, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	m_ImgArray.GetAt(p_nNo-1)->SetShowRuler(p_bShowRuler);
	if(!p_bShowRuler)
		m_ImgArray.GetAt(p_nNo-1)->SetShowDib(TRUE);
	InvalidateRect(m_ImgArray.GetAt(p_nNo-1)->m_rtTotalRect,FALSE);
	return 0;
}

// ��������	: ��ȡԪ������
// ����		: short FAR* p_nOutNum,���� short p_nKind,����short p_nNoͼ������
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::GetElementNum(short FAR* p_nOutNum, short p_nKind, short p_nNo) 
{
	if((p_nNo<1) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	switch(p_nKind){
	case LINE_SET:*p_nOutNum = m_ImgArray.GetAt(p_nNo-1)->m_DocLineArray.GetSize();break;
	case RECT_SET:*p_nOutNum = m_ImgArray.GetAt(p_nNo-1)->m_DocRectArray.GetSize();break;
	case POINT_SET:*p_nOutNum = m_ImgArray.GetAt(p_nNo-1)->m_DocPointArray.GetSize();break;
	case TEXT_SET:*p_nOutNum = m_ImgArray.GetAt(p_nNo-1)->m_DocTextArray.GetSize();break;
	default:*p_nOutNum=0;break;
	}
	return 0;
}
// ��������	: ��תͼ��
// ����		: short p_nNo,ͼ������ double p_dAngle,�Ƕ� short p_nMode, BOOL p_bInterpolate,�Ƿ��ֵ BOOL p_bContinue�Ƿ�����
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::RotateImg(short p_nNo, double p_dAngle, short p_nMode, BOOL p_bInterpolate, BOOL p_bContinue) 
{
	//add by yaka 20010413
	if((p_nNo<0) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	m_ImgArray.GetAt(p_nNo-1)->SetRotate(p_dAngle , p_bContinue);
	RefreshByParent(m_ImgArray.GetAt(p_nNo-1)->m_rtTotalRect,TRUE);
	return 0;
	//add end
}
short CJetImgCtrlCtrl::RotateImage(short p_nNo, short p_dAngle, short p_bContinue) 
{
	if((p_nNo<0) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	m_ImgArray.GetAt(p_nNo-1)->SetRotate(p_dAngle , p_bContinue);
	RefreshByParent(m_ImgArray.GetAt(p_nNo-1)->m_rtTotalRect,TRUE);
	return 0;
	
}

// ��������	: ����ͼ��
// ����		: short p_nNo,ͼ������ double p_fZoom, ����BOOL p_bContinue�Ƿ����
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

short CJetImgCtrlCtrl::StretchImg(short p_nNo, double p_fZoom, BOOL p_bContinue) 
{
	//modify by yaka 20010416
	if((p_nNo<0) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	m_ImgArray.GetAt(p_nNo-1)->SetStretchScale((float)p_fZoom , p_bContinue);
	RefreshByParent(m_ImgArray.GetAt(p_nNo-1)->m_rtTotalRect,TRUE);
	return 0;
}
// ��������	: ����ͼ����ʾ����
// ����		: float FAR* p_fpWidthRatio,��ȱ��� float FAR* p_fpHeightRatio�߶ȱ���
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::SetShowRatio(float FAR* p_fpWidthRatio, float FAR* p_fpHeightRatio) 
{
	float fTotalWidth = 0 ,fTotalHeight = 0;
	short i;
	m_aWidthRatio.SetSize(m_nCol);
	for (i = 0 ; i< m_nCol ; i++ )
		fTotalWidth += p_fpWidthRatio[i];
	for (i = 0 ; i< m_nCol ; i++ )
	{
		m_aWidthRatio[i] = p_fpWidthRatio[i] / fTotalWidth;
	}
	m_aHeightRatio.SetSize(m_nRow);
	for (i = 0 ; i< m_nRow ; i++ )
		fTotalHeight += p_fpHeightRatio[i];
	for (i = 0 ; i< m_nRow ; i++ )
	{
		m_aHeightRatio[i] = p_fpHeightRatio[i] / fTotalHeight;
	}
	for(short iTemp=0; iTemp<m_ImgArray.GetSize(); iTemp++)
		m_ImgArray.GetAt(iTemp)->SetTotalRect(GetSingleTotalRect(iTemp));
	//ˢ����Ļ��
	RefreshByParent(m_rtClientRect,TRUE);

}

//add by yaka 20010417
// ��������	: ����ɫ��
// ����		: CPoint p_x,CPoint p_y������
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

void CJetImgCtrlCtrl::DrawDashLine(CPoint p_x,CPoint p_y)
{
	CDC* pDC = GetDC();
	pDC->InvertRect( m_Dashrect );
	m_Dashrect = CRect( p_x.x - 1, p_x.y - 1 , p_y.x + 1 , p_y.y + 1) ;
	pDC->InvertRect( m_Dashrect );
	ReleaseDC(pDC);
}
//add end

//add by yaka 20010420
// ��������	: ���÷Ŵ�
// ����		: BOOL p_bMagnify,�Ƿ�Ŵ� short p_nOffsetx, short p_nOffsety, ƫ��short p_nWidth, ���short p_nHeight�߶�
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::SetMagnifer(BOOL p_bMagnify, short p_nOffsetx, short p_nOffsety, short p_nWidth, short p_nHeight) 
{
	m_bMagnify = p_bMagnify;
	if (m_bMagnify)
	{
		if (p_nWidth >= 40)
			g_nMagSize.cx = p_nWidth;
		else
			g_nMagSize.cx = 120;

		if (p_nHeight >= 40)
			g_nMagSize.cy = p_nHeight;
		else
			g_nMagSize.cy = 120;

		if (p_nOffsetx >= 0 && p_nOffsetx <= g_nMagSize.cx)
			g_nMagOffset.cx = p_nOffsetx;
		else
			g_nMagOffset.cx = g_nMagSize.cx / 2;

		if (p_nOffsety >= 0 && p_nOffsety <= g_nMagSize.cy)
			g_nMagOffset.cy = p_nOffsety;
		else
			g_nMagOffset.cy = g_nMagSize.cy / 2;
	}
}
//add end 

//add by yaka 20010426
// ��������	: �����ı�������
// ����		: BOOL p_nNeedBack,�Ƿ񱳾� short p_nEditType,�༭���� VARIANT FAR* pa_lpString,����ַ������� short p_iCount�����С
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

void CJetImgCtrlCtrl::SetText(BOOL p_nNeedBack, short p_nEditType, VARIANT FAR* pa_lpString, short p_iCount) 
{
	m_rtTempText.m_bNeedBack = p_nNeedBack;
	m_rtTempText.m_nEditType = p_nEditType;
	if (p_iCount >= 0 && (p_nEditType == COMBOBOX || p_nEditType == LISTBOX))
	{
		m_rtTempText.ma_lpTextIn.RemoveAll();
		m_rtTempText.ma_lpTextIn.SetSize(p_iCount);
		for (int i = 0 ; i< p_iCount; i++)
		m_rtTempText.ma_lpTextIn[i] = ((CString *)pa_lpString)[i];
		m_rtTempText.m_iCount = p_iCount;
	}
	else
	{
		m_rtTempText.ma_lpTextIn.RemoveAll();
		m_rtTempText.m_iCount = 0;
	}

}
//add end
// ��������	: �����ı��򱳾����ϳ���
//����		: BOOL p_nNeedBack,�Ƿ񱳾� 
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

void CJetImgCtrlCtrl::SetTextNeedBack(BOOL p_bNeedBack) 
{
	m_rtTempText.m_bNeedBack = p_bNeedBack;

}

void CJetImgCtrlCtrl::OnOutLineColorChanged() 
{
	// TODO: Add notification handler code
	InvalidateControl();
	SetModifiedFlag();
}


void CJetImgCtrlCtrl::OnImgBackColorChanged() 
{
	InvalidateControl();
	SetModifiedFlag();
}

void CJetImgCtrlCtrl::OnMagnifyChanged() 
{
	// TODO: Add notification handler code
	InvalidateControl();
	SetModifiedFlag();
}

void CJetImgCtrlCtrl::OnColChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

void CJetImgCtrlCtrl::OnRowChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}
//add by yaka 20010514
// ��������	: ��ӡͼ��
// ����		: short p_nNo,ͼ������ float p_fZoom,���� short p_nPointx, short p_nPointyƫ����
// ����ֵ	: short ����ֵ
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
short CJetImgCtrlCtrl::PrintImg(short p_nNo, float p_fZoom, short p_nPointx, short p_nPointy) 
{
	if((p_nNo<0) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	CDC *m_pDC = GetDC();
	m_ImgArray.GetAt(p_nNo-1)->PrintImage(m_pDC,p_fZoom,p_nPointx,p_nPointy);
	ReleaseDC(m_pDC);
	return 0;
}
short CJetImgCtrlCtrl::PrintImage(short p_nNo, long p_nWidth, long p_nHeight, short p_nPointx, short p_nPointy) 
{
	if((p_nNo<0) || (p_nNo>m_ImgArray.GetSize()))
		return -1203;
	m_ImgArray.GetAt(p_nNo-1)->PrintImage(p_nWidth,p_nHeight,p_nPointx,p_nPointy);
	return 0;
}

//add end
// ��������	: �������
// ����		: 
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

void CJetImgCtrlCtrl::vClearFocus()
{
	vClearElementAll();
	m_pFocusImg = NULL;
	m_nImgFocus = -1;
}
// ��������	: ��Ӧ��ʱ��
// ����		: UINT nIDEvent��ʱ����
// ����ֵ	: void
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
void CJetImgCtrlCtrl::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	InvalidateRect(m_ImgArray.GetAt(nIDEvent-1)->m_rtShowRect,FALSE);
	m_ImgArray.GetAt(nIDEvent-1)->SetNextImg();
	COleControl::OnTimer(nIDEvent);
}

