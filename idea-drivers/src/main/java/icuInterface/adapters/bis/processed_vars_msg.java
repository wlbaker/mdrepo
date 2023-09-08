package icuInterface.adapters.bis;

import java.nio.ByteBuffer;

import lombok.Data;

@Data
public class processed_vars_msg {
	dsc_info_struct proc_dsc_info; // Info. on dsc, pic and selftest
	// Impedance info for 2 channels.
	impedance_info_struct[] impedance_info; // 2
	long host_filt_setting;
	long host_smoothing_setting;
	// Spectral and Bispectral artifact detection masks.
	long host_spectral_art_mask;
	long host_bispectral_art_mask;
	// trend variables for 3 channels (ch1, ch2 and ch12 combined) 
	be_trend_variables_info[] trend_variables; // 3
	
	public processed_vars_msg(ByteBuffer bb) {
		proc_dsc_info = new dsc_info_struct( bb );
		impedance_info = new impedance_info_struct[2];
		impedance_info[0] = new impedance_info_struct( bb );
		impedance_info[1] = new impedance_info_struct( bb );
		host_filt_setting = bb.getLong();
		host_smoothing_setting = bb.getLong();
		host_spectral_art_mask = bb.getLong();
		trend_variables = new be_trend_variables_info[3];
		trend_variables[0] = new be_trend_variables_info( bb );
		trend_variables[1] = new be_trend_variables_info( bb );
		trend_variables[2] = new be_trend_variables_info( bb );
	}
};
