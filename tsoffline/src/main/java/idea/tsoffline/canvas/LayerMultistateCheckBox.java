package idea.tsoffline.canvas;

import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/*
 * Tri-state checkbox example
 * @s1w_
*/
import javax.swing.Icon;
import javax.swing.JCheckBox;
import javax.swing.UIManager;

import lombok.Getter;
import idea.tsoffline.HPSplitableLayer;


@SuppressWarnings("serial")
public class LayerMultistateCheckBox extends JCheckBox implements Icon, ActionListener {

			
    final static boolean MIDasSELECTED = true;  //consider mid-state as selected ?
    
    @Getter
    HPSplitableLayer layer;

    public LayerMultistateCheckBox(HPSplitableLayer layer) {
        super(layer.getName());
        this.layer = layer;
        
        int state = 0;
        String displayState = (String)layer.getAttribute("@displayState");
        if( displayState != null ) {
        	state = Integer.parseInt(displayState);
        }
        putClientProperty("SelectionState", state);
        
        setIcon(this);
        addActionListener(this);
        
        // this.setForeground( Color.GREEN );
        
    }

    public LayerMultistateCheckBox(String text, int sel) {
        /* tri-state checkbox has 3 selection states:
         * 0 unselected
         * 1 mid-state selection
         * 2 fully selected
        */
        super(text, sel > 1 ? true : false);

        switch (sel) {
            case 2: setSelected(true);
        	case 3:
            case 1:
            case 0:
                putClientProperty("SelectionState", sel);
                break;
           default:
                throw new IllegalArgumentException();
        }
        addActionListener(this);
        setIcon(this);
    }

    @Override
    public boolean isSelected() {
        if (MIDasSELECTED && (getSelectionState() > 0)) return true;
        else return super.isSelected();
    }

    public int getSelectionState() {
        return (getClientProperty("SelectionState") != null ? (int)getClientProperty("SelectionState") :
                                         super.isSelected() ? 2 :
                                         0);
    }

    public void setSelectionState(int sel) {
        switch (sel) {
            case 2: setSelected(true);
                    break;
        	case 3: 
            case 1: 
            case 0: setSelected(false);
                    break;
           default: throw new IllegalArgumentException();
        }
        putClientProperty("SelectionState", sel);
        
        layer.addAttribute("@displayState", "" + sel);

    }


    final static Icon icon = UIManager.getIcon("CheckBox.icon");

    @Override
    public void paintIcon(Component c, Graphics g, int x, int y) {
        int w = getIconWidth();
        int h = getIconHeight();
        
    	g.setColor( Color.GRAY );
        g.fillRect(x+1, y+1, w-2, h-2);
        // icon.paintIcon(c, g, x, y);
        int state = getSelectionState();
        if (state == 0) return;

        Color color = layer.getDefaultColor();
        g.setColor(c.isEnabled() ? color : new Color(51, 51, 51)  );
        if( state == 1 ) {
        	g.fillRect(x+4, y+4, w-8, h-8);
            if (!c.isEnabled()) return;
            g.setColor( new Color(81, 81, 81));
            g.drawRect(x+4, y+4, w-9, h-9);
        } else if( state == 2 ) {
        	g.fillRect(x+2, y+2, w-4, h-4);
            if (!c.isEnabled()) return;
            g.setColor( new Color(81, 81, 81));
            g.drawRect(x+2, y+2, w-5, h-5);
        } else if( state == 3 ) {
        	g.fillOval(x+2, y+2, w-5, h-5);
            if (!c.isEnabled()) return;
            g.setColor( new Color(81, 81, 81));  // dark border
            g.drawOval(x+2, y+2, w-5, h-5);
        }

    }

    @Override
    public int getIconWidth() {
        return icon.getIconWidth();
    }

    @Override
    public int getIconHeight() {
        return icon.getIconHeight();
    }

    public void actionPerformed(ActionEvent e) {
        int n_states = 4;

        LayerMultistateCheckBox tcb = (LayerMultistateCheckBox)e.getSource();
        if (tcb.getSelectionState() == 0)
            tcb.setSelected(false);
        
        int state = (tcb.getSelectionState() + 1) % n_states;

        tcb.putClientProperty("SelectionState", state );
        layer.addAttribute("@displayState", "" + state);

    }
}