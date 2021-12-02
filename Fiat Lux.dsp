# Microsoft Developer Studio Project File - Name="Fiat Lux" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Fiat Lux - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Fiat Lux.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Fiat Lux.mak" CFG="Fiat Lux - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Fiat Lux - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Fiat Lux - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Fiat Lux - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /MT /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 opengl32.lib glu32.lib winmm.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "Fiat Lux - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 opengl32.lib glu32.lib glaux.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Fiat Lux - Win32 Release"
# Name "Fiat Lux - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=".\Fiat Lux.cpp"
# End Source File
# Begin Source File

SOURCE=".\Fiat Lux.rc"
# End Source File
# Begin Source File

SOURCE=".\Fiat LuxDoc.cpp"
# End Source File
# Begin Source File

SOURCE=".\Fiat LuxView.cpp"
# End Source File
# Begin Source File

SOURCE=.\Info.cpp
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MyDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\olorOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\Progess.cpp
# End Source File
# Begin Source File

SOURCE=.\RollOverButton.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=".\Fiat Lux.h"
# End Source File
# Begin Source File

SOURCE=".\Fiat LuxDoc.h"
# End Source File
# Begin Source File

SOURCE=".\Fiat LuxView.h"
# End Source File
# Begin Source File

SOURCE=.\Info.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MyDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\olorOptions.h
# End Source File
# Begin Source File

SOURCE=.\Progess.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\RollOverButton.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=".\res\about fiat lux.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\about fiat lux2.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\about.bmp
# End Source File
# Begin Source File

SOURCE=".\res\ACD Wallpaper.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap2.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Elmer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Elmer.ico
# End Source File
# Begin Source File

SOURCE=".\res\Fiat Lux.ico"
# End Source File
# Begin Source File

SOURCE=".\res\Fiat Lux.rc2"
# End Source File
# Begin Source File

SOURCE=".\res\Fiat LuxDoc.ico"
# End Source File
# Begin Source File

SOURCE=".\res\FiatLux-vol5.bmp"
# End Source File
# Begin Source File

SOURCE=.\RES\FiatLux4bmp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon.ico
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small color down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small color focus.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small color up.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small flat active.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small flat down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small flat gray.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small info down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small info focus.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small info up.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small Light down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small Light focus.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small Light up.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small smooth active.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small smooth down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small smooth gray.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small solid active.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small solid down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small solid gray.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small wf down.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small wf focus.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\small wf gray.bmp"
# End Source File
# Begin Source File

SOURCE=".\res\Custom buttons\test Light focus.bmp"
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBTest.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
