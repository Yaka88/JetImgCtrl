// DrawElement.h: interface for the CDrawElement class.
//
//////////////////////////////////////////////////////////////////////
// 文件名	: DrawElement.h
// 所属项目	: 公共项目
// 版本号	: 1.0
// 内容		: 显示元素头文件
// 创建日期	: 2001/02/01
// 作者		: yaka
// 备注 		: 
#if !defined(AFX_DRAWELEMENT_H__32B3467A_45FF_4921_A397_597C47C1A90F__INCLUDED_)
#define AFX_DRAWELEMENT_H__32B3467A_45FF_4921_A397_597C47C1A90F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 类名		: CDrawElement
// 父类名	: CObject
// 功能描述	: 显示元素类
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 
class CDrawElement : public CObject  
{
public:
	CDrawElement();
	DECLARE_DYNCREATE(CDrawElement)
	virtual	void OffsetElement(CPoint p_Offset){};
	virtual	void OffsetElement(int p_x,int p_y){};
	virtual	void NormalizeElement(){};
	virtual	BOOL IsElementEmpty(){return TRUE;};
	virtual	void SetElementEmpty(){};
	virtual void ShowElement(CRect p_ShowRect,CDC* pDC){};
	virtual	BOOL bPointInElement(CPoint& pa_Point){return FALSE;};
	virtual void SetFocus(BOOL p_bFocus){};
	virtual BOOL GetFocus(){return FALSE;};
	virtual void SetItemDate(LPVOID p_lpDate){};
	virtual LPVOID GetItemDate(){return NULL;};
	virtual void StretchElement(float p_fx,float p_fy){};
	virtual ~CDrawElement();

};

#endif // !defined(AFX_DRAWELEMENT_H__32B3467A_45FF_4921_A397_597C47C1A90F__INCLUDED_)
