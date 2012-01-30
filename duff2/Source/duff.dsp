# Microsoft Developer Studio Project File - Name="duff" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=duff - Win32 Debug Unicode
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "duff.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "duff.mak" CFG="duff - Win32 Debug Unicode"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "duff - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "duff - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "duff - Win32 Static Release" (based on "Win32 (x86) Application")
!MESSAGE "duff - Win32 Debug Unicode" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "duff - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\Binaries\Release"
# PROP Intermediate_Dir "..\Binaries\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W4 /GX /O2 /I "ResizableLib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib version.lib ResizableLib\Binaries\Release\ResizableLib.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "duff - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Binaries\Debug"
# PROP Intermediate_Dir "..\Binaries\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "ResizableLib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "ISOLATION_AWARE_ENABLED" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Kernel32.lib winmm.lib version.lib ResizableLib\Binaries\Debug\ResizableLib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "duff - Win32 Static Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "duff___Win32_Static_Release"
# PROP BASE Intermediate_Dir "duff___Win32_Static_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Binaries\ReleaseStatic"
# PROP Intermediate_Dir "Binaries\ReleaseStatic"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W4 /GX /O2 /I "ResizableLib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W4 /GX /O2 /I "ResizableLib" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 winmm.lib version.lib ResizableLib\Release\ResizableLib.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib version.lib ResizableLib\Release_Static\ResizableLib.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "duff - Win32 Debug Unicode"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "duff___Win32_Debug_Unicode"
# PROP BASE Intermediate_Dir "duff___Win32_Debug_Unicode"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Binaries\DebugUnicode"
# PROP Intermediate_Dir "Binaries\DebugUnicode"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "ResizableLib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W4 /Gm /GX /ZI /Od /I "ResizableLib" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_UNICODE" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 Kernel32.lib winmm.lib version.lib ResizableLib\Release\ResizableLib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT BASE LINK32 /nodefaultlib
# ADD LINK32 Kernel32.lib winmm.lib version.lib ResizableLib\Release\ResizableLib.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "duff - Win32 Release"
# Name "duff - Win32 Debug"
# Name "duff - Win32 Static Release"
# Name "duff - Win32 Debug Unicode"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AboutDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CharEncSch.cpp
# End Source File
# Begin Source File

SOURCE=.\Column.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnDupeSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnFileAccessDate.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnFileAttributes.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnFileCreationDate.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnFileLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnFileModifyDate.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnFilename.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnFilenameFull.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnFileSize.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnFileTypeDesc.cpp
# End Source File
# Begin Source File

SOURCE=.\ColumnFileVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\DirectoryInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\duff.cpp
# End Source File
# Begin Source File

SOURCE=.\duffDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DuffModule.cpp
# End Source File
# Begin Source File

SOURCE=.\DuffObject.cpp
# End Source File
# Begin Source File

SOURCE=.\DuffOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DuffOptionsConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DuffPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\DuffPluginManager.cpp
# End Source File
# Begin Source File

SOURCE=.\DuffProcessorPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\DupeFindDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DuplicateFileFind.cpp
# End Source File
# Begin Source File

SOURCE=.\DuplicateFileFindConfigurer.cpp
# End Source File
# Begin Source File

SOURCE=.\DuplicateListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DuplicateListHeaderCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\FileInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\FilenameEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\Filter.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterFileAttributes.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterFileAttributesForm.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterFileContents.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterFileContentsForm.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterFileDate.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterFileDateForm.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterFilename.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterFileSize.cpp
# End Source File
# Begin Source File

SOURCE=.\FilterFileSizeForm.cpp
# End Source File
# Begin Source File

SOURCE=.\GetFolder.cpp

!IF  "$(CFG)" == "duff - Win32 Release"

!ELSEIF  "$(CFG)" == "duff - Win32 Debug"

# ADD CPP /Yu

!ELSEIF  "$(CFG)" == "duff - Win32 Static Release"

!ELSEIF  "$(CFG)" == "duff - Win32 Debug Unicode"

# ADD BASE CPP /Yu
# ADD CPP /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp
# End Source File
# Begin Source File

SOURCE=.\Layer.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerFileData.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerFilename.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerFilenameForm.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerMP3DataForm.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerMP3FileData.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerTextData.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerTextDataForm.cpp
# End Source File
# Begin Source File

SOURCE=.\Marker.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkerFileDate.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkerFileDateForm.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkerFileLocation.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkerFileLocationForm.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkerFilename.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkerFilenameForm.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkerFileSize.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkerFileSizeForm.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkerFileVersion.cpp
# End Source File
# Begin Source File

SOURCE=.\MarkerFileVersionForm.cpp
# End Source File
# Begin Source File

SOURCE=.\NumEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsGeneralForm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsMarkerForm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsProcessForm.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionsSoundForm.cpp
# End Source File
# Begin Source File

SOURCE=.\Processor.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageDebug.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageDirectories.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageDuplicates.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageFilters.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageLayers.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageProcesses.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageSelections.cpp
# End Source File
# Begin Source File

SOURCE=.\PropertyPageStatusLog.cpp
# End Source File
# Begin Source File

SOURCE=.\ResizableLib\ResizablePage.cpp
# End Source File
# Begin Source File

SOURCE=.\ResizablePropertySheet.cpp
# End Source File
# Begin Source File

SOURCE=.\stdafx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TextClipboard.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\TimeOut.cpp
# End Source File
# Begin Source File

SOURCE=.\VersionInfo.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AboutDlg.h
# End Source File
# Begin Source File

SOURCE=.\CharEncSch.h
# End Source File
# Begin Source File

SOURCE=.\Column.h
# End Source File
# Begin Source File

SOURCE=.\ColumnDupeSet.h
# End Source File
# Begin Source File

SOURCE=.\ColumnFileAccessDate.h
# End Source File
# Begin Source File

SOURCE=.\ColumnFileAttributes.h
# End Source File
# Begin Source File

SOURCE=.\ColumnFileCreationDate.h
# End Source File
# Begin Source File

SOURCE=.\ColumnFileLocation.h
# End Source File
# Begin Source File

SOURCE=.\ColumnFileModifyDate.h
# End Source File
# Begin Source File

SOURCE=.\ColumnFilename.h
# End Source File
# Begin Source File

SOURCE=.\ColumnFilenameFull.h
# End Source File
# Begin Source File

SOURCE=.\ColumnFileSize.h
# End Source File
# Begin Source File

SOURCE=.\ColumnFileTypeDesc.h
# End Source File
# Begin Source File

SOURCE=.\ColumnFileVersion.h
# End Source File
# Begin Source File

SOURCE=.\defines.h
# End Source File
# Begin Source File

SOURCE=.\DirectoryInfo.h
# End Source File
# Begin Source File

SOURCE=.\duff.h
# End Source File
# Begin Source File

SOURCE=.\duffDlg.h
# End Source File
# Begin Source File

SOURCE=.\DuffModule.h
# End Source File
# Begin Source File

SOURCE=.\DuffObject.h
# End Source File
# Begin Source File

SOURCE=.\DuffOptions.h
# End Source File
# Begin Source File

SOURCE=.\DuffOptionsConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\DuffPlugin.h
# End Source File
# Begin Source File

SOURCE=.\DuffPluginManager.h
# End Source File
# Begin Source File

SOURCE=.\DuffProcessorPlugin.h
# End Source File
# Begin Source File

SOURCE=.\DuffStatus.h
# End Source File
# Begin Source File

SOURCE=.\DupeFindDlg.h
# End Source File
# Begin Source File

SOURCE=.\DuplicateFileFind.h
# End Source File
# Begin Source File

SOURCE=.\DuplicateFileFindConfigurer.h
# End Source File
# Begin Source File

SOURCE=.\DuplicateListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DuplicateListHeaderCtrl.h
# End Source File
# Begin Source File

SOURCE=.\FileInfo.h
# End Source File
# Begin Source File

SOURCE=.\FilenameEdit.h
# End Source File
# Begin Source File

SOURCE=.\Filter.h
# End Source File
# Begin Source File

SOURCE=.\FilterFileAttributes.h
# End Source File
# Begin Source File

SOURCE=.\FilterFileAttributesForm.h
# End Source File
# Begin Source File

SOURCE=.\FilterFileContents.h
# End Source File
# Begin Source File

SOURCE=.\FilterFileContentsForm.h
# End Source File
# Begin Source File

SOURCE=.\FilterFileDate.h
# End Source File
# Begin Source File

SOURCE=.\FilterFileDateForm.h
# End Source File
# Begin Source File

SOURCE=.\FilterFilename.h
# End Source File
# Begin Source File

SOURCE=.\FilterFileSize.h
# End Source File
# Begin Source File

SOURCE=.\FilterFileSizeForm.h
# End Source File
# Begin Source File

SOURCE=.\getfolder.h
# End Source File
# Begin Source File

SOURCE=.\hyperlink.h
# End Source File
# Begin Source File

SOURCE=.\Layer.h
# End Source File
# Begin Source File

SOURCE=.\LayerFileData.h
# End Source File
# Begin Source File

SOURCE=.\LayerFilename.h
# End Source File
# Begin Source File

SOURCE=.\LayerFilenameForm.h
# End Source File
# Begin Source File

SOURCE=.\LayerFileTextDataForm.h
# End Source File
# Begin Source File

SOURCE=.\LayerMP3DataForm.h
# End Source File
# Begin Source File

SOURCE=.\LayerMP3FileData.h
# End Source File
# Begin Source File

SOURCE=.\LayerTextData.h
# End Source File
# Begin Source File

SOURCE=.\LayerTextDataForm.h
# End Source File
# Begin Source File

SOURCE=.\Marker.h
# End Source File
# Begin Source File

SOURCE=.\MarkerFileDate.h
# End Source File
# Begin Source File

SOURCE=.\MarkerFileDateForm.h
# End Source File
# Begin Source File

SOURCE=.\MarkerFileLocation.h
# End Source File
# Begin Source File

SOURCE=.\MarkerFileLocationForm.h
# End Source File
# Begin Source File

SOURCE=.\MarkerFilename.h
# End Source File
# Begin Source File

SOURCE=.\MarkerFilenameForm.h
# End Source File
# Begin Source File

SOURCE=.\MarkerFileSize.h
# End Source File
# Begin Source File

SOURCE=.\MarkerFileSizeForm.h
# End Source File
# Begin Source File

SOURCE=.\MarkerFileVersion.h
# End Source File
# Begin Source File

SOURCE=.\MarkerFileVersionForm.h
# End Source File
# Begin Source File

SOURCE=.\NumEdit.h
# End Source File
# Begin Source File

SOURCE=.\OptionsGeneralForm.h
# End Source File
# Begin Source File

SOURCE=.\OptionsMarkerForm.h
# End Source File
# Begin Source File

SOURCE=.\OptionsProcessForm.h
# End Source File
# Begin Source File

SOURCE=.\OptionsSoundForm.h
# End Source File
# Begin Source File

SOURCE=.\Processor.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageDebug.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageDirectories.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageDuplicates.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageFilters.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageLayers.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageOptions.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageProcesses.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageSelections.h
# End Source File
# Begin Source File

SOURCE=.\PropertyPageStatusLog.h
# End Source File
# Begin Source File

SOURCE=.\ResizableLib\ResizablePage.h
# End Source File
# Begin Source File

SOURCE=.\ResizablePropertySheet.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# Begin Source File

SOURCE=.\TextClipboard.h
# End Source File
# Begin Source File

SOURCE=.\TimeOut.h
# End Source File
# Begin Source File

SOURCE=.\util.h
# End Source File
# Begin Source File

SOURCE=.\VersionInfo.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Resource\duff.ico
# End Source File
# Begin Source File

SOURCE=.\duff.rc
# End Source File
# Begin Source File

SOURCE=.\Resource\duff.rc2
# End Source File
# Begin Source File

SOURCE=.\Resource\duffcan.bmp
# End Source File
# Begin Source File

SOURCE=.\Resource\TabImages.bmp
# End Source File
# End Group
# Begin Group "Installation Scripts"

# PROP Default_Filter "*.nsi"
# Begin Source File

SOURCE=.\Installation\duff.nsi

!IF  "$(CFG)" == "duff - Win32 Release"

!ELSEIF  "$(CFG)" == "duff - Win32 Debug"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "duff - Win32 Static Release"

!ELSEIF  "$(CFG)" == "duff - Win32 Debug Unicode"

!ENDIF 

# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter "*.doc"
# Begin Source File

SOURCE=..\Documentation\Database.mdb
# End Source File
# Begin Source File

SOURCE=..\Documentation\FileComparisonLayer.doc
# End Source File
# Begin Source File

SOURCE=..\Documentation\FilenameMarkerAlgorithm.txt
# End Source File
# Begin Source File

SOURCE=..\Documentation\Glossary.doc
# End Source File
# Begin Source File

SOURCE=..\Documentation\help.htm
# End Source File
# Begin Source File

SOURCE=..\Documentation\Plugin.doc
# End Source File
# Begin Source File

SOURCE=..\Documentation\PluginManager.doc
# End Source File
# Begin Source File

SOURCE=..\Documentation\ReadMe.txt
# End Source File
# Begin Source File

SOURCE=..\Documentation\rose.mdl
# End Source File
# Begin Source File

SOURCE=..\Documentation\todo.txt
# End Source File
# Begin Source File

SOURCE=..\Documentation\visio.vsd
# End Source File
# End Group
# End Target
# End Project
