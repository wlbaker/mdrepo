/* - BErrorListener -
 * Display the error description in a messagebox
 *
 * Copyright 2011 Phidgets Inc.
 * This work is licensed under the Creative Commons Attribution 2.5 Canada License.
 * To view a copy of this license, visit http://creativecommons.org/licenses/by/2.5/ca/
 */
package icuInterface.adapters.phidget;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import com.phidgets.event.ErrorEvent;
import com.phidgets.event.ErrorListener;

public class BErrorListener implements ErrorListener {

    private JFrame appFrame;

    public BErrorListener(JFrame appFrame) {
        this.appFrame = appFrame;
    }

    @Override
	public void error(ErrorEvent errorEvent) {
        JOptionPane.showMessageDialog(appFrame, errorEvent.toString(), "Bridge Error Event", JOptionPane.ERROR_MESSAGE);
    }
}
