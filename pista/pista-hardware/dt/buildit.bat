cl /DWIN32 /MDd -I..\..\..\..\resources\win32\include -I..\..\..\include -I..\.. api.c 
rem cl /DWIN32 /MDd /I..\..\liblabjackusb /nologo /c u3.c
rem cl /DWIN32 /MDd /I..\..\liblabjackusb /nologo /c api.c
rem cl /DWIN32 /MDd /I..\..\liblabjackusb /nologo /c u3Stream.c
rem cl /DWIN32 /MDd /nologo u3.obj api.obj ..\..\liblabjackusb\labjackusb.obj ..\..\libusb-1.0\lib\libusb-1.0.lib 
