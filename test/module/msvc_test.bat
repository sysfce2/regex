REM Basic command line to build everything with msvc:

cl /std:c++latest /EHsc /nologo /W4 /c "%VCToolsInstallDir%\modules\std.ixx"
cl /std:c++latest /EHsc /nologo /W4 /c /interface /I ..\..\..\.. ..\..\module\regex.cxx

for %%f in (*.cpp) do (
   cl /std:c++latest /EHsc /nologo /W4 /I ..\..\..\.. %%f std.obj regex.obj
)