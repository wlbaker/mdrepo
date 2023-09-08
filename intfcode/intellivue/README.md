2018-03-15
jlamothe@docboxinc.com
rengland@docboxinc.com

This document explains how to build and run the Docbox ICE DDS Intellivue
device driver, including a data simulator - a separate application. Both are
Linux applications, known to work with the RTI Ubuntu 16.04 toolchain package
rti_connext_dds-5.3.0.7-pro-target-x64Linux3gcc5.4.0.

This package contains the necessary pqxx and log4cplus libraries, which will
be installed via the process below.

It requires RTI Connext DDS 5.3 and PostgreSQL installed on the user's machine
prior. PostgreSQL can be installed via apt-get or any similar package manager.

Ensure the NDDSHOME environment variable is set. It should point to the
Connext directory, the parent directory of its bin.

Run the following command to build the shared libraries for the Intellivue
project & simulator:

   Scripts/init_dev.sh

Make sure that PostgreSQL is up, running, and accessible. To test, enter the
following command:

   psql -U postgres

If you are unable to connect, edit the configuration file
/etc/postgresql/9.5/main/pg_hba.conf 
to trust your local account to access postgres. In this file, change the Method
value from "peer" to "trust" on the four lines: 85, 90, 92, and 94. 
Then, reload the configuration file:

   sudo service postgresql reload

To build, and subsequently run, the driver + simulator execute the following script:

   cd PhilipsIntellivueMP70
   ./ddpiBuildAndRun.sh
   ./runDdpiDriver.sh

The "Intellivue Socat Terminal" will display text like so:

  Driver port is /dev/ttyS0
  Simulator Port is /dev/ttyS1

Meanwhile, the driver window will query for the Driver port like:

  Enter Intellivue Socat Driver PORT NUMBER (0, 1, 2..., (not /dev/ttyS<number>)): 0

In response to the above, enter "0" per the Socat terminal
