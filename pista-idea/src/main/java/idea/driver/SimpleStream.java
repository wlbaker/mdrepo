package idea.driver;

import java.text.DecimalFormat;
import java.text.NumberFormat;

/**
 *  2-channel stream on the U3 using the UD driver.
 *
 *  support@labjack.com
 */

import java.util.Arrays;

import com.labjack.LJUD;
import com.labjack.LJUDException;
import com.sun.jna.Memory;
import com.sun.jna.Pointer;
import com.sun.jna.ptr.DoubleByReference;
import com.sun.jna.ptr.IntByReference;

public class SimpleStream {

	public SimpleStream() {
	}

	private void handleLJUDException(LJUDException e) {
		e.printStackTrace();
		if (e.getError() > LJUD.Errors.MIN_GROUP_ERROR.getValue()) {
			System.exit(-1);
		}
	}

	// Displays warning message if there is one. Error values < 0 are warnings
	// and do not cause a LJUDException in the LJUD class.
	private void checkForWarning(int error) {
		Pointer errorStringPtr = new Memory(256);
		if (error < 0) {
			LJUD.errorToString(error, errorStringPtr);
			System.out.println("Warning: " + errorStringPtr.getString(0).trim());
		}
	}

	public void runExample() {
		try {
			int intErrorcode = 0;
			IntByReference refHandle = new IntByReference(0);
			int intHandle = 0;
			int i = 0, k = 0;
			IntByReference refIOType = new IntByReference(0);
			IntByReference refChannel = new IntByReference(0);
			DoubleByReference refValue = new DoubleByReference(0);
			DoubleByReference refBacklog = new DoubleByReference(0.0);
			DoubleByReference refZero = new DoubleByReference(0);
			double scanRate = 1000;
			long delayms = 1000;
			double numScans = 2 * scanRate * delayms / 1000; // 2x the expected
																// # of scans
			DoubleByReference refNumScansRequested = new DoubleByReference(0.0);
			double[] adblData = new double[2 * (int) numScans]; // Max buffer
																// size
																// (#channels*numScansRequested)
			IntByReference dummyInt = new IntByReference(0);
			DoubleByReference dummyDouble = new DoubleByReference(0.0);
			NumberFormat formatter = new DecimalFormat("0.000");
			Boolean isDone = false;

			// Read and display the UD and LJUDJava versions.
			System.out.println("UD Driver Version = " + formatter.format(LJUD.getDriverVersion()));

			// Open the first found LabJack U3.
			intErrorcode = LJUD.openLabJack(LJUD.Constants.dtU3, LJUD.Constants.ctUSB, "1", 1, refHandle);
			checkForWarning(intErrorcode);
			intHandle = refHandle.getValue();

			// Read and display the hardware version of this U3.
			LJUD.eGet(intHandle, LJUD.Constants.ioGET_CONFIG, LJUD.Constants.chHARDWARE_VERSION, refValue, 0);
			System.out.println("U3 Hardware Version = " + formatter.format(refValue.getValue()));

			// Read and display the firmware version of this U3.
			LJUD.eGet(intHandle, LJUD.Constants.ioGET_CONFIG, LJUD.Constants.chFIRMWARE_VERSION, refValue, 0);
			System.out.println("U3 Firmware Version = " + formatter.format(refValue.getValue()) + "\n");

			// Start by using the pin_configuration_reset IOType so that all
			// pin assignments are in the factory default condition.
			LJUD.ePut(intHandle, LJUD.Constants.ioPIN_CONFIGURATION_RESET, 0, 0, 0);

			// Configure FIO0 and FIO1 as analog, all else as digital. That
			// means we
			// will start from channel 0 and update all 16 flexible bits. We
			// will
			// pass a value of b0000000000000011 or d3.
			LJUD.ePut(intHandle, LJUD.Constants.ioPUT_ANALOG_ENABLE_PORT, 0, 3, 16);

			// Configure the stream:
			// Set the scan rate.
			LJUD.addRequest(intHandle, LJUD.Constants.ioPUT_CONFIG, LJUD.Constants.chSTREAM_SCAN_FREQUENCY, scanRate,
					0, 0);
			// Give the driver a 5 second buffer (scanRate * 2 channels * 5
			// seconds).
			LJUD.addRequest(intHandle, LJUD.Constants.ioPUT_CONFIG, LJUD.Constants.chSTREAM_BUFFER_SIZE,
					scanRate * 2 * 5, 0, 0);
			// Configure reads to retrieve whatever data is available without
			// waiting (wait mode LJ_swNONE). See comments below to change this
			// program to use LJ_swSLEEP mode.
			LJUD.addRequest(intHandle, LJUD.Constants.ioPUT_CONFIG, LJUD.Constants.chSTREAM_WAIT_MODE,
					LJUD.Constants.swSLEEP, 0, 0);
			// Define the scan list as AIN0 then AIN1.
			LJUD.addRequest(intHandle, LJUD.Constants.ioCLEAR_STREAM_CHANNELS, 0, 0, 0, 0);
			LJUD.addRequest(intHandle, LJUD.Constants.ioADD_STREAM_CHANNEL, 0, 0, 0, 0); // first
																							// method
																							// for
																							// single
																							// ended
																							// reading
																							// -
																							// AIN0
			LJUD.addRequest(intHandle, LJUD.Constants.ioADD_STREAM_CHANNEL_DIFF, 1, 0, 32, 0); // second
																								// method
																								// for
																								// single
																								// ended
																								// reading
																								// -
																								// AIN1

			// Execute the list of requests.
			LJUD.goOne(intHandle);

			// Get all the results just to check for errors.
			LJUD.getFirstResult(intHandle, refIOType, refChannel, refValue, dummyInt, dummyDouble);
			isDone = false;
			while (!isDone) {
				try {
					LJUD.getNextResult(intHandle, refIOType, refChannel, refValue, dummyInt, dummyDouble);
				} catch (LJUDException le) {
					if (le.getError() == LJUD.Errors.NO_MORE_DATA_AVAILABLE.getValue()) {
						isDone = true;
					} else {
						throw le;
					}
				}
			}

			// Start the stream.
			try {
				LJUD.eGet(intHandle, LJUD.Constants.ioSTART_STREAM, 0, refValue, 0);
			} catch (LJUDException le) {
				try {
					LJUD.eGet(intHandle, LJUD.Constants.ioSTOP_STREAM, 0, refZero, 0);
					LJUD.eGet(intHandle, LJUD.Constants.ioSTART_STREAM, 0, refValue, 0);
				} catch (LJUDException lee) {
					// ok to fail here
					System.err.println("stopStream request returned: " + lee );
					throw lee;
				}
			}

			// The actual scan rate is dependent on how the desired scan rate
			// divides into the LabJack clock. The actual scan rate is returned
			// in the value parameter from the start stream command.
			System.out.println("Actual Scan Rate = " + formatter.format(refValue.getValue()));
			System.out.println("Actual Sample Rate = " + formatter.format(2 * refValue.getValue()));

			// Read data
			while (System.in.available() <= 0) { // Loop will run until Enter is
													// hit

				// Since we are using wait mode LJ_swNONE, we will wait a
				// little,
				// then read however much data is available. Thus this delay
				// will
				// control how fast the program loops and how much data is read
				// each
				// loop. An alternative common method is to use wait mode
				// LJ_swSLEEP
				// where the stream read waits for a certain number of scans. In
				// such
				// a case you would not have a delay here, since the stream read
				// will
				// actually control how fast the program loops.
				//
				// To change this program to use sleep mode,
				// -change numScans to the actual number of scans desired per
				// read,
				// -change wait mode addrequest value to LJ_swSLEEP,
				// -comment out the following Sleep command.

				Thread.sleep(delayms); // Remove if using LJ_swSLEEP.

				// init array so we can easily tell if it has changed
				Arrays.fill(adblData, 9999.0);

				// Read the data. We will request twice the number we expect, to
				// make sure we get everything that is available.
				// Note that the array we pass must be sized to hold enough
				// SAMPLES,
				// and the Value we pass specifies the number of SCANS to read.
				refNumScansRequested.setValue(numScans);
				LJUD.eGet(intHandle, LJUD.Constants.ioGET_STREAM_DATA, LJUD.Constants.chALL_CHANNELS,
						refNumScansRequested, adblData);
				// The displays the number of scans that were actually read.
				System.out.println("\nIteration # " + i);
				System.out.println("Number read = " + refNumScansRequested.getValue());
				// This displays just the first scan.
				System.out.println("First scan = " + formatter.format(adblData[0]) + ", "
						+ formatter.format(adblData[1]));

				// Retrieve the current backlog. The UD driver retrieves stream
				// data
				// from the U3 in the background, but if the computer is too
				// slow
				// for some reason the driver might not be able to read the data
				// as
				// fast as the U3 is acquiring it, and thus there will be data
				// left
				// over in the U3 buffer.
				LJUD.eGet(intHandle, LJUD.Constants.ioGET_CONFIG, LJUD.Constants.chSTREAM_BACKLOG_COMM, refBacklog, 0);
				System.out.println("Comm Backlog = " + refBacklog.getValue());
				// Retrieve the current UD driver backlog. If this is growing,
				// then the application software is not pulling data from the UD
				// driver fast enough.
				LJUD.eGet(intHandle, LJUD.Constants.ioGET_CONFIG, LJUD.Constants.chSTREAM_BACKLOG_UD, refBacklog, 0);
				System.out.println("UD Backlog = " + refBacklog.getValue());

				i++;
			}

			// Stop the stream
			LJUD.eGet(intHandle, LJUD.Constants.ioSTOP_STREAM, 0, dummyDouble, 0);
		} catch (LJUDException le) {
			handleLJUDException(le);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		new SimpleStream().runExample();
	}

}