package org.pistax;

import java.io.IOException;
import java.io.OutputStream;

import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.UnsupportedCommOperationException;

class RxtxCBAdapter extends PistaCommHandler {
	private SerialPort port;
	private CommPortIdentifier portId;

	public RxtxCBAdapter(String portName) {
		super();
		try {
			portId = CommPortIdentifier.getPortIdentifier(portName);
		} catch (NoSuchPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	@Override
	public int open() throws PortInUseException {
		port = (SerialPort) portId.open("RxtxCB", 2000);
		return 0;
	}

	@Override
	public int config(int baud, int datab, int stopb, char parity) throws UnsupportedCommOperationException {

		port.setSerialPortParams(baud, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
		return 0;
	}

	@Override
	public int write(byte[] buf) throws IOException {
		System.out.println("Rxtx send: " + buf);

		OutputStream os = port.getOutputStream();
		os.write(buf);
		return 0;
	}

	@Override
	public int close() {
		if (port != null) {
			port.close();
			port = null;
		}
		return 0;
	}

}
