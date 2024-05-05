// MyPoint.h: interface for the CMyPoint class.
//
// 文件名	: MyPoint.h
// 所属项目	: 公共项目
// 版本号	: 1.0
// 内容		: 显示点头文件
// 创建日期	: 2001/02/01
// 作者		: yaka
// 备注 		: 
//////////////////////////////////////////////////////////////////////
//Create by yaka 20010427
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "math.h"
// 类名		: CMyPoint
// 父类名	: CDrawElement
// 功能描述	: 显示点类
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
class CMyPoint:public CDrawElement
{
private:
	CBrush m_brush1;//焦点时的brush;
	CBrush m_brush2;//非焦点时的brush
	CRect m_rtShow;//仅显示时用到；
public:
	CPoint m_Point;
	long m_lradii;  //半径
	BOOL m_bIsFocus;
	LPVOID m_lpDate;
public:
	CMyPoint():m_Point(0,0),m_brush1(RGB(0,0,255)),
		m_brush2(RGB(255,0,0))
	{
		m_lradii = 0 ;
		m_bIsFocus=FALSE;
		m_lpDate = NULL;
	}
	CMyPoint(const CMyPoint& pa_MyPoint):m_brush1(RGB(0,0,255)),
		m_brush2(RGB(255,0,0))
	{
		m_Point = pa_MyPoint.m_Point;
		m_lradii = pa_MyPoint.m_lradii;
		m_bIsFocus=pa_MyPoint.m_bIsFocus;
		m_lpDate = pa_MyPoint.m_lpDate;
	}
	DECLARE_DYNCREATE(CMyPoint)

public:
	void SetFocus(BOOL p_bFocus){m_bIsFocus = p_bFocus;};
	BOOL GetFocus(){return m_bIsFocus;};
	void SetItemDate(LPVOID p_lpDate){m_lpDate = p_lpDate;};
	LPVOID GetItemDate(){return m_lpDate;};
	void OffsetElement(CPoint pa_Offset)
	{
		m_Point.Offset(pa_Offset.x,pa_Offset.y);
	}
	void OffsetElement(int px,int py)
	{
		m_Point.Offset(px,py);
	}

	void StretchElement(float p_fx,float p_fy)
	{
		m_Point.x = (int)(m_Point.x / p_fx);
		m_Point.y = (int)(m_Point.y / p_fy);
		m_lradii = long(m_lradii / sqrt(p_fx * p_fy));
	}

	CMyPoint& operator=(const CMyPoint& pa_MyPoint){
		m_Point = pa_MyPoint.m_Point;
		m_lradii = pa_MyPoint.m_lradii;
		m_bIsFocus=pa_MyPoint.m_bIsFocus;
		m_lpDate = pa_MyPoint.m_lpDate;
		return *this;
	}
	/*
	CMyPoint& operator=(const CPoint& pa_Point)
	{
		m_Point = pa_Point;
		return *this;
	}
	*/
	BOOL IsElementEmpty()
	{
		return (m_lradii <= 0);
	}
//	void NormalizeElement()
//	{
//	}
	void SetElementEmpty()
	{	
		m_lradii = 0 ;
	}
	void InflatePoint(int p_x, int p_y)
	{
		m_lradii = m_lradii + (p_x + p_y)/2 ;
	}
	
	//p_ShowRect为允许显示的区域。实际需要显示的区域可能大于这个区域。以整个窗口的左上角为坐标；
	void ShowElement(CRect p_ShowRect,CDC* pDC)
	{
		long ltemp = 0;
		
		if (m_Point.x < p_ShowRect.right && m_Point.x > p_ShowRect.left && m_Point.y < p_ShowRect.bottom && m_Point.y > p_ShowRect.top)
		{
			ltemp = min(p_ShowRect.right - m_Point.x , m_Point.x - p_ShowRect.left);
			ltemp = min(p_ShowRect.bottom - m_Point.y , ltemp);
			ltemp = min(m_Point.y - p_ShowRect.top , ltemp);
			ltemp = min(m_lradii , ltemp);
			m_rtShow = CRect(m_Point.x - ltemp, m_Point.y - ltemp, m_Point.x + ltemp,m_Point.y + ltemp);
		}
		else
			m_rtShow = CRect(0,0,0,0);
		CBrush *pOldBrush = NULL;
		if(m_bIsFocus)
		{
			pOldBrush = pDC->SelectObject(&m_brush1);
		}
		else{
			pOldBrush = pDC->SelectObject(&m_brush2);
		}
		pDC->Ellipse(&m_rtShow);
		pDC->SelectObject(pOldBrush);
		
	}

	inline BOOL bPointInElement(CPoint& pa_Point)
	{
		if ((long)sqrt((pa_Point.x - m_Point.x) * (pa_Point.x - m_Point.x) + 
			(pa_Point.y - m_Point.y) * (pa_Point.y - m_Point.y)) <= (m_lradii -2))
			return TRUE;
		else
			return FALSE;
	}
	virtual ~CMyPoint(){};
};

