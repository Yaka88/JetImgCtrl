// DrawDIB.h: interface for the CDrawDIB class.
//
//////////////////////////////////////////////////////////////////////
// 文件名	: DrawDIB.h
// 所属项目	: 公共项目
// 版本号	: 1.0
// 内容		: 显示HDIB头文件
// 创建日期	: 2001/02/01
// 作者		: yaka
// 备注 		: 
#if !defined(AFX_DRAWDIB_H__705CEDFC_ABBA_4805_94FF_5254FCEAAF0F__INCLUDED_)
#define AFX_DRAWDIB_H__705CEDFC_ABBA_4805_94FF_5254FCEAAF0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define PALVERSION   0x300

#define DWORD_WBYTES(x)	((((x) + 31UL) >> 5) << 2)
#define IS_WIN30_DIB(lpbi)  ((*(LPDWORD)(lpbi)) == sizeof(BITMAPINFOHEADER))
#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

// 类名		: CDrawDIB
// 父类名	: 无
// 功能描述	: 显示HDIB类
// 创建日期	: 2000/02/01
// 作者		: yaka
// 备注 	: 

class CDrawDIB  
{
public:
	HDIB StretchDIB(HDIB hDib,float p_zoomx,float p_zoomy);
	CDrawDIB();
	virtual ~CDrawDIB();
	BOOL   PaintDIB (HDC, LPRECT, HDIB, LPRECT, CPalette* pPal);
	BOOL    CreateDIBPalette(HDIB hDIB, CPalette* cPal);
	LPSTR    FindDIBBits (LPSTR lpbi);
	DWORD   DIBWidth (LPSTR lpDIB);
	DWORD    DIBHeight (LPSTR lpDIB);
	WORD     PaletteSize (LPSTR lpbi);
	WORD     DIBNumColors (LPSTR lpbi);
	HGLOBAL   CopyHandle (HGLOBAL h);

};

#endif // !defined(AFX_DRAWDIB_H__705CEDFC_ABBA_4805_94FF_5254FCEAAF0F__INCLUDED_)
