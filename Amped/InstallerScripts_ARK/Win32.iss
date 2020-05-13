[Messages]
WelcomeLabel2=This is the Amped Ark installer. Remember to use the 64bit installer with 64bit and 32bit installer with 32bit operating systems and digital audio workstations.%n%nAmped Ark Standalone will be installed to:%nC:\Program Files\ML Sound Lab\Amped%n%nAmped Ark VST3 plugin will be installed to:%nC:\Program Files\Common Files\VST3%n%nFrom October 2018 onward the second version of VST has been closed down. Only VST3 is now officially supported so be sure to enable VST3 in your digital audio workstation. 

[Setup]
AppName=Amped - Ark
AppVersion=0.1.0
DefaultDirName={commonpf32}
DefaultGroupName=Amped
OutputBaseFilename=Amped-Ark-Win32Bit
UninstallFilesDir="{pf}\ML Sound Lab\Amped"
DisableDirPage=yes
LicenseFile=licence.txt
DisableWelcomePage=no


[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; \
    GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

 
[Files]
Source: "..\Builds\VisualStudio2019\Win32\Release\VST3\Amped - Ark.vst3"; DestDir: "{commonpf32}\Common Files\VST3"
Source: "..\Builds\VisualStudio2019\Win32\Release\Standalone Plugin\Amped - Ark.exe"; DestDir: "{commonpf32}\ML Sound Lab\Amped"
//Source: "..\Builds\VisualStudio2019\icon.ico"; DestDir: "{commonpf32}\ML Sound Lab\Amped"

[Icons]
Name: "{userdesktop}\Amped - Ark"; Filename: "{commonpf32}\ML Sound Lab\Amped\Amped - Ark.exe"; Tasks: desktopicon