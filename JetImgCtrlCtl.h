#if !defined(AFX_JETIMGCTRLCTL_H__C2111BF9_4B15_44C9_9BF1_AA87D4C10D40__INCLUDED_)
#define AFX_JETIMGCTRLCTL_H__C2111BF9_4B15_44C9_9BF1_AA87D4C10D40__INCLUDED_
// 文件名	: JetImgCtrlctl.h
// 所属项目	: 公共项目
// 版本号	: 1.0
// 内容		: 显示控件头文件
// 创建日期	: 2001/02/01
// 作者		: yaka
// 备注 		: 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "SingleImg.h"

// JetImgCtrlCtl.h : Declaration of the CJetImgCtrlCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlCtrl : See JetImgCtrlCtl.cpp for implementation.
// 类名		: CJetImgCtrlCtrl
// 父类名	: COleControl
// 功能描述	: 显示控件类
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
class CJetImgCtrlCtrl : public COleControl
{
	DECLARE_DYNCREATE(CJetImgCtrlCtrl)
	friend class CSingleImg;

// Constructor
public:
	CJetImgCtrlCtrl();
// Attributes
	CSingleImg* m_pFocusImg;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJetImgCtrlCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CJetImgCtrlCtrl();
private:
	void DrawDashLine(CPoint p_x , CPoint p_y);
	CArray<CSingleImg*,CSingleImg*> m_ImgArray;
	//add by yaka 20010416
	CArray<float , float> m_aWidthRatio;
	CArray<float , float> m_aHeightRatio;
	//add end
//	int m_nRow;
//	int m_nCol;
	int m_nMaxImg;

	int m_nVScrollMax, m_nHScrollMax;
	int m_nImgFocus;//窗口中哪幅图象具有焦点；
	CSize m_sizeLine;
	//鼠标处于可以画框状态；正在画框；鼠标处于可以微调框状态；正在微调框；等
	enum	MOUSERECTSTATE{MOUSE_RECT_NULL=0, NEED_DRAWRECT=1, DRAWRECT=2, NEED_DRAGRECT=4, DRAGRECT=8};
	enum	MOUSELINESTATE{MOUSE_LINE_NULL=0, NEED_DRAWLINE=1, DRAWLINE=2, NEED_DRAGLINE=4, DRAGLINE=8};
	enum	MOUSETEXTSTATE{MOUSE_TEXT_NULL=0, NEED_DRAWTEXT=1, DRAWTEXT=2, NEED_DRAGTEXT=4, DRAGTEXT=8};
	enum	MOUSEPOINTSTATE{MOUSE_POINT_NULL=0, NEED_DRAWPOINT=1, DRAWPOINT=2, NEED_DRAGPOINT=4, DRAGPOINT=8};

	int		m_iRectState,m_iLineState,m_iTextState,m_iPointState;
	int		m_iRotation;
	CPoint	m_ScrollPoint;//临时变量，存放滚动条位置；

/*注意：m_prtDocRect、m_rtViewRect、m_rtCurTotalRect、m_rtShowRect、m_rtClientRect的含义各不相同。
1、m_prtDocRect指当前具有焦点方框的真实的图象数据点阵区域(以该幅图象的左上角为原点0,0)。但此时仍然没有考虑BMP图象首尾颠倒的问题，若再调用
	GetImageRectCoord(..)函数，则解决了这个问题。
2、m_rtViewRect直接由m_prtDocRect减去滚动条位置得到，注意m_rtViewRect的边界完全可能超过屏幕
	允许的显示范围。这时在显示该方框时，就应该由函数vShowElement控制好。

3、m_rtCurTotalRect实际是控制单个图象允许显示的范围，一般就是整个显示窗口的区域，但也可以是窗口的一部分
	区域，这样可以实现一个窗口显示多幅图象的功能。
4、m_rtCurShowRect实际是指焦点图象实际显示的范围（小于允许显示的范围，最起码小了画边框的面积。）
5、m_rtClientRect则是指整个显示窗口的客户区*/

	//当前具有焦点的元素及其序号；
	
	CMyRect		m_rtViewRect,m_rtTempRect;
	CMyRect*	m_prtDocRect;
	CMyLine		m_liViewLine,m_liTempLine;
	CMyLine*	m_pliDocLine;
	CMyText		m_rtViewText,m_rtTempText;
	CMyText*	m_prtDocText;
	CMyPoint	m_rtViewPoint,m_rtTempPoint;
	CMyPoint*	m_prtDocPoint;

	int m_nLineFocus;
	int m_nRectFocus;
	int m_nTextFocus;
	int m_nPointFocus;

	CRect   m_rtCurTotalRect;//当前具有焦点的图象允许实际显示区域；
	CRect	m_rtClientRect;	//本图象显示控件的整个窗口区域；
	CRect	m_rtCurShowRect;//当前具有焦点的图象实际显示区域（不是可能允许显示区域），若没有哪幅图象焦点，则整个窗口具有焦点；
	CRect	m_Dashrect;   //add by yaka 20010417
//	HANDLE m_hHeap;	//内存堆句柄；

	void vClearVarible();
	inline CRect GetSingleTotalRect(int p_nIndex);

    int  GetScrollPos32(int nBar, BOOL bGetTrackPos = FALSE);
    BOOL SetScrollPos32(int nBar, int nPos, BOOL bRedraw = TRUE);
	void	vShowElement(CDrawElement& p_Element);

	inline void vGetViewElement(CDrawElement& p_Element,int p_x, int p_y);
	inline void vGetViewElement(CDrawElement* p_pElement,int p_x, int p_y);

	void vClearElement(int pa_iFlag,BOOL p_ClearState=TRUE);
	void vClearElementAll(BOOL p_ClearState=TRUE);

	inline void vScroll(CPoint& point);
	void vShowRectOrLine(int pa_iState);
	inline BOOL bPointInRect(CPoint& pa_Point, CRect& pa_Rect);
	inline BOOL bPointInLine(CPoint& pa_Point, CMyLine& pa_Line);
	inline BOOL bPointNearAnother(CPoint& p1, CPoint& p2, int iFlag);
	BOOL	bGetFocusElement(CPoint& point);
	inline BOOL bSetFocusByMouse(CPoint& point);
	inline short InnerAddImgFile(BOOL pa_bFlag,HDIB p_hdib, LPCTSTR lpszFileName,long p_nPosition,BOOL p_bIsAdd);
	void GetScrollPosition(CPoint& p_ScrollPoint);
	inline void RefreshByParent(const CRect& p_Rect,BOOL bErase,CRect* p_ValidRect=NULL) ;

	DECLARE_OLECREATE_EX(CJetImgCtrlCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CJetImgCtrlCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CJetImgCtrlCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CJetImgCtrlCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CJetImgCtrlCtrl)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnNcActivate(BOOL bActive);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CJetImgCtrlCtrl)
	OLE_COLOR m_outLineColor;
	afx_msg void OnOutLineColorChanged();
	OLE_COLOR m_imgBackColor;
	afx_msg void OnImgBackColorChanged();
	BOOL m_bMagnify;
	afx_msg void OnMagnifyChanged();
	short m_nCol;
	afx_msg void OnColChanged();
	short m_nRow;
	afx_msg void OnRowChanged();
	afx_msg void SetMaxImg(short p_nRow, short p_nCol);
	afx_msg short GetDrawState(short p_nNo);
	afx_msg short GetMaxImg();
	afx_msg short GetCurImgNum();
	afx_msg short CoverImgFile(LPCTSTR lpszFileName, long p_nPosition);
	afx_msg short AddImgFile(LPCTSTR lpszFileName, short p_nPosition);
	afx_msg short AddImgDib(long p_hdib, short p_nPosition);
	afx_msg short CoverImgDib(long p_hdib, short p_nPosition);
	afx_msg short SetFocus(short p_nFocus);
	afx_msg short GetFocus();
	afx_msg void ClearAllImg();
	afx_msg short SetReferPoint(long p_nReferx, long p_nRefery, short p_nKind, short p_nNo);
	afx_msg short SetElementColor(short ColorR, short ColorG, short ColorB, short p_nKind, short p_nNo);
	afx_msg short ShowLine(long p_nStartx, long p_nStarty, long p_nEndx, long p_nEndy, long p_lpData, short p_nNo);
	afx_msg short ShowPoint(long p_nx, long p_ny, long p_nDia, long p_lpData, short p_nNo);
	afx_msg short ShowRect(long p_nOriginx, long p_nOriginy, long p_nWidth, long p_nHeight, long p_lpData, short p_nNo);
	afx_msg short ShowText(long p_nOriginx, long p_nOriginy, long p_nWidth, long p_nHeight, long p_lpData, LPCTSTR pa_lpszText, short p_nNo);
	afx_msg short GetItemData(long FAR* p_pOutData, short p_nKind, long p_nItem, short p_nNo);
	afx_msg short GetDrawPoint(long p_nItem, long FAR* p_pnOutx, long FAR* p_pnOuty, short p_nNo);
	afx_msg short GetDrawLine(long p_nItem, long FAR* p_pnOStartx, long FAR* p_pnOStarty, long FAR* p_pnOEndx, long FAR* p_pnOEndy, short p_nNo);
	afx_msg short GetDrawRect(long p_nItem, long FAR* p_pnOOriginx, long FAR* p_pnOOriginy, long FAR* p_pnOWidth, long FAR* p_pnOHeight, short p_nNo);
	afx_msg short GetMousePosition(long p_x, long p_y);
	afx_msg short DeleteElement(long p_nItem, short p_nDrawState, short p_nNo);
	afx_msg short SetItemData(long p_pData, short p_nKind, long p_nItem, short p_nNo);
	afx_msg short EnsureElementVisible(long p_nItem, short p_nKind, short p_nNo);
	afx_msg short SetShowRuler(BOOL p_bShowRuler, short p_nNo);
	afx_msg short SetShowState(short p_nShowState, short p_nNo);
	afx_msg short GetShowState(short p_nNo);
	afx_msg short SetDrawState(short p_nDrawState, short p_nNo);
	afx_msg void RefreshImg();
	afx_msg short GetElementNum(short FAR* p_nOutNum, short p_nKind, short p_nNo);
	afx_msg short GetDrawText(long p_nItem, long FAR* p_pnOOriginx, long FAR* p_pnOOriginy, long FAR* p_pnOWidth, long FAR* p_pnOHeight, LPCTSTR p_lpOText, short FAR* p_pnLen, short p_nNo);
	afx_msg short RotateImg(short p_nNo, double p_dAngle, short p_nMode, BOOL p_bInterpolate, BOOL p_bContinue);
	afx_msg short StretchImg(short p_nNo, double p_fZoom, BOOL p_bContinue);
	afx_msg void SetShowRatio(float FAR* p_fpWidthRatio, float FAR* p_fpHeightRatio);
	afx_msg void SetMagnifer(BOOL p_bMagnify, short p_nOffsetx, short p_nOffsety, short p_nWidth, short p_nHeight);
	afx_msg void SetText(BOOL p_nNeedBack, short p_nEditType, VARIANT FAR* pa_lpString, short p_iCount);
	afx_msg void SetTextNeedBack(BOOL p_bNeedBack);
	afx_msg short PrintImg(short p_nNo, float p_fZoom, short p_nPointx, short p_nPointy);
	afx_msg short PrintImage(short p_nNo, long p_nWidth, long p_nHeight, short p_nPointx, short p_nPointy);
	afx_msg short RotateImage(short p_nNo, short p_dAngle, short p_bContinue);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CJetImgCtrlCtrl)
	void FireClickImg(long p_x, long p_y)
		{FireEvent(eventidClickImg,EVENT_PARAM(VTS_I4  VTS_I4), p_x, p_y);}
	void FireElementGetFocus(long p_nItem, short p_nDrawState)
		{FireEvent(eventidElementGetFocus,EVENT_PARAM(VTS_I4  VTS_I2), p_nItem, p_nDrawState);}
	void FireElementLoseFocus(long p_nItem, short p_nDrawState)
		{FireEvent(eventidElementLoseFocus,EVENT_PARAM(VTS_I4  VTS_I2), p_nItem, p_nDrawState);}
	void FireBeginModify(long p_nItem, short p_nDrawState)
		{FireEvent(eventidBeginModify,EVENT_PARAM(VTS_I4  VTS_I2), p_nItem, p_nDrawState);}
	void FireBeginDrawNew(short p_nDrawState)
		{FireEvent(eventidBeginDrawNew,EVENT_PARAM(VTS_I2), p_nDrawState);}
	void FireEndDrawNew(long p_nItem, short p_nDrawState)
		{FireEvent(eventidEndDrawNew,EVENT_PARAM(VTS_I4  VTS_I2), p_nItem, p_nDrawState);}
	void FireEndModify(long p_nItem, short p_nDrawState)
		{FireEvent(eventidEndModify,EVENT_PARAM(VTS_I4  VTS_I2), p_nItem, p_nDrawState);}
	void FireOnDrawing(short p_nDrawState)
		{FireEvent(eventidOnDrawing,EVENT_PARAM(VTS_I2), p_nDrawState);}
	void FireOnModifying(long p_nItem, short p_nDrawState)
		{FireEvent(eventidOnModifying,EVENT_PARAM(VTS_I4  VTS_I2), p_nItem, p_nDrawState);}
	void FireOnDraw(long p_pDC)
		{FireEvent(eventidOnDraw,EVENT_PARAM(VTS_I4), p_pDC);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	void vClearFocus();
	enum {
	//{{AFX_DISP_ID(CJetImgCtrlCtrl)
	dispidOutLineColor = 1L,
	dispidImgBackColor = 2L,
	dispidMagnify = 3L,
	dispidCol = 4L,
	dispidRow = 5L,
	dispidSetMaxImg = 6L,
	dispidGetDrawState = 7L,
	dispidGetMaxImg = 8L,
	dispidGetCurImgNum = 9L,
	dispidCoverImgFile = 10L,
	dispidAddImgFile = 11L,
	dispidAddImgDib = 12L,
	dispidCoverImgDib = 13L,
	dispidSetFocus = 14L,
	dispidGetFocus = 15L,
	dispidClearAllImg = 16L,
	dispidSetReferPoint = 17L,
	dispidSetElementColor = 18L,
	dispidShowLine = 19L,
	dispidShowPoint = 20L,
	dispidShowRect = 21L,
	dispidShowText = 22L,
	dispidGetItemData = 23L,
	dispidGetDrawPoint = 24L,
	dispidGetDrawLine = 25L,
	dispidGetDrawRect = 26L,
	dispidGetMousePosition = 27L,
	dispidDeleteElement = 28L,
	dispidSetItemData = 29L,
	dispidEnsureElementVisible = 30L,
	dispidSetShowRuler = 31L,
	dispidSetShowState = 32L,
	dispidGetShowState = 33L,
	dispidSetDrawState = 34L,
	dispidRefreshImg = 35L,
	dispidGetElementNum = 36L,
	dispidGetDrawText = 37L,
	dispidRotateImg = 38L,
	dispidStretchImg = 39L,
	dispidSetShowRatio = 40L,
	dispidSetMagnifer = 41L,
	dispidSetText = 42L,
	dispidSetTextNeedBack = 43L,
	dispidPrintImg = 44L,
	dispidPrintImage = 45L,
	dispidRotateImage = 46L,
	eventidClickImg = 1L,
	eventidElementGetFocus = 2L,
	eventidElementLoseFocus = 3L,
	eventidBeginModify = 4L,
	eventidBeginDrawNew = 5L,
	eventidEndDrawNew = 6L,
	eventidEndModify = 7L,
	eventidOnDrawing = 8L,
	eventidOnModifying = 9L,
	eventidOnDraw = 10L,
	//}}AFX_DISP_ID
	};
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JETIMGCTRLCTL_H__C2111BF9_4B15_44C9_9BF1_AA87D4C10D40__INCLUDED)
