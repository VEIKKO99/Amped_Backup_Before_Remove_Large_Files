[Messages]
WelcomeLabel2=This is the Amped Roots Free installer. Remember to use the 64bit installer with 64bit and 32bit installer with 32bit operating systems and digital audio workstations.%n%nAmped Roots Standalone will be installed to:%nC:\Program Files\ML Sound Lab\Amped%n%nAmped Roots VST3 plugin will be installed to:%nC:\Program Files\Common Files\VST3%n%nFrom October 2018 onward the second version of VST has been closed down. Only VST3 is now officially supported so be sure to enable VST3 in your digital audio workstation. 

[Setup]
AppName=Amped - Roots
AppVersion=1.2.2
DefaultDirName={commonpf32}
DefaultGroupName=Amped
OutputBaseFilename=Amped-Win32Bit
UninstallFilesDir="{pf}\ML Sound Lab\Amped"
DisableDirPage=yes
LicenseFile=licence.txt
DisableWelcomePage=no


[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; \
    GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

 
[Files]
Source: "..\Builds\VisualStudio2019\Win32\Release\VST3\Amped - Roots.vst3"; DestDir: "{commonpf32}\Common Files\VST3"
Source: "..\Builds\VisualStudio2019\Win32\Release\Standalone Plugin\Amped - Roots.exe"; DestDir: "{commonpf32}\ML Sound Lab\Amped"
//Source: "..\Builds\VisualStudio2019\icon.ico"; DestDir: "{commonpf32}\ML Sound Lab\Amped"

[Icons]
Name: "{userdesktop}\Amped - Roots"; Filename: "{commonpf32}\ML Sound Lab\Amped\Amped - Roots.exe"; Tasks: desktopicon