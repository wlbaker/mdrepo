package idea.r;

import java.io.*;
import java.lang.reflect.InvocationTargetException;
import java.awt.FileDialog;
import java.awt.Frame;
import java.util.Enumeration;
import java.util.Iterator;

import org.rosuda.JRI.Rengine;
import org.rosuda.REngine.REXPMismatchException;
import org.rosuda.REngine.REngine;
import org.rosuda.REngine.REngineException;
import org.rosuda.REngine.RList;

import icuInterface.PlatformUtil;

import org.rosuda.JRI.REXP;
import org.rosuda.JRI.RVector;
import org.rosuda.JRI.RMainLoopCallbacks;

public class rJavaTest {

    public static void main(String[] args) throws REXPMismatchException, REngineException, ClassNotFoundException, NoSuchMethodException, IllegalAccessException, InvocationTargetException {

		String iu = System.getProperty("jri.ignore.ule");
		String p = System.getProperty("java.library.path");
		System.out.println("original java library path: " + p);

//		boolean jriLoaded;
//				try {
//    	            System.loadLibrary("jri");
//    				jriLoaded = true;
//    	        } catch (UnsatisfiedLinkError e) {
//    				jriLoaded = false; // should be implicit, but well ...
//    				if (iu == null || !iu.equals("yes")) {
//    					System.err.println("Cannot find JRI native library!\nPlease make sure that the JRI native library is in a directory listed in java.library.path.\n");
//    					e.printStackTrace();
//    					System.exit(1);
//    				}
//    	        }

    	        PlatformUtil.init();
    	REngine re = RUtil.getREngine();
    	
    	//args = new String[] { "--vanilla" };
        //REngine re= REngine.engineForClass( "org.rosuda.REngine.JRI.JRIEngine", args, null, false);
        //REXP x;
        re.parseAndEval("print(1:10/3)");
        org.rosuda.REngine.REXP x;
		System.out.println(x=re.parseAndEval("iris"));
        // RVector v = x.asVector();
		
		System.out.println( "is vec? " + x.isVector());
		System.out.println( "is list? " + x.isList());
         org.rosuda.REngine.REXP names = x.getAttribute("names");
        if (names!=null) {
            System.out.println("has names:" + names);
//            Iterator it = names.iterator();
//            while( it.hasNext() ) { //for (String name : names.) {
//            	org.rosuda.REngine.REXP exp = (org.rosuda.REngine.REXP) it.next();
//                System.out.println( exp.getAttribute("names"));
//            }
        }

//        if (true) {
//            System.out.println("Now the console is yours ... have fun");
//            re.startMainLoop();
//        } else {
//            re.end();
//            System.out.println("end");
//        }
    }
}