/*
 * Created by JFormDesigner on Fri Feb 03 12:13:14 CST 2017
 */

package idea.tsoffline.canvas;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.util.Set;

import javax.swing.DefaultComboBoxModel;
import javax.swing.JComboBox;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.ListCellRenderer;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.tsoffline.HPSplitableLayer;
import idea.tsoffline.TimeseriesType;
import idea.tsoffline.model.FormulaOp;
import idea.tsoffline.model.FormulaSignal;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
public class SimpleFormulaEditorPanel extends JPanel {
	private FormulaSignal formula;
	private ListCellRenderer<? super HPSplitableLayer> r;
	private ListCellRenderer<? super HPSplitableLayer> s;
	public SimpleFormulaEditorPanel(Set<HPSplitableLayer> sigs) {
		initComponents();

		FormulaOp [] arr = new FormulaOp [] { FormulaOp.Add, FormulaOp.Subtract, FormulaOp.Divide, FormulaOp.Mean, FormulaOp.Derivative };
		operation.setModel( new DefaultComboBoxModel<FormulaOp>( arr ) );
		
		s = sig1.getRenderer();
		r = new ListCellRenderer<HPSplitableLayer>() {

			@Override
			public Component getListCellRendererComponent(JList<? extends HPSplitableLayer> list, HPSplitableLayer value,
					int index, boolean isSelected, boolean cellHasFocus) {
				JLabel label = (JLabel) s.getListCellRendererComponent(list, value, index, isSelected, cellHasFocus);
				label.setText(value.getAlias());
				return label;
			}
			
		};
		refresh( sigs );
	}

	public void setSignals(Set<HPSplitableLayer> sigs) {
		refresh(sigs);
	}
	
	private void refresh(Set<HPSplitableLayer> sigs) {
		if( sigs == null ) {
			return;
		}

		// count the number of non-annotation signals
		int count = 0;
		for( HPSplitableLayer sig : sigs ) {
			if( sig.getTyp() == TimeseriesType.TT_ANNOTATION) {
				// skip
			} else {
				count++;
			}
		}
		
		// make an array of non-annotation signals
		HPSplitableLayer[] arr = new HPSplitableLayer[count];
		int idx = 0;
		for( HPSplitableLayer sig : sigs ) {
			if( sig.getTyp() == TimeseriesType.TT_ANNOTATION) {
				// skip
			} else {
				arr[idx++] = sig;
			}
		}

		// create the combo box models
		sig1.setModel( new DefaultComboBoxModel<HPSplitableLayer>(arr));
		sig2.setModel( new DefaultComboBoxModel<HPSplitableLayer>(arr));
		
		sig1.setRenderer( r );
		sig2.setRenderer( r );
	}

	public FormulaSignal getFormulaSignal() {
		FormulaSignal f = formula;
		f.op = (FormulaOp)operation.getSelectedItem();
		
		f.sig1 = ((HPSplitableLayer)sig1.getSelectedItem()).getLocation();
		if( f.op == FormulaOp.Mean || f.op == FormulaOp.Derivative) {
			f.sig2 = null;
		} else {
			f.sig2 = ((HPSplitableLayer)sig2.getSelectedItem()).getLocation();
		}
		return f;
	}

	public void setFormula(FormulaSignal formula ) {
		this.formula = formula;
		setSelection( sig1, formula.sig1 );
		setSelection( sig2, formula.sig2 );
		operation.setSelectedItem( formula.op);

	}

	private void setSelection(JComboBox<HPSplitableLayer> sig1, String value) {
		DefaultComboBoxModel<HPSplitableLayer> m = (DefaultComboBoxModel<HPSplitableLayer>)sig1.getModel();
		for( int i = 0; i < m.getSize(); i++ ) {
			HPSplitableLayer it = m.getElementAt(i  );
			String loc = it.getLocation();
			if( loc.equals( value) ) { 
				sig1.setSelectedIndex(i);
				break;
			}
		}
		
	}

	private void operationActionPerformed(ActionEvent e) {
		FormulaOp op = (FormulaOp) operation.getSelectedItem();
		switch( op ) {
		case Derivative:
		case Mean:
			sig1.setEnabled(true);
			sig1.setVisible(true);
			sig2.setEnabled(false);
			sig2.setVisible(false);
			break;
		default:
			sig1.setEnabled(true);
			sig1.setVisible(true);
			sig2.setEnabled(true);
			sig2.setVisible(true);
		}
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents
		operation = new JComboBox<>();
		sig1 = new JComboBox<>();
		sig2 = new JComboBox<>();

		//======== this ========
		setLayout(new FormLayout(
			"30dlu, 2*(default:grow)",
			"default"));

		//---- operation ----
		operation.addActionListener(e -> operationActionPerformed(e));
		add(operation, CC.xy(1, 1));
		add(sig1, CC.xy(2, 1));
		add(sig2, CC.xy(3, 1));
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	private JComboBox<FormulaOp> operation;
	private JComboBox<HPSplitableLayer> sig1;
	private JComboBox<HPSplitableLayer> sig2;
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
