package idea.gui.tree.checkbox;

import java.awt.BorderLayout;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.SwingUtilities;
import javax.swing.ToolTipManager;
import javax.swing.UIManager;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeExpansionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeCellRenderer;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;

public class FileTreeViewer extends JFrame {

	private static final long serialVersionUID = 1L;
	public static final ImageIcon ICON_COMPUTER = new ImageIcon("");
	public static final ImageIcon ICON_DISK = new ImageIcon("defaults1.png");
	public static final ImageIcon ICON_FOLDER = new ImageIcon("fol_orig.png");
	public static final ImageIcon ICON_EXPANDEDFOLDER = new ImageIcon("folder_open.png");

	protected JTree m_tree;
	protected DefaultTreeModel m_model;

	private CheckTreeManager checkTreeManager;

	protected TreePath m_clickedPath;

	@SuppressWarnings("serial")
	public FileTreeViewer() {
		super("Demo tree check box");
		setSize(400, 300);

		DefaultMutableTreeNode top = new DefaultMutableTreeNode(new IconData(ICON_COMPUTER, null, "Computer"));

		DefaultMutableTreeNode node;
		File[] roots = File.listRoots();
		for (int k = 0; k < roots.length; k++) {
			node = new DefaultMutableTreeNode(new IconData(ICON_DISK, null, new FileNode(roots[k])));
			top.add(node);
			node.add(new DefaultMutableTreeNode(new Boolean(true)));
		}

		m_model = new DefaultTreeModel(top);

		m_tree = new JTree(m_model) {
			public String getToolTipText(MouseEvent ev) {
				if (ev == null)
					return null;
				TreePath path = m_tree.getPathForLocation(ev.getX(), ev.getY());
				if (path != null) {
					FileNode fnode = getFileNode(getTreeNode(path));
					if (fnode == null)
						return null;
					File f = fnode.getFile();
					return (f == null ? null : f.getPath());
				}
				return null;
			}
		};

		ToolTipManager.sharedInstance().registerComponent(m_tree);

		m_tree.putClientProperty("JTree.lineStyle", "Angled");

		TreeCellRenderer renderer = new IconCellRenderer();
		m_tree.setCellRenderer(renderer);

		m_tree.addTreeExpansionListener(new DirExpansionListener());

		m_tree.getSelectionModel().setSelectionMode(TreeSelectionModel.SINGLE_TREE_SELECTION);
		m_tree.setShowsRootHandles(true);
		m_tree.setEditable(false);

		checkTreeManager = new CheckTreeManager(m_tree, null);

		JScrollPane s = new JScrollPane();
		s.getViewport().add(m_tree);
		getContentPane().add(s, BorderLayout.CENTER);

		WindowListener wndCloser = new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		};

		addWindowListener(wndCloser);

		setVisible(true);
	}

	DefaultMutableTreeNode getTreeNode(TreePath path) {
		return (DefaultMutableTreeNode) (path.getLastPathComponent());
	}

	FileNode getFileNode(DefaultMutableTreeNode node) {
		if (node == null)
			return null;
		Object obj = node.getUserObject();
		if (obj instanceof IconData)
			obj = ((IconData) obj).getObject();
		if (obj instanceof FileNode)
			return (FileNode) obj;
		else
			return null;
	}

	public CheckTreeManager getCheckTreeManager() {
		return checkTreeManager;
	}

	// Make sure expansion is threaded and updating the tree model
	// only occurs within the event dispatching thread.
	class DirExpansionListener implements TreeExpansionListener {
		public void treeExpanded(TreeExpansionEvent event) {
			final DefaultMutableTreeNode node = getTreeNode(event.getPath());
			final FileNode fnode = getFileNode(node);

			Thread runner = new Thread() {
				public void run() {
					if (fnode != null && fnode.expand(node)) {
						Runnable runnable = new Runnable() {
							public void run() {
								m_model.reload(node);
							}
						};
						SwingUtilities.invokeLater(runnable);
					}
				}
			};
			runner.start();
		}

		public void treeCollapsed(TreeExpansionEvent event) {
		}
	}

	public static void main(String argv[]) {
		try {
			UIManager.setLookAndFeel("com.sun.java.swing.plaf.windows.WindowsLookAndFeel");
		} catch (Exception evt) {
		}
		new FileTreeViewer();
	}
}


