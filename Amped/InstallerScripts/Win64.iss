[Setup]
AppName=Amped - Roots
ArchitecturesInstallIn64BitMode=x64
AppVersion=1.0.0
DefaultDirName={cf}
DefaultGroupName=Amped
OutputBaseFilename=Amped-Win64Bit
UninstallFilesDir="{pf}\ML Sound Lab\Amped"
DisableDirPage=yes
LicenseFile=licence.txt
 
[Files]
Source: "..\Builds\VisualStudio2019\x64\Release\VST3\Amped - Roots.vst3"; DestDir: "{cf}\VST3"
Source: "..\Builds\VisualStudio2019\x64\Release\Standalone Plugin\Amped - Roots.exe"; DestDir: "{pf}\ML Sound Lab\Amped"

