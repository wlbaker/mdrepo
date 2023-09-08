/*
 * Created by JFormDesigner on Wed Jun 10 11:35:17 CDT 2015
 */

package idea.tsoffline.vizwiz;

import java.awt.BorderLayout;

import javax.swing.JPanel;

import org.rosuda.REngine.REXP;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngine;
import org.rosuda.REngine.REngineException;

import idea.schema.rp.RpAnalysis;
import idea.schema.rp.RpStudy;
import idea.GuiUtil;
import idea.gui.WizardMasterInterface;
import idea.gui.WizardPanelInterface;
import idea.r.RCue;
import idea.r.RUtil;

/**
 * @author User #1
 */
@SuppressWarnings("serial")
public class RPlotWizardPanel extends JPanel implements WizardPanelInterface {
	private RpAnalysis anal;
	private WizardMasterInterface wiz;

	public RPlotWizardPanel(WizardMasterInterface wiz, RpStudy study, RpAnalysis anal) {
		initComponents();
		
		this.anal = anal;
		this.wiz = wiz;

		try {
			initRPlot(this, "plot0");
		} catch (Exception e) {
			throw new RuntimeException("generating plot interface", e);
		}
		
		
	}

	private RCue initRPlot(JPanel parent, String plotName) throws REngineException, REXPMismatchException {

		REngine engine = RUtil.getREngine();
		if (engine == null) {
			GuiUtil.showMessage("R-Engine not ready.");
			return null;
		}

		RCue.parent = parent;
		engine.parseAndEval(".setenv <- if (exists(\"Sys.setenv\")) Sys.setenv else Sys.putenv");
		// engine.eval(".setenv(\"JAVAGD_CLASS_NAME\"=\"idea/r/RCue\")");
		engine.parseAndEval(".setenv(\"JAVAGD_CLASS_NAME\"=\"idea/r/RCue\")");
		REXP v = engine.parseAndEval("library(JavaGD)");
		System.out.println("v=" + v);
		v = engine.parseAndEval("JavaGD(name=\"" + plotName + "\")");
		System.out.println("v=" + v);

		RCue cue = new RCue();
		//		cue.gdActivate();
		//		cue.gdOpen( 200, 200);

		v = engine.parseAndEval("plot(rnorm(100))");
		System.out.println("v=" + v);
		return cue;
	}

	private void initComponents() {
		// JFormDesigner - Component initialization - DO NOT MODIFY  //GEN-BEGIN:initComponents

		//======== this ========
		setLayout(new BorderLayout());
		// JFormDesigner - End of component initialization  //GEN-END:initComponents
	}

	@Override
	public void refresh() {
		

	}

	@Override
	public void previous() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public boolean next() {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean finish() {
		// TODO Auto-generated method stub
		return false;
	}

	// JFormDesigner - Variables declaration - DO NOT MODIFY  //GEN-BEGIN:variables
	// JFormDesigner - End of variables declaration  //GEN-END:variables
}
