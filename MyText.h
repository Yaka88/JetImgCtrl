// MyText.h: interface for the MyText class.
//
//////////////////////////////////////////////////////////////////////
// 文件名	: MyText.h
// 所属项目	: 公共项目
// 版本号	: 1.0
// 内容		: 显示文本框头文件
// 创建日期	: 2001/02/01
// 作者		: yaka
// 备注 		: 
#if !defined(AFX_MYTEXT_H__B29532DF_6760_45A0_8216_BFCD70A87C1B__INCLUDED_)
#define AFX_MYTEXT_H__B29532DF_6760_45A0_8216_BFCD70A87C1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern CEdit* g_pEdit;
extern CComboBox* g_pCombobox;
extern CListBox* g_pListbox;
// 类名		: CMyText
// 父类名	: CDrawElement
// 功能描述	: 显示文本框类
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
class CMyText:public CDrawElement
{
private:
	CPen m_pen1;//焦点时的pen;
	CPen m_pen2;//非焦点时的pen
	CRect m_rect;
	CRect m_rtShow;//仅显示时用到；
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
public://纯粹附属于m_rect；
	int left ;
	int right;
	int top;
	int bottom;
//	CEdit* edit;  //test
	BOOL m_bIsFocus;
	BOOL m_bNeedBack;//是否需要绘制背景及文本框等；
	//add by yaka 20010426
	CArray <CString, CString> ma_lpTextIn;//字符串数组
	int m_iCount;	
	//add end
	short m_nEditType; 
	LPVOID m_lpDate;
	CString m_strText;

public:
	CMyText():m_rect(-1,-1,-1,-1),m_pen1(PS_DASH, 1, RGB(0,255,0)),
		m_pen2(PS_SOLID, 1, RGB(0,0,0))
	{
//	m_pEdit = NULL;
		SetLRTB();
		m_bIsFocus=FALSE;
		m_bNeedBack = FALSE;
		m_nEditType = EDIT; //test
		m_lpDate = NULL;
//		ma_lpTextIn = NULL;
		m_iCount = 0;
		m_strText.Empty();
	}
	CMyText(const CMyText& pa_MyText):m_pen1(PS_DASH, 1, RGB(0,255,0)),
		m_pen2(PS_SOLID, 1, RGB(0,0,0))
	{
//		m_pEdit = NULL ;
		//m_rect = pa_MyText.m_rect;//不能用，对方的数据成员之间可能不同步，以public为准；
		m_rect.left = pa_MyText.left;
		m_rect.right = pa_MyText.right;
		m_rect.top = pa_MyText.top;
		m_rect.bottom = pa_MyText.bottom;
		SetLRTB();
		m_bIsFocus=pa_MyText.m_bIsFocus;
		m_lpDate = pa_MyText.m_lpDate;
		m_strText = pa_MyText.m_strText;
		m_bNeedBack = pa_MyText.m_bNeedBack;
		m_nEditType = pa_MyText.m_nEditType; 
		ma_lpTextIn.Copy(pa_MyText.ma_lpTextIn); 
		m_iCount = pa_MyText.m_iCount; 
	}
	DECLARE_DYNCREATE(CMyText)

public:
	
	BOOL GetFocus(){return m_bIsFocus;};
	void SetItemDate(LPVOID p_lpDate){m_lpDate = p_lpDate;};
	LPVOID GetItemDate(){return m_lpDate;};
	void SetFocus(BOOL p_bFocus)
	{	//modify by kaka 200104026
		if (m_bIsFocus == TRUE && p_bFocus == FALSE)
		{
			switch (m_nEditType)
			{
			case EDIT: 
				if (g_pEdit !=NULL)
				{
				g_pEdit->GetWindowText(m_strText);
				g_pEdit->DestroyWindow();
				g_pEdit = NULL;
				}
				break;
			case COMBOBOX:
				if (g_pCombobox !=NULL)
				{
				g_pCombobox->GetWindowText(m_strText);
				g_pCombobox->DestroyWindow();
				g_pCombobox = NULL;
				}
				break;
			case LISTBOX:
				if (g_pListbox !=NULL)
				{
				int nIndex = g_pListbox->GetCurSel();
				if (nIndex != LB_ERR)
				{
					g_pListbox->GetText(nIndex,m_strText);
				}
				g_pListbox->DestroyWindow();
				g_pListbox = NULL;
				}
				break;
			case STATIC:
				break;
			}
		}//modify end
		m_bIsFocus = p_bFocus;
	}
	//add by yaka 20010426
	void CreateEdit(CWnd* pParentWnd)
	{
		int i;
		switch (m_nEditType)
		{
		case EDIT:
			if (g_pEdit == NULL)
			{
				g_pEdit = new CEdit();
				g_pEdit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER |ES_AUTOHSCROLL,
				CRect(0, 0, 0, 0), pParentWnd, UINT(-1));
			}
			g_pEdit->SetWindowText(m_strText);
			break;
		case COMBOBOX:
			if (g_pCombobox == NULL)
			{
				g_pCombobox = new CComboBox();
				g_pCombobox->Create(CBS_AUTOHSCROLL|CBS_DROPDOWN|WS_CHILD|WS_VSCROLL|CBS_DISABLENOSCROLL|WS_VISIBLE,
				CRect(0, 0, 0, 0), pParentWnd, UINT(-1));
				for(i=0; i<m_iCount; i++)
				{
					TCHAR tTempText[50];
				_stprintf(tTempText,TEXT("%s"),ma_lpTextIn[i]);
					g_pCombobox->AddString(tTempText);
				}
			}
			g_pCombobox->SetWindowText(m_strText);
			g_pCombobox->ShowWindow(SW_HIDE);
			break;
		case LISTBOX:
			if (g_pListbox == NULL)
			{
				g_pListbox = new CListBox();
				g_pListbox->Create(LBS_STANDARD|WS_CHILD|WS_VISIBLE|WS_VSCROLL|LBS_DISABLENOSCROLL,
				CRect(0, 0, 0, 0), pParentWnd, UINT(-1));
				for(i=0; i<m_iCount; i++)
				{
					TCHAR tTempText[50];
				_stprintf(tTempText,TEXT("%s"),ma_lpTextIn[i]);
					g_pListbox->AddString(tTempText);
				}
				g_pListbox->ShowWindow(SW_HIDE);
			}
			break;
		case STATIC:
			break;
		}
	}
	//add end
	void OffsetElement(CPoint pa_Offset)
	{
		SetRect();//不能丢，保证数据成员之间同步；
		m_rect.OffsetRect(pa_Offset.x,pa_Offset.y);
		SetLRTB();//不能丢，保证对方的数据成员之间同步；
	}
	void OffsetElement(int px,int py)
	{
		SetRect();//不能丢，保证数据成员之间同步；
		m_rect.OffsetRect(px,py);
		SetLRTB();//不能丢，保证对方的数据成员之间同步；
	}
	void NormalizeElement()
	{
		SetRect();//不能丢，保证数据成员之间同步；
		m_rect.NormalizeRect();
		SetLRTB();//注意都不能丢！
	}
	void StretchElement(float p_fx,float p_fy)
	{
		m_rect.left = (long)(m_rect.left / p_fx);
		m_rect.right = (long)(m_rect.right / p_fx);
		m_rect.top = (long)(m_rect.top / p_fy);
		m_rect.bottom = (long)(m_rect.bottom / p_fy);
		SetLRTB();
	}

	CMyText& operator=(const CMyText& pa_MyText){
		//m_rect = pa_MyText.m_rect;//不能用，对方的数据成员之间可能不同步，以public为准；
		m_rect.left = pa_MyText.left;
		m_rect.right = pa_MyText.right;
		m_rect.top = pa_MyText.top;
		m_rect.bottom = pa_MyText.bottom;
		SetLRTB();//不能丢，保证对方的数据成员之间同步；
		m_bIsFocus=pa_MyText.m_bIsFocus;
		m_lpDate = pa_MyText.m_lpDate;
		m_strText = pa_MyText.m_strText;
		m_bNeedBack = pa_MyText.m_bNeedBack;
		m_nEditType = pa_MyText.m_nEditType; 
		ma_lpTextIn.Copy(pa_MyText.ma_lpTextIn); 
		m_iCount = pa_MyText.m_iCount; 
		return *this;
	}
	CMyText& operator=(const CRect& pa_Rect){
		m_rect = pa_Rect;
		SetLRTB();//不能丢，保证对方的数据成员之间同步；
		return *this;
	}
	CRect* GetRect()
	{
		return &m_rect;
	}
	BOOL IsElementEmpty()
	{
		SetRect();//不能丢，保证数据成员之间同步；
		if(m_rect.IsRectEmpty())
			return TRUE;
		else if(m_strText.IsEmpty())
			return TRUE;
		else
			return FALSE;
	}

	void SetElementEmpty()
	{
		SetRect();//不能丢，保证数据成员之间同步；
		m_rect.SetRectEmpty();
		m_strText.Empty();
		SetLRTB();//不能丢，保证对方的数据成员之间同步；
	}
	void InflateRect(int p_x, int p_y)
	{
		SetRect();//不能丢，保证数据成员之间同步；
		m_rect.InflateRect(p_x,p_y);
		SetLRTB();//不能丢，保证对方的数据成员之间同步；
	}

	//p_ShowRect为允许显示的区域。实际需要显示的区域可能大于这个区域。以整个窗口的左上角为坐标；
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
		int OldBkMode;
		COLORREF TextBkClr;
		COLORREF OldTextColor,OldTextBackColor;
		if(m_bIsFocus){
		

			pOldPen = pDC->SelectObject(&m_pen1);
			nOldRop = pDC->SetROP2(R2_XORPEN);
			TextBkClr = ::GetSysColor(COLOR_HIGHLIGHT);
			OldTextColor = pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
			OldTextBackColor = pDC->SetBkColor(TextBkClr);
			OldBkMode = pDC->SetBkMode(OPAQUE);
		}
		else{
			pOldPen = pDC->SelectObject(&m_pen2);
			nOldRop = pDC->SetROP2(R2_COPYPEN);
			TextBkClr = RGB(0xFF, 0xFF, 0xE0);//RGB(148,148,148);//::GetSysColor(COLOR_WINDOW)
			OldTextColor = pDC->SetTextColor(RGB(255,0,0));//GetSysColor(COLOR_WINDOWTEXT)
			OldTextBackColor = pDC->SetBkColor(TextBkClr);
			OldBkMode = pDC->SetBkMode(TRANSPARENT);
		}
		//modify by yaka 20010423
		if (m_bIsFocus || m_bNeedBack)
		{
			pDC->MoveTo(m_rtShow.left, m_rtShow.bottom);
			(iFlag & 8) ? pDC->MoveTo(m_rtShow.right, m_rtShow.bottom) : pDC->LineTo(m_rtShow.right, m_rtShow.bottom);
			(iFlag & 2) ? pDC->MoveTo(m_rtShow.right, m_rtShow.top) : pDC->LineTo(m_rtShow.right, m_rtShow.top);
			(iFlag & 4) ? pDC->MoveTo(m_rtShow.left, m_rtShow.top) : pDC->LineTo(m_rtShow.left, m_rtShow.top);
			(iFlag & 1) ? pDC->MoveTo(m_rtShow.left, m_rtShow.bottom) : pDC->LineTo(m_rtShow.left, m_rtShow.bottom);

			CBrush brush(TextBkClr);
			pDC->FillRect(m_rtShow, &brush);
		}
		//modify end

		//如果m_rect也需要随之改变则执行系列语句：
		/*m_rect = m_rtShow;
		SetLRTB();*/
		m_rtShow.DeflateRect(1,1);
		//字体大小也应该跟着改变.

		//add by yaka 20010420
		long lfontWidth = m_rtShow.Width() / (m_strText.GetLength() + 1);
		CFont Font;
		LOGFONT m_Logfont;
		m_Logfont.lfHeight = m_rtShow.Height()* 3/4;
	//	m_Logfont.lfWidth = (long)(m_Logfont.lfHeight/2);
	//	if (m_Logfont.lfWidth > lfontWidth)
		m_Logfont.lfWidth = lfontWidth;
		m_Logfont.lfEscapement = 0;
		m_Logfont.lfOrientation = 0;
		m_Logfont.lfWeight = 400;
		m_Logfont.lfItalic = 0;
		m_Logfont.lfUnderline = 0;
		m_Logfont.lfStrikeOut = 0;
		m_Logfont.lfCharSet = DEFAULT_CHARSET;//CHINESEBIG5_CHARSET;//
		m_Logfont.lfPitchAndFamily = VARIABLE_PITCH ;
		Font.CreateFontIndirect(&m_Logfont);
		//Font.CreatePointFont(m_rtShow.Height() * 8 , "NULL");
		CFont* pOldFont = pDC->SelectObject(&Font);
		//add end
		
		pDC->DrawText(m_strText,&m_rtShow,DT_VCENTER|DT_CENTER|DT_END_ELLIPSIS|DT_SINGLELINE);
		if (m_bIsFocus)
		{
				//add by yaka 20010426
			m_rtShow.DeflateRect(2 ,2 ,2 ,2);
			switch (m_nEditType)
			{
			case EDIT:
				if (g_pEdit !=NULL)
				{
					m_rtShow.bottom = m_rtShow.top + 20;
					g_pEdit->MoveWindow(m_rtShow);
					g_pEdit->ShowWindow(SW_SHOW);
				}
				break;
			case COMBOBOX:
				if (g_pCombobox !=NULL)
				{
					CRect tempRect;
					g_pCombobox->GetWindowRect(tempRect);
					if (!(g_pCombobox->IsWindowVisible()) || (m_rtShow.Width() != tempRect.Width()))
					{
						if (m_rtShow.Height() < 100)
							m_rtShow.bottom = m_rtShow.top + 100;
						g_pCombobox->MoveWindow(m_rtShow);
						g_pCombobox->ShowWindow(SW_SHOW);
					}
				}
				break;
			case LISTBOX:
				if (g_pListbox !=NULL)
				{
					CRect TempRect;
					g_pListbox->GetWindowRect(TempRect);
					if (!(g_pListbox->IsWindowVisible()) || (m_rtShow.Width() != TempRect.Width()))
					{
						if (m_rtShow.Height() < 100)
							m_rtShow.bottom = m_rtShow.top + 100;
						g_pListbox->MoveWindow(m_rtShow);
						g_pListbox->ShowWindow(SW_SHOW);
					}
				}
				break;
			case STATIC:
				break;
			} //add end
		}
		
		pDC->SetROP2(nOldRop);
		pDC->SelectObject(pOldPen);
		pDC->SetBkColor(OldTextBackColor);
		pDC->SetTextColor(OldTextColor);
		pDC->SetBkMode(OldBkMode);
		pDC->SelectObject(pOldFont);
	}

	inline BOOL bPointInElement(CPoint& pa_Point)
	{
		SetRect();//不能丢，保证数据成员之间同步；
		CRect rect(m_rect);
		rect.DeflateRect(2,2);//注意4是有讲究的，保证不包括微调触发区域；
		rect.NormalizeRect();
		if((pa_Point.x<rect.right) && (pa_Point.x >= rect.left) && (pa_Point.y < rect.bottom) && (pa_Point.y >= rect.top))
			return TRUE;
		else
			return FALSE;
	}
};

#endif // !defined(AFX_MYTEXT_H__B29532DF_6760_45A0_8216_BFCD70A87C1B__INCLUDED_)
