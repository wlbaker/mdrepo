HOME=`pwd`

#get our ports for socat

driverPort=0
simPort=0

function find_open_ports {

	echo "Searching for Hard Serial Ports In Use AND Emulated Ports in Use"
	while dmesg | grep "ttyS"$driverPort" " || ps ax | grep -v grep | grep link=/dev/ttyS$driverPort
	do
		((driverPort++))
	done
	simPort=driverPort
	((simPort++))
	while dmesg | grep "ttyS"$simPort" " || ps ax | grep -v grep | grep link=/dev/ttyS$driverPort
	do
		((simPort++))
	done
}

find_open_ports

#To Enter ttyS ports manually, uncomment the line below.
#manual_port_selection

function build_all {
	simulator_build
	driver_build
}

function make_build {
    echo "making dir build"
    mkdir -p build
    cd build && cmake ../ -DCMAKE_MODULE_PATH=/usr/local/cmake/modules
	make
}

function simulator_build {
	cd $HOME/simulator
	echo "Checking if Intellivue Simulator build exists..."
	make_build

}

function driver_build {
	cd $HOME
	echo "Checking if Intellivue Driver build exists..."
	make_build
}

function run_socat() {
	echo -ne "\033]0;Intellivue Socat Terminal\007"
	sudo -v
	echo "Driver port is /dev/ttyS$1"
	echo "Simulator Port is /dev/ttyS$2"
	gnome-terminal --working-directory=$PWD --geometry 80X25+10+500 -x bash -c "run_intellivue_simulator $2; bash"
	sudo socat -d -d PTY,raw,echo=0,link=/dev/ttyS$1 PTY,raw,echo=0,link=/dev/ttyS$2 
}

function manual_port_selection {
	read -p "Please enter driver port and simulator port (space seperated) " driverPort simPort
}

function run_intellivue_simulator() {
	echo -ne "\033]0;Intellivue Simulator\007"
	cd $HOME/simulator/build
	sudo ./ds-philips-intellivue-mp70 -portname /dev/ttyS$1 -baud 115200 -databits 8 -parity none -stopbits 0 -datafilename ../../sample_data/dd_intellivue_mp70_response.log.06242014.6mins
}


build_all
export -f run_socat
export -f run_intellivue_simulator

gnome-terminal --geometry 80x25+10+10 -x bash -c "run_socat $driverPort $simPort; bash"
