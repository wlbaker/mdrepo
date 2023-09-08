package opt.sigmapad;

import java.io.File;

public class LaunchSWT {

	public static void main(String[] args) {
		// System.setProperty("user.home", System.getenv("USERPROFILE"));
		File tmps = new File("c:/tmp/.swt");
		tmps.mkdirs();
		
		System.setProperty("swt.library.path", tmps.getPath());
		System.getProperty("user.home");
		SigmaPadSWT.main(args);
	}

}
