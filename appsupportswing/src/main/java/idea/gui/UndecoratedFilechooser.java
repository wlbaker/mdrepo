/*
 * http://stackoverflow.com/questions/33640908/how-to-navigate-to-a-network-host-in-jfilechooser
 */

package idea.gui;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dialog;
import java.awt.Frame;
import java.awt.HeadlessException;
import java.awt.Window;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import javax.accessibility.AccessibleContext;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRootPane;
import javax.swing.UIManager;

@SuppressWarnings("serial")
public class UndecoratedFilechooser extends JFileChooser {

	public JPanel nakedPanel;
	
	@Override
	public JDialog createDialog(Component parent) throws HeadlessException {
		String title = getUI().getDialogTitle(this);
        putClientProperty(AccessibleContext.ACCESSIBLE_DESCRIPTION_PROPERTY, 
                          title);

        JDialog dialog;
        Window window = (Window)parent; // UndecoratedOptionPane.getWindowForComponent(parent);
        if (window instanceof Frame) {
            dialog = new JDialog((Frame)window, title, true);	
        } else {
            dialog = new JDialog((Dialog)window, title, true);
        }
        dialog.setComponentOrientation(this.getComponentOrientation());

        Container contentPane = dialog.getContentPane();
        contentPane.setLayout(new BorderLayout());
        contentPane.add(this, BorderLayout.CENTER);
 
        // wlb
        nakedPanel = (JPanel)contentPane;
        if (JDialog.isDefaultLookAndFeelDecorated()) {
            boolean supportsWindowDecorations = 
            UIManager.getLookAndFeel().getSupportsWindowDecorations();
            if (supportsWindowDecorations) {
                dialog.getRootPane().setWindowDecorationStyle(JRootPane.FILE_CHOOSER_DIALOG);
            }
        }
        dialog.pack();
        dialog.setLocationRelativeTo(parent);

	return dialog;
	}

	public void hideOptions() {
		hideOptions( getComponents() );
	}
	
	private void hideOptions( Component[] components ) {
		for( Component c : components ) {
			if( c == nakedPanel ) {
				continue;
			}
			
			if( c instanceof JButton ) {
				JButton b = (JButton)c;
				if( "Cancel".equals(b.getText()) ) {
					JPanel p = (JPanel)b.getParent();
					p.setVisible( false );
				}
			} else if ( c instanceof JPanel ) {
				hideOptions( ((JPanel)c).getComponents() );
			}
		}
		
	}

	/**
	 * Create a shell folder for a given network path.
	 *
	 * @param path File to test for existence.
	 * @return ShellFolder representing the given computer node.
	 * @throws IllegalArgumentException given path is not a computer node.
	 * @throws FileNotFoundException given path could not be found.
	 */
	
//	public static ShellFolder getComputerNodeFolder(String path)
//	        throws FileNotFoundException {
//	    File file = new NonCanonicalizingFile(path);
//	    if (ShellFolder_isComputerNode(file)) {
//	        return new Win32ShellFolderManager2().createShellFolder(file);
//	    } else {
//	        throw new IllegalArgumentException("Given path is not a computer node.");
//	    }
//	}

	private static final class NonCanonicalizingFile extends File {
	    public NonCanonicalizingFile(String path) {
	        super(path);
	    }

	    @Override
	    public String getCanonicalPath() throws IOException {
	        // Win32ShellFolderManager2.createShellFolder() will call getCanonicalPath() on this file.
	        // Base implementation of getCanonicalPath() calls WinNTFileSystem.canonicalize() which fails on
	        // computer nodes (e.g. "\\blah"). We skip the canonicalize call, which is safe at this point because we've
	        // confirmed (in approveSelection()) that this file represents a computer node.
	        return getAbsolutePath();
	    }
	}
	
	private static boolean ShellFolder_isComputerNode(File selectedFile ) {
		return false;
	}
	@Override
    public void approveSelection() {
        File selectedFile = getSelectedFile();
        if (selectedFile != null && ShellFolder_isComputerNode(selectedFile)) {
//            try {
//                // Resolve path and try to navigate to it
//                setCurrentDirectory(getComputerNodeFolder(selectedFile.getPath()));
//            } catch (FileNotFoundException ex) {
                // Alert user if given computer node cannot be accessed
                JOptionPane.showMessageDialog(this, "Cannot access " + selectedFile.getPath());
//            }
        } else {
            super.approveSelection();
        }
    }

}
