package java9;

import java.io.*;
import java.lang.reflect.Constructor;
import java.util.Enumeration;
import java.util.ResourceBundle;
import java.util.stream.Collectors;

class ByteArrayClassLoader extends ClassLoader {

	public Class buildClass(String name, byte[] ba) {

		return defineClass(name, ba, 0, ba.length);
	}

}

public class Main {
	private static String metal_su = "com.sun.swing.internal.plaf.metal.resources.metal";

	public static void main(String[] args) {

		// load from the the module where a given class is
		try {
			InputStream is = Class.forName(metal_su).getResourceAsStream("metal.class");
			byte[] rawBytes = is.readAllBytes();
			System.out.println("byte count=" + rawBytes.length);
			ByteArrayClassLoader loader = new ByteArrayClassLoader();
			Class clazz = loader.buildClass(metal_su, rawBytes);

			Constructor<?> ctor = clazz.getConstructor();
			Object object = ctor.newInstance(new Object[] {});

			ResourceBundle bundle = (ResourceBundle) object;
			Enumeration<String> keyEn = bundle.getKeys();
			while (keyEn.hasMoreElements()) {
				String key = keyEn.nextElement();
				if (key.contains("FileChooser")) {
					String value = bundle.getString(key);
					System.out.println(key + ": " + value);
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}

		// load from a specific module
		// Optional<Module> specificModule =
		// ModuleLayer.boot().findModule("PlaygroundApi");
		// specificModule.ifPresent(module -> {
		// try {
		// InputStream is = module.getResourceAsStream("config.yml");
		// Main.read(is);
		// } catch (Exception e) {
		// throw new RuntimeException(e);
		// }
		// });
	}

	private static void read(InputStream is) {
		String s = new BufferedReader(new InputStreamReader(is)).lines().collect(Collectors.joining("\n"));
		System.out.println("resource: " + s);
	}
}
