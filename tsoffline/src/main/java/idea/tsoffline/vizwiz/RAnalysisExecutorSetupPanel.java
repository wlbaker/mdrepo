/*
 * Created by JFormDesigner on Wed Jun 10 10:26:07 CDT 2015
 */

package idea.tsoffline.vizwiz;

import java.awt.BorderLayout;
import java.awt.Color;
import java.io.File;
import java.io.InputStream;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

import javax.swing.JLabel;
import javax.swing.JPanel;

import org.fife.ui.rsyntaxtextarea.RSyntaxTextArea;
import org.fife.ui.rsyntaxtextarea.SyntaxConstants;
import org.fife.ui.rtextarea.RTextScrollPane;
import org.rosuda.REngine.REXP;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngine;

import com.jgoodies.forms.factories.CC;
import com.jgoodies.forms.layout.FormLayout;

import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpStudy;
import idea.schema.rp.StringStringMap;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.r.RUtil;
import idea.tsoffline.AppUtil;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.model.OfflineSignal;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
@Slf4j
public class RAnalysisExecutorSetupPanel extends JPanel implements WizardPanelInterface {
	private WizardMasterInterface wiz;
	private RpAnalysis anal;
	private OfflineSignal[] sigs;
	private TsPSwingCanvas canvas;
	RSyntaxTextArea textArea;

	public RAnalysisExecutorSetupPanel(WizardMasterInterface wiz, RpStudy study, RpAnalysis anal) {
		initComponents();

		this.anal = anal;
		this.wiz = wiz;

		wiz.enableNext(true);

		StringStringMap map = anal.getParam();

		script.setText(map.get("script"));

		textArea = new RSyntaxTextArea(20, 60);
		textArea.setSyntaxEditingStyle(SyntaxConstants.SYNTAX_STYLE_PYTHON);
		// textArea.setBackground(Color.DARK_GRAY);
		textArea.setHighlightCurrentLine(false);
		textArea.setMarginLineEnabled(false);
		textArea.setCodeFoldingEnabled(false);
		textArea.setCaretColor(Color.DARK_GRAY);
		RTextScrollPane sp = new RTextScrollPane(textArea);
		this.add(sp, BorderLayout.CENTER);

		String s;
		String scriptPath = map.get("script");
		try {
			File f = new File(map.get("script"));
			if (f.exists()) {
				byte[] encoded = Files.readAllBytes(Paths.get(scriptPath));
				s = new String(encoded, StandardCharsets.UTF_8);
			} else {
				byte[] buf = new byte[256];
				InputStream in = getClass().getResourceAsStream("/" + scriptPath);
				StringBuffer out = new StringBuffer();
				do {
					int n = in.read(buf);
					if (n <= 0)
						break;

					out.append(new String(buf, 0, n));
				} while (true);

				s = out.toString();
			}
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			s = e.getMessage();
			textArea.setEditable(false);
		}

		textArea.setText(s);

		refresh();
	}

	private org.rosuda.REngine.REXP runAnalysis() {
		REngine re = RUtil.getREngine();

		if (re == null) {
			GuiUtil.showMessage("R Engine not available.");
			return null;
		}

		String script = textArea.getText();
		return AppUtil.runScript(env_name, script, true);

	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY
		// //GEN-BEGIN:initComponents
		panel2 = new JPanel();
		label4 = new JLabel();
		script = new JLabel();
		panel3 = new JPanel();

		// ======== this ========
		setLayout(new BorderLayout());

		// ======== panel2 ========
		{
			panel2.setLayout(new FormLayout("right:[50dlu,default], $lcgap, default:grow", "default, $lgap, default"));

			// ---- label4 ----
			label4.setText("Script:");
			panel2.add(label4, CC.xy(1, 1));

			// ---- script ----
			script.setText("text");
			panel2.add(script, CC.xy(3, 1));
		}
		add(panel2, BorderLayout.NORTH);

		// ======== panel3 ========
		{
			panel3.setLayout(new FormLayout("2*(default, $lcgap), default", ""));
		}
		add(panel3, BorderLayout.SOUTH);
		// //GEN-END:initComponents
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY
	// //GEN-BEGIN:variables
	private JPanel panel2;
	private JLabel label4;
	private JLabel script;
	private JPanel panel3;
	private String env_name;

	// JFormDesigner - End of variables declaration //GEN-END:variables
	@Override
	public void refresh() {

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean next() {

		AppUtil.clearPendingPlots();

		REXP ok = runAnalysis();
		REXP cl = ok.getAttribute("class");
		try {
			if (cl != null && cl.asString() != null && cl.asString().equals("try-error")) {
				ok = null;
			}
		} catch (REXPMismatchException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return ok != null;
	}

	@Override
	public boolean finish() {
		return true;
	}

	public void setEnvironmentName(String rEnvName) {
		env_name = rEnvName;
	}
}
