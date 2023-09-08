package icuInterface.adapters.bis;

import java.nio.ByteBuffer;

import lombok.Data;

@Data
public class processed_vars_with_extra_vars_msg {
	dsc_info_struct proc_dsc_info;
	 impedance_info_struct [] impedance_info;  // 2
	 long host_filt_setting;
	 long host_smoothing_setting;
	 long host_spectral_art_mask;
	 long host_bispectral_art_mask;
	/*--------------------------------------------------------------+
	| trend variables for 3 channels (ch1, ch2 and ch12 combined) |
	| with extra variables |
	+--------------------------------------------------------------*/
	 be_trend_variables_extra_info [] trend_variables_extra; // 3
	 
	 public processed_vars_with_extra_vars_msg(ByteBuffer bb) {
			proc_dsc_info = new dsc_info_struct( bb );
			impedance_info = new impedance_info_struct[2];
			impedance_info[0] = new impedance_info_struct( bb );
			impedance_info[1] = new impedance_info_struct( bb );
			host_filt_setting = bb.getLong();
			host_smoothing_setting = bb.getLong();
			host_spectral_art_mask = bb.getLong();
			trend_variables_extra = new be_trend_variables_extra_info[3];
			trend_variables_extra[0] = new be_trend_variables_extra_info( bb );
			trend_variables_extra[1] = new be_trend_variables_extra_info( bb );
			trend_variables_extra[2] = new be_trend_variables_extra_info( bb );
	}
}
