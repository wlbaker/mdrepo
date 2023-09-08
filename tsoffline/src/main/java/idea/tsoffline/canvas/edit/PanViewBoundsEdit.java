package idea.tsoffline.canvas.edit;

import javax.swing.undo.AbstractUndoableEdit;
import javax.swing.undo.CannotRedoException;
import javax.swing.undo.CannotUndoException;

import org.piccolo2d.PCamera;
import org.piccolo2d.util.PBounds;

import lombok.Getter;
import idea.tsoffline.canvas.TsBaseCanvas;

public class PanViewBoundsEdit extends AbstractUndoableEdit {
	TsBaseCanvas canvas;

	@Getter
	private PCamera node;
	@Getter
	private PBounds original;
	@Getter
	private PBounds revision;

	public PanViewBoundsEdit(TsBaseCanvas canvas, PCamera node, PBounds ori, PBounds desired) {
		this.canvas = canvas;
		this.node = node;
		this.original = ori;
		this.revision = desired;
	}

	@Override
	public void undo() throws CannotUndoException {
		super.undo();
		canvas.applyPanToBounds(node, original);
	}

	@Override
	public void redo() throws CannotRedoException {
		super.redo();
		canvas.applyPanToBounds(node, revision);
	}

}

