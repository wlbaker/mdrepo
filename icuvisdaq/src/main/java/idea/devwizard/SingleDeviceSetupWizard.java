/*
 * Created by JFormDesigner on Mon Oct 05 16:18:54 CDT 2009
 */

package idea.devwizard;


import java.awt.CardLayout;
import java.awt.Component;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.LinkedList;

import javax.swing.JButton;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSeparator;

import com.jgoodies.forms.layout.CellConstraints;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpDevice;
import idea.schema.rp.RpHardware;
import idea.schema.rp.RpStudy;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;

// import static WizDeviceID.*;

/**
 * @author User #2
 */
@SuppressWarnings("serial")
public class SingleDeviceSetupWizard extends JPanel implements SetupWizardInterface {

	private CardLayout card;

	private RpStudy study;
	private RpHardware hw_config;
	private RpDevice dev;

	LinkedList<Component> stack = new LinkedList<Component>();

	private boolean finished = false;

	public SingleDeviceSetupWizard( RpStudy study, RpHardware hw_config ) {
		initComponents();
		card = (CardLayout) filler.getLayout();
		this.study = study;
		this.hw_config = hw_config;

		pushPage( new WizDevicePanel(this, hw_config));		
	}

	public boolean isExecute() {
		return finished;
	}
	
	private void nextActionPerformed(ActionEvent e) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				ri.next();
				
				if( ri instanceof WizDevicePanel ) {
					// next page is ok
				} else {
					// we're done
					finished = true;
					GuiUtil.closeDialog( this );
				}
				break;
			}
		}
	}
	
	private void finishActionPerformed(ActionEvent e) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				boolean ok = ri.finish();
				if (ok) {
					setFinished(true);
					GuiUtil.closeDialog(this);
				}
				break;
			}
		}
	}

	private void previousActionPerformed(ActionEvent e) {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				ri.previous();
				break;
			}
		}

		popPage();
		refresh();
	}

	private void cancelActionPerformed(ActionEvent e) {
		GuiUtil.closeDialog( this );
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		// Generated using JFormDesigner non-commercial license
		panel2 = new JPanel();
		filler = new JPanel();
		separator1 = new JSeparator();
		panel1 = new JPanel();
		previous = new JButton();
		next = new JButton();
		finish = new JButton();
		cancel = new JButton();
		CellConstraints cc = new CellConstraints();

		//======== this ========
		setLayout(new FormLayout(
			"[250dlu,default]:grow",
			"fill:default:grow, 2*($lgap, default)"));

		//======== panel2 ========
		{
			panel2.setLayout(new FormLayout(
				"default:grow",
				"fill:default:grow"));

			//======== filler ========
			{
				filler.setLayout(new CardLayout());
			}
			panel2.add(filler, cc.xy(1, 1));
		}
		add(panel2, cc.xy(1, 1));
		add(separator1, cc.xy(1, 3));

		//======== panel1 ========
		{
			panel1.setLayout(new FormLayout(
				"default:grow, 6*($lcgap, default), $ugap, default",
				"default"));

			//---- previous ----
			previous.setText("< Previous");
			previous.setEnabled(false);
			previous.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					previousActionPerformed(e);
				}
			});
			panel1.add(previous, cc.xy(9, 1));

			//---- next ----
			next.setText("Next >");
			next.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					nextActionPerformed(e);
				}
			});
			panel1.add(next, cc.xy(11, 1));

			//---- finish ----
			finish.setText("Finish");
			finish.setEnabled(false);
			finish.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					finishActionPerformed(e);
				}
			});
			panel1.add(finish, cc.xy(13, 1));

			//---- cancel ----
			cancel.setText("Cancel");
			cancel.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					cancelActionPerformed(e);
				}
			});
			panel1.add(cancel, cc.xy(15, 1));
		}
		add(panel1, cc.xy(1, 5));
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	// Generated using JFormDesigner non-commercial license
	private JPanel panel2;
	private JPanel filler;
	private JSeparator separator1;
	private JPanel panel1;
	private JButton previous;
	private JButton next;
	private JButton finish;
	private JButton cancel;
	// JFormDesigner - End of variables declaration //GEN-END:variables

	public void pushPage(JPanel panel ) {
		try {
			String tag = panel.getName();
			
			filler.add(panel, tag);
			card.show(filler, tag);
			stack.addFirst(panel);
			
			previous.setEnabled( true );
		} catch (Exception e) {
			e.printStackTrace();
			JOptionPane.showMessageDialog(null, "Internal Error: " + e.getMessage());
		}

	}

	public void enableNext(boolean b) {
		next.setEnabled(b);
	}

	public void enablePrevious(boolean b) {
		previous.setEnabled(b);
	}

	public void enableFinish(boolean b) {
		finish.setEnabled(b);
	}

	private void popPage() {
		Component page = stack.removeFirst();
		filler.remove(page);
		
		// ? card.removeLayoutComponent( page );
		
		page = stack.getFirst();
		String tag = page.getName();
		
		card.show( filler, page.getName() );
		
		previous.setEnabled( stack.size() > 1 );
	}
	
	public void popPageUntil(String key) {

		// nothing to do here for single device setup
	}

	public void refresh() {
		for (Component c : filler.getComponents()) {
			if (c.isVisible() && c instanceof WizardPanelInterface) {
				// there should be only one visible component
				WizardPanelInterface ri = (WizardPanelInterface) c;
				ri.refresh();
				break;
			}
		}
	}

	public RpStudy getStudy() {
		return study;
	}

	public void setStudy(RpStudy study) {
		this.study = study;
	}
	
	public RpHardware getHardware() {
		return hw_config;
	}

	public void setHardware( RpHardware hw_config ) {
		this.hw_config = hw_config;
	}

	public void pushSignalSelectionPage(Class<?> clazz) {
		try {
			_pushSignalSelectionPage( clazz );
		} catch (Exception e ) {
			GuiUtil.showError("Signal Selection Panel: ", e);
		}
	}
	
	public void _pushSignalSelectionPage(Class<?> clazz) throws SecurityException, NoSuchMethodException, IllegalArgumentException, InstantiationException, IllegalAccessException, InvocationTargetException {
		
		Constructor<?> mid = clazz.getConstructor( WizardMasterInterface.class, RpDevice.class );
		Object[] args = new Object[] { this, dev };
		// args[0] = null;
		JPanel panel = (JPanel) mid.newInstance( args);
		panel.setName("Signal Selection");
		
		pushPage( panel );
	}

	public void setDevice(RpDevice dev) {
		this.dev = dev;
	}

	public RpDevice getDevice() {
		return dev;
	}


	@Override
	public void setFinished(boolean b) {
		finished = b;
	}

}
