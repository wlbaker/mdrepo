package org.pistax.model;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;

import idea.message.StreamID;
import idea.model.IntfUtil;
import idea.model.PersistentItem;
import idea.persistence.Waveform;
import lombok.Data;
import idea.schema.rp.RpMetric;

@Entity
@Table(name = "MCCUL_IS")
@SuppressWarnings("serial")
@Data
public class MCCUL_isensor extends PersistentItem {

	protected static RpMetric[] metrics;

	public static final String CH0_LOC = "ch0";
	public static final String CH1_LOC = "ch1";
	public static final String CH2_LOC = "ch2";
	public static final String CH3_LOC = "ch3";
	public static final String CH4_LOC = "ch4";
	public static final String CH5_LOC = "ch5";
	public static final String CH6_LOC = "ch6";
	public static final String CH7_LOC = "ch7";
	public static final String CH8_LOC = "ch8";
	public static final String CH9_LOC = "ch9";
	public static final String CH10_LOC = "ch10";
	public static final String CH11_LOC = "ch11";
	public static final String CH12_LOC = "ch12";
	public static final String CH13_LOC = "ch13";
	public static final String CH14_LOC = "ch14";
	public static final String CH15_LOC = "ch15";

	static {
		metrics = IntfUtil.getMetrics(MCCUL_isensor.class);
	}

	@Override
	public RpMetric[] getMetrics()  {
		return metrics;
	}

	public MCCUL_isensor() {
		super(StreamID.WAVEFORM);
	}


	@Waveform(loc = CH0_LOC, code = CH0_LOC, unit = "mmHg", freq = 50, spp = 50, m=0.01)
	private int[] ch0;
	@Waveform(loc = CH1_LOC, code = CH1_LOC, unit = "inH2O", freq = 50, spp = 50, m=1)
	private int[] ch1;
	@Waveform(loc = CH2_LOC, code = CH2_LOC, freq = 50, spp = 50, m=1)
	private int[] ch2;
	@Waveform(loc = CH3_LOC, code = CH3_LOC, freq = 50, spp = 50, m=1)
	private int[] ch3;
	@Waveform(loc = CH4_LOC, code = CH4_LOC, freq = 50, spp = 50, m=1)
	private int[] ch4;
	@Waveform(loc = CH5_LOC, code = CH5_LOC, freq = 50, spp = 50, m=1)
	private int[] ch5;
	@Waveform(loc = CH6_LOC, code = CH6_LOC, freq = 50, spp = 50, m=1)
	private int[] ch6;
	@Waveform(loc = CH7_LOC, code = CH7_LOC, freq = 50, spp = 50, m=1)
	private int[] ch7;
	@Waveform(loc = CH8_LOC, code = CH8_LOC, freq = 50, spp = 50, m=1)
	private int[] ch8;
	@Waveform(loc = CH9_LOC, code = CH9_LOC, freq = 50, spp = 50, m=1)
	private int[] ch9;
	@Waveform(loc = CH10_LOC, code = CH10_LOC, freq = 50, spp = 50, m=1)
	private int[] ch10;
	@Waveform(loc = CH11_LOC, code = CH11_LOC, freq = 50, spp = 50, m=1)
	private int[] ch11;
	@Waveform(loc = CH12_LOC, code = CH12_LOC, freq = 50, spp = 50, m=1)
	private int[] ch12;
	@Waveform(loc = CH13_LOC, code = CH13_LOC, freq = 50, spp = 50, m=1)
	private int[] ch13;
	@Waveform(loc = CH14_LOC, code = CH14_LOC, freq = 50, spp = 50, m=1)
	private int[] ch14;
	@Waveform(loc = CH15_LOC, code = CH15_LOC, freq = 50, spp = 50, m=1)
	private int[] ch15;
}

