package idea.tsoffline.canvas.edit;

import java.util.List;

import javax.swing.undo.AbstractUndoableEdit;
import javax.swing.undo.CannotRedoException;
import javax.swing.undo.CannotUndoException;

import org.piccolo2d.PLayer;
import org.piccolo2d.PNode;

import lombok.Getter;
import idea.tsoffline.canvas.TsBaseCanvas;
import idea.tsoffline.canvas.TsPSwingCanvas;

public class DeleteNodesEdit extends AbstractUndoableEdit {
	TsBaseCanvas canvas;

	@Getter
	private PLayer layer;
	@Getter
	List<PNode> nodes;

	public DeleteNodesEdit(TsPSwingCanvas canvas, PLayer layer, List<PNode> nodes) {
		
		this.canvas = canvas;
		this.layer = layer;
		this.nodes = nodes;
	}

	@Override
	public void undo() throws CannotUndoException {
		super.undo();
		layer.addChildren( nodes );
		canvas.redrawAxisLayer(0);
	}

	@Override
	public void redo() throws CannotRedoException {
		super.redo();
		layer.removeChildren( nodes );
		canvas.redrawAxisLayer(0);
	}

}

