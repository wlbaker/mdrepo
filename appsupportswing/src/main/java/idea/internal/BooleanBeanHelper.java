package idea.internal;

import java.beans.PropertyChangeListener;

import com.jgoodies.binding.beans.ExtendedPropertyChangeSupport;

public class BooleanBeanHelper {

	private ExtendedPropertyChangeSupport changeSupport = new ExtendedPropertyChangeSupport(this);

	private boolean value;

	public void addPropertyChangeListener(PropertyChangeListener x) {
		changeSupport.addPropertyChangeListener(x);
	}

	public void removePropertyChangeListener(PropertyChangeListener x) {
		changeSupport.removePropertyChangeListener(x);
	}

	public void setValue(boolean value) {
		boolean oldValue = this.value;
		this.value = value;
		changeSupport.firePropertyChange("value", oldValue, value);
	}

	public boolean getValue() {
		return value;
	}

}
