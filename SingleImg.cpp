// SingleImg.cpp: implementation of the CSingleImg class.
//
// 文件名	: SingleImg.cpp
// 所属项目	: 公共项目
// 版本号	: 1.0
// 内容		: 单图像实现文件
// 创建日期	: 2001/02/01
// 作者		: yaka
// 备注 		: 
#include "stdafx.h"
#include "JetImgCtrl.h"
#include "SingleImg.h"
#include "JetImgCtrlCtl.h"
#include "math.h"
#include "JetImgSeeApi.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CSingleImg,CObject)
int g_nDrawState = RECT_SET;
int g_nShowState = STRETCH_SCALE_FILLRECT;//STRETCH_NOT;//
CSize g_nMagSize(120 , 120);    //add by yaka 20010419
CSize g_nMagOffset(60 , 60);
// 功能描述	: 当图像构造函数
// 参数		: 
// 返回值	: 
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
CSingleImg::CSingleImg()
{
//	m_hHeap = p_Heap;
	m_pShowWnd = NULL;
	m_pSizeLine = NULL;
	i_SubImgCount = 1;
	i_SubImgIndex = 0;
	m_pHScrollMax = m_pVScrollMax = NULL;
	m_hdib = NULL;
	m_Orihdib = NULL;
	m_pShowWnd = NULL;
	m_bShowRuler = FALSE;
	m_bCanSetRect = m_bCanSetLine = m_bCanSetText =m_bCanSetPoint= TRUE;//扫描或导入的图象质量是否通过；
	m_bIsFocus = FALSE;
	mp_Palette = new CPalette;
	m_DocRectArray.RemoveAll();
	m_DocLineArray.RemoveAll();
	m_DocTextArray.RemoveAll();
	m_DocPointArray.RemoveAll();
	m_iSetState = g_nDrawState;
	m_iShowState = g_nShowState;
	//add by yaka 20010414
	m_bRotateState = TRUE;
	m_bShowMagnifer = FALSE;
	m_dAngle = 0 ;
	m_nDrag = NOTDRAG;
	//add end
	m_fScale = 1;
	SetAllRefersh(FALSE);
}

CSingleImg::~CSingleImg()
{
	vClearVarible();
	if(mp_Palette != NULL){
		delete mp_Palette;
		mp_Palette = NULL;
	}
}


// 功能描述	: 每更换一幅图象，该函中的属性都应该恢复；其他属性可以继承上次显示图象的属性
// 参数		: BOOL p_bRefresh是否刷新
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::SetAllRefersh(BOOL p_bRefresh)
{
	m_bShowDibRefresh = p_bRefresh;
	m_bShowRectRefersh = p_bRefresh;
	m_bShowStateRefesh = p_bRefresh;
	m_bShowRulerRefresh = p_bRefresh;
	m_bShowFocusRefresh = p_bRefresh;
	m_ixOffset = m_iyOffset = 0;
	m_fzoomx = m_fzoomy = 1;
	m_rtShowRect.SetRectEmpty();
}

void CSingleImg::RepaintNotChange()
{
	m_bShowDibRefresh = TRUE;
	m_bShowRulerRefresh = TRUE;
	m_bShowFocusRefresh = TRUE;
}

// 功能描述	: 清除一些变量内存
// 参数		: 
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	:
void CSingleImg::vClearVarible()
{
	if(m_pShowWnd != NULL){
		m_pShowWnd->vClearElementAll();
		if(m_bIsFocus)
			m_pShowWnd->vClearFocus(); 
	}
	m_rtTotalRect.SetRectEmpty();
	if((m_hdib!= NULL) && (m_hdib != m_Orihdib))
	{
		GlobalFree(m_hdib);
		m_hdib = NULL;
	}
	//add by yaka 20010620
	if((m_Orihdib!= NULL) && (m_bNeedFreeMemory))
	{
		GlobalFree(m_Orihdib);
		m_Orihdib = NULL;
	}
	//add end
	int iTemp=0;
	for(iTemp=0; iTemp<m_DocRectArray.GetSize(); iTemp++)
		delete m_DocRectArray.GetAt(iTemp);
	m_DocRectArray.RemoveAll();
	for(iTemp=0; iTemp<m_DocLineArray.GetSize(); iTemp++)
		delete m_DocLineArray.GetAt(iTemp);
	m_DocLineArray.RemoveAll();
	for(iTemp=0; iTemp<m_DocTextArray.GetSize(); iTemp++)
		delete m_DocTextArray.GetAt(iTemp);
	m_DocTextArray.RemoveAll();
	for(iTemp=0; iTemp<m_DocPointArray.GetSize(); iTemp++)
		delete m_DocPointArray.GetAt(iTemp);
	m_DocPointArray.RemoveAll();
	SetAllRefersh(FALSE);
	
}

// 功能描述	: 设置窗口
// 参数		: CJetImgCtrlCtrl* p_pWnd,CSize* p_pSizeLine,int* p_pnHScrollMax, int* p_pnVScrollMax
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::SetShowWindow(CJetImgCtrlCtrl* p_pWnd,CSize* p_pSizeLine,int* p_pnHScrollMax, int* p_pnVScrollMax)
{
	m_pShowWnd = p_pWnd;
	ASSERT(m_pShowWnd != NULL);
	HWND hWnd = m_pShowWnd->GetSafeHwnd();
	ASSERT(hWnd != NULL);
	m_pSizeLine = p_pSizeLine;
	m_pHScrollMax = p_pnHScrollMax;
	m_pVScrollMax = p_pnVScrollMax;
}


// 功能描述	: 设置要显示的图象句柄
// 参数		: HDIB hdib,long* p_lpPrecise,int index
// 返回值	: BOOL 是否成功
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
BOOL CSingleImg::bSetImgDib(HDIB hdib,int index)
{
	if(m_Orihdib == hdib)
		return TRUE;
	if(hdib == NULL)
		return FALSE;
	if(m_Orihdib != NULL)
		vClearVarible();
	m_Orihdib = hdib;
	m_hdib = hdib;			//add by yaka 20010620
	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)::GlobalLock(m_Orihdib);
	if(lpbi == NULL)
		return FALSE;
	m_nDibWidth = lpbi->biWidth;
	m_nDibHeight = abs(lpbi->biHeight);
	//add by yaka 20010622
	if (lpbi->biClrImportant > 0x80000000)
	{
		i_SubImgCount = lpbi->biClrImportant - 0x80000000;
		lpbi->biClrImportant = 0;
		m_pShowWnd->SetTimer(index + 1, 4000 / i_SubImgCount ,NULL); 
		m_nDibHeight = m_nDibHeight / i_SubImgCount;
	}
	else
	{
		i_SubImgCount = 1;
		m_pShowWnd->KillTimer(index + 1);
	}
	m_aindex = index;
	//add end
	m_wBit = lpbi->biBitCount;
	m_DrawDib.CreateDIBPalette(m_Orihdib, mp_Palette); //add by yaka 200106020
	::GlobalUnlock(m_Orihdib);
	SetAllRefersh(TRUE);
	return TRUE;
	/*bAjustImgDib();*/
}

void CSingleImg::SetShowDib(BOOL p_bShowDib)
{
	m_bShowDibRefresh = TRUE;
}

void CSingleImg::SetTotalRect(const CRect& p_Rect)
{
	if(m_rtTotalRect == p_Rect)
		return;
	m_rtTotalRect = p_Rect;
	m_bShowRectRefersh = TRUE;
}

void CSingleImg::SetShowState(short p_nState)
{
	if(m_iShowState == p_nState)
		return;
	m_iShowState = p_nState;
	m_bShowStateRefesh = TRUE;
	m_bShowRectRefersh = TRUE;
}
// 功能描述	: 设置缩放比例
// 参数		: float p_fScale , BOOL p_bContinue
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::SetStretchScale(float p_fScale , BOOL p_bContinue)
{
	//modify by yaka 20010416
	if (p_bContinue)
	{
		if (p_fScale == 1)
			return;
		m_fScale *= p_fScale;
	}
	else
	{
		if(m_fScale == p_fScale)
			return;
		m_fScale = p_fScale;
	}
	if(m_iShowState == STRETCH_ANY_SCALE){
		m_bShowStateRefesh = TRUE;
		m_bShowRectRefersh = TRUE;
	}
}

//add by yaka 20010414
// 功能描述	: 设置旋转参数
// 参数		: ,double p_dAngle , BOOL p_bContinue
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::SetRotate(double p_dAngle , BOOL p_bContinue)
{
	if (i_SubImgCount > 1 )
		return;
	double oldAngle = m_dAngle;
	if (p_bContinue)
	{
		m_dAngle += p_dAngle;
	}
	else
	{
		m_dAngle = p_dAngle ;
	}
	m_dAngle = (double)((long)m_dAngle % 360) ;
	if (m_dAngle < 0)
		m_dAngle +=360.0;	
	if(m_dAngle == oldAngle)
		return;
	m_bRotateState = TRUE;
	m_bShowStateRefesh = TRUE;
	m_bShowRectRefersh = TRUE;
}
//add end

void CSingleImg::SetShowRuler(BOOL pa_bShow)
{
	if(m_bShowRuler == pa_bShow)
		return;
	m_bShowRuler = pa_bShow;
	m_bShowRulerRefresh = TRUE;
}

// 功能描述	: 设置焦点
// 参数		: 
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::SetFocus()
{
	if(m_bIsFocus)
		return;
	m_bIsFocus = TRUE;
	m_pShowWnd->m_rtCurShowRect = m_rtShowRect;
	m_pShowWnd->m_rtCurTotalRect = m_rtTotalRect;
	ResetScrollBars();
	m_bShowFocusRefresh = TRUE;
}
// 功能描述	: 失去焦点
// 参数		: int pa_ixOffset, int pa_iyOffset
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::SetLoseFocus(int pa_ixOffset, int pa_iyOffset)
{
	if(!m_bIsFocus)
		return;
	m_ixOffset = pa_ixOffset;//记录下此时滚动条服务于本图象时的位置；
	m_iyOffset = pa_iyOffset;//记录下此时滚动条服务于本图象时的位置；
	m_bIsFocus = FALSE;
	int ii=0; 
	BOOL bFlag = FALSE;
	switch(GetDrawState()){
	case POINT_SET://add by yaka 20010428
		for(ii=0; ii<m_DocPointArray.GetSize(); ii++){
			if(m_DocPointArray.GetAt(ii)->GetFocus()){
				m_DocPointArray.GetAt(ii)->SetFocus(FALSE);
				bFlag=TRUE;
			}
		}
		break;//add end
	case TEXT_SET:
		for(ii=0; ii<m_DocTextArray.GetSize(); ii++){
			if(m_DocTextArray.GetAt(ii)->GetFocus()){
				m_DocTextArray.GetAt(ii)->SetFocus(FALSE);
				bFlag=TRUE;
			}
		}
		break;
	case LINE_SET:
		for(ii=0; ii<m_DocLineArray.GetSize(); ii++){
			if(m_DocLineArray.GetAt(ii)->GetFocus()){
				m_DocLineArray.GetAt(ii)->SetFocus(FALSE);
				bFlag=TRUE;
			}
		}
		break;
	case RECT_SET:		
		for(ii=0; ii<m_DocRectArray.GetSize(); ii++){
			if(m_DocRectArray.GetAt(ii)->GetFocus()){
				m_DocRectArray.GetAt(ii)->SetFocus(FALSE);
				bFlag = TRUE;
			}
		}
		break;
	}
	if(bFlag)
		m_bShowDibRefresh = TRUE;
	m_bShowFocusRefresh = TRUE;
}

void CSingleImg::SetDrawState(short p_nState)
{
	m_iSetState = p_nState;
}	

#define WORD_WBYTES(x)	((((x) + 15 ) >> 4) << 1)


// 功能描述	: 计算可显示大小
// 参数		:
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::WorkOutShowRect()
{
	m_rtShowRect = m_rtTotalRect;
	m_rtShowRect.DeflateRect(LINE3D,LINE3D);//为了留出控件画三维边缘线。
	float fzoomx=1,fzoomy=1;
	switch(m_iShowState){
	case STRETCH_SCALE_FILLRECT:{
		fzoomx = (float)(m_nDibWidth )/ m_rtShowRect.Width();
		fzoomy = (float)(m_nDibHeight )/ m_rtShowRect.Height();
		m_fScale = fzoomx = fzoomy = max(fzoomx,fzoomy);
		break;
	}
	case STRETCH_NOTSCALE_FILLRECT:{
		m_fScale = fzoomx = (float)(m_nDibWidth )/ m_rtShowRect.Width();
		fzoomy = (float)(m_nDibHeight )/ m_rtShowRect.Height();
		break;
	}
	case STRETCH_NOT:{
		m_fScale = fzoomx=fzoomy=1;
		break;
	}
	case STRETCH_ANY_SCALE:{
		fzoomx=fzoomy=m_fScale;
		break;
	}
	default:
		break;
	}
	//在此计算该幅图象的实际显示区域；
	if(m_iShowState == STRETCH_NOTSCALE_FILLRECT){
		m_nCurWidth = m_rtShowRect.Width();
		m_nCurHeight = m_rtShowRect.Height();
	}
	else{
		m_nCurWidth = (int)((m_nDibWidth )/ fzoomx);
		m_nCurHeight = (int)((m_nDibHeight )/ fzoomy);
	}

	if((m_fzoomx!=fzoomx) || (m_fzoomy!=fzoomy)){
		m_fzoomx = fzoomx;
		m_fzoomy = fzoomy;
//		m_bShowStateRefesh = TRUE;//需要重新创建位图；
	}
	int iTempx=0,iTempy=0;
	if(m_nCurWidth<m_rtShowRect.Width())
		iTempx = (m_rtShowRect.Width()-m_nCurWidth)/2;
	if(m_nCurHeight<m_rtShowRect.Height())
		iTempy = (m_rtShowRect.Height()-m_nCurHeight)/2;
	m_rtShowRect.DeflateRect(iTempx,iTempy);
	m_bShowFocusRefresh = TRUE;//需要重新刷新滚动条；
	m_bShowDibRefresh = TRUE;
}
// 功能描述	: 调整HDIB
// 参数		: CDC* p_pDC设备上下文
// 返回值	: BOOL 是否成功
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
BOOL CSingleImg::bAjustImgDib()
{
	HDIB TempDib;
	if (m_hdib != m_Orihdib)
		GlobalFree(m_hdib);
	if (m_dAngle == 0)
		TempDib = m_Orihdib;
	else
		TempDib = RotateImage(m_Orihdib, m_dAngle); 
	if (TempDib == NULL)
		return FALSE;
	
	LPSTR lpDIB = (LPSTR)::GlobalLock(TempDib);
	m_nDibHeight = abs(m_DrawDib.DIBHeight(lpDIB));
	m_nDibWidth = m_DrawDib.DIBWidth(lpDIB);
	m_nDibHeight = m_nDibHeight / i_SubImgCount;
	::GlobalUnlock(TempDib);

	WorkOutShowRect();

	m_hdib = m_DrawDib.StretchDIB(TempDib,m_fzoomx,m_fzoomy);

	if (m_hdib == NULL)
		return FALSE;
	if (m_dAngle != 0)
	{
		GlobalFree(TempDib);
	}
	return TRUE;

	//add end 
}

// 功能描述	: 加矩形
// 参数		: CMyRect*& pa_lpDocRect,int& p_nOutReturn
// 返回值	: BOOL 是否成功
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
BOOL CSingleImg::bAddRect(CMyRect*& pa_lpDocRect,int& p_nOutReturn)
{
	if(pa_lpDocRect->IsElementEmpty())
		return FALSE;
	p_nOutReturn = -1;
	if(m_hdib == NULL){
		AfxMessageBox("还未设置显示图象的句柄!");
		return FALSE;
	}
	if(pa_lpDocRect == NULL)
		return FALSE;
	CMyRect* pRect = new CMyRect(*pa_lpDocRect);
	pRect->NormalizeElement();
	BOOL bFlag = FALSE;
	//modify by yaka 20010426
	if (pRect->right > m_nDibWidth)
		pRect->right = m_nDibWidth;
	if (pRect->right <= 0)
		bFlag = TRUE;
	if (pRect->bottom >m_nDibHeight)
		pRect->bottom = m_nDibHeight;
	if (pRect->bottom <=0)
		bFlag = TRUE;
	if (pRect->left>=m_nDibWidth)
		bFlag = TRUE;
	if (pRect->left<0)
		pRect->left = 0;
	if (pRect->top>=m_nDibHeight)
		bFlag = TRUE;
	if (pRect->top<0)
		pRect->top = 0;
	//modify end
	if(bFlag){
//		AfxMessageBox("该区域的设置发生异常!");
		return FALSE;
	}
	p_nOutReturn = m_DocRectArray.Add(pRect);
	pa_lpDocRect = pRect;
	return TRUE;
}
//add by yaka 20010427
// 功能描述	: 加点
// 参数		: CMyPoint*& pa_lpDocPoint,int& p_nOutReturn
// 返回值	: BOOL 是否成功
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
BOOL CSingleImg::bAddPoint(CMyPoint*& pa_lpDocPoint,int& p_nOutReturn)
{
	if(pa_lpDocPoint->IsElementEmpty())
		return FALSE;
	p_nOutReturn = -1;
	if(m_hdib == NULL){
		AfxMessageBox("还未设置显示图象的句柄!");
		return FALSE;
	}
	if(pa_lpDocPoint == NULL)
		return FALSE;
	CMyPoint* pPoint = new CMyPoint(*pa_lpDocPoint);
	if (pPoint->m_Point.x > m_nDibWidth)
		pPoint->m_Point.x = m_nDibWidth;
	if (pPoint->m_Point.x < 0)
		pPoint->m_Point.x = 0 ;
	if (pPoint->m_Point.y > m_nDibHeight)
		pPoint->m_Point.y = m_nDibHeight;
	if (pPoint->m_Point.y < 0)
		pPoint->m_Point.y = 0 ;

	p_nOutReturn = m_DocPointArray.Add(pPoint);
	pa_lpDocPoint = pPoint;
	return TRUE;
}
//add end
// 功能描述	: 加文本框
// 参数		: CMyText*& pa_lpDocText,int& p_nOutReturn
// 返回值	: BOOL 是否成功
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
BOOL CSingleImg::bAddText(CMyText*& pa_lpDocText,int& p_nOutReturn)
{
	if(pa_lpDocText->IsElementEmpty())
		return FALSE;
	p_nOutReturn = -1;
	if(m_hdib == NULL){
		AfxMessageBox("还未设置显示图象的句柄!");
		return FALSE;
	}
	if(pa_lpDocText == NULL)
		return FALSE;
	CMyText* pText = new CMyText(*pa_lpDocText);
	pText->NormalizeElement();
	BOOL bFlag = FALSE;
		//modify by yaka 20010426
	if (pText->right > m_nDibWidth)
		pText->right = m_nDibWidth;
	if (pText->right <= 0)
		bFlag = TRUE;
	if (pText->bottom >m_nDibHeight)
		pText->bottom = m_nDibHeight;
	if (pText->bottom <=0)
		bFlag = TRUE;
	if (pText->left>=m_nDibWidth)
		bFlag = TRUE;
	if (pText->left<0)
		pText->left = 0;
	if (pText->top>=m_nDibHeight)
		bFlag = TRUE;
	if (pText->top<0)
		pText->top = 0;
	//modify end
	if(bFlag){
//		AfxMessageBox("该文本显示区域的设置发生异常!");
		return FALSE;
	}
	p_nOutReturn = m_DocTextArray.Add(pText);
	pa_lpDocText = pText;
	return TRUE;
}
// 功能描述	: 加线条
// 参数		: CMyLine*& pa_lpDocLine,int& p_nOutReturn
// 返回值	: BOOL 是否成功
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
BOOL CSingleImg::bAddLine(CMyLine*& pa_lpDocLine,int& p_nOutReturn)
{
	if(pa_lpDocLine->IsElementEmpty())
		return FALSE;
	p_nOutReturn = -1;
	if(m_hdib == NULL){
		AfxMessageBox("还未设置显示图象的句柄!");
		return FALSE;
	}
	if(pa_lpDocLine == NULL)
		return FALSE;
	CMyLine* pLine = new CMyLine(*pa_lpDocLine);
	pLine->NormalizeElement();

	BOOL bFlag = FALSE;
		//modify by yaka 20010426
	if (pLine->m_End.x > m_nDibWidth)
		pLine->m_End.x = m_nDibWidth;
	if (pLine->m_End.x <= 0)
		pLine->m_End.x = 0;
	if (pLine->m_End.y >m_nDibHeight)
		pLine->m_End.y = m_nDibHeight;
	if (pLine->m_End.y <=0)
		pLine->m_End.y = 0;
	if (pLine->m_Begin.x >=m_nDibWidth)
		pLine->m_Begin.x =m_nDibWidth;
	if (pLine->m_Begin.x <0)
		pLine->m_Begin.x = 0;
	if (pLine->m_Begin.y > m_nDibHeight)
		pLine->m_Begin.y = m_nDibHeight;
	if (pLine->m_Begin.y < 0)
		pLine->m_Begin.y = 0;
	//modify end
	if(bFlag){
//		AfxMessageBox("该线条的设置发生异常!");
		return FALSE;
	}
	p_nOutReturn = m_DocLineArray.Add(pLine);
	pa_lpDocLine = pLine;
	return TRUE;
}
// 功能描述	: 显示外框
// 参数		: CDC* p_pDC,BOOL p_bFocus
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::ShowAboutFocus(CDC* p_pDC,BOOL p_bFocus) 
{
	// create and select a thick, black pen
	CPen penBlack;
	if(p_bFocus)
		penBlack.CreatePen(PS_SOLID, 4, m_pShowWnd->m_outLineColor); //modify by yaka 20010429
	else
		penBlack.CreatePen(PS_SOLID, 4, GetSysColor(COLOR_3DFACE));//注意该颜色就是控件窗口的背景色；
	CPen* pOldPen = p_pDC->SelectObject(&penBlack);
	int nOldRop = p_pDC->SetROP2(R2_COPYPEN);
	CRect rect = m_rtTotalRect;
	rect.DeflateRect(2, 2);
	// draw a thick black rectangle 
	p_pDC->MoveTo(rect.left,rect.top);
	p_pDC->LineTo(rect.right,rect.top);
	p_pDC->LineTo(rect.right,rect.bottom);
	p_pDC->LineTo(rect.left,rect.bottom);
	p_pDC->LineTo(rect.left,rect.top);
	p_pDC->SetROP2(nOldRop);
   	p_pDC->SelectObject(pOldPen);
	p_pDC->DrawEdge(m_rtTotalRect, EDGE_SUNKEN, BF_RECT);
}

inline void CSingleImg::vGetViewElement(CDrawElement& p_Element,int p_x, int p_y)
{
	/*CRuntimeClass* pRunClass = NULL;
	pRunClass = p_Element.GetRuntimeClass();
	if(pRunClass != NULL)	AfxMessageBox(pRunClass->m_lpszClassName);*/
	p_Element.StretchElement(m_fzoomx,m_fzoomy);
	p_Element.OffsetElement(-p_x,-p_y);//扣除滚动条的位置；
	p_Element.OffsetElement(m_rtShowRect.left,m_rtShowRect.top);//该幅图象实际显示区域在整个窗口中的位置；
	p_Element.NormalizeElement();
}

void CSingleImg::vShowElement(CDrawElement* p_pElement,CDC* p_DC)
{
	if(p_DC == NULL)
		return;
	p_pElement->ShowElement(m_rtShowRect,p_DC);
}

// 功能描述	: 显示单幅图像
// 参数		: CDC* p_pDC,int pa_ixOffset,int pa_iyOffset
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::ShowSingleImg(CDC* p_pDC,int pa_ixOffset,int pa_iyOffset) 
{	
	if(p_pDC == NULL) 
		return;
	if(m_hdib == NULL)//一切免谈；
		return;
	int iTempx = (m_bIsFocus) ? pa_ixOffset : m_ixOffset;
	int iTempy = (m_bIsFocus) ? pa_iyOffset : m_iyOffset;
	if (iTempx == 1) iTempx = 0;
	if (iTempy == 1) iTempy = 0;
	
	if(m_bShowStateRefesh || m_bShowRectRefersh){//第1步；
		if(!bAjustImgDib())
			return;
		m_bShowRulerRefresh = TRUE; //add by yaka 20010425
		m_bShowStateRefesh = FALSE;
		m_bShowRectRefersh = FALSE;
	}
	
		RECT lpDCRect={m_rtShowRect.left, m_rtShowRect.top,m_rtShowRect.right,m_rtShowRect.bottom};
//		RECT lpDIBRect = {long(iTempx  * m_fzoomx) , long((m_nCurHeight - iTempy - m_rtShowRect.Height())* m_fzoomy+ i_SubImgIndex * m_nDibHeight) ,
//			long((m_rtShowRect.Width() + iTempx )* m_fzoomx)  , long((m_nCurHeight - iTempy )* m_fzoomy  + i_SubImgIndex * m_nDibHeight) };
		RECT lpDIBRect = {iTempx ,  iTempy + i_SubImgIndex * m_nCurHeight ,
			m_rtShowRect.Width() + iTempx  ,  iTempy + m_rtShowRect.Height() + i_SubImgIndex * m_nCurHeight };

		if (!m_DrawDib.PaintDIB(p_pDC->m_hDC,&lpDCRect, m_hdib,&lpDIBRect, mp_Palette))
			return;
		m_bShowDibRefresh = FALSE;
		
	//add by yaka 20010418	
		if (m_bIsFocus && m_bShowMagnifer)
		{
			int iTempx2 =(m_MousePoint.x - m_rtShowRect.left + iTempx) * m_nDibWidth /m_nCurWidth;
			int iTempy2 =(m_MousePoint.y - m_rtShowRect.top + iTempy) * m_nDibHeight /m_nCurHeight;
			RECT lpDCRect={m_MousePoint.x - g_nMagOffset.cx , m_MousePoint.y - g_nMagOffset.cy ,
				m_MousePoint.x - g_nMagOffset.cx + g_nMagSize.cx ,  m_MousePoint.y - g_nMagOffset.cy + g_nMagSize.cy};
			RECT lpDIBRect = {iTempx2 - g_nMagOffset.cx, iTempy2 - g_nMagOffset.cy + i_SubImgIndex * m_nDibHeight, 
				iTempx2 - g_nMagOffset.cx + g_nMagSize.cx ,  iTempy2 - g_nMagOffset.cy + g_nMagSize.cy + i_SubImgIndex * m_nDibHeight};
			if (!m_DrawDib.PaintDIB(p_pDC->m_hDC,&lpDCRect, m_Orihdib,&lpDIBRect, mp_Palette))
				return;
		
		}
	//add end
		//显示图象上元素；
		for(int ii=0; ii<m_DocTextArray.GetSize(); ii++)
		{
			m_rtTempViewText = *(m_DocTextArray.GetAt(ii));
			vGetViewElement(m_rtTempViewText,iTempx,iTempy);
			vShowElement(&m_rtTempViewText,p_pDC);
		}
		for(ii=0; ii<m_DocPointArray.GetSize(); ii++)
		{
			m_rtTempViewPoint = *(m_DocPointArray.GetAt(ii));
			vGetViewElement(m_rtTempViewPoint,iTempx,iTempy);
			vShowElement(&m_rtTempViewPoint,p_pDC);
		}
		for(ii=0; ii<m_DocRectArray.GetSize(); ii++)
		{
			m_rtTempViewRect = *(m_DocRectArray.GetAt(ii));
			vGetViewElement(m_rtTempViewRect,iTempx,iTempy);
			vShowElement(&m_rtTempViewRect,p_pDC);
		}
		for(ii=0; ii<m_DocLineArray.GetSize(); ii++)
		{
			m_liTempViewLine = *(m_DocLineArray.GetAt(ii));
			vGetViewElement(m_liTempViewLine,iTempx,iTempy);
			vShowElement(&m_liTempViewLine,p_pDC);
		}

	
	//}
	ShowAboutFocus(p_pDC,m_bIsFocus);
	if(m_bShowFocusRefresh){//第四步；
		//	ShowAboutFocus(p_pDC,m_bIsFocus);
		if(m_bIsFocus){
			m_pShowWnd->m_rtCurShowRect = m_rtShowRect;
			m_pShowWnd->m_rtCurTotalRect = m_rtTotalRect;
			ResetScrollBars();
		}
		m_bShowRulerRefresh = TRUE;
		m_bShowFocusRefresh = FALSE;
	}
	if(m_bShowRulerRefresh){//第五步；
		if(m_bShowRuler)
			vDrawRuler(p_pDC);
		m_bShowRulerRefresh = FALSE;
	}
}


// 功能描述	: 初始化滚动条参数
// 参数		: 
// 返回值	: 
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::ResetScrollBars()
{

	m_pSizeLine->cx = max(m_nCurWidth/100,10);
	m_pSizeLine->cy = max(m_nCurHeight/100,10);
    if (m_rtShowRect.Height() < m_nCurHeight)
		*m_pVScrollMax = m_nCurHeight-m_rtShowRect.Height(); 
    else
        *m_pVScrollMax = 1;
    if (m_rtShowRect.Width() < m_nCurWidth)
		*m_pHScrollMax = m_nCurWidth-m_rtShowRect.Width(); 
	   else
        *m_pHScrollMax = 1;

    ASSERT((*m_pVScrollMax) < INT_MAX && (*m_pHScrollMax) < INT_MAX); 
	m_pShowWnd->SetScrollRange(SB_VERT, 0, *m_pVScrollMax, TRUE);
    m_pShowWnd->SetScrollRange(SB_HORZ, 0, *m_pHScrollMax, TRUE);
	m_pShowWnd->SetScrollPos32(SB_VERT, m_iyOffset);
	m_pShowWnd->SetScrollPos32(SB_HORZ, m_ixOffset);
}
// 功能描述	: 画标尺
// 参数		: CDC* pa_pDC
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 

void CSingleImg::vDrawRuler(CDC* pa_pDC)
{
	CRect rectTemp = m_rtTotalRect;
	CSize sFont;
	//得到字体的高度；
	CPen pen(PS_SOLID, 1, RGB(0, 255, 255));
	CPen *pOldPen = pa_pDC->SelectObject(&pen);
	int nOldRop = pa_pDC->SetROP2(R2_COPYPEN);//R2_XORPEN
	COLORREF OldColor = pa_pDC->SetBkColor(RGB(200,150,0));

	sFont = pa_pDC->GetTextExtent("100",lstrlen("100"));
	int iRulerHeight = 5 + sFont.cy;//标尺高度；
	int iRulerWidth = 5 + sFont.cx;	

	int by = m_rtShowRect.bottom;
	int x = m_rtShowRect.left;//标尺起点
	int x2 = x + m_rtShowRect.Width();//标尺终点；
	int cxTemp = x - 10;//因为下列循环中一开始多加10；
	TCHAR tText[20];
	pa_pDC->MoveTo(x, by);
	//modify by yaka 20010425
	if (m_rtTotalRect.bottom >= m_rtShowRect.bottom + iRulerHeight)
		rectTemp.bottom = by + iRulerHeight;
	else
		rectTemp.bottom = by - 5;//从此开始，rectTemp用作写标记的区域。
		//modify end
	do{
		cxTemp += 10;//每隔10点画短线；
		pa_pDC->LineTo(cxTemp,by);
		pa_pDC->LineTo(cxTemp,by+5);//画短线（高度为5）；
		pa_pDC->MoveTo(cxTemp,by);
		if(((cxTemp-x)%50) == 0){//每隔50个点写标记。
			_stprintf(tText,TEXT("%d"),(cxTemp-x));
			sFont = pa_pDC->GetTextExtent(tText,lstrlen(tText));
			rectTemp.left= cxTemp-sFont.cx/2;
			rectTemp.right = rectTemp.left+sFont.cx;
			rectTemp.top = rectTemp.bottom - sFont.cy;
			pa_pDC->DrawText(tText,-1,&rectTemp, DT_CENTER | DT_BOTTOM );
			DrawBigDot(pa_pDC, cxTemp, by);
		}
	}while(cxTemp<=x2);

//add by yaka 20010425
	rectTemp = m_rtTotalRect;
	int lx= m_rtShowRect.left;
	int y = m_rtShowRect.top;//标尺起点
	int y2 = y + m_rtShowRect.Height();//标尺终点；
	int cyTemp = y2 + 10;//因为下列循环中一开始多加10；
	//TCHAR tText[20];
	pa_pDC->MoveTo(lx, y);
	if (m_rtTotalRect.left <= m_rtShowRect.left - iRulerWidth)
		rectTemp.left = lx - iRulerWidth;
	else
		rectTemp.left = lx + 5;//从此开始，rectTemp用作写标记的区域。
	do{
		cyTemp -= 10;//每隔10点画短线；
		pa_pDC->LineTo(lx,cyTemp);
		pa_pDC->LineTo(lx - 5,cyTemp);//画短线（高度为5）；
		pa_pDC->MoveTo(lx ,cyTemp);
		if(((y2 - cyTemp)%50) == 0){//每隔50个点写标记。
			_stprintf(tText,TEXT("%d"),(y2 - cyTemp));
			if ((y2 - cyTemp) != 0)
			{
				sFont = pa_pDC->GetTextExtent(tText,lstrlen(tText));
				rectTemp.bottom = cyTemp + sFont.cy/2;
				rectTemp.right = rectTemp.left + sFont.cx;
				rectTemp.top = rectTemp.bottom - sFont.cy;
				pa_pDC->DrawText(tText,-1,&rectTemp, DT_CENTER | DT_BOTTOM );
			}
			DrawBigDot(pa_pDC, lx ,cyTemp);
		}
	}while(cyTemp >= y);
	pa_pDC->SetBkColor(OldColor);
	pa_pDC->SetROP2(nOldRop);
	pa_pDC->SelectObject(pOldPen);
}
//add end


// 功能描述	: 画大点
// 参数		: CDC* pdc, int x, int y位置
// 返回值	: 
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::DrawBigDot(CDC* pdc, int x, int y)
{
	COLORREF cr=RGB(255, 0, 0);
	pdc->SetPixel(x, y, cr);
	pdc->SetPixel(x-1, y, cr);
	pdc->SetPixel(x+1, y, cr);
	pdc->SetPixel(x, y+1, cr);
	pdc->SetPixel(x, y-1, cr);
	pdc->SetPixel(x-1, y+1, cr);
	pdc->SetPixel(x-1, y-1, cr);
	pdc->SetPixel(x+1, y+1, cr);
	pdc->SetPixel(x+1, y-1, cr);
}


// 功能描述	: 确保图象上画的元素可见
// 参数		: long p_nItem,short p_nKind,int p_Linex,int p_Liney
// 返回值	: BOOL 是否成功
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
BOOL CSingleImg::bEnsurePartVisible(long p_nItem,short p_nKind,int p_Linex,int p_Liney)
{
	BOOL bFlag;
	if(m_pShowWnd == NULL)
		return FALSE;
	if(p_nItem<0)
		return FALSE;
	CPoint p_ScrollPoint;
	//modify by yaka 20010515
	CPoint OldScrollPoint;
	switch(p_nKind){
	case TEXT_SET:
		if(p_nItem >= m_DocTextArray.GetSize())
			return FALSE;
		if (m_DocTextArray.GetAt(p_nItem)->IsElementEmpty())
			return FALSE;
		do{	
			bFlag = FALSE;
			m_pShowWnd->GetScrollPosition(p_ScrollPoint);
			OldScrollPoint = p_ScrollPoint;
			m_rtTempViewText = *m_DocTextArray.GetAt(p_nItem);
			vGetViewElement(m_rtTempViewText,p_ScrollPoint.x,p_ScrollPoint.y);
			if ((m_rtTempViewText.left + m_rtTempViewText.right) /2  > m_rtShowRect.CenterPoint().x + p_Linex /2 )
			{
				m_pShowWnd->SendMessage(WM_HSCROLL, SB_LINERIGHT, 0); 
				bFlag = TRUE;
			}
			else if((m_rtTempViewText.left + m_rtTempViewText.right) /2 < m_rtShowRect.CenterPoint().x - p_Linex /2)
			{
				m_pShowWnd->SendMessage(WM_HSCROLL, SB_LINELEFT, 0); 
				bFlag = TRUE;
			}
			if ((m_rtTempViewText.top + m_rtTempViewText.bottom) /2 > m_rtShowRect.CenterPoint().y + p_Liney /2 )
			{
				m_pShowWnd->SendMessage(WM_VSCROLL, SB_LINEDOWN, 0); 
				bFlag = TRUE;
			}
			else if((m_rtTempViewText.top + m_rtTempViewText.bottom) /2 < m_rtShowRect.CenterPoint().y - p_Liney /2 )
			{
				m_pShowWnd->SendMessage(WM_VSCROLL, SB_LINEUP, 0); 
				bFlag = TRUE;
			}
			m_pShowWnd->UpdateWindow();
			m_pShowWnd->GetScrollPosition(p_ScrollPoint);
			if (OldScrollPoint == p_ScrollPoint)
				bFlag = FALSE;
		}while(bFlag);
		break;
	case RECT_SET:
		if(p_nItem >= m_DocRectArray.GetSize())
			return FALSE;
		if (m_DocRectArray.GetAt(p_nItem)->IsElementEmpty())
			return FALSE;
		do{
			bFlag = FALSE;
			m_pShowWnd->GetScrollPosition(p_ScrollPoint);
			OldScrollPoint = p_ScrollPoint;
			m_rtTempViewRect = *m_DocRectArray.GetAt(p_nItem);
			vGetViewElement(m_rtTempViewRect,p_ScrollPoint.x,p_ScrollPoint.y);
			if ((m_rtTempViewRect.left + m_rtTempViewRect.right) /2> m_rtShowRect.CenterPoint().x + p_Linex)
			{
				m_pShowWnd->SendMessage(WM_HSCROLL, SB_LINERIGHT, 0); 
				bFlag = TRUE;
			}
			else if((m_rtTempViewRect.left + m_rtTempViewRect.right) /2 < m_rtShowRect.CenterPoint().x - p_Linex)
			{
				m_pShowWnd->SendMessage(WM_HSCROLL, SB_LINELEFT, 0); 
				bFlag = TRUE;
			}
			if ((m_rtTempViewRect.top + m_rtTempViewRect.bottom) /2 > m_rtShowRect.CenterPoint().y + p_Liney)
			{
				m_pShowWnd->SendMessage(WM_VSCROLL, SB_LINEDOWN, 0); 
				bFlag = TRUE;
			}
			else if((m_rtTempViewRect.top + m_rtTempViewRect.bottom) /2 < m_rtShowRect.CenterPoint().y - p_Liney)
			{
				m_pShowWnd->SendMessage(WM_VSCROLL, SB_LINEUP, 0); 
				bFlag = TRUE;
			}
			m_pShowWnd->UpdateWindow();
			m_pShowWnd->GetScrollPosition(p_ScrollPoint);
			if (OldScrollPoint == p_ScrollPoint)
				bFlag = FALSE;
		}while(bFlag);
		break;
	case LINE_SET:
		if(p_nItem >= m_DocLineArray.GetSize())
			return FALSE;
		if (m_DocLineArray.GetAt(p_nItem)->IsElementEmpty())
			return FALSE;
		do{
			bFlag = FALSE;
			m_pShowWnd->GetScrollPosition(p_ScrollPoint);
			OldScrollPoint = p_ScrollPoint;
			m_liTempViewLine = *m_DocLineArray.GetAt(p_nItem);
			vGetViewElement(m_liTempViewLine,p_ScrollPoint.x,p_ScrollPoint.y);
			if ((m_liTempViewLine.m_Begin.x + m_liTempViewLine.m_End.x) /2 > m_rtShowRect.CenterPoint().x + p_Linex)
			{
				m_pShowWnd->SendMessage(WM_HSCROLL, SB_LINERIGHT, 0); 
				bFlag = TRUE;
			}
			else if((m_liTempViewLine.m_Begin.x + m_liTempViewLine.m_End.x) /2 < m_rtShowRect.CenterPoint().x - p_Linex)
			{
				m_pShowWnd->SendMessage(WM_HSCROLL, SB_LINELEFT, 0); 
				bFlag = TRUE;
			}
			if ((m_liTempViewLine.m_Begin.x + m_liTempViewLine.m_End.x) /2 > m_rtShowRect.CenterPoint().y + p_Liney)
			{
				m_pShowWnd->SendMessage(WM_VSCROLL, SB_LINEDOWN, 0); 
				bFlag = TRUE;
			}
			else if((m_liTempViewLine.m_Begin.x + m_liTempViewLine.m_End.x) /2 < m_rtShowRect.CenterPoint().y - p_Liney)
			{
				m_pShowWnd->SendMessage(WM_VSCROLL, SB_LINEUP, 0); 
				bFlag = TRUE;
			}
			m_pShowWnd->UpdateWindow();
			m_pShowWnd->GetScrollPosition(p_ScrollPoint);
			if (OldScrollPoint == p_ScrollPoint)
				bFlag = FALSE;
		}while(bFlag);
		break;
	case POINT_SET://add by yaka 20010429
		if(p_nItem >= m_DocPointArray.GetSize())
			return FALSE;
		if (m_DocPointArray.GetAt(p_nItem)->IsElementEmpty())
			return FALSE;
		do{
			bFlag = FALSE;
			m_pShowWnd->GetScrollPosition(p_ScrollPoint);
			OldScrollPoint = p_ScrollPoint;
			m_rtTempViewPoint = *m_DocPointArray.GetAt(p_nItem);
			vGetViewElement(m_rtTempViewPoint,p_ScrollPoint.x,p_ScrollPoint.y);
			if((m_rtTempViewPoint.m_Point.x) > m_rtShowRect.CenterPoint().x + p_Linex) 
			{
				m_pShowWnd->SendMessage(WM_HSCROLL, SB_LINERIGHT, 0); 
				bFlag = TRUE;
			}
			else if((m_rtTempViewPoint.m_Point.x) < m_rtShowRect.CenterPoint().x - p_Linex)
			{
				m_pShowWnd->SendMessage(WM_HSCROLL, SB_LINELEFT, 0); 
				bFlag = TRUE;
			}
			if((m_rtTempViewPoint.m_Point.y) > m_rtShowRect.CenterPoint().y + p_Liney)
			{
				m_pShowWnd->SendMessage(WM_VSCROLL, SB_LINEDOWN, 0); 
				bFlag = TRUE;
			}
			else if((m_rtTempViewPoint.m_Point.y ) < m_rtShowRect.CenterPoint().y - p_Liney)
			{
				m_pShowWnd->SendMessage(WM_VSCROLL, SB_LINEUP, 0); 
				bFlag = TRUE;
			}
			m_pShowWnd->UpdateWindow();
			m_pShowWnd->GetScrollPosition(p_ScrollPoint);
			if (OldScrollPoint == p_ScrollPoint)
				bFlag = FALSE;
		}while(bFlag);
		break;//add end
	default:break;
	}
	return TRUE;
}
// 功能描述	: 设置鼠标位置
// 参数		: CPoint p_MousePoint
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
BOOL CSingleImg::SetMouse(CPoint p_MousePoint)
{
	CSize POffset = p_MousePoint - m_MousePoint;
	m_bShowMagnifer = TRUE;
	if ((abs(POffset.cx) > 2 || abs(POffset.cy) > 2))
	{
		m_MousePoint = p_MousePoint;
		return TRUE;
	}
	return FALSE;

}
//add by yaka 20010514
// 功能描述	: 打印图像
// 参数		: CDC *p_pMemdc,内存设备上下文 float p_fZoom,比例short p_nPointx, short p_nPoint偏移
// 返回值	: BOOL 是否成功
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::PrintImage(CDC *p_pMemdc, float p_fZoom,short p_nPointx, short p_nPointy)
{
			CSize TempSize(m_nDibWidth,m_nDibHeight);
			int oldMemMode = p_pMemdc->SetMapMode(MM_LOMETRIC);
			p_pMemdc->DPtoLP(&TempSize);
			p_pMemdc->SetMapMode(oldMemMode);
			DWORD dwWidth, dwHeight;
			if (p_fZoom < 0)
			{
				dwWidth = DWORD(TempSize.cx / m_fzoomx);
				dwHeight = DWORD(TempSize.cy / m_fzoomy);
			}
			else if (p_fZoom == 0)
			{
				LPSTR lpInImage = (LPSTR)::GlobalLock(m_hdib);
				if (lpInImage == NULL)
					return;
				LPBITMAPINFO m_lpBitMapInfo = (LPBITMAPINFO)lpInImage;
				if (!m_lpBitMapInfo->bmiHeader.biXPelsPerMeter || !m_lpBitMapInfo->bmiHeader.biYPelsPerMeter)
				{
					dwWidth = DWORD(TempSize.cx / m_fzoomx);
					dwHeight = DWORD(TempSize.cy / m_fzoomy);
				}
				else
				{
					dwWidth = m_nDibWidth * 10000 / m_lpBitMapInfo->bmiHeader.biXPelsPerMeter;
					dwHeight = m_nDibHeight * 10000 / m_lpBitMapInfo->bmiHeader.biYPelsPerMeter;
				}
				::GlobalUnlock(m_hdib);
			}
			else
			{
				dwWidth = DWORD(TempSize.cx / p_fZoom);
				dwHeight = DWORD(TempSize.cy / p_fZoom);
			}
			PrintImage(dwWidth,dwHeight,p_nPointx,p_nPointy);

}
void CSingleImg::PrintImage(DWORD p_nWidth, DWORD p_nHeight, short p_nPointx, short p_nPointy)
{
	CPrintDialog dlg(FALSE);
	HDC hdcPrinter ;
	if (dlg.DoModal() == IDOK)
	{
		hdcPrinter = dlg.CreatePrinterDC();
	}
	else
		return;

	if (hdcPrinter == NULL)
	{
	   AfxMessageBox(_T("Buy a printer!"));
	}
	else
	{
	   // create a CDC and attach it to the default printer
	   CDC dcPrinter;
	   dcPrinter.Attach(hdcPrinter);

	   // call StartDoc() to begin printing
	   DOCINFO docinfo;
	   memset(&docinfo, 0, sizeof(docinfo));
	   docinfo.cbSize = sizeof(docinfo);
	   docinfo.lpszDocName = _T("Printing Image By JetImgCtrl");

	   // if it fails, complain and exit gracefully
	   if (dcPrinter.StartDoc(&docinfo) < 0)
	   {
		  AfxMessageBox(_T("Printer wouldn't initalize"));
	   }
	   else
	   {
			if (dcPrinter.StartPage() < 0)
			{
				AfxMessageBox(_T("Could not start page!"));
				dcPrinter.AbortDoc();
				return;
			}

			CSize TempSize(p_nWidth,p_nHeight);
			CPoint TempPoint(p_nPointx, -p_nPointy);
			int oldPrinterMode = dcPrinter.SetMapMode(MM_LOMETRIC);
			dcPrinter.LPtoDP(&TempSize);
			dcPrinter.LPtoDP(&TempPoint);
			dcPrinter.SetMapMode(oldPrinterMode);
			RECT lpDCRect = {TempPoint.x, TempPoint.y,TempPoint.x +TempSize.cx, TempPoint.y +TempSize.cy};
			RECT lpDIBRect = { 0, 0, m_nDibWidth ,m_nDibHeight};

			if (m_dAngle == 0)
			{
				m_DrawDib.PaintDIB(dcPrinter.m_hDC,&lpDCRect,m_Orihdib,&lpDIBRect, mp_Palette);
			}
			else
			{
				HDIB TempDib = RotateImage(m_Orihdib,m_dAngle);
				if (TempDib == NULL)
					return ;
				else
				{
					m_DrawDib.PaintDIB(dcPrinter.m_hDC,&lpDCRect,TempDib,&lpDIBRect, mp_Palette);
					GlobalFree(TempDib);
				}
			}

			dcPrinter.EndPage();
			dcPrinter.EndDoc();
	   }
	}




}
//add end
//add by yaka 20010622
// 功能描述	: 设置gif的下一幅图像
// 参数		: 
// 返回值	: void
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
void CSingleImg::SetNextImg()
{
	i_SubImgIndex = (i_SubImgIndex +1 ) % i_SubImgCount ;
}
//add end

