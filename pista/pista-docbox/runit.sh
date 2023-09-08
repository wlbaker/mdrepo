export NDDSHOME=/opt/RTI/rti_connext_dds-5.3.1
export PATH=${PATH}:/opt/RTI/rti_connext_dds-5.3.1/bin
export LD_LIBRARY_PATH=/opt/DocBoxInc/lib:/opt/RTI/rti_connext_dds-5.3.1/lib/x64Linux3gcc5.4.0:/opt/bernard/lib
export NDDS_QOS_PROFILES=file:///opt/DocBoxInc/etc/QoS.xml
export DICES_DIM_DURABLE_QOS_PROFILE_BASE_NAME=DICES::DeviceModule
export COORDINATOR_DOMAIN_ID=30
# ./infinity-driver  --localIp 192.168.50.1
./infinity-driver  --localIp 10.1.127.43
# LD_LIBRARY_PATH=/opt/DocBoxInc/lib:/opt/RTI/rti_connext_dds-5.3.1/lib/x64Linux3gcc5.4.0 /usr/local/infinity-driver/infinity-driver
