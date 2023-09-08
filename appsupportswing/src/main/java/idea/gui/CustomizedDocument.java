package idea.gui;

import java.awt.Toolkit;

import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.PlainDocument;



@SuppressWarnings("serial")
public class CustomizedDocument extends PlainDocument {

    int maxChars = 0;

    boolean upperCase = false;

    boolean numeric = false;
    boolean decimal = false;

    public void setMaxChars(int maxChars) {
        this.maxChars = maxChars;
    }

    public int getMaxChars() {
        return maxChars;
    }

    public void setUpperCase(boolean upperCase) {
        this.upperCase = upperCase;
    }

    public boolean isUpperCase() {
        return upperCase;
    }

    public void setNumeric(boolean numeric) {
        setNumeric( numeric, true);
    }

    public void setNumeric(boolean numeric, boolean decimal) {
        this.numeric = numeric;
        this.decimal = decimal;
    }

    public boolean isNumeric() {
        return numeric;
    }

    public void insertString(int offs, String str, AttributeSet a) throws BadLocationException {

        if (str == null)
            return;

        if ( getLength() + str.length() > maxChars) {
            Toolkit.getDefaultToolkit().beep();
            return;
        }

        char[] result = str.toCharArray();

        if (isUpperCase()) {
            result = str.toCharArray();
            for (int i = 0; i < result.length; i++) {
                result[i] = Character.toUpperCase(result[i]);
            }
        }

        if (isNumeric() && result.length > 0 ) {
            int j = 0;

            int i=0;
            
            if( result[i] == '$') {
            	// allow leading $, it is allowed to be part of the pattern
                result[j++] = result[i++];
            }
            
            for ( ; i < result.length; i++) {
                if (Character.isDigit(result[i]) 
                        || (decimal && result[i] == '.') 
                        || (decimal && result[i] == ',') 
						|| result[i] == '-') {
                    result[j++] = result[i];
                } else {
                	System.err.println( "non-numeric char: " + result[i] + " in " + str );
                    Toolkit.getDefaultToolkit().beep();
                    return;
                }
            }
        }

        super.insertString(offs, new String(result), a);
    }

}
