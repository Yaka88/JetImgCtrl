// MyRect.h: interface for the CMyRect class.
//
//////////////////////////////////////////////////////////////////////
// �ļ���	: MyRect.h
// ������Ŀ	: ������Ŀ
// �汾��	: 1.0
// ����		: ��ʾ����ͷ�ļ�
// ��������	: 2001/02/01
// ����		: yaka
// ��ע 		: 
#if !defined(AFX_MYRECT_H__38B0B447_3F26_473C_B9B6_ADB3FECD3D99__INCLUDED_)
#define AFX_MYRECT_H__38B0B447_3F26_473C_B9B6_ADB3FECD3D99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ����		: CMyRect
// ������	: CDrawElement
// ��������	: ��ʾ������
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
class CMyRect:public CDrawElement
{
private:
	CPen m_pen1;//����ʱ��pen;
	CPen m_pen2;//�ǽ���ʱ��pen
	CRect m_rect;
	CRect m_rtShow;//����ʾʱ�õ���
	void SetLRTB()
	{
		left = m_rect.left;
		right = m_rect.right;
		top = m_rect.top;
		bottom = m_rect.bottom;
	}
	void SetRect()
	{
		m_rect.left = left;
		m_rect.right = right;
		m_rect.top = top;
		m_rect.bottom = bottom;
	}
public://���⸽����m_rect��
	int left ;
	int right;
	int top;
	int bottom;
	BOOL m_bIsFocus;
	LPVOID m_lpDate;
public:
	CMyRect():m_rect(-1,-1,-1,-1),m_pen1(PS_DASH, 1, RGB(255,0,0)),
		m_pen2(PS_SOLID, 1, RGB(0,255,0))
	{
		SetLRTB();
		m_bIsFocus=FALSE;
		m_lpDate = NULL;
	}
	CMyRect(const CMyRect& pa_MyRect):m_pen1(PS_DASH, 1, RGB(255,0,0)),
		m_pen2(PS_SOLID, 1, RGB(0,255,0))
	{
		//m_rect = pa_MyRect.m_rect;//�����ã��Է������ݳ�Ա֮����ܲ�ͬ������publicΪ׼��
		m_rect.left = pa_MyRect.left;
		m_rect.right = pa_MyRect.right;
		m_rect.top = pa_MyRect.top;
		m_rect.bottom = pa_MyRect.bottom;
		SetLRTB();
		m_bIsFocus=pa_MyRect.m_bIsFocus;
		m_lpDate = pa_MyRect.m_lpDate;
	}
	DECLARE_DYNCREATE(CMyRect)

public:
	void SetFocus(BOOL p_bFocus){m_bIsFocus = p_bFocus;};
	BOOL GetFocus(){return m_bIsFocus;};
	void SetItemDate(LPVOID p_lpDate){m_lpDate = p_lpDate;};
	LPVOID GetItemDate(){return m_lpDate;};
	void OffsetElement(CPoint pa_Offset)
	{
		SetRect();//���ܶ�����֤���ݳ�Ա֮��ͬ����
		m_rect.OffsetRect(pa_Offset.x,pa_Offset.y);
		SetLRTB();//���ܶ�����֤�Է������ݳ�Ա֮��ͬ����
	}
	void OffsetElement(int px,int py)
	{
		SetRect();//���ܶ�����֤���ݳ�Ա֮��ͬ����
		m_rect.OffsetRect(px,py);
		SetLRTB();//���ܶ�����֤�Է������ݳ�Ա֮��ͬ����
	}
	void NormalizeElement()
	{
		SetRect();//���ܶ�����֤���ݳ�Ա֮��ͬ����
		m_rect.NormalizeRect();
		SetLRTB();//ע�ⶼ���ܶ���
	}
	void StretchElement(float p_fx,float p_fy)
	{
		m_rect.left = (long)(m_rect.left / p_fx);
		m_rect.right = (long)(m_rect.right / p_fx);
		m_rect.top = (long)(m_rect.top / p_fy);
		m_rect.bottom = (long)(m_rect.bottom / p_fy);
		SetLRTB();
	}

	CMyRect& operator=(const CMyRect& pa_MyRect){
		//m_rect = pa_MyRect.m_rect;//�����ã��Է������ݳ�Ա֮����ܲ�ͬ������publicΪ׼��
		m_rect.left = pa_MyRect.left;
		m_rect.right = pa_MyRect.right;
		m_rect.top = pa_MyRect.top;
		m_rect.bottom = pa_MyRect.bottom;
		SetLRTB();//���ܶ�����֤�Է������ݳ�Ա֮��ͬ����
		m_bIsFocus=pa_MyRect.m_bIsFocus;
		m_lpDate = pa_MyRect.m_lpDate;
		return *this;
	}
	CMyRect& operator=(const CRect& pa_Rect){
		m_rect = pa_Rect;
		SetLRTB();//���ܶ�����֤�Է������ݳ�Ա֮��ͬ����
		return *this;
	}
	CRect* GetRect()
	{
		return &m_rect;
	}
	BOOL IsElementEmpty()
	{
		SetRect();//���ܶ�����֤���ݳ�Ա֮��ͬ����
		return m_rect.IsRectEmpty();
	}
	void SetElementEmpty()
	{
		SetRect();//���ܶ�����֤���ݳ�Ա֮��ͬ����
		m_rect.SetRectEmpty();
		SetLRTB();//���ܶ�����֤�Է������ݳ�Ա֮��ͬ����
	}
	void InflateRect(int p_x, int p_y)
	{
		SetRect();//���ܶ�����֤���ݳ�Ա֮��ͬ����
		m_rect.InflateRect(p_x,p_y);
		SetLRTB();//���ܶ�����֤�Է������ݳ�Ա֮��ͬ����
	}
	
	//p_ShowRectΪ������ʾ������ʵ����Ҫ��ʾ��������ܴ�������������������ڵ����Ͻ�Ϊ���ꣻ
	void ShowElement(CRect p_ShowRect,CDC* pDC)
	{
		int iFlag = 0;
		m_rtShow = m_rect;

		if(left < p_ShowRect.left){
			m_rtShow.left = p_ShowRect.left;
			iFlag |= 1;
		}
		if(right < p_ShowRect.left){
			m_rtShow.right = p_ShowRect.left;
			iFlag |= 2;
		}
		if(right > p_ShowRect.right){
			m_rtShow.right = p_ShowRect.right;
			iFlag |= 2;
		}
		if(left > p_ShowRect.right){
			m_rtShow.left = p_ShowRect.right;
			iFlag |= 1;
		}
		if(top < p_ShowRect.top){
			m_rtShow.top = p_ShowRect.top;
			iFlag |= 4;
		}
		if(bottom < p_ShowRect.top){
			m_rtShow.bottom = p_ShowRect.top;
			iFlag |= 8;
		}
		if(bottom > p_ShowRect.bottom){
			m_rtShow.bottom = p_ShowRect.bottom;
			iFlag |= 8;
		}
		if(top > p_ShowRect.bottom){
			m_rtShow.top = p_ShowRect.bottom;
			iFlag |= 4;
		}
		CPen *pOldPen = NULL;
		int nOldRop;
		if(m_bIsFocus){
			pOldPen = pDC->SelectObject(&m_pen1);
			nOldRop = pDC->SetROP2(R2_XORPEN);
		}
		else{
			pOldPen = pDC->SelectObject(&m_pen2);
			nOldRop = pDC->SetROP2(R2_COPYPEN);
		}
		pDC->MoveTo(m_rtShow.left, m_rtShow.bottom);
		(iFlag & 8) ? pDC->MoveTo(m_rtShow.right, m_rtShow.bottom) : pDC->LineTo(m_rtShow.right, m_rtShow.bottom);
		(iFlag & 2) ? pDC->MoveTo(m_rtShow.right, m_rtShow.top) : pDC->LineTo(m_rtShow.right, m_rtShow.top);
		(iFlag & 4) ? pDC->MoveTo(m_rtShow.left, m_rtShow.top) : pDC->LineTo(m_rtShow.left, m_rtShow.top);
		(iFlag & 1) ? pDC->MoveTo(m_rtShow.left, m_rtShow.bottom) : pDC->LineTo(m_rtShow.left, m_rtShow.bottom);
		pDC->SetROP2(nOldRop);
		pDC->SelectObject(pOldPen);
		//���m_rectҲ��Ҫ��֮�ı���ִ��ϵ����䣺
		/*m_rect = m_rtShow;
		SetLRTB();*/
	}

	inline BOOL bPointInElement(CPoint& pa_Point)
	{
		SetRect();//���ܶ�����֤���ݳ�Ա֮��ͬ����
		CRect rect(m_rect);
		rect.DeflateRect(2,2);//ע��4���н����ģ���֤������΢����������
		rect.NormalizeRect();
		if((pa_Point.x<rect.right) && (pa_Point.x >= rect.left) && (pa_Point.y < rect.bottom) && (pa_Point.y >= rect.top))
			return TRUE;
		else
			return FALSE;
	}
	virtual ~CMyRect(){};
};

#endif // !defined(AFX_MYRECT_H__38B0B447_3F26_473C_B9B6_ADB3FECD3D99__INCLUDED_)
