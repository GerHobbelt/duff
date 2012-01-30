; example1.nsi
;
; This script is perhaps one of the simplest NSIs you can make. All of the
; optional settings are left to their default settings. The instalelr simply 
; prompts the user asking them where to install, and drops of notepad.exe
; there. If your Windows directory is not C:\windows, change it below.
;

; The name of the installer
Name "DUFF - DUplicate File Finder"

; The file to write
OutFile "duff-0.6.9.26.exe"

; The default installation directory
InstallDir  "$PROGRAMFILES\DUff"

; The text to prompt the user to enter a directory
DirText "Choose a directory where I should install DUFF"


AutoCloseWindow false
ShowInstDetails show
ShowUninstDetails show
ComponentText "This will install DUFF - DUplicate File Finder 0.6.9.26 by Helamonster"


; The stuff to install
Section "DUFF program (reqired)"

  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  ; Put file there
  File "..\..\Binaries\Release\duff.exe"
  File "..\Resource\animate.avi"
  File "home.url"

  SetOutPath $INSTDIR\Plugins
  File "..\..\Binaries\Release\Plugins\delete.dll"
  File "..\..\Binaries\Release\Plugins\move.dll"
  File "..\..\Binaries\Release\Plugins\savelist.dll"
  File "..\..\Binaries\Release\Plugins\sendto.dll"


  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\DUFF" "DisplayName" "DUFF - DUplicate File Finder"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\DUFF" "UninstallString" '"$INSTDIR\uninstall.exe"'

  ; write uninstaller
  WriteUninstaller "uninstall.exe"

  ; add program name to application paths
  WriteRegStr HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\DUFF.exe" "Path" "$INSTDIR\DUFF.exe"


;SetAutoClose true

SectionEnd ; end the section

;SectionDivider " Optional compenents "

; start menu shortcuts
Section "Start Menu group and shorcuts"

  ; create shortuts
  CreateDirectory "$SMPROGRAMS\DUFF"
  CreateShortCut "$SMPROGRAMS\DUFF\DUFF.lnk" "$INSTDIR\DUFF.exe"
  CreateShortCut "$SMPROGRAMS\DUFF\Uninstall.lnk" "$INSTDIR\uninstall.exe"
  CreateShortCut "$SMPROGRAMS\DUFF\Helamonster's Page.lnk" "$INSTDIR\home.url"

SectionEnd

Section "Desktop shortcut"

  ; create shortuts
  CreateShortCut "$DESKTOP\DUFF.lnk" "$INSTDIR\DUFF.exe"

SectionEnd


Function .onInstSuccess
    MessageBox MB_YESNO|MB_ICONQUESTION  "Installation was successful.$\n$\nDo you want to run DUFF now?" IDNO NoReadme
	; todo: fix this or duff because when executed from another directory, the animate control is not loaded
      Exec "$INSTDIR\DUFF.exe" ; view readme or whatever, if you want.
    NoReadme:
FunctionEnd



; uninstall stuff

UninstallText "This will uninstall DUFF - DUplicate File Finder by Helamonster"

; special uninstall section.
Section "Uninstall"


  ; close the program
  FindWindow $0 "" "Dulicate File Finder"
  IsWindow $0 ItIs ItIsNot
  ItIs:
  SendMessage $0 16 0 0
  Sleep 500
  ItIsNot:


  ; remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\DUFF"
  DeleteRegKey HKLM "SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\DUFF.exe"

  ; remove files
  Delete "$INSTDIR\DUFF.exe"
  Delete "$INSTDIR\DUFF.ini"
  Delete "$INSTDIR\home.url"
  Delete "$DESKTOP\DUFF.lnk"
 
  ; MUST REMOVE UNINSTALLER, too
  Delete "$INSTDIR\uninstall.exe"

  ; remove shortcuts, if any.
  Delete "$SMPROGRAMS\DUFF\DUFF.lnk"
  Delete "$SMPROGRAMS\DUFF\Uninstall.lnk"
  Delete "$SMPROGRAMS\DUFF\Helamonster's Page.lnk"

  ; remove directories used.
  RMDir "$INSTDIR"
  RMDir "$SMPROGRAMS\DUFF"

SectionEnd


; eof
