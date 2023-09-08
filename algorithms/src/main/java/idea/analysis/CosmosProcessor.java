package idea.analysis;

import idea.conf.DeviceCapabilities;
import idea.intf.StreamProducer;
import idea.message.StreamID;
import idea.model.PersistentItem;
import idea.model.dev.OntonixMeasurement;
import idea.schema.rp.RpMetric;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

import lombok.extern.slf4j.Slf4j;

import com.sun.jna.Native;

@Slf4j
public class CosmosProcessor extends AbstractAnalysisProcessor {

	// private static String libraryFile =
	// "c:\\opt\\workspace\\caddo\\algorithms\\lib\\win32\\ontonet_dll";
	// private static String libraryFile = "ontonet_dll";
	private static String libraryFile = "c:\\opt\\workspace\\chaktaw\\algorithms\\lib\\win32\\ontonet_dll";
	// String licenseFile =
	// "c:\\opt\\workspace\\caddo\\algorithms\\lib\\win32\\license.dat";
	// private static String licenseFile =
	// "c:\\opt\\tools\\ontomed\\license\\license.dat";
	private static String licenseFile = "c:\\opt\\tools\\ontomed2\\license_2.dat";
	String toOntonixFile = "c:\\tmp\\ontomed\\data\\cosmos_in.csv";
	String fromOntonixFile = "c:\\tmp\\ontomed\\data\\cosmos_out.out";

	private static Ontonet ontonet;
	private static DeviceCapabilities caps;
	static RpMetric[] metrics;
	
	static {
		try {
			ontonet = (Ontonet) Native.loadLibrary(libraryFile, Ontonet.class);
			boolean tf = ontonet.initLicense(licenseFile);
			System.out.println("initLicense=" + tf);
		} catch (UnsatisfiedLinkError er) {
			log.error(er.getMessage());
		}
		
		 caps = new DeviceCapabilities(CosmosProcessor.class);
		 caps.setDriverName("ONTO_COSMOS");

		 caps.addStream(StreamID.MEASUREMENT, OntonixMeasurement.class);
	}


	public CosmosProcessor() {

	}

	protected OntonixMeasurement processLogFile(File f) throws IOException {
		OntonixMeasurement block = new OntonixMeasurement();
		BufferedReader in = new BufferedReader(new FileReader(f));

		String line;
		int output_line = 0;
		if (in != null) {
			// (line = in.readLine()) != null) {
			// if (output_line > 0) {
			// log.error("not expecting more than one line in COSMOS file");
			// break;
			// }
			// int ch = line.charAt(0);
			// if (!Character.isDigit(ch)) {
			// log.error("CosmosProcessor skipping line: {}", line);
			// continue; // column titles??
			// }
			// line.split(",");
			String[] arr = readLines(in);
			in.close();

			if (arr.length < 10) {
				log.error("DATA ERROR IN COSMOS LOG: {} arr.length={}", f, arr.length);
			} else {
				int idx = 0;
				String tm = arr[idx++];
				int shortTermStability = (int) (100 * Double.parseDouble(arr[idx++]));
				int midTermStability = (int) (100 * Double.parseDouble(arr[idx++]));
				int longTermStability = (int) (100 * Double.parseDouble(arr[idx++]));
				int complexity = (int) (100 * Double.parseDouble(arr[idx++]));
				int lower_complexity = (int) (100 * Double.parseDouble(arr[idx++]));
				int upper_complexity = (int) (100 * Double.parseDouble(arr[idx++]));
				int entropy = (int) (100 * Double.parseDouble(arr[idx++]));
				int robustness = (int) (100 * Double.parseDouble(arr[idx++]));

				block.setSTS( shortTermStability);
				block.setMTS( midTermStability);
				block.setLTS(longTermStability);
				block.setCPLX(complexity);
				block.setLWRCPLX(lower_complexity);
				block.setUPRCPLX(upper_complexity);
				block.setENTR(entropy);
				block.setROBUST(robustness);
			}
		}

		return block;
	}

	private String[] readLines(BufferedReader in) throws IOException {
		List<String> arr = new LinkedList<String>();
		String line;
		while ((line = in.readLine()) != null) {
			arr.add(line);
		}
		String[] ar = new String[arr.size()];
		return arr.toArray(ar);
	}

	public String process(String inFile, String labels) {
		byte cal = ontonet.calculate(inFile, labels);
		boolean tf = ontonet.writeTXT(inFile, labels, fromOntonixFile);
		log.info("RESULTS calc: {} writeObf: {}", cal, tf);

		try {
			OntonixMeasurement block = processLogFile(new File(fromOntonixFile));
			fireStreamEvent(0,this,StreamID.MEASUREMENT, block);
		} catch (IOException e) {
			log.error("processing log file");
		}
		return fromOntonixFile;
	}

	@Override
	public void streamEvent(int jobID, StreamProducer source, StreamID sid, PersistentItem item) {
		// TODO Auto-generated method stub

	}

	@Override
	public DeviceCapabilities getStaticCapabilities() {
		return caps;
	}

	@Override
	void reset() {
		// TODO Auto-generated method stub

	}

	private static String nms_old = "tm,SpO2.HR,CVP.MEAN,GEDV,GEDVI,EVLW,EVLWI,PCCI,p-SVRI,SVV,etCO2a,PA.PWP,PA.MEAN"
			+ ",PA.SYS,PA.DIA,ART.PWP,ART.MEAN,ART.SYS,ART.DIA,ART.HR,ECG.PP,ECG.ARR,ECG.PVC,ECG.HR,SPO2_SATU,SPO2_PR"
			+ ",Ta,C,R,Pmin,Pocc,Pmean,Pplat,PEEP,iPEEP,Ppeak,TrVol,TVexp,fspn,MVspn,MV,Ltc,MTF,GTemp,ftotal,VTasb"
			+ ",NIF,RSBI,CO2,DS,rDS,etCO2,FiO2,HRspO2,SPO2";


}
