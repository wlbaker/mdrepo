/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.12
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package org.pistax;

public class pista_data_packet {
  private transient long swigCPtr;
  protected transient boolean swigCMemOwn;

  protected pista_data_packet(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(pista_data_packet obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        PISTAXJNI.delete_pista_data_packet(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public void setTm(long value) {
    PISTAXJNI.pista_data_packet_tm_set(swigCPtr, this, value);
  }

  public long getTm() {
    return PISTAXJNI.pista_data_packet_tm_get(swigCPtr, this);
  }

  public void setSource_name(String value) {
    PISTAXJNI.pista_data_packet_source_name_set(swigCPtr, this, value);
  }

  public String getSource_name() {
    return PISTAXJNI.pista_data_packet_source_name_get(swigCPtr, this);
  }

  public void setStream_id(int value) {
    PISTAXJNI.pista_data_packet_stream_id_set(swigCPtr, this, value);
  }

  public int getStream_id() {
    return PISTAXJNI.pista_data_packet_stream_id_get(swigCPtr, this);
  }

  public void setPayload_sz(int value) {
    PISTAXJNI.pista_data_packet_payload_sz_set(swigCPtr, this, value);
  }

  public int getPayload_sz() {
    return PISTAXJNI.pista_data_packet_payload_sz_get(swigCPtr, this);
  }

  public void setPayload(SWIGTYPE_p_void value) {
    PISTAXJNI.pista_data_packet_payload_set(swigCPtr, this, SWIGTYPE_p_void.getCPtr(value));
  }

  public SWIGTYPE_p_void getPayload() {
    long cPtr = PISTAXJNI.pista_data_packet_payload_get(swigCPtr, this);
    return (cPtr == 0) ? null : new SWIGTYPE_p_void(cPtr, false);
  }

  public void setNext_stream(pista_data_packet value) {
    PISTAXJNI.pista_data_packet_next_stream_set(swigCPtr, this, pista_data_packet.getCPtr(value), value);
  }

  public pista_data_packet getNext_stream() {
    long cPtr = PISTAXJNI.pista_data_packet_next_stream_get(swigCPtr, this);
    return (cPtr == 0) ? null : new pista_data_packet(cPtr, false);
  }

  public pista_data_packet() {
    this(PISTAXJNI.new_pista_data_packet(), true);
  }

}