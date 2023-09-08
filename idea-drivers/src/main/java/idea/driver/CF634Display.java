package idea.driver;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.intf.AdapterInterface;
import idea.intf.DisplayInterface;
import idea.intf.SerialAdapter;
import idea.schema.rp.RpDevice;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class CF634Display extends SerialAdapter implements AdapterInterface, DisplayInterface {

	private static final String driverName = "z/CrystalFonz CF634";

	public static final char NEW_LINE = (char) 13;
	private SerialDeviceConfiguration conf;

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(CF634Display.class);
	}

	/**
	 * 
	 */
	public CF634Display(RpDevice conf) {
		super(conf);
	}

	/**
	 * 
	 */
	public enum Command {

		CursorHome(1), HideDisplay(2), RestoreDisplay(3), HideCursor(4), ShowUnderscoreCursor(5), //
		ShowBlinkingBlock(6), ShowInvertedBlinkingBlock(7), //
		Backspace(8), ControlBootScreen(9), LF(10), Delete(11), FF(12), CR(13), Backlight(14), //
		Contrast(15), Rsrv(16), SetCursorPosition(17), HorizontalBar(18), //
		ScrollOn(19), ScrollOff(20), SetScrollingChars(21), EnableScrolling(22), WrapOn(23), WrapOff(24), //
		SetCustomChar(25), Reboot(26), ESC(27), LBN(28), LCDController(30), InfoScreen(31);

		private final int code;

		private Command(int code) {
			this.code = code;
		}

		public double getCode() {
			return code;
		}

	}

	@Override
	public void connect() throws IOException {

		String portName = conf.getPort();

		connect(portName, 19200, 8, 1, 0);

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return null;
	}

	@Override
	public int tick() {
		return 0;
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		System.err.println("NOT EXPECTING SERIAL EVENT");

		log.error("device disconnect?");

	}

	@Override
	public void setDisplayMessage(String topLine, String bottomLine) throws IOException {
		OutputStream out = getOutputStream();
		out.write(topLine.getBytes());
		if (bottomLine != null) {
			out.write("\r".getBytes());
			out.write(bottomLine.getBytes());
		}
	}

	public void setDisplayMessage(String txt) throws IOException {
		setDisplayMessage(txt, null);

	}

	public void sendCommand(Command c) throws IOException {
		OutputStream out = getOutputStream();
		out.write((byte) c.code);
	}

	public void showInfoScreen() throws IOException {
		sendCommand(CF634Display.Command.InfoScreen);
	}

	public void clear() throws IOException {
		setDisplayMessage("\r\n\r\n\r\n\r\n\r\n");
	}

	public void hideCursor() throws IOException {
		sendCommand(CF634Display.Command.HideCursor);
	}

	public void disableWrap() throws IOException {
		sendCommand(CF634Display.Command.WrapOff);
	}

	public void home() throws IOException {
		sendCommand(CF634Display.Command.CursorHome);
	}

}
