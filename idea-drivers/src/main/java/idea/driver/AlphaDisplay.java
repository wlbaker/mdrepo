package idea.driver;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import icuInterface.ConnectionStatus;
import icuInterface.RpUtil;
import icuInterface.conf.dev.SerialDeviceConfiguration;
import idea.conf.DeviceCapabilities;
import idea.conf.DeviceConfiguration;
import idea.intf.CharValues;
import idea.intf.DisplayInterface;
import idea.intf.SerialAdapter;
import lombok.extern.slf4j.Slf4j;

@Slf4j
public class AlphaDisplay extends SerialAdapter implements DisplayInterface {

	private static final String driverName = "z/AlphaDisplay";
	public static final char NEW_LINE = (char) 13;

	public static SerialDeviceConfiguration createConfigInstance() {
		return new SerialDeviceConfiguration(AlphaDisplay.class);
	}

	/**
	 * 
	 */
	public AlphaDisplay(DeviceConfiguration conf) {
		super(conf);
		this.conf = conf;
	}

	private void sendPacket(byte[] bytes) throws IOException {
		OutputStream out = getOutputStream();
		if (out == null) {
			log.error("output stream is null");
		} else {
			synchronized (out) {
				out.write(bytes);
			}
		}
	}

	/**
	 * Sends a priority message to the sign. Priority messages do not need
	 * memory allocation on the sign and will be displayed until another
	 * priority message is sent or a blank one is sent.
	 * 
	 * @param message
	 *            Text of the message
	 * @param signAddress
	 *            Sign address if more than one (usually "00")
	 * @param displayPosition
	 *            Which line to display on (default is middle)
	 * @param mode
	 *            text mode
	 * @throws IOException
	 */
	public void sendPriorityMessage(String message, String signAddress, char displayPosition, String mode)
			throws IOException {
		byte[] bytes = getPriorityMessageBytes(message, signAddress, displayPosition, mode.toCharArray());
		sendPacket(bytes);
	}

	/**
	 * 
	 * @param message
	 * @param signAddress
	 * @param displayPosition
	 * @param specialMode
	 * @throws IOException
	 */
	public void sendPriorityMessage(String message, String signAddress, DisplayPositions displayPosition,
			SpecialModes specialMode) throws IOException {
		byte[] bytes = getPriorityMessageBytes(message, signAddress, displayPosition.getChar(),
				specialMode.getCharArray());
		sendPacket(bytes);
	}

	/**
	 * 
	 * @param message
	 * @param signAddress
	 * @param displayPosition
	 * @param textMode
	 * @throws IOException
	 */
	public void sendPriorityMessage(String message, String signAddress, DisplayPositions displayPosition,
			TextModes textMode) throws IOException {
		byte[] bytes = getPriorityMessageBytes(message, signAddress, displayPosition.getChar(),
				textMode.getCharArray());
		sendPacket(bytes);
	}

	/**
	 * Sets a display message on the LED with no special text modes (sends in
	 * "Hold" mode);
	 * 
	 * @param topLine
	 *            Top line String
	 * @param bottomLine
	 *            Bottom Line String
	 * @throws IOException
	 */
	@Override
	public void setDisplayMessage(String topLine, String bottomLine) throws IOException {
		topLine = (topLine != null && topLine.length() > 0) ? topLine : "   ";
		bottomLine = (bottomLine != null && bottomLine.length() > 0) ? bottomLine : "   ";
		sendPriorityMessage(topLine + NEW_LINE + bottomLine, "00", DisplayPositions.MiddleLine, TextModes.Hold);
	}

	/**
	 * Returns the byte array with all proper formatting for the frame.
	 * 
	 * @param message
	 * @param signAddress
	 * @param displayPosition
	 * @param mode
	 */
	protected byte[] getPriorityMessageBytes(String message, String signAddress, char displayPosition, char[] mode) {
		StringBuilder output = new StringBuilder();
		for (int i = 0; i < 5; i++) {
			output.append(CharValues.NUL.getChar()); // 5 nulls for synchro
		}
		output.append(CharValues.SOH.getChar()); // SOH
		output.append("Z"); // TYPE CODE
		output.append(signAddress); // SIGN ADDRESS
		output.append(CharValues.STX.getChar()); // START OF TX

		output.append("A"); // COMMAND CODE
		output.append("0"); // File Label
		output.append(CharValues.ESC.getChar()); // Start of mode Field
		output.append(displayPosition); // Display Position
		output.append(mode); // Display Mode

		output.append(message); // Text Message
		output.append(CharValues.EOT.getChar()); // End of Transmission

		String outstr = output.toString();
		return outstr.getBytes();
	}

	/**
	 * 
	 * @param fileLabel
	 * @param fileType
	 * @param fileSize
	 * @param extraData
	 * @throws IOException
	 */
	public void sendMemoryConfiguration(String fileLabel, String fileType, String fileSize, String extraData)
			throws IOException {
		String data = fileLabel + fileType + "L" + fileSize + extraData;
		sendSpecialFunctionsCommand("$", data);
	}

	/**
	 * 
	 * @param SFLabel
	 * @param SFData
	 * @throws IOException
	 */
	public void sendSpecialFunctionsCommand(String SFLabel, String SFData) throws IOException {
		sendPacket(getTransmissionFrameBytes("E", SFLabel, SFData));
	}

	/**
	 * 
	 * @param fileLabel
	 * @param HW
	 * @param rowData
	 * @throws IOException
	 */
	public void sendDotsPicture(String fileLabel, String HW, String rowData) throws IOException {
		sendPacket(getTransmissionFrameBytes("I", fileLabel + HW, rowData));
	}

	/**
	 * 
	 * @param commandCode
	 * @param label
	 * @param data
	 * @return
	 */
	protected byte[] getTransmissionFrameBytes(String commandCode, String label, String data) {
		StringBuilder output = new StringBuilder();
		for (int i = 0; i < 5; i++) {
			output.append(CharValues.NUL.getChar()); // 5 nulls for synchro
		}
		output.append(CharValues.SOH.getChar()); // SOH
		output.append("Z"); // TYPE CODE
		output.append("00"); // SIGN ADDRESS
		output.append(CharValues.STX.getChar()); // START OF TX
		output.append(commandCode); // COMMAND CODE
		output.append(label);
		output.append(data); // //SpecialFunctions Label
		output.append(CharValues.EOT.getChar()); // End of Transmission

		String outstr = output.toString();
		return outstr.getBytes();
	}

	/****************************************************************************
	 * *************************************************************************
	 * * ENUMS
	 * ******************************************************************
	 * ********
	 ****************************************************************************/

	/**
	 * 
	 */
	public enum TextModes {

		Rotate(97), Hold(98), Flash(99), RollUp(101), RollDown(102), RollLeft(103), RollRight(104), WipeUp(
				105), WipeDown(106), WipeLeft(107), WipeRight(108), Scroll(109), AutoMode(
						111), RollIn(112), RollOut(113), WipeIn(114), WipeOut(115), CompressedRotate(116), Special(110);

		private final int mode;

		private TextModes(int mode) {
			this.mode = mode;
		}

		public double getMode() {
			return mode;
		}

		public char getChar() {
			return (char) mode;
		}

		public char[] getCharArray() {
			char[] charray = { (char) mode };
			return charray;
		}

	}

	/**
	 * 
	 */
	public enum SpecialModes {

		Twinkle(48), Sparkle(49), Snow(50), Interlock(51), Switch(52), Slide(53), Spray(54), Starburst(55), Welcome(
				56), SlotMachine(57);

		private final int mode;

		private SpecialModes(int mode) {
			this.mode = mode;
		}

		public double getMode() {
			return mode;
		}

		public char getChar() {
			return (char) mode;
		}

		public char[] getCharArray() {
			char[] charray = { (char) TextModes.Special.getMode(), (char) mode };
			return charray;
		}
	}

	/**
	 * 
	 */
	public enum CommandCodes {

		WriteTextFile(65), ReadTextFile(66), WriteSpecialFunctions(69), ReadSpecialFunctions(70), WriteStringFile(
				71), ReadStringFile(72), WriteDOTSPic(73), ReadDOTSPic(
						74), WriteAlphaVisionDOTSPic(77), ReadAlphaVisionDOTSPic(78), WriteAlphaVisionBulletinMsg(79);

		private final int code;

		private CommandCodes(int code) {
			this.code = code;
		}

		public double getCode() {
			return code;
		}

		public char getChar() {
			return (char) code;
		}
	}

	/**
	 * 
	 */
	public enum DisplayPositions {

		TopLine(34), MiddleLine(32), BottomLine(38);

		private final int position;

		private DisplayPositions(int position) {
			this.position = position;
		}

		public double getPosition() {
			return position;
		}

		public char getChar() {
			return (char) position;
		}
	}

	@Override
	public void connect() throws IOException {
		String portName = RpUtil.getParam(conf, "port");
		connect(portName, 9600, 8, 1, 0);
	}

	@Override
	public void process(InputStream in, OutputStream out) throws IOException {
		System.err.println("NOT EXPECTING SERIAL EVENT!");
	}

	@Override
	public ConnectionStatus getStatus() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int tick() {
		// TODO Auto-generated method stub

		return 0;
	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		// TODO Auto-generated method stub
		return null;
	}

}
