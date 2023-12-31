/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.pistax;

public class PistaDev {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected PistaDev(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(PistaDev obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        PISTAXJNI.delete_PistaDev(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public PistaDev(pista_dev_inst di) {
    this(PISTAXJNI.new_PistaDev(pista_dev_inst.getCPtr(di), di), true);
  }

  public PistaStream getStream(int streamId) {
    return new PistaStream(PISTAXJNI.PistaDev_getStream(swigCPtr, this, streamId), true);
  }

  public int connect() {
    return PISTAXJNI.PistaDev_connect(swigCPtr, this);
  }

  public int disconnect() {
    return PISTAXJNI.PistaDev_disconnect(swigCPtr, this);
  }

  public int setOption(String key, String val) {
    return PISTAXJNI.PistaDev_setOption(swigCPtr, this, key, val);
  }

  public int getStatus() {
    return PISTAXJNI.PistaDev_getStatus(swigCPtr, this);
  }

  public int handle(byte[] data) {
    return PISTAXJNI.PistaDev_handle(swigCPtr, this, data);
  }

  public void attach(SWIGTYPE_p_f_p_q_const__void_p_q_const__char_int__int writer, SWIGTYPE_p_void comm_priv) {
    PISTAXJNI.PistaDev_attach__SWIG_0(swigCPtr, this, SWIGTYPE_p_f_p_q_const__void_p_q_const__char_int__int.getCPtr(writer), SWIGTYPE_p_void.getCPtr(comm_priv));
  }

  public void attach(SWIGTYPE_p_f_p_void_p_pista_data_packet__int writer, SWIGTYPE_p_void event_priv) {
    PISTAXJNI.PistaDev_attach__SWIG_1(swigCPtr, this, SWIGTYPE_p_f_p_void_p_pista_data_packet__int.getCPtr(writer), SWIGTYPE_p_void.getCPtr(event_priv));
  }

  public void attach(PistaEventHandler h) {
    PISTAXJNI.PistaDev_attach__SWIG_2(swigCPtr, this, PistaEventHandler.getCPtr(h), h);
  }

  public void attach(PistaCommHandler comm) {
    PISTAXJNI.PistaDev_attach__SWIG_3(swigCPtr, this, PistaCommHandler.getCPtr(comm), comm);
  }

  public PistaDataPacket poll(int sid) {
    long cPtr = PISTAXJNI.PistaDev_poll(swigCPtr, this, sid);
    return (cPtr == 0) ? null : new PistaDataPacket(cPtr, false);
  }

  public int dump(int flags) {
    return PISTAXJNI.PistaDev_dump(swigCPtr, this, flags);
  }

  public pista_dev_inst c_inst() {
    long cPtr = PISTAXJNI.PistaDev_c_inst(swigCPtr, this);
    return (cPtr == 0) ? null : new pista_dev_inst(cPtr, false);
  }

  public int sendEvent(PistaDataPacket cxxpkt) {
    return PISTAXJNI.PistaDev_sendEvent(swigCPtr, this, PistaDataPacket.getCPtr(cxxpkt), cxxpkt);
  }

}
