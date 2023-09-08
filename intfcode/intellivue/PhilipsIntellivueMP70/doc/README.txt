Setup:

Prerequisites:
RTI DDS Connext 4.5f 
Boost C++ Libraries 1.50.0

Note: Modify makefile for different versions of DDS.

Open intellivuexmlcfg.xml and select protocol.
If you choose RS232 protocol, you may need to configure serial port in intellivueserialcfg.xml. It should work already.
If you choose UDP protocol, a bootp server will need to be running to answer the bootp request from the monitor.
Choose demo mode if the intellivue monitor isn't connected to computer or simulated data is needed. 

To Generate IDL:
Note: Only if the idl change otherwise do not re-run the generator
mike@docbox:/opt/RTI/RTI_Launcher_1.0.0/scripts$ ./rtilauncher 
Utilities -> Code Generator -> (use settings below)
/opt/RTI/ndds.4.5d/scripts/rtiddsgen -language C++ -namespace -stringSize 255 -sequenceSize 100 -replace /home/mike/intellivue/intellivueMP70Members.idl
/opt/RTI/ndds.4.5d/scripts/rtiddsgen -language C++ -namespace -stringSize 255 -sequenceSize 100 -replace -example i86Linux2.6gcc4.4.5 /home/mike/intellivue/intellivueMP70.idl

To Compile:
Note: Modifiy the make file when new files are added to the project
mike@docbox:/home/mike/intellivue# make -f makefile_intellivueMP70_i86Linux2.6gcc4.4.5

To Run:
Note: Open the publisher and subscriber on separate terminals
mike@docbox:/home/mike/intellivue# objs/i86Linux2.6gcc4.4.5/intellivueMP70_subscriber 0
mike@docbox:/home/mike/intellivue# objs/i86Linux2.6gcc4.4.5/intellivueMP70_publisher 0

