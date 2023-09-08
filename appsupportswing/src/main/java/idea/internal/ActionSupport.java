package idea.internal;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JComponent;
import javax.swing.event.EventListenerList;

public class ActionSupport {
	/* *********************************************************************************
	 * Boilerplate code for adding actions and calling events 
	 */
	
    /**
     * Adds an <code>ActionListener</code> to the form.
     * @param name 
     * @param listenerList 
     * @param l the <code>ActionListener</code> to be added
     */
    public static void addActionListener(EventListenerList listenerList, Class<ActionListener> name, ActionListener l) {
        listenerList.add(ActionListener.class, l);
    }
    
    /**
     * Removes an <code>ActionListener</code> from the form.
     *
     * @param l the listener to be removed
     */
    public static void removeActionListener(EventListenerList listenerList, ActionListener l) {
	    listenerList.remove(ActionListener.class, l);
    }

    /**
     * Notifies all listeners that have registered interest for
     * notification on this event type.  The event instance 
     * is lazily created using the <code>event</code> 
     * parameter.
     *
     * @param event  the <code>ActionEvent</code> object
     * @see EventListenerList
     */
    public static void fireActionPerformed(EventListenerList listenerList, String actionCommand, Object source) {
        // Guaranteed to return a non-null array
        Object[] listeners = listenerList.getListenerList();
        ActionEvent e = null;
        
        // if (e == null) {
            e = new ActionEvent(source,
                                ActionEvent.ACTION_PERFORMED,
                                actionCommand
                                // event.getWhen(),
                                // event.getModifiers()
                                );
         // }
            
        // Process the listeners last to first, notifying
        // those that are interested in this event
        for (int i = listeners.length-2; i>=0; i-=2) {
            if (listeners[i]==ActionListener.class) {
                // Lazily create the event:
                ((ActionListener)listeners[i+1]).actionPerformed(e);
            }          
        }
    }

	public static void fireActionPerformed(ActionListener[] al, String actionCommand, JComponent source) {
        ActionEvent e = new ActionEvent(source,
                ActionEvent.ACTION_PERFORMED,
                actionCommand
                // event.getWhen(),
                // event.getModifiers()
                );
		
        for (ActionListener l : al ) {
            l.actionPerformed(e);
        }
	}


}
