#if !defined(AFX_JETIMGCTRL_H__84F1F92D_9213_40B9_A066_4A73D4462A56__INCLUDED_)
#define AFX_JETIMGCTRL_H__84F1F92D_9213_40B9_A066_4A73D4462A56__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// JetImgCtrl.h : main header file for JETIMGCTRL.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CJetImgCtrlApp : See JetImgCtrl.cpp for implementation.

class CJetImgCtrlApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JETIMGCTRL_H__84F1F92D_9213_40B9_A066_4A73D4462A56__INCLUDED)
