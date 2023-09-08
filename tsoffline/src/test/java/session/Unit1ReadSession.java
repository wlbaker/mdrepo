package session;

import java.io.File;
import java.io.IOException;

import idea.tsoffline.persist.TsoSessionSTPUtil;

public class Unit1ReadSession {

	public static void main(String[] args) throws IOException {
		// File f = new File("/opt/study/rubal/BAMC 2719.002.stp");
		File share = new File("\\\\amedfsbamc0106\\ResearchData");
		
		// File folder = new File(share, "\\HiFi Research\\5. ISR - (Baker & Salinas)\\BAMC 485 (Normal) R-Ex");
		// File stpFile = new File(folder, "4685(exercise)_160830_1616_s_001.stp");

		File folder = new File(share, "\\HiFi Research\\5. ISR - (Baker & Salinas)\\ISR_HEM1_Rubal\\REBOA-036");
		// File stpFile = new File(folder, "Splice REBOA-036.stp");
		File stpFile = new File(folder, "REBOA-036.stp");

		// File stp = new File( folder, "4685(rest)_160830_1556_s_001.stp");
		
		TsoSessionSTPUtil util = new TsoSessionSTPUtil();
		util.readSessionFile(stpFile);
		
		System.out.println("\n\n******************\n\n");
		
		File verifyFile = new File(folder, "out.stp");
		util.readSessionFile(verifyFile);
	}

}
