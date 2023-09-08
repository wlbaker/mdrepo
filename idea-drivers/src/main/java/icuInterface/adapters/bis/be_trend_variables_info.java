package icuInterface.adapters.bis;

import java.nio.ByteBuffer;

import lombok.Data;

@Data
public class be_trend_variables_info {

	short burst_suppress_ratio; /*
								 * index variable giving percent of suppressed
								 * seconds in last 63 sec. for selected channel.
								 * range from 0 - 1000 in .1% steps
								 */
	short spectral_edge_95; /*
							 * in HZ ranged from 0-30.0 Hz in units of 0.01 Hz
							 */
	short bis_bits; /* BIS field debug data */
	short bispectral_index; /* Ranges from 0 - 100 */
	short bispectral_alternate_index; /* same as above */
	short bispectral_alternate2_index; /* same as above */
	/*
	 * in dB with respect to .01 uV rms. ranged from 0 to 100 dB in 0.01 units
	 */
	short total_power;

	/*
	 * in dB with respect to .01 uV rms. ranged from 0 to 100 dB in 0.01 units
	 */
	short emg_low;
	/*
	 * index variable giving the signal quality of the bisIndex which is
	 * combined with BSR 0 - 1000 in .1% steps
	 */
	long bis_signal_quality;
	long second_artifact; /*
						 * bit field indicating TYPE OF ARTIFACT for the last
						 * second.
						 */

	public be_trend_variables_info(ByteBuffer bb) {
		burst_suppress_ratio = bb.getShort();
		spectral_edge_95 = bb.getShort();
		bis_bits = bb.getShort();
		bispectral_index = bb.getShort();
		bispectral_alternate_index = bb.getShort();
		bispectral_alternate2_index = bb.getShort();
		total_power = bb.getShort();
		emg_low = bb.getShort();
		bis_signal_quality = bb.getLong();
		second_artifact = bb.getLong();
	}
}
