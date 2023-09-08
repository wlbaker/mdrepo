package idea.tsoffline.event_editor;

import java.text.ParseException;
import java.text.SimpleDateFormat;

import javax.swing.DefaultCellEditor;
import javax.swing.JFormattedTextField;

@SuppressWarnings("serial")
public class DateEditor3 extends DefaultCellEditor {

	public DateEditor3(String fmt ) {
		this(new JFormattedTextField(new SimpleDateFormat( fmt )));
	}

	public DateEditor3(final JFormattedTextField ftf) {
		super(ftf);
		setClickCountToStart(1);
		delegate = new EditorDelegate() {
			@Override
			public void setValue(Object value) {
				ftf.setValue(value);
			}

			@Override
			public Object getCellEditorValue() {
				// could call ftf.commitEdit() here instead of overriding stopCellEditing()   
				return ftf.getValue();
			}

			@Override
			public boolean stopCellEditing() {
				try {
					ftf.commitEdit();
				} catch (ParseException e) {
					return false; // This will prevent the cell from losing focus.   
					// (User will have to enter a valid date or hit escape to revert.)   
					// Alternative is to not return anything here--cell will revert.   
				}
				return super.stopCellEditing();
			}
		}; // end anonymous subclass of DefaultCellEditor.EditorDelegate   
	}
}
