/**
 * @file intellivue_serial.h
 *
 * Constructs a serial request and checks serial responses
 * Philips IntelliVue MP70.
 *
 * Reference:
 * 		Data Export Interface Programming Guide
 * 		IntelliVue Patient Monitor
 * 		MP70
 *
 * 		Philips Reorder Part Number: 451261001426
 *
 * @author Michael Szwaja
 */
//=============================================================================
#ifndef DD_PHILIPS_INTELLIVUE_MP70_SIMULATOR_SRC_INTELLIVUE_SERIAL_H_
#define DD_PHILIPS_INTELLIVUE_MP70_SIMULATOR_SRC_INTELLIVUE_SERIAL_H_

typedef struct
{
	uint8_t* newrequest;
	int length;
} serialMessage;

class intellivue_serial
{
public:
  intellivue_serial();
  virtual ~intellivue_serial();

  /**
   * Creates a serial message to send out serial port.
   * @param buffer of bytes.
   * @param number of bytes in the buffer.
   */
  int construct_serial_msg(uint8_t buf[], int numbytes);

  /**
   * Returns the number of bytes in serial request message.
   * Precondition: construct_serial_msg() was called first.
   * @return int number of bytes
   */
  int get_numbytes();

  /**
   * Gets new serial request message.
   * Precondition: construct_serial_msg() was called first.
   * @return buffer of bytes
   */
  uint8_t* get_bytes();

  /**
   * Remove header, FCS, BOF, EOF, inserted 0x7D's. Uses FCS to check message.
   * Result should be the same as a UDP response.
   * @param pointer to buffer
   * @param number of bytes
   * @return status.
   */
  static int unwrap_serial_msg(uint8_t* buf, ssize_t* numbytes);

private:
  // Disallow use of implicitly generated member functions:
  intellivue_serial(const intellivue_serial& src);
  intellivue_serial &operator=(const intellivue_serial& rhs);

  /**
   * Generate a FCS table for the HDLC FCS.
   * The HDLC polynomial: x**0 + x**5 + x**12 + x**16 (0x8408).
   */
  static void create_fcs_table();

  /**
   * Calculate a new FCS given the current FCS and the new data.
   * @param frame check sequence
   * @param [in, out] return_fcs Return new FCS
   * @param pointer to char array
   * @param length of char array
   * @return new frame check sequence
   */
  static int pppfcs(
    const uint16_t fcs,
    uint16_t* return_fcs,
    uint8_t* cp,
    int len);

  serialMessage serialrequest;
};

#endif
