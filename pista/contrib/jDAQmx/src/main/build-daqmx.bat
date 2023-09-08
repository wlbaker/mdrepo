cl -Iinclude -I"\opt\jdk1.6.0_17\include" -I"c:\opt\jdk1.6.0_17\include\win32"  /MT /c src/daqmx/NIDaqJ.cpp -Fobuild/win32/daqmx/NIDaqJ.obj
cl -Iinclude -I"\Program Files\java\jdk1.6.0_13\include" -I"\Program Files\java\jdk1.6.0_13\include\win32"  /MT /c src/daqmx/NIFuncs.cpp
cl -Iinclude -I"\Program Files\java\jdk1.6.0_13\include" -I"\Program Files\java\jdk1.6.0_13\include\win32"  /MT /c src/daqmx/Local.cpp
cl /LD /Feidea-ni.dll NIDaqJ.obj NIFuncs.obj Local.obj ../lib/msvc/NIDAQmx.lib 
