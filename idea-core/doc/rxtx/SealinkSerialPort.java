package icuInterface.lib;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketAddress;
import java.net.UnknownHostException;
import java.util.TooManyListenersException;

import com.fazecast.jSerialComm.SerialPort;
import com.fazecast.jSerialComm.SerialPortDataListener;

import idea.conf.DeviceConfiguration;
import idea.intf.SerialAdapter;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class SealinkSerialPort extends SerialAdapter implements Runnable {

	SocketAddress addr;
	// dc.socket().bind(new InetSocketAddress("0.0.0.0", MEDCI_PORT));
	// // final SelDatagramChannel c = new SelDatagramChannel(dc,
	private Socket socket;
	private SerialPortDataListener listener;
	private ByteArrayInputStream inputStream;

	public SealinkSerialPort(String name) {
		String[] ar = name.split(":");

		// Create socket that is connected to server on specified port
		String server = ar[0];
		int servPort = Integer.parseInt(ar[1]);
		socket = new Socket(server, servPort);
		System.out.println("Connected to server...sending echo string");

		Thread th = new Thread(this);
		th.run();
	}

	public SealinkSerialPort(int sz_out) {
		log.error("Not ready to create size-delimited output streams");
		// outStream = new ByteArrayOutputStream( sz_out );
	}

	public void setData( byte [] data ) {
		this.setData(data, 0, data.length);
	}
	
	public void setData( byte [] data, int offset, int count ) {
		inputStream = new ByteArrayInputStream(data, offset, count);
	}
	@Override
	public InputStream getInputStream() throws IOException {
		return inputStream; // return socket.getInputStream();
	}

	@Override
	public OutputStream getOutputStream() throws IOException {
		return socket.getOutputStream();
	}

	/*
	 * 
	 * unimplemented methods
	 */

	@Override
	public void setSerialPortParams(int b, int d, int s, int p)
			throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub

	}

	@Override
	public int getBaudRate() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int getDataBits() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int getStopBits() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int getParity() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void setFlowControlMode(int flowcontrol)
			throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub

	}

	@Override
	public int getFlowControlMode() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public boolean isDTR() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void setDTR(boolean state) {
		// TODO Auto-generated method stub

	}

	@Override
	public void setRTS(boolean state) {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean isCTS() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isDSR() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isCD() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isRI() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean isRTS() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void sendBreak(int duration) {
		// TODO Auto-generated method stub

	}

	@Override
	public void addEventListener(SerialPortEventListener lsnr)
			throws TooManyListenersException {
		listener = lsnr;
	}

	@Override
	public void removeEventListener() {
		// TODO Auto-generated method stub

	}

	@Override
	public void notifyOnDataAvailable(boolean enable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void notifyOnOutputEmpty(boolean enable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void notifyOnCTS(boolean enable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void notifyOnDSR(boolean enable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void notifyOnRingIndicator(boolean enable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void notifyOnCarrierDetect(boolean enable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void notifyOnOverrunError(boolean enable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void notifyOnParityError(boolean enable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void notifyOnFramingError(boolean enable) {
		// TODO Auto-generated method stub

	}

	@Override
	public void notifyOnBreakInterrupt(boolean enable) {
		// TODO Auto-generated method stub

	}

	@Override
	public byte getParityErrorChar() throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public boolean setParityErrorChar(byte b)
			throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public byte getEndOfInputChar() throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public boolean setEndOfInputChar(byte b)
			throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean setUARTType(String type, boolean test)
			throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public String getUARTType() throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean setBaudBase(int BaudBase)
			throws UnsupportedCommOperationException, IOException {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public int getBaudBase() throws UnsupportedCommOperationException,
			IOException {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public boolean setDivisor(int Divisor)
			throws UnsupportedCommOperationException, IOException {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public int getDivisor() throws UnsupportedCommOperationException,
			IOException {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public boolean setLowLatency() throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean getLowLatency() throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean setCallOutHangup(boolean NoHup)
			throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean getCallOutHangup() throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void enableReceiveFraming(int f)
			throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub

	}

	@Override
	public void disableReceiveFraming() {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean isReceiveFramingEnabled() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public int getReceiveFramingByte() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void disableReceiveTimeout() {
		// TODO Auto-generated method stub

	}

	@Override
	public void enableReceiveTimeout(int time)
			throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean isReceiveTimeoutEnabled() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public int getReceiveTimeout() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void enableReceiveThreshold(int thresh)
			throws UnsupportedCommOperationException {
		// TODO Auto-generated method stub

	}

	@Override
	public void disableReceiveThreshold() {
		// TODO Auto-generated method stub

	}

	@Override
	public int getReceiveThreshold() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public boolean isReceiveThresholdEnabled() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void setInputBufferSize(int size) {
		// TODO Auto-generated method stub

	}

	@Override
	public int getInputBufferSize() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void setOutputBufferSize(int size) {
		// TODO Auto-generated method stub

	}

	@Override
	public int getOutputBufferSize() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void run() {
		try {
			_run();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void _run() throws IOException {
		byte [] data = new byte[256];
		
		while (true) {
			InputStream in = socket.getInputStream();
				int count = in.read(data);
				System.out.println("set data: " + count );
				setData(data, 0, count);
				System.out.println("fire();");
		}
	}

	@Override
	public void connect() throws IOException {
		// TODO Auto-generated method stub
		
	}

	@Override
	public DeviceConfiguration getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int tick() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public int getListeningEvents() {
		return SerialPort.LISTENING_EVENT_DATA_RECEIVED;
	}

}
