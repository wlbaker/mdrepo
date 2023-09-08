package icuInterface.adapters.bis;

import java.nio.ByteBuffer;

class dsc_info_struct {
	public static final byte SINGLE_CHANNEL_OR_SENSOR_TYPE = 1; /* Sensor Plus */
	public static final byte DUAL_CHANNEL_OR_SENSOR_TYPE = 2; /* Quatro */
	public static final byte PEDIATRIC_OR_SENSOR_TYPE = 3; /* Pediatric */
	public static final byte DUAL_CHANNEL_ICU_SENSOR_TYPE = 4; /* Extend */
	public static final byte DEMO_SENSOR_TYPE = 5; /* Demo (Plus) */
	public static final byte PEDIATRIC_XP_SENSOR_TYPE = 7; /* Pediatric XP */
	/*
	 * Plus Simulator
	 */
	public static final byte SINGLE_CHANNEL_SENSOR_SIMULATOR = 8;
	public static final byte DUAL_CHANNEL_SENSOR_SIMULATOR = 9; /* Quatro Sim. */
	public static final byte SEMI_REUSABLE_SENSOR_TYPE = 12; /* SRS Type 1 */
	public static final byte EXTEND_DEMO_SENSOR_TYPE = 13; /* Demo (Extend) */
	public static final byte BILATERAL_SENSOR_TYPE = 14; /* Bilateral */
	public static final byte BILATERAL_SENSOR_TYPE_1 = 16; /* new Bilateral */
	/*
	 * 4 channel Sim.
	 */
	public static final byte FOUR_CHANNEL_SENSOR_SIMULATOR = 17;

	public static final byte QUICK_SELFTEST_PASS = 0;
	/*
	 * Set when avg noise test fails.
	 */
	public static final byte QUICK_GAIN_TEST_BIT = 0x1;
	/*
	 * Set when blocked gain test fails.
	 */
	public static final byte QUICK_NOISE_TEST_BIT = 0x2;
	/* Set for timeout, DSC disconnect and other failures during the test . */
	public static final byte QUICK_TEST_FAIL_BIT = 0x4;
	/*
	 * Set when the quick test has not been run at all. Cleared when the test is
	 * done at least once.
	 */
	public static final byte QUICK_TEST_RESULT_VALID_BIT = 0x8;

	byte dsc_id; /* DSC ID from status nibble 1 */
	byte dsc_id_legal; /*
						 * Flag when non-zero indicates that a legaldsc is
						 * connected
						 */
	byte pic_id; /* (Sensor Type * 10)+ PIC ID */
	byte pic_id_legal; /* if non-zero, a legal pic is connected. */

	/* Number of channels on the DSC connected. Valid only when dsc_id is legal. */
	short dsc_numofchan;
	/*
	 * If zero, test passed. If non-zero, the bit fields in the result indicate
	 * which test(s) failed.
	 */
	short quick_test_result;
	/* DSC gain (in uV/ADC) = dsc_gain_num/dsc_gain_divisor */
	long dsc_gain_num;
	long dsc_gain_divisor;
	/* DSC offset (in uV/ADC) = dsc_offset_num/dsc_offset_divisor */
	long dsc_offset_num;
	long dsc_offset_divisor;

	public dsc_info_struct(ByteBuffer bb) {
		dsc_id = bb.get();
		dsc_id_legal = bb.get(); /*
								 * Flag when non-zero indicates that a legaldsc
								 * is connected
								 */
		pic_id = bb.get(); /* (Sensor Type * 10)+ PIC ID */
		pic_id_legal = bb.get(); /* if non-zero, a legal pic is connected. */

		/*
		 * Number of channels on the DSC connected. Valid only when dsc_id is
		 * legal.
		 */
		dsc_numofchan = bb.getShort();
		/*
		 * If zero, test passed. If non-zero, the bit fields in the result
		 * indicate which test(s) failed.
		 */
		quick_test_result = bb.getShort();
		dsc_gain_num = bb.getLong();
		dsc_gain_divisor = bb.getLong();
		dsc_offset_num = bb.getLong();
		dsc_offset_divisor = bb.getLong();
	}

}
