[Setup]
AppName=Amped - Roots - Beta 1
AppVersion=0.9.1
DefaultDirName={commonpf32}
DefaultGroupName=Amped
OutputBaseFilename=Amped-Win32Bit
UninstallFilesDir="{pf}\ML Sound Lab\Amped"
DisableDirPage=yes
 
[Files]
Source: "..\Builds\VisualStudio2019\Win32\Release\VST3\Amped - Roots - Beta 1.vst3"; DestDir: "{commonpf32}\Common Files\VST3"
Source: "..\Builds\VisualStudio2019\Win32\Release\Standalone Plugin\Amped - Roots - Beta 1.exe"; DestDir: "{commonpf32}\ML Sound Lab\Amped"
