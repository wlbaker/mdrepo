package idea;

import java.util.Enumeration;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

public class ZZTestToneUtil {

	/**
	 * @param args
	 * @throws InterruptedException 
	 */
	public static void main(String[] args) throws Exception {
		String fullPath = "c:\\opt\\meddaq\\bin\\meddaq64.exe!\\idea\\analysis";
		String jarPath = fullPath.replaceFirst("[.]jar[!].*", ".jar").replaceFirst("[.]exe[!].*", ".exe").replaceFirst("file:", "");
		
		System.out.println("fullpath=" + fullPath);
		System.out.println("jarpath=" + jarPath);
		JarFile jarFile = new JarFile(jarPath);
		Enumeration<JarEntry> entries = jarFile.entries();
		while (entries.hasMoreElements()) {
			JarEntry entry = entries.nextElement();
			String entryName = entry.getName();
			
			System.out.println("name=" + entryName);
		}
		jarFile.close();

		ToneUtil.playTone(300, 4000, 10);
		
		Thread.sleep(4000);
		ToneUtil.playTone(1000, 8000, 10);

		Thread.sleep(4000);
		ToneUtil.playTone(1000, 8000, 20);
		Thread.sleep(4000);
		ToneUtil.playTone(1000, 8000, 80);
	}

}
