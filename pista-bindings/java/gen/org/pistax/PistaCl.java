/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.pistax;

public class PistaCl {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected PistaCl(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PistaCl obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        PISTAXJNI.delete_PistaCl(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static PistaCl getInstance() {
    return new PistaCl(PISTAXJNI.PistaCl_getInstance(), false);
  }

  public int driver_count() {
    return PISTAXJNI.PistaCl_driver_count(swigCPtr, this);
  }

  public PistaDriver driver(int idx) {
    long cPtr = PISTAXJNI.PistaCl_driver__SWIG_0(swigCPtr, this, idx);
    return (cPtr == 0) ? null : new PistaDriver(cPtr, false);
  }

  public PistaDriver driver(String name) {
    long cPtr = PISTAXJNI.PistaCl_driver__SWIG_1(swigCPtr, this, name);
    return (cPtr == 0) ? null : new PistaDriver(cPtr, false);
  }

  public int service_count() {
    return PISTAXJNI.PistaCl_service_count(swigCPtr, this);
  }

  public PistaService service(int idx) {
    long cPtr = PISTAXJNI.PistaCl_service__SWIG_0(swigCPtr, this, idx);
    return (cPtr == 0) ? null : new PistaService(cPtr, false);
  }

  public PistaService service(String name) {
    long cPtr = PISTAXJNI.PistaCl_service__SWIG_1(swigCPtr, this, name);
    return (cPtr == 0) ? null : new PistaService(cPtr, false);
  }

  public int run() {
    return PISTAXJNI.PistaCl_run(swigCPtr, this);
  }

  public int tick() {
    return PISTAXJNI.PistaCl_tick(swigCPtr, this);
  }

  public int stop() {
    return PISTAXJNI.PistaCl_stop(swigCPtr, this);
  }

  public SWIGTYPE_p_pista_context c_inst() {
    long cPtr = PISTAXJNI.PistaCl_c_inst(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_pista_context(cPtr, false);
  }

}
