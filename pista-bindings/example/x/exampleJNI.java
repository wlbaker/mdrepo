/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.7
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class exampleJNI {
  public final static native void delete_SerialIO(long jarg1);
  public final static native void SerialIO_send(long jarg1, SerialIO jarg1_, String jarg2, int jarg3);
  public final static native void SerialIO_sendSwigExplicitSerialIO(long jarg1, SerialIO jarg1_, String jarg2, int jarg3);
  public final static native long new_SerialIO();
  public final static native void SerialIO_director_connect(SerialIO obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void SerialIO_change_ownership(SerialIO obj, long cptr, boolean take_or_release);
  public final static native long new_PistaDev();
  public final static native void delete_PistaDev(long jarg1);
  public final static native void PistaDev_delSerialIO(long jarg1, PistaDev jarg1_);
  public final static native void PistaDev_setSerialIO(long jarg1, PistaDev jarg1_, long jarg2, SerialIO jarg2_);
  public final static native void PistaDev_send(long jarg1, PistaDev jarg1_, String jarg2, int jarg3);

  public static void SwigDirector_SerialIO_send(SerialIO self, String buf, int len) {
    self.send(buf, len);
  }

  private final static native void swig_module_init();
  static {
    swig_module_init();
  }
}
