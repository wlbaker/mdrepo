package idea.gui.tree.checkbox;

import java.awt.BorderLayout;
import java.awt.Component;

import javax.swing.JPanel;
import javax.swing.JTree;
import javax.swing.tree.TreeCellRenderer;
import javax.swing.tree.TreePath;

public class CheckTreeCellRenderer extends JPanel implements TreeCellRenderer {

	static final long serialVersionUID = 0;

	CheckTreeSelectionModel selectionModel;
	private TreeCellRenderer delegate;
	TristateCheckBox checkBox = new TristateCheckBox();

	public CheckTreeCellRenderer(TreeCellRenderer delegate, CheckTreeSelectionModel selectionModel) {
		this.delegate = delegate;
		this.selectionModel = selectionModel;

		setLayout(new BorderLayout());
		setOpaque(false);
		checkBox.setOpaque(false);

	}

	public Component getTreeCellRendererComponent(JTree tree, Object value, boolean selected, boolean expanded,
			boolean leaf, int row, boolean hasFocus) {
		Component renderer = delegate.getTreeCellRendererComponent(tree, value, selected, expanded, leaf, row,
				hasFocus);

		TreePath path = tree.getPathForRow(row);

		if (path != null) {
			if (selectionModel.isPathSelected(path, true)) {
				checkBox.setState(checkBox.SELECTED);
			} else {
				checkBox.setState(checkBox.NOT_SELECTED);
			}

			if (selectionModel.isPartiallySelected(path)) {
				checkBox.setState(TristateCheckBox.DONT_CARE);
			}
		}

		removeAll();

		add(checkBox, BorderLayout.WEST);
		add(renderer, BorderLayout.CENTER);
		
		return this;
	}

	public TreeCellRenderer getDelegate() {
		return delegate;
	}

	public void setDelegate(TreeCellRenderer delegate) {
		this.delegate = delegate;
	}

	public CheckTreeSelectionModel getSelectionModel() {
		return selectionModel;
	}

	public void setSelectionModel(CheckTreeSelectionModel selectionModel) {
		this.selectionModel = selectionModel;
	}
}

