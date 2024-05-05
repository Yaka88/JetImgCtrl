// DrawElement.h: interface for the CDrawElement class.
//
//////////////////////////////////////////////////////////////////////
// �ļ���	: DrawElement.h
// ������Ŀ	: ������Ŀ
// �汾��	: 1.0
// ����		: ��ʾԪ��ͷ�ļ�
// ��������	: 2001/02/01
// ����		: yaka
// ��ע 		: 
#if !defined(AFX_DRAWELEMENT_H__32B3467A_45FF_4921_A397_597C47C1A90F__INCLUDED_)
#define AFX_DRAWELEMENT_H__32B3467A_45FF_4921_A397_597C47C1A90F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ����		: CDrawElement
// ������	: CObject
// ��������	: ��ʾԪ����
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
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
