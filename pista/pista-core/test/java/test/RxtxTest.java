package test;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.TooManyListenersException;

import org.pistax.PistaCl;
import org.pistax.PistaCommHandler;
import org.pistax.PistaDataPacket;
import org.pistax.PistaDev;
import org.pistax.PistaDriver;
import org.pistax.PistaEventHandler;

import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.PortInUseException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent;
import gnu.io.SerialPortEventListener;
import gnu.io.UnsupportedCommOperationException;


public class RxtxTest implements SerialPortEventListener {
	PistaDriver drv;
	PistaDev impl;
	
	static SerialPort port = null;
	
	PistaCommHandler c = new PistaCommHandler() {

		@Override
		public int write(byte[] data) throws IOException {
			System.out.println("REQ TO FORWARD DATA!");
			
			OutputStream out = port.getOutputStream();
			out.write(data);
			return data.length;
		}
		
	};
	
	PistaEventHandler h = new PistaEventHandler() {
		public int event(PistaDataPacket pkt) {
			System.out.println("got event: " + pkt.getStreamID() );

			if (pkt.getStreamID() == 'M') {
			} else if (pkt.getStreamID() == 'W') {
			} else if (pkt.getStreamID() == 'S') {
			}

			return 0;
		}
	};

	public void run() {
		// PistaIO usb0 = JavaSerialIO.connect("/dev/ttyUSB0");

		int tick_count = 0;

		PistaCl pista = PistaCl.getInstance();

		drv = pista.driver("imp731");
		impl = drv.allocate();
		
		// impl.setIO( usb0 );

		impl.attach(h);
		impl.attach(c);

		long tm0 = 0;
		do {
			long dt = System.currentTimeMillis() - tm0;
			if (dt > 1000) {
				tm0 = System.currentTimeMillis();

				pista.tick();
				System.out.println("tick");
			}
			try {
				Thread.sleep(2000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} while (tick_count < 100);

		// impl.detach();
		System.out.println("done");
	}

	@Override
	public void serialEvent(SerialPortEvent event) {
		try {
			_serialEvent(event);
		} catch (Exception e) {
			e.printStackTrace( );
		} catch (Throwable t) {
			t.printStackTrace( );
		}
	}

	public void _serialEvent(SerialPortEvent event) throws IOException {

		Object src = event.getSource();

		//
		// Dispatch event to individual methods. This keeps this ugly
		// switch/case statement as short as possible.
		//
		switch (event.getEventType()) {
		case SerialPortEvent.OUTPUT_BUFFER_EMPTY:
			break;

		case SerialPortEvent.DATA_AVAILABLE:
			SerialPort port = (SerialPort) src;
			InputStream in = port.getInputStream();
			int avail = in.available();
			byte [] buf = new byte[avail];  // we could use a fixed size buf
			
			in.read(buf);

			// System.out.print("SENDING: ");
			// System.out.println( LoggingUtil.encode(buf));
			
			impl.handle(buf );
				
			break;


		default:
			System.err.println("UNKNOWN EVENT: " + event);
			break;
		}

	}
	
	public static void main(String[] args) throws IOException, NoSuchPortException, PortInUseException, UnsupportedCommOperationException {

		String portName = "/dev/ttyUSB0";

		CommPortIdentifier portIdentifier = CommPortIdentifier.getPortIdentifier(portName);
		if (portIdentifier.isCurrentlyOwned()) {
			System.out.println("Error: Port is currently in use");
		}
		port = (SerialPort) portIdentifier.open("PistaTest", 2000);

		int baud = 115200;
		port.setSerialPortParams(baud, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);

		
		System.loadLibrary("jpistax");
		PistaCl pista = null;
		try {
			pista = PistaCl.getInstance();
		} catch (UnsatisfiedLinkError e) {
			System.err.println("Could not load pista: " + e.getMessage());
			return;
		}

		System.out.println("creating app");
		RxtxTest tester = new RxtxTest();
		try {
			
			port.addEventListener( tester );
			port.notifyOnDataAvailable( true );
			tester.run();
		} catch (TooManyListenersException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
