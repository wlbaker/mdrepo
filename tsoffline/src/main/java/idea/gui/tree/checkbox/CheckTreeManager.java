package idea.gui.tree.checkbox;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

import javax.swing.JCheckBox;
import javax.swing.JTree;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.TreePath;


public class CheckTreeManager extends MouseAdapter implements TreeSelectionListener {
	//CheckTreeSelectionModel selectionModel;
	private JTree tree = new JTree();

	int hotspot = new JCheckBox().getPreferredSize().width;
	private CheckTreeCellRenderer renderer;

	public CheckTreeManager(JTree tree, CheckTreeSelectionModel checkTreeSelectionModel) {
		this.tree = tree;

		CheckTreeSelectionModel selectionModel;
		if (checkTreeSelectionModel != null) {
			//selectionModel = new CheckTreeSelectionModel(tree.getModel()); 
			selectionModel = checkTreeSelectionModel;

		} else {
			selectionModel = new CheckTreeSelectionModel(tree.getModel());
			//System.out.println(selectionModel.getSelectionPath());
		}

		renderer = new CheckTreeCellRenderer(tree.getCellRenderer(), selectionModel);
		tree.setCellRenderer(renderer);

		tree.addMouseListener(this);
		selectionModel.addTreeSelectionListener(this);
	}

	public void mouseClicked(MouseEvent me) {
		//System.out.println("start...");

		TreePath path = tree.getPathForLocation(me.getX(), me.getY());
		//System.out.println(Arrays.asList(path));

		if (path == null) {
			//System.out.println("path==null");
			return;
		}

		if (me.getX() / 1.2 > tree.getPathBounds(path).x + hotspot) {
			//System.out.println("me.getX()/1.2>tree.getPathBounds(path).x+hotspot");
			return;
		}

		CheckTreeSelectionModel selectionModel = renderer.getSelectionModel();
		boolean selected = selectionModel.isPathSelected(path, true);
		selectionModel.removeTreeSelectionListener(this);

		try {
			if (selected) {
				//System.out.println("selected");
				selectionModel.removeSelectionPath(path);
			} else {
				//System.out.println("not selected");
				selectionModel.addSelectionPath(path);
			}
		} finally {
			//System.out.println("finally");
			selectionModel.addTreeSelectionListener(this);
			tree.treeDidChange();
		}
	}

	public CheckTreeSelectionModel getSelectionModel() {
		return renderer.getSelectionModel();
	}

	public void setSelectionModel(CheckTreeSelectionModel selectionModel) {
		renderer.setSelectionModel(selectionModel);

	}

	public void valueChanged(TreeSelectionEvent e) {
		tree.treeDidChange();
	}
}
