package icuInterface.adapters.propaq;

import icuInterface.CRCUtil;

public class PropaqPacket {

	/*
	* Command Packets
	*/
	public final static byte SystemCommand = 0x02;
	public final static byte WaveformCommand = 0x05;
	public final static byte TrendCommand = 0x06;
	public final static byte ControlCommand = 0x08;

	/*
	* Request Packets
	*/
	public final static byte AlarmLimitRequest = 0x10;
	public final static byte SensorConfiguration = 0x01;
	public final static byte SensorRequest = 0x11;
	public final static byte SystemRequest = 0x12;
	public final static byte NumericRequest = 0x14;
	public final static byte WaveformRequest = 0x15;
	public final static byte TrendRequest = 0x16;
	public final static byte ChannelRequest = 0x17;

	/*
	* Response Packets
	*/
	public final static byte AlarmLimitResponse = 0x20;
	public final static byte SensorResponse = 0x21;
	public final static byte SystemResponse = 0x22;
	public final static byte NumericResponse = 0x24;
	public final static byte WaveformResponse = 0x25;
	public final static byte TrendResponse = 0x26;
	public final static byte ChannelResponse = 0x27;
	public final static byte ControlResponse = 0x28;

	/*
	* AutoMode Packets
	*/
	public final static byte AutoAlarmLimit = 0x30;
	public final static byte AutoSensor = 0x31;
	public final static byte AutoSystem = 0x32;
	public final static byte AutoNumeric = 0x34;
	public final static byte AutoWaveform = 0x35;
	public final static byte AutoTrend = 0x36;
	public final static byte AutoChannel = 0x37;

	/*
	* init packet
	*/
	public static byte[] initPacket = { 0x02, (byte) 0xfd, 0x08, 0x01, 0x09, 0x0 };  // includes CRC

	/*
	* packet for waveform transfer
	*/

	public static byte[] autoTransferOn = { WaveformCommand, PropaqID.AutoModeOnOff, 0x01 };

	public static byte[] autoTransferOff = { WaveformCommand, PropaqID.AutoModeOnOff, 0x00 };

	/*
	* packets for polling connection to keep the link alive
	*/
	public static byte[] keepAlivePoll = { ControlCommand, PropaqID.Poll };

	public static byte[] keepAliveAuto = { ControlCommand, PropaqID.AutoLink };

	public static int maxPropaqPacket = 256;

	public byte length;
	public byte lengthComp;
	public byte type;
	public byte CRC1;
	public byte CRC2;
	public byte[] data = new byte[PropaqPacket.maxPropaqPacket];

	public PropaqPacket(byte[] values) {
		this.length = values[0];
		this.lengthComp = values[1];
		this.type = values[2];
		this.CRC1 = values[values.length - 2];
		this.CRC2 = values[values.length - 1];

		System.arraycopy(this.data, 0, values, 0, length);
	}

	public static byte[] packetStream(byte[] data) {
		byte[] tmp = new byte[data.length + 4];

		tmp[0] = (byte) data.length;
		tmp[1] = (byte) (tmp[0] ^ 0xff);

		System.arraycopy(data, 0, tmp, 2, data.length);

		int CRC = CRCUtil.getCRC16(data, 0, data.length);
		tmp[tmp.length - 2] = (byte) (CRC & 0xff);
		tmp[tmp.length - 1] = (byte) ((CRC >> 8) & 0xff);

		return tmp;
	}

}