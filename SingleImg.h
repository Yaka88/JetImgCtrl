// SingleImg.h: interface for the CSingleImg class.
//
//////////////////////////////////////////////////////////////////////
// 文件名	: SingleImg.h
// 所属项目	: 公共项目
// 版本号	: 1.0
// 内容		: 单图像头文件
// 创建日期	: 2001/02/01
// 作者		: yaka
// 备注 		: 
#if !defined(AFX_SINGLEIMG_H__55683B28_6B5C_4627_BF71_9AE942D15674__INCLUDED_)
#define AFX_SINGLEIMG_H__55683B28_6B5C_4627_BF71_9AE942D15674__INCLUDED_
#include "DrawDIB.h"   //add by yaka 200106020
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//add by yaka 20010416
//拖拉方向
#define	NOTDRAG			0
#define	DRAGEAST		1
#define	DRAGSOUTH		2
#define	DRAGWEST		3
#define	DRAGNORTH		4
//add end

#define LINE3D 4	//应该大于2，否则边缘线（宽度为2）就会覆盖图象
class CJetImgCtrlCtrl;
// 类名		: CSingleImg
// 父类名	: NULL
// 功能描述	: 单图像类
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
class CSingleImg:public CObject
{
protected:
	DECLARE_DYNCREATE(CSingleImg)

public:
	// Construction
	CSingleImg();

public:
	void PrintImage(DWORD p_nWidth,DWORD p_nHeight,short p_nPointx, short p_nPointy);
	void SetNextImg();
	void PrintImage(CDC* p_pMemdc, float p_fZoom,short p_nPointx,short p_nPointy);
	BOOL SetMouse(CPoint p_MousePoint);
	void SetShowWindow(CJetImgCtrlCtrl* p_pWnd,CSize* p_pSizeLine,int* p_pnHScrollMax, int* p_pnVScrollMax);
	void SetTotalRect(const CRect& p_Rect);
	BOOL bSetImgDib(HDIB hdib,int index);
	void SetShowDib(BOOL p_bShowDib);
	void SetShowRuler(BOOL pa_bShow);
	void ShowSingleImg(CDC* pa_pDC,int pa_ixOffset,int pa_iyOffset);
	void SetFocus();
	BOOL GetFocus(){return m_bIsFocus;};
	void SetLoseFocus(int pa_ixOffset, int pa_iyOffset);
	BOOL bAddRect(CMyRect*& pa_lpDocRect,int& p_nOutReturn);
	BOOL bAddLine(CMyLine*& pa_lpDocLine,int& p_nOutReturn);
	BOOL bAddText(CMyText*& pa_lpDocText,int& p_nOutReturn);
	BOOL bAddPoint(CMyPoint*& pa_lpDocPoint,int& p_nOutReturn);
	BOOL bEnsurePartVisible(long p_nItem,short p_nKind,int p_Linex,int p_Liney);
	void RepaintNotChange();

	//设置图象显示状态，当m_iSetState=STRETCH_ANY_SCALE时，必须调用SetStretchScale，否则作为STRETCH_NOT处理；
	void	SetShowState(short p_nState);
	int		GetShowState(){return m_iShowState;};
	void	SetDrawState(short p_nState);
	int		GetDrawState(){return m_iSetState;};
	void	SetStretchScale(float p_fScale ,BOOL p_bContinue);
	void	SetRotate(double p_dAngle, BOOL p_bContinue);
	BOOL	bAjustImgDib();
	void WorkOutShowRect();

// Attributes
	int m_nDibWidth, m_nDibHeight;//位图宽和高；

	short	m_nDrag;   //add by yaka 20010416
	BOOL	m_bShowMagnifer;

	int m_wBit;
	BOOL m_bCanSetRect,m_bCanSetLine,m_bCanSetText,m_bCanSetPoint;
	CPoint  m_MousePoint;
	CPalette* mp_Palette;

	CRect   m_rtTotalRect;//该幅图象在整个控件窗口中的允许显示区域；
	CRect	m_rtShowRect;//该幅图象在整个控件窗口中的图象实际显示区域，比允许显示区域小或等于；
	CArray<CMyRect*,CMyRect*> m_DocRectArray;//存放方框的链表；(方框信息是相对于以所在图象左上角为基准点的真实大小)
	CArray<CMyLine*,CMyLine*> m_DocLineArray;//存放线条的链表；
	CArray<CMyText*,CMyText*> m_DocTextArray;
	CArray<CMyPoint*,CMyPoint*> m_DocPointArray;
	float m_fzoomx,m_fzoomy;		//本图象当前缩放比例；
	BOOL m_bNeedFreeMemory;//是否自己释放内存；

	virtual ~CSingleImg();
private:
	CJetImgCtrlCtrl* m_pShowWnd;//该图象显示区域所在的窗口；
	CDrawDIB m_DrawDib;
	CSize* m_pSizeLine;
	int* m_pHScrollMax;
	int* m_pVScrollMax;
	DWORD i_SubImgCount;
	DWORD i_SubImgIndex;
	HDIB m_Orihdib;				//图象内存句柄；
	HDIB m_hdib;			//add by yaka 20010620
	BOOL m_bShowRuler;//是否显示标尺；
	int m_ixOffset;//当具有焦点时，用他跟踪滚动条的位置；
	int m_iyOffset;//当具有焦点时，用他跟踪滚动条的位置；
	BOOL m_bIsFocus;//本图象显示区域当前是否为焦点；
//	HANDLE m_hHeap;	//内存堆句柄；
	
	CMyRect m_rtTempViewRect;//临时变量；
	CMyLine	m_liTempViewLine;//临时变量；
	CMyText	m_rtTempViewText;
	CMyPoint m_rtTempViewPoint;
	int		m_iSetState;//设置状态，如区域设置、线条设置，点设置，文本设置


	float m_fScale;					//仅当显示状态为第四种时有用；
	int m_nCurWidth,m_nCurHeight;	//本图象当前缩放后长度；
	int		m_iShowState;//显示状态，如STRETCH_SCALE_FILLRECT,STRETCH_NOTSCALE_FILLRECT,STRETCH_NOT.....
	//add by yaka 20010414
	BOOL	m_bRotateState;
	double  m_dAngle;
	//add end

	//几个是否需要刷新的标志变量；
	//BOOL m_bCreateDibRefresh;
	BOOL m_bShowDibRefresh;
	BOOL m_bShowRectRefersh;
	BOOL m_bShowStateRefesh;
	BOOL m_bShowRulerRefresh;
	BOOL m_bShowFocusRefresh;

private:
	int m_aindex;
//	BOOL bGetBitmap(LPBYTE lpSrcByte, CBitmap* p_pBitmap,CDC* p_pDC=NULL);
	void ResetScrollBars();
	void vClearVarible();
	void vDrawRuler(CDC* pa_pDC);
	void DrawBigDot(CDC* pdc, int x, int y);
	void vShowElement(CDrawElement* p_pElement,CDC* p_DC);
	inline void vGetViewElement(CDrawElement& p_Element,int p_x, int p_y);
	void ShowAboutFocus(CDC* p_pDC,BOOL p_bFocus);
	void SetAllRefersh(BOOL p_bRefresh);
};

#endif // !defined(AFX_SINGLEIMG_H__55683B28_6B5C_4627_BF71_9AE942D15674__INCLUDED_)
