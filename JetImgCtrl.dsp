# Microsoft Developer Studio Project File - Name="JetImgCtrl" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=JetImgCtrl - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "JetImgCtrl.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "JetImgCtrl.mak" CFG="JetImgCtrl - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "JetImgCtrl - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "JetImgCtrl - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "JetImgCtrl - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Release
TargetPath=.\Release\JetImgCtrl.ocx
InputPath=.\Release\JetImgCtrl.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ELSEIF  "$(CFG)" == "JetImgCtrl - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Ext "ocx"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Ext "ocx"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# Begin Custom Build - Registering ActiveX Control...
OutDir=.\Debug
TargetPath=.\Debug\JetImgCtrl.ocx
InputPath=.\Debug\JetImgCtrl.ocx
SOURCE="$(InputPath)"

"$(OutDir)\regsvr32.trg" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	regsvr32 /s /c "$(TargetPath)" 
	echo regsvr32 exec. time > "$(OutDir)\regsvr32.trg" 
	
# End Custom Build

!ENDIF 

# Begin Target

# Name "JetImgCtrl - Win32 Release"
# Name "JetImgCtrl - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DrawDIB.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawElement.cpp
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrl.def
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrl.odl
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrl.rc
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrlCtl.cpp
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrlPpg.cpp
# End Source File
# Begin Source File

SOURCE=.\MyLine.cpp
# End Source File
# Begin Source File

SOURCE=.\MyPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\MyRect.cpp
# End Source File
# Begin Source File

SOURCE=.\MyText.cpp
# End Source File
# Begin Source File

SOURCE=.\SingleImg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DrawDIB.h
# End Source File
# Begin Source File

SOURCE=.\DrawElement.h
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrl.h
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrlApi.h
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrlCtl.h
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrlPpg.h
# End Source File
# Begin Source File

SOURCE=.\JetImgSeeApi.h
# End Source File
# Begin Source File

SOURCE=.\MyLine.h
# End Source File
# Begin Source File

SOURCE=.\MyPoint.h
# End Source File
# Begin Source File

SOURCE=.\MyRect.h
# End Source File
# Begin Source File

SOURCE=.\MyText.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SingleImg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\JetImgCtrl.ico
# End Source File
# Begin Source File

SOURCE=.\JetImgCtrlCtl.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=.\JetImgSee.lib
# End Source File
# End Target
# End Project
# Section JetImgCtrl : {9991E755-7AFA-4E3B-8056-CF723D978F3F}
# 	2:5:Class:CJetImgCtrl
# 	2:10:HeaderFile:jetimgctrl1.h
# 	2:8:ImplFile:jetimgctrl1.cpp
# End Section
# Section JetImgCtrl : {C51F7B20-3D4A-483E-B698-04B2253189D3}
# 	2:21:DefaultSinkHeaderFile:jetimgctrl1.h
# 	2:16:DefaultSinkClass:CJetImgCtrl
# End Section
