mkdir lib
mkdir include
mkdir include\libusb-1.0
copy \opt\tools\libusb-1.0.19\Win32\Debug\lib\*.lib lib
copy \opt\tools\libusb-1.0.19\libusb\libusb.h include\libusb-1.0


xcopy \opt\tools\exodriver\liblabjackusb\*.h include 
