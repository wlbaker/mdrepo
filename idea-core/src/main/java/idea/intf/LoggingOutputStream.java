package idea.intf;

import static icuInterface.LoggingUtil.encode;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.OutputStream;

public class LoggingOutputStream extends OutputStream {
	OutputStream ori;
	private OutputStream logger;

	public LoggingOutputStream(OutputStream ori, OutputStream logger)
			throws FileNotFoundException {
		this.ori = ori;
		this.logger = logger;
	}

	@Override
	public void write(byte[] b, int off, int len) throws IOException {
		logger.write("[out] :".getBytes());
		logger.write(encode(b, off, len).getBytes());
		logger.write('\n');
		if (ori != null) {
			ori.write(b, off, len);
		}
	}

	@Override
	public void write(byte[] b) throws IOException {
		logger.write("[out] :".getBytes());
		logger.write(encode(b).getBytes());
		logger.write('\n');
		if (ori != null) {
			ori.write(b);
		}
	}

	@Override
	public void write(int b) throws IOException {
		logger.write("[out] :".getBytes());
		
		byte [] oneb = new byte[] { (byte) b };
		logger.write(encode(oneb).getBytes());
		logger.write('\n');
		if (ori != null) {
			ori.write(b);
		}
	}
}

