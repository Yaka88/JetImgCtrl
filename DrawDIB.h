// DrawDIB.h: interface for the CDrawDIB class.
//
//////////////////////////////////////////////////////////////////////
// �ļ���	: DrawDIB.h
// ������Ŀ	: ������Ŀ
// �汾��	: 1.0
// ����		: ��ʾHDIBͷ�ļ�
// ��������	: 2001/02/01
// ����		: yaka
// ��ע 		: 
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

// ����		: CDrawDIB
// ������	: ��
// ��������	: ��ʾHDIB��
// ��������	: 2000/02/01
// ����		: yaka
// ��ע 	: 

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
