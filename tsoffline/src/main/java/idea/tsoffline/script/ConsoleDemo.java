package idea.tsoffline.script;

import java.lang.reflect.InvocationTargetException;

import javax.swing.JFrame;

import org.rosuda.REngine.REXP;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngine;
import org.rosuda.REngine.REngineException;

import idea.r.RUtil;

//import pulpcore.image.Colors;
//import pulpcore.scene.Scene2D;
//import pulpcore.sprite.FilledSprite;
//import pulpcore.sprite.ImageSprite;
//import astroboid.toolkit.ConsoleFrame;

public class ConsoleDemo { // extends Scene2D {
//	ImageSprite man, spirit;
//
//	@Override
//	public void load() {
//		add(new FilledSprite(Colors.WHITE));
//
//		man = new ImageSprite("Man.png", 10, 10);
//		add(man);
//		spirit = new ImageSprite("Spirit.png", 100, 10);
//		add(spirit);
//		
//		ConsoleFrame consoleFrame = new ConsoleFrame();
//
//		ScriptEngineManager scriptEngineManager = new ScriptEngineManager();
//		ScriptEngine scriptEngine = scriptEngineManager.getEngineByName("JavaScript");
//		scriptEngine.put("demo", this);
//
//		consoleFrame.setScriptEngine(scriptEngine);
//		consoleFrame.setLocation(900, 200);
//		consoleFrame.setVisible(true);
//	}
//
//	public ImageSprite getMan() {
//		return man;
//	}
//
//	public void setMan(ImageSprite man) {
//		this.man = man;
//	}
//
//	public ImageSprite getSpirit() {
//		return spirit;
//	}
//
//	public void setSpirit(ImageSprite spirit) {
//		this.spirit = spirit;
//	}
	
	private static void explain(REXP ok) throws REXPMismatchException {
		REXP cl = ok.getAttribute("class");
		if (cl != null && cl.asString() != null && cl.asString().equals("try-error")) {
			System.err.println("R error: " + ok.asString());
			throw new RuntimeException(ok.asString());
		}
	}

	public static void main( String [] args ) throws ClassNotFoundException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, REngineException, REXPMismatchException {
		JFrame frame = new JFrame("Script Console");

		// ConsolePanel console = new ConsolePanel();
		ConsolePanel console = new ConsolePanel();
		RUtil.init(console);
		REngine re = RUtil.getREngine();
		re.parseAndEval(".setenv <- if (exists(\"Sys.setenv\")) Sys.setenv else Sys.putenv");
		re.parseAndEval(".setenv(\"JAVAGD_CLASS_NAME\"=\"idea/r/RCue\")");

		REXP ok = re.parseAndEval("library(JavaGD)");
		explain(ok);

		// ScriptPanel console = new ScriptPanel();
 		frame.getContentPane().add(console);
		frame.setSize(900, 400);
		// GuiUtil.doNonModalDialog("Script", null, panel, null);

		frame.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );

		frame.setVisible(true);
		
	}
}
