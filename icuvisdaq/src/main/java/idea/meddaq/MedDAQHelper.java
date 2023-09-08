package idea.meddaq;

/**
 * 
 * This program is a launcher for Clinical in situations where environment variables
 * and paths need to be set before starting a second JVM.
 * 
 * One path variable that needs to be set is R_HOME.
 * 
 */

//import org.apache.log4j.Logger; 
import java.io.File;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.net.URLDecoder;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Map;

public class MedDAQHelper {
	private static int verbose;

	private static String r_home = "c:\\opt\\tools\\R\\R-2.15.0";

	/**
	 * If the provided class has been loaded from a jar file that is on the
	 * local file system, will find the absolute path to that jar file.
	 * 
	 * @param context
	 *            The jar file that contained the class file that represents
	 *            this class will be found. Specify {@code null} to let
	 *            {@code LiveInjector} find its own jar.
	 * @throws IllegalStateException
	 *             If the specified class was loaded from a directory or in some
	 *             other way (such as via HTTP, from a database, or some other
	 *             custom classloading device).
	 */
	public static String findPathJar(Class<?> context) throws IllegalStateException {
		if (context == null)
			context = MedDAQHelper.class;
		String rawName = context.getName();
		String classFileName;
		/*
		 * rawName is something like package.name.ContainingClass$ClassName. We
		 * need to turn this into ContainingClass$ClassName.class.
		 */{
			int idx = rawName.lastIndexOf('.');
			classFileName = (idx == -1 ? rawName : rawName.substring(idx + 1)) + ".class";
		}

		String uri = context.getResource(classFileName).toString();
		if (uri.startsWith("file:")) {
			// throw new IllegalStateException("This class has been loaded from a directory and not from a jar file.");
			return null;
		}
		if (!uri.startsWith("jar:file:")) {
			int idx = uri.indexOf(':');
			String protocol = idx == -1 ? "(unknown)" : uri.substring(0, idx);
			throw new IllegalStateException("This class has been loaded remotely via the " + protocol
					+ " protocol. Only loading from a jar on the local file system is supported.");
		}

		int idx = uri.indexOf('!');
		// As far as I know, the if statement below can't ever trigger, so it's
		// more of a sanity check thing.
		if (idx == -1)
			throw new IllegalStateException(
					"You appear to have loaded this class from a local jar file, but I can't make sense of the URL!");

		try {
			String fileName = URLDecoder.decode(uri.substring("jar:file:".length(), idx), Charset.defaultCharset()
					.name());
			return new File(fileName).getAbsolutePath();
		} catch (UnsupportedEncodingException e) {
			throw new InternalError("default charset doesn't exist. Your VM is borked.");
		}
	}

	public Process startNewJavaProcess(final String optionsAsString, final String mainClass, final String[] arguments)
			throws IOException {
		ProcessBuilder processBuilder = createProcess(optionsAsString, mainClass, arguments);
		Process process = processBuilder.start();
		// log.debug("Process " + process.toString() + " has started");
		return process;
	}

	private ProcessBuilder createProcess(final String optionsAsString, final String mainClass, final String[] args) {
		String jvm = System.getProperty("java.home") + File.separator + "bin" + File.separator + "java";
		String classpath = System.getProperty("java.class.path");
		// log.debug("classpath: " + classpath);
		// String workingDirectory = System.getProperty("user.dir");
		List<String> command = new ArrayList<String>();
		command.add(jvm);

		if (optionsAsString != null) {
			String[] options = optionsAsString.split(" ");
			command.addAll(Arrays.asList(options));
		}
		command.add(mainClass);
		if (args != null) {
			command.addAll(Arrays.asList(args));
		}
		ProcessBuilder processBuilder = new ProcessBuilder(command);
		Map<String, String> environment = processBuilder.environment();
		environment.put("CLASSPATH", classpath);

		String data_model = System.getProperty("sun.arch.data.mode", "32");

		String ARCH = ("64".equals(data_model)) ? "x64" : "i386";

		String pathName = "Path";
		String path = environment.get(pathName);
		if (path == null) {
			pathName = "PATH";
			path = environment.get(pathName);
		}

		path = r_home + File.separator + "bin" + File.separator + ARCH + File.pathSeparator + path;

		String cwd = System.getProperty("user.dir");
		File userDir = new File(cwd);
		String name = userDir.getName();
		if ("cardioStrip".equals(name)) {
			File datamanager = new File(userDir.getParentFile(), "datamanager");
			File datamanager_lib = new File(datamanager, "lib");
			File datamanager_dll = new File(datamanager_lib, "win" + data_model);
			path += File.pathSeparatorChar + datamanager_dll.getAbsolutePath();

			File icuinterface = new File(userDir.getParentFile(), "ICUInterface");
			File icuinterface_lib = new File(icuinterface, "lib");
			File icuinterface_dll = new File(icuinterface_lib, "win" + data_model);
			path += File.pathSeparatorChar + icuinterface_dll.getAbsolutePath();
		}

		environment.put(pathName, path);
		environment.put("R_HOME", r_home);

		if (verbose > 0) {
			System.out.println("classpath=" + classpath);
			System.out.println("user.dir=" + userDir);
		}
		return processBuilder;
	}

	private static void usage() {
		System.out.println("usage: [--r_home arg]");
	}

	public static void main(String[] args) throws IOException {

		String logfile = null;
		for (int idx = 0; idx < args.length; idx++) {
			String arg = args[idx];

			if (arg.startsWith("-v")) {
				verbose++;
			}
			if (arg.equalsIgnoreCase("--r_home")) {
				r_home = args[++idx];
			}
			if (arg.equalsIgnoreCase("--log")) {
				logfile = args[++idx];
			}
		}

		MedDAQHelper processor = new MedDAQHelper();

		if (logfile == null) {
			String os = System.getProperty("os.name");
			if ("Linux".equals(os)) {
				logfile = "/tmp/mg.log";
			} else {
				logfile = "c:/tmp/mg.log";
			}
		}

		String pj = processor.findPathJar(idea.meddaq.MedDAQLauncher.class);

		ProcessBuilder proc = processor.createProcess(null, "idea.mg_daq.MgDAQLauncher", new String[] { "-log",
				logfile });

		if (verbose > 0) {
			System.out.println("pj= " + pj);
			System.out.println("proc= " + proc.command());
		}
		proc.start();

		System.exit(2);
	}

}
