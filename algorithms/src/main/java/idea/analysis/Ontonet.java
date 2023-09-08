package idea.analysis;

import com.sun.jna.Library;

public interface Ontonet extends Library {
	public boolean initLicense(String filename);

	public byte calculate(String filename, String names);

	public boolean writeObf(String inFilename, String names, String outFile);
	public boolean writeTXT(String inFilename, String names, String outFile);
}
