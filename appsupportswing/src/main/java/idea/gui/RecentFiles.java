package idea.gui;

import java.io.File;
import java.util.LinkedList;
import java.util.prefs.BackingStoreException;

import javax.swing.JMenuItem;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class RecentFiles {

	public static void load(AppSetup setup, JMenuItem[] recent) {

		LinkedList<File> files = new LinkedList<File>();
		
		int idx = 0;
		for (JMenuItem item : recent) {
			String key = "recent_" + idx;

			String txt = setup.persistReadString(key, null);
			if (txt == null) {
				item.setVisible(false);
			} else {
				File file = new File(txt);
				if( files.contains( file )) {
					log.debug( "load skipping: {}", file );
					item.setVisible(false);
				} else {
					item.setText(menuTextFromFile(file));
					item.putClientProperty("file", file);
					item.setVisible(true);
					
					log.debug( "load recent: {}", file );
					files.add( file );
				}
			}

			idx++;
		}

	}

	private static String menuTextFromFile(File file) {
		File parent = file.getParentFile();
		String extension = "";
		if (parent != null) {
			extension = " [" + parent.getAbsolutePath() + "]";
		}
		String txt = file.getName() + extension;
		return txt;
	}

	public static void addFile(AppSetup setup, JMenuItem[] recent, File file) throws BackingStoreException {

		LinkedList<File> files = new LinkedList<File>();

		int idx = 0;
		for (JMenuItem item : recent) {
			String key = "recent_" + (idx++);

			// save a copy before we overwrite it

			if (file == null || files.contains(file)) {
				// already saved. Just ignore
				setup.persistWriteString(key, null );
			} else {
				files.add(file);
				setup.persistWriteString(key, file.getAbsolutePath());
				log.debug("saved recent: {} as {}", key, file.getAbsolutePath());

			}

			file = (File) item.getClientProperty("file");
		}

		load(setup, recent);
	}

}
