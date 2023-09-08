function run_driver() {
	echo -ne "\033]0;Intellivue Driver\007"
	read -p "Enter Intellivue Socat Driver PORT NUMBER (0, 1, 2..., (not /dev/ttyS<number>)): " driverPort
	cd build
	sudo ./dd-philips-intellivue-mp70 -portname /dev/ttyS$driverPort -udi hello
}

export -f run_driver
gnome-terminal --working-directory=$PWD --geometry 80x25+790+500 -x bash -c "run_driver; bash"
