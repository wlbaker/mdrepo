package idea.r;

import java.io.File;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.util.Iterator;

import lombok.extern.slf4j.Slf4j;

import org.rosuda.JRI.Rengine;
import org.rosuda.REngine.REXP;
import org.rosuda.REngine.REXPExpressionVector;
import org.rosuda.REngine.REXPGenericVector;
import org.rosuda.REngine.REXPJavaReference;
import org.rosuda.REngine.REXPLanguage;
import org.rosuda.REngine.REXPList;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REXPNull;
import org.rosuda.REngine.REXPS4;
import org.rosuda.REngine.REXPString;
import org.rosuda.REngine.REXPSymbol;
import org.rosuda.REngine.REXPUnknown;
import org.rosuda.REngine.REngine;
import org.rosuda.REngine.REngineCallbacks;
import org.rosuda.REngine.REngineException;
import org.rosuda.REngine.REngineStdOutput;
import org.rosuda.REngine.RList;
import org.rosuda.REngine.JRI.JRIEngine;

@Slf4j
public class RUtil {
	private static REngine eng;
	private static boolean failed = false;
	private static String R_HOME;
	private static String failedReason = null;
	private static long rni_ver;
	private static long eng_ver;

	public static REngine getREngine() {
		if (eng == null && !failed) {
			try {
				failed = true;
				RUtil.init(new REngineStdOutput());
				failed = false;
			} catch (Throwable e1) {
				failedReason = e1.getMessage();
				log.error("getREngine() failure: {}", e1.getMessage());
			}

		}
		return eng;
	}

	public static void init(REngineCallbacks callbacks) throws REngineException, REXPMismatchException, ClassNotFoundException,
			NoSuchMethodException, IllegalAccessException, InvocationTargetException {
		String sep = File.pathSeparator;
		R_HOME = System.getenv("R_HOME");

		if (R_HOME == null) {
			if (":".equals(sep)) { // linux or Unix variant
				R_HOME = "/usr/lib64/R";
			} else { // windows
				R_HOME = "c:\\opt\\tools\\R\\latest";
			}
		}

		initREngine(R_HOME, callbacks);
	}

	public static void initREngine(String R_HOME, REngineCallbacks callbacks) throws REngineException, REXPMismatchException,
			ClassNotFoundException, NoSuchMethodException, IllegalAccessException, InvocationTargetException {

		String path_sep = File.pathSeparator; // colon or semicolon
		char sep = File.separatorChar;

		RUtil.R_HOME = R_HOME;

		// if (vm.indexOf("64-bit") >= 0) {
		// os_id += "64";
		// }
		// String data_model = System.getProperty("sun.arch.data.model", "32");
		// String ARCH = (data_model.equals"64") ? "\\x64" : "\\i386";
		String vm = System.getProperty("java.vm.name").toLowerCase();
		String ARCH = "";
		// String RJ = "rj";
		String RJAVA = "rJava";
		if (sep == '\\') {
			// windows
			ARCH = (vm.indexOf("64-bit") > 0) ? "\\x64" : "\\i386";
			// RJ = "rJava";
		}

		//String BIN = sep + "bin" + ARCH;

		String p = System.getProperty("java.library.path");
		p = p + path_sep + check_and_fix_path( R_HOME + sep + "bin" + ARCH );
		p = p + path_sep + check_and_fix_path( R_HOME + sep + "library" + sep + RJAVA + sep + "jri" + ARCH);
		p = p + path_sep + check_and_fix_path( R_HOME + "" + sep + "library" + sep + RJAVA + sep + "libs" + ARCH);
		System.setProperty("java.library.path", p);
		p = System.getProperty("java.library.path");
		System.out.println("2- java.library.path: " + p);

		/**
		 * At first the system property is updated with the new value. This
		 * might be a relative path � or maybe you want to create that path
		 * dynamically.
		 * 
		 * The Classloader has a static field (sys_paths) that contains the
		 * paths. If that field is set to null, it is initialized automatically.
		 * Therefore forcing that field to null will result into the
		 * reevaluation of the library path as soon as loadLibrary() is called�
		 */

		Field fieldSysPath;
		try {
			fieldSysPath = ClassLoader.class.getDeclaredField("sys_paths");
			fieldSysPath.setAccessible(true);
			fieldSysPath.set(null, null);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		// c:\opt\tools\R\R-2.15.0\bin\i386

		if (sep == '\\') {
			// windows
			// System.load(R_HOME + BIN + "" + sep + "Rzlib.dll"); // required
			// by R
			// System.load(R_HOME + BIN + "" + sep + "Riconv.dll"); // required
			// by R
			//
			// System.load(R_HOME + BIN + "" + sep + "Rblas.dll"); // required
			// by R
			// System.load(R_HOME + BIN + "" + sep + "Rlapack.dll"); // required
			// by R??
			// System.load(R_HOME + BIN + "" + sep + "Rgraphapp.dll"); //
			// required by R
			System.load( check_and_fix_path( R_HOME + sep + "bin" + ARCH) + sep + "R.dll");
		} else {
			System.load(R_HOME + "/lib" + sep + "libR.so");
		}

		System.load(
				R_HOME + "" + sep + "library" + sep + RJAVA + sep + "jri" + ARCH + "" + sep + _r_libname("lib", "jri"));
		System.load(
				R_HOME + "" + sep + "library" + sep + RJAVA + sep + "libs" + ARCH + "" + sep + _r_libname("", "rJava"));
		// System.load( R_HOME + "" + sep + "library" + sep + "JavaGD" + sep +
		// "libs" + ARCH + "" + sep + "WinRegistry.dll");
		System.load(R_HOME + "" + sep + "library" + sep + "JavaGD" + sep + "libs" + ARCH + "" + sep
				+ _r_libname("", "JavaGD"));

		rni_ver = Rengine.rniGetVersion();
		eng_ver = Rengine.getVersion();

		if (rni_ver != eng_ver) {
			String m = "** Version mismatch - Java files don't match library version for R Engine.";
			System.err.println(m);
			throw new RuntimeException(m); // GuiUtil.showMessage(m);
		}

		eng = null; // Rengine.getMainEngine();

		if (eng == null) {
			String args[] = { "--vanilla" };
			// REngineCallbacks callbacks = new REngineStdOutput();
			// new Rengine(new String[] {"--vanilla"}, true, null)
			// eng = new Rengine(args, false, null);
			// eng = JRIEngine.createEngine(args, new TextConsoleA(), false);
			eng = REngine.engineForClass("org.rosuda.REngine.JRI.JRIEngine", args, callbacks, false);
		}
		System.out.println("engine=" + eng);

		// if (!eng.waitForR()) {
		// System.out.println("Cannot load R");
		// return;
		// }

		REXP x = eng.parseAndEval("library( rJava )");
		System.out.println("REXP result = " + x);

		System.out.println();
		System.out.println("--------------");
		System.out.println();

		//110218 JDK10 * cannot call .jinit() if the JVM is already running
		//110218 JDK10 x = eng.parseAndEval(".jinit( )");
		//110218 JDK10 System.out.println("REXP result = " + x);

	}

	private static String check_and_fix_path(String p) {
		File f = new File(p);
		if( f.exists() ) {
			// fine
		} else {
			p = p.replace("i386", "x32");
			f = new File(p);
			if( !f.exists() ) {
				log.error("NO SUCH R-LIBRARY SEGMENT: {}", p );
			}
		}
		return p;
	}

	private static String _r_libname(String prefix, String root) {
		if (File.pathSeparatorChar == ';') {
			root = root + ".dll";
		} else {
			root = prefix + root + ".so"; // no lib prefix
		}
		return root;
	}

	public static String getName() {
		String name;

		if (R_HOME == null) {
			name = "R: <unspecified>";
		} else {
			String[] ar = R_HOME.split("[\\\\]");
			if (ar.length == 0) {
				name = "R: _empty_";
			} else if (ar.length == 1) {
				name = "R: " + ar[0];
			} else {
				name = ar[ar.length - 2] + ":" + ar[ar.length - 1];
			}
		}

		return name;
	}

	public static String getStatus() {
		String status;
		if (eng == null && failed == false) {
			status = "[Not Initialized]";
		} else if (eng == null && failed == true) {
			status = "[Failed] ";
			if (failedReason != null) {
				status += failedReason;
			}
		} else {
			status = (eng == null) ? "[UNKNOWN]" : "Ready";
		}

		return status;
	}

	public static String getVersion() throws REngineException, REXPMismatchException {
		String ver;
		if (rni_ver == eng_ver) {
			ver = "RNI:" + rni_ver;
		} else {
			ver = "RNI:" + rni_ver + " != " + eng_ver;
		}

		if( eng != null ) {
			REXP exp = eng.parseAndEval("sessionInfo()");
			// ver = exp.asString();
			RList list = exp.asList();
			REXPGenericVector o = (REXPGenericVector) list.get("R.version");
			RList sessionInfo = (RList)o.asList();
			REXPString str = (REXPString)sessionInfo.get("version.string");
			ver = str.asString();
			//String[] sess = exp.asStrings();
			//if( sess != null && sess.length > 0 ) {
			//	ver = sess[0];
			//}
		}
		return ver;
	}
	
	public static StringBuffer describe(StringBuffer ret, int level, REXP exp) throws REXPMismatchException {
		level--;
		if( level == 0 ) {
			return null;
		}
		
		if( ret == null ) {
			ret = new StringBuffer();
		}
		if (exp != null) {
			REXPList attr = exp._attr();
			if( attr != null && attr.length() > 0 ) {
				ret.append("{\n  ");
				describe(ret, level, attr);
				ret.append("}\n");
			}
			
			if (exp.isNull()) {
				// ret.append("<null result>");
			} else if (exp instanceof REXPNull) {
				ret.append("<null result..shouldnt be here?>\n");
			} else if (exp instanceof REXPGenericVector) {
				REXPGenericVector vec = (REXPGenericVector)exp;
				
				if( exp instanceof REXPExpressionVector ) {
					ret.append("REXPExpression");
				}
				RList list = vec.asList();
				for( int i = 0; i < list.size() ; i++ ) {
					REXP robj = (REXP) list.get( i );
					ret.append( "[" + (i+1) + "] ");
					describe(ret, level, robj);
					ret.append("\n");
				}
			} else if (exp instanceof REXPList) {
				REXPList vec = (REXPList)exp;
				
				RList list = vec.asList();
				for( int i = 0; i < list.size() ; i++ ) {
					REXP robj = (REXP) list.get( i );
					ret.append( "[" + (i+1) + "] ");
					describe(ret, level, robj);
					ret.append("\n");
				}
			} else if (exp instanceof REXPJavaReference) {
				REXPJavaReference ref = (REXPJavaReference) exp;
				Object o = ref.asNativeJavaObject();
				if( o instanceof Throwable ) {
					log.error("return error from R:", (Throwable)o);
				}
				String s = o.toString();
				ret.append(" ");
				ret.append(s);
			} else if (exp instanceof REXPUnknown) {
				REXPUnknown ref = (REXPUnknown) exp;
				ret.append("[unknown str: " + ref.toString() + "]");
			} else if (exp instanceof REXPSymbol) {
				REXPSymbol ref = (REXPSymbol) exp;
				ret.append(ref.asString() );
			} else if (exp instanceof REXPLanguage) {
				REXPLanguage ref = (REXPLanguage) exp;
				ret.append("[" );
				RList rl = ref.asList();
				Iterator it = rl.iterator();
				while( it.hasNext() ) {
					Object node = it.next();
					describe(ret, level, (REXP) node );
					ret.append( " ");
				}
				ret.append("]");
			} else if (exp instanceof REXPS4) {
				REXPS4 ref = (REXPS4) exp;
				ret.append("FIXME: decode REXPS4\n");
				ret.append(exp.toDebugString());
			} else if (exp instanceof REXP) {
				String[] ss = exp.asStrings();
				int     len = 0;
				boolean nl = true;
				int idx = 1;
				for (String s : ss) {
					if( s == null ) {
						s = "NA";
					}  else {
						s = "\"" + s + "\"";
					}
					int seglen = s.length();
					int padded_len = ((len+1)/10 + 1)*10;  
					if( len == 0 ) {						
						ret.append("[");
						ret.append( idx );
						ret.append("] ");
					} else if (padded_len + seglen > 80 ) {
						len = 0;
						ret.append("\n");
						ret.append("[");
						ret.append( idx );
						ret.append("] ");
					} else {
						while( len < padded_len ) {
							ret.append(" ");
							len++;
						}
					}
					
					ret.append(s);
					len += seglen;
					idx++;
				}
			} else {
				// of course this code is unreachable!
				// REngine eng = AppFrame.getREngine();
				String dbg = exp.toDebugString();
				ret.append(" debug: " );
				ret.append(dbg);
			}
		}
		
		return ret;
	}


}
