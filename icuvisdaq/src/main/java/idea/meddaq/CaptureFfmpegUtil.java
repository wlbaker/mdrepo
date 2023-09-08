package idea.meddaq;

import java.io.File;

//import org.zeromq.ZMQ;

public class CaptureFfmpegUtil {

//	ZMQ.Context context;
//	ZMQ.Socket socket;

	private void init() {
//		context = ZMQ.context(1);
//
//		// Socket to talk to server
//		System.out.println("Connecting to hello world server");
//
//		socket = context.socket(ZMQ.REQ);
//		socket.setSendTimeOut(1000);
//		socket.setReceiveTimeOut(1000);
//
//		socket.connect("tcp://localhost:5665");

	}

	public boolean beginVideoCapture(File f) {
//		String[] requests = { "RESET", "OUTPUT \"" + f + "\"", "RECORD" };
//
//		for (String request : requests) {
//			System.out.println("Sending: " + request);
//			socket.send(request.getBytes(ZMQ.CHARSET), 0);
//
//			byte[] reply = socket.recv(0);
//			if (reply == null) {
//				System.out.println("FAILED: No server");
//				return false;
//			}
//			System.out.println("Received " + new String(reply, ZMQ.CHARSET));
//		}

		return true;
	}

	private void status() {
//		String request = "STATUS";
//		try {
//			System.out.println("Sending: " + request);
//			socket.send(request.getBytes(ZMQ.CHARSET), 0);
//		} catch (Exception ee) {
//			ee.printStackTrace();
//			return;
//		}
//
//		byte[] reply = socket.recv(0);
//		if (reply == null) {
//			System.out.println("FAILED: No server");
//			return;
//		}
//		System.out.println("Received " + new String(reply, ZMQ.CHARSET));
//
//		try {
//			Thread.sleep(1000);
//		} catch (InterruptedException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
	}

	public void endVideoCapture() {
//		String request = "STOP";
//		System.out.println("Sending: " + request);
//		socket.send(request.getBytes(ZMQ.CHARSET), 0);
//
//		byte[] reply = socket.recv(0);
//		System.out.println("Received " + new String(reply, ZMQ.CHARSET));
//
//		socket.close();
//		context.term();
	}

	public static void main(String[] args) {
		CaptureFfmpegUtil util = new CaptureFfmpegUtil();

		util.init();

		char sep = File.separatorChar;
		// String path_sep = File.pathSeparator; // colon or semicolon

		String outputFile;
		if (sep == '/') {
			outputFile = "/opt/study/vasc";
		} else {
			outputFile = "C:/opt/study/vasc";
		}
		util.beginVideoCapture(new File(outputFile));

		util.status();

		util.endVideoCapture();
	}

}
