package idea.tsoffline.canvas.edit;

import java.awt.geom.AffineTransform;

import javax.swing.undo.AbstractUndoableEdit;
import javax.swing.undo.CannotRedoException;
import javax.swing.undo.CannotUndoException;

import org.piccolo2d.PNode;

import lombok.Getter;
import idea.tsoffline.canvas.TsBaseCanvas;

public class TransformEdit extends AbstractUndoableEdit {
	TsBaseCanvas canvas;

	@Getter
	private PNode node;
	@Getter
	private AffineTransform original;
	@Getter
	private AffineTransform revision;

	public TransformEdit(TsBaseCanvas canvas, PNode node, AffineTransform ori, AffineTransform desired) {
		this.canvas = canvas;
		this.node = node;
		this.original = ori;
		this.revision = desired;
	}

	@Override
	public void undo() throws CannotUndoException {
		super.undo();
		canvas.applyTransform(node, original);
	}

	@Override
	public void redo() throws CannotRedoException {
		super.redo();
		canvas.applyTransform(node, revision);
	}

	@Override
	public String getPresentationName() {
		return "Reposition";
	}

}

