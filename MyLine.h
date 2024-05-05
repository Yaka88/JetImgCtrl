//CMyLine.h
//
// 文件名	: MyLine.h
// 所属项目	: 公共项目
// 版本号	: 1.0
// 内容		: 显示线条头文件
// 创建日期	: 2001/02/01
// 作者		: yaka
// 备注 		: 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// 类名		: CMyLine
// 父类名	: CDrawElement
// 功能描述	: 显示线条类
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
class CMyLine:public CDrawElement
{
public:
	CMyLine():m_Begin(-1,-1),m_End(-1,-1),m_pen1(PS_DASH, 1, RGB(255, 0, 0)),
		m_pen2(PS_SOLID, 1, RGB(0, 255, 0))
	{
		m_bIsFocus=FALSE;
		m_lpDate = NULL;
	}
	CMyLine(const CMyLine& pa_Line):m_pen1(PS_DASH, 1, RGB(255, 0, 0)),
		m_pen2(PS_SOLID, 1, RGB(0, 255, 0)){
		m_Begin.x=pa_Line.m_Begin.x;
		m_End.x=pa_Line.m_End.x;
		m_Begin.y=pa_Line.m_Begin.y;
		m_End.y=pa_Line.m_End.y;
		m_bIsFocus = pa_Line.m_bIsFocus;
		m_lpDate = pa_Line.m_lpDate;
	}
	CPoint m_Begin;	
	CPoint m_End;
	LPVOID m_lpDate;
	DECLARE_DYNCREATE(CMyLine)
private:
	CPen m_pen1;//焦点时的pen;
	CPen m_pen2;//非焦点时的pen
	CPoint m_ShowBegin;//仅显示时用到；
	CPoint m_ShowEnd;//仅显示时用到；请参考MyRect.h中的m_rtShow，谨慎添加。
	BOOL m_bIsFocus;
public:
	void SetItemDate(LPVOID p_lpDate){m_lpDate = p_lpDate;};
	LPVOID GetItemDate(){return m_lpDate;};
	void SetFocus(BOOL p_bFocus){m_bIsFocus = p_bFocus;};
	BOOL GetFocus(){return m_bIsFocus;};
	void OffsetElement(CPoint pa_Offset){
		m_Begin.x+=pa_Offset.x;
		m_End.x+=pa_Offset.x;
		m_Begin.y+=pa_Offset.y;
		m_End.y+=pa_Offset.y;
	}
	void OffsetElement(int px,int py){
		m_Begin.x+=px;
		m_End.x+=px;
		m_Begin.y+=py;
		m_End.y+=py;
	}
	void NormalizeElement(){
		int iTemp;
		if(m_Begin.x>m_End.x){
			iTemp=m_Begin.x;
			m_Begin.x=m_End.x;
			m_End.x=iTemp;
			iTemp=m_Begin.y;
			m_Begin.y=m_End.y;
			m_End.y=iTemp;
		}
	}
	CMyLine& operator=(const CMyLine& pa_Line){
		m_Begin.x=pa_Line.m_Begin.x;
		m_End.x=pa_Line.m_End.x;
		m_Begin.y=pa_Line.m_Begin.y;
		m_End.y=pa_Line.m_End.y;
		m_bIsFocus = pa_Line.m_bIsFocus;
		m_lpDate = pa_Line.m_lpDate;
		return *this;
	}
	BOOL IsElementEmpty(){
		if((m_Begin.x==m_End.x) && (m_End.y==m_Begin.y))
			return TRUE;
		else
			return FALSE;
	}
	void SetElementEmpty(){
		m_Begin.x=m_End.x;
		m_End.y=m_Begin.y;
	}
	void DrawCrossLine(CDC* pdc, int x, int y)
	{
		COLORREF cr=RGB(0, 255, 0);
		pdc->SetPixel(x, y, cr);
		pdc->SetPixel(x-1, y+1, cr);	pdc->SetPixel(x-2, y+2, cr);	pdc->SetPixel(x-3, y+3, cr);
		pdc->SetPixel(x-1, y-1, cr);	pdc->SetPixel(x-2, y-2, cr);	pdc->SetPixel(x-3, y-3, cr);
		pdc->SetPixel(x+1, y+1, cr);	pdc->SetPixel(x+2, y+2, cr);	pdc->SetPixel(x+3, y+3, cr);
		pdc->SetPixel(x+1, y-1, cr);	pdc->SetPixel(x+2, y-2, cr);	pdc->SetPixel(x+3, y-3, cr);
	}
	void StretchElement(float p_fx,float p_fy)
	{
		m_Begin.x = (long)(m_Begin.x / p_fx);
		m_End.x = (long)(m_End.x / p_fx);
		m_Begin.y = (long)(m_Begin.y / p_fy);
		m_End.y = (long)(m_End.y / p_fy);
	}
	//p_ShowRect为允许显示的区域。实际需要显示的区域可能大于这个区域。以整个窗口的左上角为坐标；
	void ShowElement(CRect p_ShowRect,CDC* pDC)
	{
		int iFlag = 0;
		int Delx,Dely;
		float fk = -(float)(m_End.y-m_Begin.y)/(m_End.x-m_Begin.x);
		if(m_Begin.x < p_ShowRect.left){
			if(m_End.x <= p_ShowRect.left)
				return;
			Delx=p_ShowRect.left-m_Begin.x;
			m_Begin.x = p_ShowRect.left;
			m_Begin.y -= (int)(fk*Delx+0.5);
			iFlag |= 1;
		}
		if(m_Begin.y < p_ShowRect.top){
			if(m_End.y <= p_ShowRect.top)
				return;
			Dely = p_ShowRect.top-m_Begin.y;
			m_Begin.y = p_ShowRect.top;
			m_Begin.x -= (int)(Dely/fk+0.5);
			iFlag |= 1;
		}
		if(m_Begin.y > p_ShowRect.bottom){
			if(m_End.y>=p_ShowRect.bottom)
				return;
			Dely = p_ShowRect.bottom-m_Begin.y;
			m_Begin.y = p_ShowRect.bottom;
			m_Begin.x -= (int)(Dely/fk+0.5);
			iFlag |= 1;
		}
		if(m_End.x >= p_ShowRect.right){
			if(m_Begin.x >= p_ShowRect.right)
				return;
			Delx=p_ShowRect.right-m_End.x;
			m_End.x = p_ShowRect.right;
			if(fk>0)
				m_End.y -= (int)(fk*Delx-0.5);
			else			
				m_End.y -= (int)(fk*Delx-0.5);
			iFlag |= 2;
		}
		if(m_End.y >= p_ShowRect.bottom){
			Dely = p_ShowRect.bottom-m_End.y;
			m_End.y = p_ShowRect.bottom;
			m_End.x -= (int)(Dely/fk-0.5);
			iFlag |= 2;
		}
		if(m_End.y < p_ShowRect.top){
			Dely = p_ShowRect.top-m_End.y;
			m_End.y = p_ShowRect.top;
			m_End.x -= (int)(Dely/fk+0.5);
			iFlag |= 2;
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
		pDC->MoveTo(m_Begin.x, m_Begin.y);
		if(!(iFlag&1))
			DrawCrossLine(pDC, m_Begin.x, m_Begin.y);
		pDC->LineTo(m_End.x, m_End.y);
		if(!(iFlag&2))
			DrawCrossLine(pDC, m_End.x, m_End.y);
		pDC->SetROP2(nOldRop);
		pDC->SelectObject(pOldPen);
	}
	inline BOOL bPointInElement(CPoint& pa_Point)
	{
		CRect rect(m_Begin.x,m_Begin.y,m_End.x,m_End.y);
		rect.DeflateRect(6,6);//注意6是有讲究的，保证不包括微调触发区域；
		rect.NormalizeRect();
		if((pa_Point.x<rect.right) && (pa_Point.x >= rect.left) && (pa_Point.y < rect.bottom) && (pa_Point.y >= rect.top))
			return TRUE;
		else
			return FALSE;
	}
	virtual ~CMyLine(){};
};