/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.2
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package idea.jljack;

public class ExoDriverJNI {
  public final static native double LJUSB_LIBRARY_VERSION_get();
  public final static native int LJ_VENDOR_ID_get();
  public final static native int UE9_PRODUCT_ID_get();
  public final static native int U3_PRODUCT_ID_get();
  public final static native int U6_PRODUCT_ID_get();
  public final static native int U12_PRODUCT_ID_get();
  public final static native int BRIDGE_PRODUCT_ID_get();
  public final static native int T7_PRODUCT_ID_get();
  public final static native int DIGIT_PRODUCT_ID_get();
  public final static native int UNUSED_PRODUCT_ID_get();
  public final static native int UE9_PIPE_EP1_OUT_get();
  public final static native int UE9_PIPE_EP1_IN_get();
  public final static native int UE9_PIPE_EP2_IN_get();
  public final static native int U3_PIPE_EP1_OUT_get();
  public final static native int U3_PIPE_EP2_IN_get();
  public final static native int U3_PIPE_EP3_IN_get();
  public final static native int U6_PIPE_EP1_OUT_get();
  public final static native int U6_PIPE_EP2_IN_get();
  public final static native int U6_PIPE_EP3_IN_get();
  public final static native int U12_PIPE_EP1_IN_get();
  public final static native int U12_PIPE_EP2_OUT_get();
  public final static native int U12_PIPE_EP0_get();
  public final static native int BRIDGE_PIPE_EP1_OUT_get();
  public final static native int BRIDGE_PIPE_EP2_IN_get();
  public final static native int BRIDGE_PIPE_EP3_IN_get();
  public final static native int T7_PIPE_EP1_OUT_get();
  public final static native int T7_PIPE_EP2_IN_get();
  public final static native int T7_PIPE_EP3_IN_get();
  public final static native int DIGIT_PIPE_EP1_OUT_get();
  public final static native int DIGIT_PIPE_EP2_IN_get();
  public final static native float LJUSB_GetLibraryVersion();
  public final static native long LJUSB_GetDevCount(long jarg1);
  public final static native long LJUSB_GetDevCounts(long jarg1, long jarg2, long jarg3);
  public final static native int LJUSB_OpenAllDevices(long jarg1, long jarg2, long jarg3);
  public final static native long LJUSB_OpenDevice(long jarg1, long jarg2, long jarg3);
  public final static native boolean LJUSB_ResetConnection(long jarg1);
  public final static native long LJUSB_Write(long jarg1, long jarg2, long jarg3);
  public final static native long LJUSB_Read(long jarg1, long jarg2, long jarg3);
  public final static native long LJUSB_Stream(long jarg1, long jarg2, long jarg3);
  public final static native long LJUSB_WriteTO(long jarg1, long jarg2, long jarg3, long jarg4);
  public final static native long LJUSB_ReadTO(long jarg1, long jarg2, long jarg3, long jarg4);
  public final static native long LJUSB_StreamTO(long jarg1, long jarg2, long jarg3, long jarg4);
  public final static native void LJUSB_CloseDevice(long jarg1);
  public final static native boolean LJUSB_IsHandleValid(long jarg1);
  public final static native int LJUSB_GetDeviceDescriptorReleaseNumber(long jarg1);
  public final static native long LJUSB_GetHIDReportDescriptor(long jarg1, long jarg2, long jarg3);
  public final static native long LJUSB_BulkRead(long jarg1, short jarg2, long jarg3, long jarg4);
  public final static native long LJUSB_BulkWrite(long jarg1, short jarg2, long jarg3, long jarg4);
  public final static native boolean LJUSB_AbortPipe(long jarg1, long jarg2);
}