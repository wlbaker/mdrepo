package org.pistax;

import java.io.IOException;
import java.io.OutputStream;

import com.fazecast.jSerialComm.SerialPort;

class JSerialCBAdapter extends PistaCommHandler {
	private SerialPort port;
	// private CommPortIdentifier portId;

	public JSerialCBAdapter(String portName) {
		super();
		// try {
			// portId = CommPortIdentifier.getPortIdentifier(portName);
			port = SerialPort.getCommPort(portName);
		// } catch (NoSuchPortException e) {
			//e.printStackTrace();
		//}
	}

	@Override
	public int open() throws IOException {
		port.openPort(2000);
		return 0;
	}

	@Override
	public int config(int baud, int datab, int stopb, char parity) throws IOException {

		// port.setSerialPortParams(baud, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
		port.setComPortParameters(baud, 8, SerialPort.ONE_STOP_BIT, SerialPort.NO_PARITY);
		return 0;
	}

	@Override
	public int write(byte[] buf) throws IOException {
		System.out.println("jserial send: " + buf);

		OutputStream os = port.getOutputStream();
		os.write(buf);
		return 0;
	}

	@Override
	public int close() {
		if (port != null) {
			port.closePort();
			port = null;
		}
		return 0;
	}

}
