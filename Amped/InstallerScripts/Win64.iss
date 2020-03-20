[Setup]
AppName=Amped - Roots - Beta 1
ArchitecturesInstallIn64BitMode=x64
AppVersion=0.9.1
DefaultDirName={cf}
DefaultGroupName=Amped
OutputBaseFilename=Amped-Win64Bit
UninstallFilesDir="{pf}\ML Sound Lab\Amped"
DisableDirPage=yes
 
[Files]
Source: "..\Builds\VisualStudio2019\x64\Release\VST3\Amped - Roots - Beta 1.vst3"; DestDir: "{cf}\VST3"
Source: "..\Builds\VisualStudio2019\x64\Release\Standalone Plugin\Amped - Roots - Beta 1.exe"; DestDir: "{pf}\ML Sound Lab\Amped"

