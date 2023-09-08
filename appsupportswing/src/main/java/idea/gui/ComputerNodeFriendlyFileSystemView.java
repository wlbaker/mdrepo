/*
 * http://stackoverflow.com/questions/33640908/how-to-navigate-to-a-network-host-in-jfilechooser
 */

package idea.gui;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.swing.Icon;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileSystemView;

public class ComputerNodeFriendlyFileSystemView extends FileSystemView {

	private final FileSystemView delegate;

	public ComputerNodeFriendlyFileSystemView(FileSystemView delegate) {
		this.delegate = delegate;
	}

	private static boolean ShellFolder_isComputerNode(File selectedFile) {
		// FIXME: see article refer3enced above
		return false;
	}

	/**
	 * Create a shell folder for a given network path.
	 *
	 * @param path
	 *            File to test for existence.
	 * @return ShellFolder representing the given computer node.
	 * @throws IllegalArgumentException
	 *             given path is not a computer node.
	 * @throws FileNotFoundException
	 *             given path could not be found.
	 */
	public static File getComputerNodeFolder(String path) throws FileNotFoundException {
		File file = new NonCanonicalizingFile(path);
		if (ShellFolder_isComputerNode(file)) {
			// FIXME: here too..but Win32ShellFolderManager2() has gone missing!
			// return new Win32ShellFolderManager2().createShellFolder(file);
			return null;
		} else {
			throw new IllegalArgumentException("Given path is not a computer node.");
		}
	}

	private static final class NonCanonicalizingFile extends File {
		public NonCanonicalizingFile(String path) {
			super(path);
		}

		@Override
		public String getCanonicalPath() throws IOException {
			// Win32ShellFolderManager2.createShellFolder() will call
			// getCanonicalPath() on this file.
			// Base implementation of getCanonicalPath() calls
			// WinNTFileSystem.canonicalize() which fails on
			// computer nodes (e.g. "\\blah"). We skip the canonicalize call,
			// which is safe at this point because we've
			// confirmed (in approveSelection()) that this file represents a
			// computer node.
			return getAbsolutePath();
		}
	}

	@Override
	public File createFileObject(String path) {
		File placeholderFile = new File(path);
		if (ShellFolder_isComputerNode(placeholderFile)) {
			try {
				return getComputerNodeFolder(path);
			} catch (FileNotFoundException ex) {
				return placeholderFile;
			}
		} else {
			return delegate.createFileObject(path);
		}
	}

	// All code below simply delegates everything to the "delegate"

	@Override
	public File createNewFolder(File containingDir) throws IOException {
		return delegate.createNewFolder(containingDir);
	}

	@Override
	public boolean isRoot(File f) {
		return delegate.isRoot(f);
	}

	@Override
	public Boolean isTraversable(File f) {
		return delegate.isTraversable(f);
	}

	@Override
	public String getSystemDisplayName(File f) {
		return delegate.getSystemDisplayName(f);
	}

	@Override
	public String getSystemTypeDescription(File f) {
		return delegate.getSystemTypeDescription(f);
	}

	@Override
	public Icon getSystemIcon(File f) {
		return delegate.getSystemIcon(f);
	}

	@Override
	public boolean isParent(File folder, File file) {
		return delegate.isParent(folder, file);
	}

	@Override
	public File getChild(File parent, String fileName) {
		return delegate.getChild(parent, fileName);
	}

	@Override
	public boolean isFileSystem(File f) {
		return delegate.isFileSystem(f);
	}

	@Override
	public boolean isHiddenFile(File f) {
		return delegate.isHiddenFile(f);
	}

	@Override
	public boolean isFileSystemRoot(File dir) {
		return delegate.isFileSystemRoot(dir);
	}

	@Override
	public boolean isDrive(File dir) {
		return delegate.isDrive(dir);
	}

	@Override
	public boolean isFloppyDrive(File dir) {
		return delegate.isFloppyDrive(dir);
	}

	@Override
	public boolean isComputerNode(File dir) {
		return delegate.isComputerNode(dir);
	}

	@Override
	public File[] getRoots() {
		return delegate.getRoots();
	}

	@Override
	public File getHomeDirectory() {
		return delegate.getHomeDirectory();
	}

	@Override
	public File getDefaultDirectory() {
		return delegate.getDefaultDirectory();
	}

	@Override
	public File createFileObject(File dir, String filename) {
		return delegate.createFileObject(dir, filename);
	}

	@Override
	public File[] getFiles(File dir, boolean useFileHiding) {
		return delegate.getFiles(dir, useFileHiding);
	}

	@Override
	public File getParentDirectory(File dir) {
		return delegate.getParentDirectory(dir);
	}

	public static void main(String[] args) {

		FileSystemView fsv = FileSystemView.getFileSystemView();
		File Desktop = fsv.getRoots()[0];
		File Network = fsv.getChild(Desktop, "::{F02C1A0D-BE21-4350-88B0-7367FC96EF3C}");
		File Host = fsv.getChild(Network, "AMEDA7AISR0211"); // Must be in
																// Capital
																// Letters

		System.out.println("HOST=" + Host);
		// this gives drive letters of the current machine!  Useless.
//		File[] files = Host.listRoots();
//		if (files == null || files.length == 0) {
//			System.out.print("NO ROOTS!");
//		}
//		if (files == null || files.length == 0) {
//			files = Host.listFiles();
//		}
		File [] files = Host.listFiles();
		if (files == null) {
			System.out.print("NO FILES EITHER!");
		} else {
			for (File file : files)
				System.out.println(file.getName() + ": " + file);
		}

		ComputerNodeFriendlyFileSystemView fsv2 = new ComputerNodeFriendlyFileSystemView(
				FileSystemView.getFileSystemView());
		JFileChooser chooser = new JFileChooser("\\\\AMEDA7AISR0021", fsv2);
		chooser.showOpenDialog(null);
	}

}
