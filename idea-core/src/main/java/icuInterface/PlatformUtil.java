package icuInterface;

import java.io.File;
import java.io.IOException;
import java.lang.reflect.Field;
import java.net.URISyntaxException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

import lombok.extern.slf4j.Slf4j;

/*
 * UPDATE: some of these functions can be found here: import com.sun.jna.Platform;
 */
@Slf4j
public class PlatformUtil {

	private static boolean IS_JAMVM = false;
	private static long tm_delta = 0;

	static {
		// 
		// WLB 2023: only works before jdk17
		// initOSPath();
		// checkJAMM(); -- 2023: no longer supporting JAMM
	}

	public static void init() {
		// all the work done in the static
	}

	/*
	 * *********************************************************** Private
	 * routines
	 ***********************************************************/

	private static void initOSPath() {
		String os_id = getOSID();
		String alt_id = "lib32";
		if (os_id.indexOf("64") > 0) {
			alt_id = "lib64";
		}

		String p = System.getProperty("java.library.path");

		String sep = File.pathSeparator;
		if (";".equals(sep)) {
			// windows: keep the colons
		} else {
			// sometimes configs for linux are inadvertently copied from Windows
			sep = "[:;]";
		}

		String[] arr = p.split(sep);
		p = "";
		for (String r : arr) {
			if (File.separatorChar == '\\') {
				r = r.replace('/', '\\');
			}
			r = r.replace("\"", "");  // remove quotes in argument...can happen with Gradle launch
			String dir_seg = r + File.separator + os_id;
			File f = new File(dir_seg);
			if (!f.exists()) {
				dir_seg = r + File.separator + alt_id;
				f = new File(dir_seg);
			}
			if (!f.exists()) {
				dir_seg = r; // does the original exist??
				f = new File(dir_seg);
			}
			if (!f.exists()) {
				log.warn("java.library.path segment doesnt exist: {}", dir_seg);
			} else {
				p += dir_seg + File.pathSeparator;
				log.debug("libpath += {}", dir_seg);
			}
		}

		if ("lin32".equals(os_id)) {
			p += "/usr/lib:/usr/lib/rxtx:/usr/lib:/usr/lib/jni";
		} else if ("lin64".equals(os_id)) {
			p += "/usr/lib64:/usr/lib64/rxtx:/usr/lib64";
		}
		System.setProperty("java.library.path", p);
		log.debug("rebuilt library path: {}", p);

		Field fieldSysPath;
		try {
			fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
			fieldSysPath.setAccessible(true);
			fieldSysPath.set(null, null);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static String getOSID() {
		String os = System.getProperty("os.name");
		String os_id = "unk";
		if (os.startsWith("Linux")) {
			os_id = "lin";
		} else if (os.startsWith("Windows")) {
			os_id = "win";
		}

		// Java HotSpot(TM) 64-Bit Server VM
		String vm = System.getProperty("java.vm.name").toLowerCase();
		if (vm.indexOf("64-bit") >= 0) {
			os_id += "64";
		} else {
			// 32bit doesn't have a definite signature
			os_id += "32";
		}

		return os_id;
	}

	/*
	 * *********************************************************** Public
	 * routines
	 ***********************************************************/

	public static long currentTimeMillis() {
		long tm = System.currentTimeMillis();

		if (tm_delta != 0) {
			tm += tm_delta;
		}

		return tm;
	}

	public static boolean isJAMVM() {
		return IS_JAMVM;
	}

	public static void loadLibrary(String lib_name) {
		System.loadLibrary(lib_name);
	}

	public static ArrayList<Class<?>> getClassesForPackage(String pkgName) throws IOException {
		ArrayList<Class<?>> classes = new ArrayList<Class<?>>();
		// Get a File object for the package
		File directory = null;
		String fullPath;
		String relPath = pkgName.replace('.', '/');
		log.info("ClassDiscovery: Package: {} becomes Path: {}", pkgName, relPath);
		Enumeration<URL> resources = ClassLoader.getSystemClassLoader().getResources(relPath);
		while (resources.hasMoreElements()) {
			URL resource = resources.nextElement();
			log.info("ClassDiscovery: Resource = {}", resource);
			if (resource == null) {
				throw new RuntimeException("No resource for " + relPath);
			}
			fullPath = resource.getFile();
			log.info("ClassDiscovery: FullPath = {}", resource);

			try {
				directory = new File(resource.toURI());
			} catch (URISyntaxException e) {
				throw new RuntimeException(
						pkgName + " (" + resource
								+ ") does not appear to be a valid URL / URI.  Strange, since we got it from the system...",
						e);
			} catch (IllegalArgumentException e) {
				directory = null;
			}
			log.info("ClassDiscovery: Directory = {}", directory);

			if (directory != null && directory.exists()) {
				// Get the list of the files contained in the package
				String[] files = directory.list();
				for (int i = 0; i < files.length; i++) {
					// we are only interested in .class files
					if (files[i].endsWith(".class")) {
						// removes the .class extension
						String className = pkgName + '.' + files[i].substring(0, files[i].length() - 6);
						try {
							classes.add(Class.forName(className));
						} catch (UnsatisfiedLinkError e) {
							log.warn("UnsatisfiedLink Error: {}/{}", className, e.getMessage());
						} catch (ClassNotFoundException e) {
							log.warn("ClassNotFoundException loading: {}", className);
						} catch (Exception e) {
							log.error("Exception loading: {}", className, e);
						} catch (Throwable t) {
							log.error("Exception loading: {}", className, t);
						}
					}
				}
			} else {
				try {
					String jarPath = fullPath.replaceFirst("[.]jar[!].*", ".jar") //
							.replaceFirst("[.]exe[!].*", ".exe") //
							.replaceFirst("file:", "");
					
					jarPath = jarPath.replace("%20", " ");  // fix spaces

					JarFile jarFile = new JarFile(jarPath);
					Enumeration<JarEntry> entries = jarFile.entries();
					while (entries.hasMoreElements()) {
						JarEntry entry = entries.nextElement();
						String entryName = entry.getName();
						if( entry.isDirectory() ) {
							// recursing is not necessary, but we get it whether we want it or not
							// due to the nature of the jar entry parsing.  The Enumerator gives
							// all child entries automatically.  Hmm.
							continue;  
						}
						if (entryName.startsWith(relPath) && entryName.length() > (relPath.length() + "/".length())) {
							log.info("ClassDiscovery: JarEntry: {}", entryName);
							String className = entryName.replace('/', '.').replace('\\', '.').replace(".class", "");
							log.info("ClassDiscovery: className = {}", className);
							try {
								classes.add(Class.forName(className));
							} catch (ClassNotFoundException e) {
								// log the error and continue processing
								log.warn("ClassNotFoundException loading: {}", className);
							} catch (NoClassDefFoundError e) {
								// log the error and continue processing
								log.warn("NoClassDefFoundError loading: {}", className);
							} catch (Throwable t) {
								// log the error and continue processing
								log.error("Error while loading: {}" + className, t );
							}
						}
					}
					jarFile.close(); // 09JUN15:

				} catch (IOException e) {
					log.error(pkgName + " (" + directory + ") does not appear to be a valid package",
							e);
				}
			}
		}
		return classes;
	}

}
