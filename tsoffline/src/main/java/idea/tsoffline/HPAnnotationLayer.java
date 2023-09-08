package idea.tsoffline;

import java.util.Collection;

import org.piccolo2d.PNode;

import idea.schema.rp.RpMetric;

@SuppressWarnings("serial")
public class HPAnnotationLayer extends HPSplitableLayer {

	public HPAnnotationLayer( RpMetric m) {
		super( m);
		addAttribute("sid", "A");
	}
	
	
	/*
	 * Annotation layer has direct children...so don't treat as a splitable layer in that regard
	 */
	@SuppressWarnings("unchecked")
	public Collection<PNode> getNodes() {
		return getChildrenReference();
	}

}
