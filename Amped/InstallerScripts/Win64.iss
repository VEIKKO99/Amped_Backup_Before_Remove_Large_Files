[Setup]
AppName=Amped - NAMM Beta
ArchitecturesInstallIn64BitMode=x64
AppVersion=0.1.0
DefaultDirName={cf}
DefaultGroupName=Amped
OutputBaseFilename=Amped-Win64Bit
 
[Files]
Source: "..\Builds\VisualStudio2019\x64\Release\VST3\Amped - NAMM Beta.vst3"; DestDir: "{app}\Steinberg\VST3"
Source: "..\Builds\VisualStudio2019\x64\Release\Standalone Plugin\Amped - NAMM Beta.exe"; DestDir: "{pf}\Amped"

