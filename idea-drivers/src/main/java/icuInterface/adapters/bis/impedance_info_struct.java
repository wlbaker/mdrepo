package icuInterface.adapters.bis;

import java.nio.ByteBuffer;

public class impedance_info_struct {

	/*----------------------------------------------------------+
	| Impedance in units of 100 Ohms (or 1000 Ohms for ground |
	| impedances). |
	+----------------------------------------------------------*/
	public static final int GND_SCALE = 1000;
	public static final int NON_GND_SCALE = 100; /*
												 * Limits for the impedance
												 * values
												 */
	public static final double MAX_GND_VALUE = 100.0; /* in Kohms */
	public static final double MAX_COM_VALUE = 150.0; /* in 100 ohms */
	public static final double MAX_POS_VALUE = 75.0; /* in 100 ohms */

	public static final byte IMPED_TEST_PASS = 0; // Test passed
	public static final byte IMPED_TEST_FAIL = 0x1; // High impedance
	public static final byte IMPED_TEST_FAIL_CLIP = 0x2; // Noise
	public static final byte IMPED_TEST_FAIL_LEADOFF = 0x4; // Lead off

	/* This is the value of the impedance for the channel */
	short impedance_value;

	/*
	 * Result of the impedance test. If zero, test passed. If non-zero, the bit
	 * fields in the result indicate which test(s) failed.
	 */
	short imped_test_result;

	public impedance_info_struct(ByteBuffer bb) {
		impedance_value = bb.getShort();
		imped_test_result = bb.getShort();
	}

}
