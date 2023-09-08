package idea.jasper;

import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.HashMap;

import javax.swing.JComponent;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.KeyStroke;

import net.sf.jasperreports.engine.JRParameter;
import idea.GuiUtil;

public class ParameterManager {
	
	public static int prompt( JFrame parent, String title, String prompterClass, HashMap hm, JRParameter[] jrparamReport ) {
		
		int err = 0;
		
		JComponent prompterPanel = null;
		
		Class paneClass = null;
		
		if( prompterClass == null ) {
			prompterClass = "com.pmode.prompter.BasicSelectionPrompter";
		}
		
		if( "com.priefert.prompter.BasicSelection".equals(prompterClass) ) {
			prompterClass = "com.pmode.prompter.BasicSelectionPrompter";
		}
		if( prompterClass.equals("none")) {
			return 0;           // nothing to do here
		}
		
        try {
			paneClass = Class.forName(prompterClass);
    		prompterPanel = (JComponent) DDD.buildPage(null, paneClass);
        } catch (Exception e) {
            e.printStackTrace(System.out);
            System.out.println(" -- exception: " + prompterClass + " - " + e.getMessage());
        }
        
        PrompterInterface prompter;
        if( prompterPanel instanceof PrompterInterface ) {
        	prompter = (PrompterInterface)prompterPanel;
        } else {
        	prompter = DDD.buildPrompterInterface( paneClass, prompterPanel );
        }
        
        String value = null;
        
        prompter.setParameters(jrparamReport, hm);
        
        if( prompterPanel != null ) {
	        String[] options = {  };
	        JOptionPane p = new JOptionPane(prompterPanel, JOptionPane.PLAIN_MESSAGE, JOptionPane.NO_OPTION, null,
	                options, null);
	        JDialog d = p.createDialog(parent, title);
	        GuiUtil.initModalDialog( d, p );         // makes the escape key work
	        d.setName("$Id: ParameterManager.java,v 1.6 2008/02/19 17:23:24 bbaker Exp $");
	        d.setResizable(true); 
	        d.pack();
	        // d.setDefaultCloseOperation( WindowConstants.DO_NOTHING_ON_CLOSE );
	        p.getInputMap().remove( KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0) );
	        p.addKeyListener( new KeyListener() {

				public void keyPressed(KeyEvent e) {
					// TODO Auto-generated method stub
					
				}

				public void keyReleased(KeyEvent e) {
					// TODO Auto-generated method stub
					
				}

				public void keyTyped(KeyEvent e) {
					if (e.getKeyCode() == KeyEvent.VK_ENTER ) {
						System.err.println( "enterkey consumed! ");
						e.consume();
					}
					
				} } );
	        d.setVisible(true);
	        
	        value = (String) p.getValue();
        }

       	prompter.getParameters( hm );
        
        return err;
	}

}
