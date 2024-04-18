REM Basic command line to build everything with msvc:

del *.obj
del *.exe
del *.lib

cl /std:c++latest /EHsc /nologo /W4 /c "%VCToolsInstallDir%\modules\std.ixx"  || exit 1
cl /std:c++latest /EHsc /nologo /W4 /c /interface /I ..\..\..\.. ..\..\module\regex.cxx || exit 1
cl /std:c++latest /EHsc /nologo /W4 /c /I ..\..\..\.. ..\..\module\*.cpp || exit 1

lib *.obj /OUT:regex.lib || exit 1

time < nul

for %%f in (*.cpp) do (
   cl /std:c++latest /EHsc /nologo /W4 /I ..\..\..\.. %%f regex.lib || exit 1
)

time < nul

for %%f in (*.cpp) do (
   cl /DTEST_HEADERS /std:c++latest /EHsc /nologo /W4 /I ..\..\..\.. %%f || exit 1
)

time < nul

