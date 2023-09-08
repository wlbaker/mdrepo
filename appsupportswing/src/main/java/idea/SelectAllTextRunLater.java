package idea;

import javax.swing.JTextField;

public class SelectAllTextRunLater implements Runnable {

	private JTextField f;

	public SelectAllTextRunLater(JTextField f) {  // includes formattedtextfield
		this.f = f;
	}

	public void run() {
		f.selectAll();
	}

}
