public class runme
{
  static {
    try {
	System.out.println("loading libexample.so");
        System.loadLibrary("example");
	System.out.println("loading librxtxSerial.so");
        System.loadLibrary("rxtxSerial");

	System.out.println("LOADED!!!");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load. See the chapter on Dynamic Linking Problems in the SWIG Java documentation for help.\n" + e);
      System.exit(1);
    }
  }

  public static void main(String[] args)
  {
    System.out.println("Adding and calling a normal C++ callback");
    System.out.println("----------------------------------------");

    PistaDev              caller = new PistaDev();
    PistaCOMM            callback = new PistaCOMM();
    
    caller.setPistaCOMM(callback);
    caller.send("hello\n",6);
    caller.delPistaCOMM();

    callback = new RxtxCBAdapter();

    System.out.println();
    System.out.println("Adding and calling a Java callback");
    System.out.println("------------------------------------");

    caller.setPistaCOMM(callback);
    caller.send("hello\n",6);
    caller.delPistaCOMM();

    // Test that a double delete does not occur as the object has already been deleted from the C++ layer.
    // Note that the garbage collector can also call the delete() method via the finalizer (callback.finalize())
    // at any point after here.
    callback.delete();

    System.out.println();

    System.out.println("java exit");
  }
}

class RxtxCBAdapter extends PistaCOMM
{
  public RxtxCBAdapter()
  {
    super();
  }

  public void send( byte[] buf, int len)
  {
    System.out.println("Rxtx CB Adapter");
  }
}

