package java9;

import java.io.IOException;
import java.io.InputStream;
import java.util.Locale;
import java.util.Properties;
import java.util.ResourceBundle;

import javax.swing.plaf.metal.MetalTheme;

public class ResourceTest {

	//failed private static String metal_en = "com/sun/swing/internal/plaf/metal/resources/metal";
	private static String metal_su = "com.sun.swing.internal.plaf.metal.resources.metal";
	
//	public static void stackOverflow() throws IOException {
//		Module moduleA = MetalTheme.class.getModule();
//		
//		InputStream s1 = moduleA.getResourceAsStream(metal_su);
//		InputStream s2 = moduleA.getResourceAsStream(metal_en);
//		
//		System.out.println("s1=" + s1);
//		System.out.println("s2=" + s2);
//	}
	
	public static void substance() {
		 ResourceBundle bundle = ResourceBundle.getBundle(metal_su );
		 System.out.println("substance bundle su: " + bundle);
		 
		 //bundle = ResourceBundle.getBundle(metal_en );
		 //System.out.println("substance bundle: " + bundle);
	}
	
	public static void main(String[] args) throws IOException {
		Properties props = System.getProperties();
		// props.list( System.out );
		Object javahome = props.get("java.home");

		System.out.println("java home: " + javahome );
		// stackOverflow();
		substance();
	}

}
