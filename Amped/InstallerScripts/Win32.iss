[Setup]
AppName=Amped - NAMM Beta
AppVersion=0.1.0
DefaultDirName={cf}
DefaultGroupName=Amped
OutputBaseFilename=Amped-Win32Bit
 
[Files]
Source: "..\Builds\VisualStudio2019\Win32\Release\VST3\Amped - NAMM Beta.vst3"; DestDir: "{app}\Steinberg\VST3"
Source: "..\Builds\VisualStudio2019\Win32\Release\Standalone Plugin\Amped - NAMM Beta.exe"; DestDir: "{pf}\Amped"

