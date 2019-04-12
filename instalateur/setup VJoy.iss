; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "VjoyArduino"
#define MyAppVersion "1.0"
#define MyAppPublisher "Robotechnic"
#define MyAppURL "https://github.com/Robotechnic/VJoy-arduino"
#define MyAppExeName "vjoyArduino.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{2FC3D973-3489-4988-9070-9C5339B17472}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DisableProgramGroupPage=yes
InfoAfterFile=C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\readme.txt
OutputDir=C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy
OutputBaseFilename=setup Arduino VJoy
SetupIconFile=C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\vjoy-icon.ico
Compression=lzma
SolidCompression=yes
WizardSmallImageFile=C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\vjoy-icon.bmp

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1

[Files]
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\vjoyArduino.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\fenetre.obj"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\main.obj"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\moc_fenetre.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\moc_fenetre.obj"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\moc_moniteurserie.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\moc_moniteurserie.obj"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\moc_predefs.h"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\moc_qjoypad.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\moc_qjoypad.obj"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\moniteurserie.obj"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\qjoypad.obj"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\qrc_resources.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\qrc_resources.obj"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\Qt5SerialPort.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\readme.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\vjoy-icon.ico"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\vJoyInterface.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\arduinoSketch\*"; DestDir: "{app}\arduinoSketch\"; Flags: ignoreversion recursesubdirs
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\iconengines\*"; DestDir: "{app}\iconengines"; Flags: ignoreversion recursesubdirs
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\imageformats\*"; DestDir: "{app}\imageformats"; Flags: ignoreversion recursesubdirs
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\platforms\*"; DestDir: "{app}\platforms"; Flags: ignoreversion recursesubdirs
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\styles\*"; DestDir: "{app}\styles"; Flags: ignoreversion recursesubdirs
Source: "C:\Users\utilisateur.DESKTOP-IMS5SB5\Documents\logicielVJoy\vJoySetup.exe"; DestDir:"{app}"; Flags: ignoreversion
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{commonprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\vJoySetup.exe"; Description: "vJoy is necessary for the good operation of the application if you didn't install it, you must install it."; Flags: postinstall
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

