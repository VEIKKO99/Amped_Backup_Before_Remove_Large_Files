[Setup]
AppName=Amped - Roots
AppVersion=1.0.0
DefaultDirName={commonpf32}
DefaultGroupName=Amped
OutputBaseFilename=Amped-Win32Bit
UninstallFilesDir="{pf}\ML Sound Lab\Amped"
DisableDirPage=yes
LicenseFile=licence.txt
 
[Files]
Source: "..\Builds\VisualStudio2019\Win32\Release\VST3\Amped - Roots.vst3"; DestDir: "{commonpf32}\Common Files\VST3"
Source: "..\Builds\VisualStudio2019\Win32\Release\Standalone Plugin\Amped - Roots.exe"; DestDir: "{commonpf32}\ML Sound Lab\Amped"
