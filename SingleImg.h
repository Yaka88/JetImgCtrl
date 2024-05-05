// SingleImg.h: interface for the CSingleImg class.
//
//////////////////////////////////////////////////////////////////////
// �ļ���	: SingleImg.h
// ������Ŀ	: ������Ŀ
// �汾��	: 1.0
// ����		: ��ͼ��ͷ�ļ�
// ��������	: 2001/02/01
// ����		: yaka
// ��ע 		: 
#if !defined(AFX_SINGLEIMG_H__55683B28_6B5C_4627_BF71_9AE942D15674__INCLUDED_)
#define AFX_SINGLEIMG_H__55683B28_6B5C_4627_BF71_9AE942D15674__INCLUDED_
#include "DrawDIB.h"   //add by yaka 200106020
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//add by yaka 20010416
//��������
#define	NOTDRAG			0
#define	DRAGEAST		1
#define	DRAGSOUTH		2
#define	DRAGWEST		3
#define	DRAGNORTH		4
//add end

#define LINE3D 4	//Ӧ�ô���2�������Ե�ߣ����Ϊ2���ͻḲ��ͼ��
class CJetImgCtrlCtrl;
// ����		: CSingleImg
// ������	: NULL
// ��������	: ��ͼ����
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
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

	//����ͼ����ʾ״̬����m_iSetState=STRETCH_ANY_SCALEʱ���������SetStretchScale��������ΪSTRETCH_NOT����
	void	SetShowState(short p_nState);
	int		GetShowState(){return m_iShowState;};
	void	SetDrawState(short p_nState);
	int		GetDrawState(){return m_iSetState;};
	void	SetStretchScale(float p_fScale ,BOOL p_bContinue);
	void	SetRotate(double p_dAngle, BOOL p_bContinue);
	BOOL	bAjustImgDib();
	void WorkOutShowRect();

// Attributes
	int m_nDibWidth, m_nDibHeight;//λͼ��͸ߣ�

	short	m_nDrag;   //add by yaka 20010416
	BOOL	m_bShowMagnifer;

	int m_wBit;
	BOOL m_bCanSetRect,m_bCanSetLine,m_bCanSetText,m_bCanSetPoint;
	CPoint  m_MousePoint;
	CPalette* mp_Palette;

	CRect   m_rtTotalRect;//�÷�ͼ���������ؼ������е�������ʾ����
	CRect	m_rtShowRect;//�÷�ͼ���������ؼ������е�ͼ��ʵ����ʾ���򣬱�������ʾ����С����ڣ�
	CArray<CMyRect*,CMyRect*> m_DocRectArray;//��ŷ��������(������Ϣ�������������ͼ�����Ͻ�Ϊ��׼�����ʵ��С)
	CArray<CMyLine*,CMyLine*> m_DocLineArray;//�������������
	CArray<CMyText*,CMyText*> m_DocTextArray;
	CArray<CMyPoint*,CMyPoint*> m_DocPointArray;
	float m_fzoomx,m_fzoomy;		//��ͼ��ǰ���ű�����
	BOOL m_bNeedFreeMemory;//�Ƿ��Լ��ͷ��ڴ棻

	virtual ~CSingleImg();
private:
	CJetImgCtrlCtrl* m_pShowWnd;//��ͼ����ʾ�������ڵĴ��ڣ�
	CDrawDIB m_DrawDib;
	CSize* m_pSizeLine;
	int* m_pHScrollMax;
	int* m_pVScrollMax;
	DWORD i_SubImgCount;
	DWORD i_SubImgIndex;
	HDIB m_Orihdib;				//ͼ���ڴ�����
	HDIB m_hdib;			//add by yaka 20010620
	BOOL m_bShowRuler;//�Ƿ���ʾ��ߣ�
	int m_ixOffset;//�����н���ʱ���������ٹ�������λ�ã�
	int m_iyOffset;//�����н���ʱ���������ٹ�������λ�ã�
	BOOL m_bIsFocus;//��ͼ����ʾ����ǰ�Ƿ�Ϊ���㣻
//	HANDLE m_hHeap;	//�ڴ�Ѿ����
	
	CMyRect m_rtTempViewRect;//��ʱ������
	CMyLine	m_liTempViewLine;//��ʱ������
	CMyText	m_rtTempViewText;
	CMyPoint m_rtTempViewPoint;
	int		m_iSetState;//����״̬�����������á��������ã������ã��ı�����


	float m_fScale;					//������ʾ״̬Ϊ������ʱ���ã�
	int m_nCurWidth,m_nCurHeight;	//��ͼ��ǰ���ź󳤶ȣ�
	int		m_iShowState;//��ʾ״̬����STRETCH_SCALE_FILLRECT,STRETCH_NOTSCALE_FILLRECT,STRETCH_NOT.....
	//add by yaka 20010414
	BOOL	m_bRotateState;
	double  m_dAngle;
	//add end

	//�����Ƿ���Ҫˢ�µı�־������
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
