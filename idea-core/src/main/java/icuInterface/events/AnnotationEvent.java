package icuInterface.events;

import idea.model.Annotation;

import java.util.EventObject;

public class AnnotationEvent extends EventObject {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Annotation annoItem;

	public AnnotationEvent(Object source, Annotation annoItem) {
		super(source);
		this.setAnnotationItem(annoItem);

	}
	
	public void setAnnotationItem(Annotation annoItem) {
		this.annoItem = annoItem;
	}

	public Annotation getAnnotationItem() {
		return annoItem;		
	}

}
