/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.7
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


public class SerialIO {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected SerialIO(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(SerialIO obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        exampleJNI.delete_SerialIO(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  protected void swigDirectorDisconnect() {
    swigCMemOwn = false;
    delete();
  }

  public void swigReleaseOwnership() {
    swigCMemOwn = false;
    exampleJNI.SerialIO_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    exampleJNI.SerialIO_change_ownership(this, swigCPtr, true);
  }

  public void send(String buf, int len) {
    if (getClass() == SerialIO.class) exampleJNI.SerialIO_send(swigCPtr, this, buf, len); else exampleJNI.SerialIO_sendSwigExplicitSerialIO(swigCPtr, this, buf, len);
  }

  public SerialIO() {
    this(exampleJNI.new_SerialIO(), true);
    exampleJNI.SerialIO_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

}
