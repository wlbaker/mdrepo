package idea.tsoffline;

import java.awt.Color;
import java.awt.Dimension;
import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.Reader;
import java.io.StringReader;
import java.lang.reflect.InvocationTargetException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.swing.JPanel;
import javax.swing.SwingUtilities;

import org.rosuda.REngine.REXP;
import org.rosuda.REngine.REXPGenericVector;
import org.rosuda.REngine.REXPJavaReference;
import org.rosuda.REngine.REXPList;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngine;
import org.rosuda.REngine.REngineException;
import org.rosuda.REngine.RList;

import idea.schema.rp.RpMetric;
import lombok.extern.slf4j.Slf4j;
import idea.GuiUtil;
import idea.r.RUtil;
import idea.ts.TsFilter;
import idea.ts.TsoPrefs;
import idea.ts.TsoSession;
import idea.tsoffline.canvas.TsBaseCanvas;
import idea.tsoffline.canvas.TsPSwingCanvas;
import idea.tsoffline.model.FormulaOp;
import idea.tsoffline.model.FormulaSignal;
import idea.tsoffline.model.OfflineSignal;
import idea.tsoffline.video.TsPhaseControlPanel;
import idea.tsoffline.vizwiz.RPlotterPanel;

@Slf4j
public class AppUtil {

	private static AppUtil instance = new AppUtil();
	private static Map<String, Object> params = new HashMap<String, Object>();

	public static void setParam(String topic, String name, Object value) {
		params.put(topic + ":" + name, value);
	}

	public static Object getParam(String topic, String name) {
		return getParam(topic, name, null);
	}

	public static Object getParam(String topic, String name, Object defaultValue) {
		Object val = params.get(topic + ":" + name);
		return (val == null) ? defaultValue : val;
	}

	public static AppUtil getInstance() {
		return instance;
	}

	private static List<JPanel> pending_plots = new LinkedList<JPanel>();

	/*
	 * SCRIPT INTERFACE ROUTINES, must be public
	 */

	public static void open() throws Exception {
		AppFrame frame = AppFrame.getInstance();
		frame.openMenuItemActionPerformed(null);
	}

	public static void open(String fileName) throws Exception {
		AppFrame frame = AppFrame.getInstance();
		File f = new File(fileName);
		File sessionDir = f.getParentFile();
		TsoSession session = frame.getSessionInfoStep1(f);
		frame.openSessionFiles(null, session, sessionDir);

		/*
		 * if this is the event dispatch thread...exec async, else invoke sync
		 */
		if (SwingUtilities.isEventDispatchThread() == false) {
			//
			// this would be elegant, but maybe not appropriate for a task as complex as the
			// load...
			// which might even be finished before we get here
			//
			// synchronized (frame) {
			// frame.wait();
			// }

			for (int i = 0; i < 3; i++) {
				Thread.sleep(1000);
			}
		} else {
			log.error("Cannot wait for LOAD-COMPLETION: use \"# pragma async\" in script.");
		}
	}

	public static void close() {
		AppFrame frame = AppFrame.getInstance();
		frame.close();
	}

	public static String getSubject() {
		AppFrame frame = AppFrame.getInstance();
		return frame.getSubject();
	}

	/*
	 * Return an object: forces R to avoid type conversions from long to double!
	 */
	public static long getStartTime() {
		AppFrame frame = AppFrame.getInstance();
		return frame.getCanvas().getStartTime();
	}

	public static TsPSwingCanvas getCanvas() {
		AppFrame frame = AppFrame.getInstance();
		return frame.getCanvas();
	}

	/*
	 * Method to do this is not as obvious as it would seem, and I don't know if
	 * setwd() in the R engine performs the equivalence of the JNI call. This may be
	 * double work. Unkown without testing.
	 * 
	 * http://stackoverflow.com/questions/840190/changing-the-current-working-
	 * directory-in-java#8204584
	 */
	public static void cd(String dir) {
		REngine eng = RUtil.getREngine();
		try {
			eng.parseAndEval("setwd('" + dir + "' )");
		} catch (REngineException | REXPMismatchException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		File directory; // Desired current working directory

		directory = new File(dir).getAbsoluteFile();
		if (directory.exists() || directory.mkdirs()) {
			System.setProperty("user.dir", directory.getAbsolutePath());
		}

	}

	public static void createPlot(String title) {

		if (SwingUtilities.isEventDispatchThread()) {
			_createPlot(title);
		} else {
			Runnable r = new Runnable() {

				@Override
				public void run() {
					_createPlot(title);
				}
			};

			try {
				SwingUtilities.invokeAndWait(r);
			} catch (InvocationTargetException | InterruptedException e) {
				// FIXME: not sure where to put this message
				e.printStackTrace();
			}
		}

		/*
		 * Must be run on invoking ("R-Engine") thread
		 */
		REngine re = RUtil.getREngine();

		try {
			re.parseAndEval("JavaGD(name=\"" + title + "\")");
		} catch (REngineException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (REXPMismatchException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	/*
	 * Must be run on GUI thread
	 */

	private static void _createPlot(String title) {
		RPlotterPanel p = new RPlotterPanel();
		p.putClientProperty("title", title);

		p.setMinimumSize(new Dimension(500, 300));

		pending_plots.add(p);
	}

	public static void showPlots() {
		AppFrame f = AppFrame.getInstance();
		f.showPlots();
	}

	public static void discardPlots() {
		AppFrame f = AppFrame.getInstance();
		f.discardPlots();
	}

	public static TsPhaseControlPanel createPhaseSpaceVideo(String title) {

		TsPhaseControlPanel p = new TsPhaseControlPanel();
		p.putClientProperty("title", title);

		p.setMinimumSize(new Dimension(500, 300));

		// pending_plots.add(p);
		pending_plots.add(p);
		return p;
	}

	public static List<? extends JPanel> getPendingPlots() {
		return pending_plots;
	}

	public static void clearPendingPlots() {
		while (pending_plots.size() > 0) {
			pending_plots.remove(0);
		}
	}

	public static REXP runR(String scriptPath, boolean reportError) {

		String s = getScript(scriptPath);
		if (s == null) {
			throw new RuntimeException("No such file: " + scriptPath);
		}

		return runScript(s, reportError);
	}

	/*
	 * This will read the script to a large string, whether the script is a file or
	 * a classpath resource
	 */
	public static String getScript(String scriptPath) {
		String pwd = System.getProperty("user.dir");

		String s = null;

		String wd = (pwd == null) ? "" : pwd;

		File f = new File(scriptPath);
		if (!f.exists()) {
			f = new File(wd, scriptPath);
		}

		try {
			if (f != null && f.exists()) {
				byte[] encoded;
				encoded = Files.readAllBytes(Paths.get(f.getPath()));
				s = new String(encoded, StandardCharsets.UTF_8);
			} else {
				byte[] buf = new byte[256];
				// InputStream in =
				// AppUtil.class.getResourceAsStream(scriptPath);
				InputStream in = instance.getClass().getResourceAsStream(scriptPath);
				if (in == null) {
					in = instance.getClass().getResourceAsStream("/" + scriptPath);
				}
				if (in != null) {
					StringBuffer out = new StringBuffer();
					do {
						int n = in.read(buf);
						if (n <= 0)
							break;

						out.append(new String(buf, 0, n));
					} while (true);

					s = out.toString();
					in.close();
				}
			}
		} catch (IOException e) {
			throw new RuntimeException("IOException/No such file: " + scriptPath);
		}

		return s;
	}

	public static REXP runScript(String script, boolean reportError) {
		return runScript(null, script, reportError);
	}

	public static REXP runScript(String env_name, String script, boolean reportError) {
		REXP ok = null;

		boolean async = false;
		ArrayList<String> pragmas = parsePragmas(script);
		if (pragmas != null) {
			while (pragmas.size() > 0) {
				String tag = pragmas.remove(0);
				if ("async".equals(tag)) {
					async = true;
				} else {
					log.error("unknown pragma in script: {}", tag);
				}
			}

		}

		if (async) {
			createPlot("ZZZZ");
			Thread t = new Thread(new Runnable() {

				@Override
				public void run() {
					runScriptCurrentThread(env_name, script, reportError);
				}
			}, "runScript.Thread");

			t.start();
		} else {
			ok = runScriptCurrentThread(env_name, script, reportError);
		}

		return ok;
	}

	public static REXP runScriptCurrentThread(String env_name, String script, boolean reportError) {
		boolean success = false;
		REXP ok = null;

		REngine re = RUtil.getREngine();

		if (re == null) {
			GuiUtil.showMessage("R Engine not available.");
			return null;
		}

		script = script.replace("\r\n", "\n");
		script = script.replace("\r", "\n");

		try {
			String r_tryable;

			if (env_name == null) {
				r_tryable = "try( { eval( parse( text=z_script ) ) }, silent=TRUE)";
			} else {
				// does this environment already exist?
				REXP env = re.get(env_name, null, false);

				if (env == null) {
					// create it
					String prep_env = env_name + " <-  new.env()";
					ok = re.parseAndEval(prep_env);
				}

				// putting the close bracket of the TRY on a seperate line is a good idea
				r_tryable = "try( { eval( envir=" + env_name + ", parse( text=z_script ) ) }, silent=TRUE)";
			}

			re.assign("z_script", script);

			ok = re.parseAndEval(r_tryable);
			explain(ok);

		} catch (REngineException e1) {

			if (reportError) {
				GuiUtil.showError("Error in R script", e1);
			} else {
				throw new RuntimeException(e1);
			}
		} catch (RuntimeException e1) {

			if (reportError) {
				GuiUtil.showError("Error in R script", e1);
			} else {
				throw e1;
			}
		} catch (Throwable e1) {
			if (reportError) {
				GuiUtil.showError("Error in R script", e1);
			} else {
				throw new RuntimeException(e1);
			}
		}

		return ok;
	}

	private static ArrayList<String> parsePragmas(String script) {
		Reader r = new StringReader(script);
		BufferedReader script_reader = new BufferedReader(r);
		ArrayList<String> pragmas = new ArrayList<String>();

		while (script_reader != null) {
			try {
				String line;
				repeat: do {
					line = script_reader.readLine();
					if (line != null) {
						StringTokenizer tokenizer = new StringTokenizer(line);
						for (int i = 0; i < 3 && tokenizer.hasMoreTokens(); i++) {
							String token = tokenizer.nextToken();
							if (i == 0 && !token.startsWith("#")) {
								continue repeat;
							} else if (i == 1 && !token.equalsIgnoreCase("pragma")) {
								continue repeat;
							} else if (i == 2) {
								pragmas.add(token);
								break repeat;
							}
						}
					}
				} while (line != null);

			} catch (IOException e) {
			} finally {
				try {
					script_reader.close();
					script_reader = null;
				} catch (Exception e1) {
					// ignore
				}
				script_reader = null;
			}

		}

		return pragmas;
	}

	public static void explain(REXP ok) throws REXPMismatchException {
		REXP cl = ok.getAttribute("class");
		if (cl != null && cl.asString() != null && cl.asString().equals("try-error")) {

			// RUtil.getNativeException()
			REXPList attr = ok._attr();
			Throwable t = null;
			if (attr != null && attr.length() > 0) {
				t = drillForNativeException(attr.asList());
			}

			String message = RUtil.describe(null, 5, ok).toString();
			System.err.println("R error: " + message);
			throw new RuntimeException(message, t);
		}
	}

	public static Throwable drillForNativeException(RList list) {
		Throwable t = null;
		for (int i = 0; i < list.size() && t == null; i++) {
			REXP robj = (REXP) list.get(i);
			;
			if (robj instanceof REXPList) {
				RList list2 = ((REXPList) robj).asList();
				t = drillForNativeException(list2);
			}
			if (robj instanceof REXPGenericVector) {
				RList list2 = ((REXPGenericVector) robj).asList();
				t = drillForNativeException(list2);
			}
			if (robj instanceof REXPJavaReference) {
				REXPJavaReference ref = (REXPJavaReference) robj;
				Object o = ref.asNativeJavaObject();
				if (o instanceof Throwable) {
					t = (Throwable) o;
				}
			}
		}
		return t;
	}

	public static OfflineSignal processFormula(String name, Color sig_color, String symbolic_formula)
			throws REXPMismatchException, REngineException {
		String executable_formula = replaceTokens(symbolic_formula);

		REngine re = RUtil.getREngine();

		AppUtil.runScript("output <- NA", false);
		String script = "output <- " + executable_formula;
		AppUtil.runScript(script, true);
		Color color = Color.RED;

		OfflineSignal sig = null;
		REXP exp = re.parseAndEval("output");
		if (exp instanceof REXPJavaReference) {
			REXPJavaReference ref = (REXPJavaReference) exp;
			Object o = ref.asNativeJavaObject();

			color = color.GREEN;

			sig = (OfflineSignal) o;
			sig.setLocation(symbolic_formula);
			sig.setName(name);
			sig.setCode(null);
			sig.setDefaultColor(color);
			sig.setColor(color);
			sig.setTyp(TimeseriesType.TT_FORMULA);

		} else if (exp.isNull() || exp.isNA()[0]) {
			// sig = null; -- this is the default
		} else {
			StringBuffer txt = RUtil.describe(null, 2, exp);
			log.error("Unknown object in script evaluation: {}", txt.toString());
		}
		return sig;
	}

	private static String replaceTokens(String text) {
		Pattern pattern = Pattern.compile("\\$\\{(.+?)\\}");
		Matcher matcher = pattern.matcher(text);
		StringBuffer buffer = new StringBuffer();

		while (matcher.find()) {
			String replacement = "data$getSignalFromAlias(\"" + matcher.group(1) + "\") ";
			if (replacement != null) {
				// matcher.appendReplacement(buffer, replacement);
				// see comment
				matcher.appendReplacement(buffer, "");
				buffer.append(replacement);
			}
		}
		matcher.appendTail(buffer);
		return buffer.toString();
	}

	public static int asMilliseconds(String item) {
		String[] arr = item.split(" ");
		int unit = 1000;
		if (arr == null || arr.length < 2) {
			log.error("Scale not specified!");
			arr = new String[] { "6" };
		} else if ("sec".equals(arr[1])) {
			unit = 1000;
		} else if ("min".equals(arr[1])) {
			unit = 1000 * 60;
		} else if ("hr".equals(arr[1])) {
			unit = 1000 * 60 * 60;
		} else {
			log.error("FIXME: unexpected time unit=\"{}\"", arr[1]);
		}
		// can't parse commas by this method, so strip them out...can happen
		// when zoomed out
		String s = arr[0];
		s = s.replaceAll(",", "");
		return (int) (unit * Double.parseDouble(s));
	}

	public static boolean stringAsBoolean(String s, boolean defaultValue) {
		boolean b = defaultValue;
		if (s == null) {
			// use the default value
		} else if ("true".equalsIgnoreCase(s)) {
			b = true;
		} else if ("false".equalsIgnoreCase(s)) {
			b = true;
		} else {
			int ival = Integer.parseInt(s);
			b = (ival != 0);
		}
		return b;
	}

	public static void deleteFilter(String filterName) {
		AppFrame frame = AppFrame.getInstance();
		TsoPrefs prefs = frame.getPrefs();
		Iterator<TsFilter> it = prefs.getFilters().iterator();
		while (it.hasNext()) {
			TsFilter filter = it.next();
			if (filterName.equals(filter.getName())) {
				it.remove();
				break;
			}
		}
	}

	public static TsFilter createFilter(String filterName, String json) {
		AppFrame frame = AppFrame.getInstance();
		TsoPrefs prefs = frame.getPrefs();

		TsFilter savable = null;
		for (TsFilter f : prefs.getFilters()) {
			if (filterName.equals(f.getName())) {
				savable = f;
				break;
			}
		}

		if (savable == null) {
			savable = new TsFilter();
			prefs.getFilters().add(savable);
		}

		savable.setName(filterName);
		savable.setDescription(json);
		savable.setGlobal(true);

		return savable;
	}

	public static TsPSwingCanvas getActiveCanvas() {
		return AppFrame.getInstance().getCanvas();
	}

	public static HPSplitableLayer getSignalByName(String name) {
		HPSplitableLayer found = null;
		List<HPSplitableLayer> sigs = AppModel.getSignals();
		if (sigs != null) {
			for (HPSplitableLayer sig : sigs) {
				if (name.equals(sig.getName())) {
					found = sig;
					break;
				} else if (name.equals(sig.getCode())) {
					found = sig;
					break;
				}
			}
		}
		return found;
	}

	public static HPSplitableLayer derivative(TsBaseCanvas canvas, HPSplitableLayer src, String name) {
		RpMetric m = new RpMetric();

		FormulaSignal formula = new FormulaSignal(m);
		formula.sig1 = src.getLocation();
		formula.op = FormulaOp.Derivative;

		return AppModel.createFormulaSignal(canvas, name, Color.CYAN, formula);
	}

}
