#if !defined(AFX_JETIMGCTRLPPG_H__F620E691_7429_4AC1_ADF8_BD99EC80DE82__INCLUDED_)
#define AFX_JETIMGCTRLPPG_H__F620E691_7429_4AC1_ADF8_BD99EC80DE82__INCLUDED_
// �ļ���	: JetImgCtrlPpg.cpp
// ������Ŀ	: ������Ŀ
// �汾��	: 1.0
// ����		: ��ʾ�ؼ�����ҳͷ�ļ�
// ��������	: 2001/02/01
// ����		: yaka
// ��ע 		: 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JetImgCtrlPpg.h : Declaration of the CJetImgCtrlPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlPropPage : See JetImgCtrlPpg.cpp.cpp for implementation.
// ����		: CJetImgCtrlPropPage
// ������	: COlePropertyPage
// ��������	: ��ʾ�ؼ�����ҳ��
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 
class CJetImgCtrlPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CJetImgCtrlPropPage)
	DECLARE_OLECREATE_EX(CJetImgCtrlPropPage)

// Constructor
public:
	CJetImgCtrlPropPage();

// Dialog Data
	//{{AFX_DATA(CJetImgCtrlPropPage)
	enum { IDD = IDD_PROPPAGE_JETIMGCTRL };
	BOOL	m_bMagnifer;
	short	m_nCol;
	short	m_nRow;
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CJetImgCtrlPropPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JETIMGCTRLPPG_H__F620E691_7429_4AC1_ADF8_BD99EC80DE82__INCLUDED)
