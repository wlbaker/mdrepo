
/**
 * @mainpage Introduction
 *
 * Bindings for JAVA interface to [PISTA].
 *
 * This file defines the public API for the `libpista` communication library.
 * This API includes interfaces that can be used directly by client code.
 * <hr/>
 * @section pageTOC Content
 *   -# \ref Building
 *   -# \ref Installing
 *   -# \ref Using
 *   -# \ref Sample01
 *
 * @author William L Baker
 *
 * @copyright 2016. Licensed under the terms of the [BSD-2-Clause] license.
 *
 * [PISTA]:            https://softhorizons.com/IDEA/PISTA
 * [BSD-2-Clause]:     http://opensource.org/licenses/BSD-2-Clause
 *
 * @example Sample01.java
 * @page gencode Tutorial
 *
 * The message structures all begin with `ProtobufCMessageDescriptor *` which is
 * sufficient to allow them to be cast to `ProtobufCMessage`.
 *
 * For each message defined in a `.proto` file, we generate a number of
 */

/**
 * @defgroup grp_java_bindings JAVA Bindings
 *
 * Bindings for JAVA interface to [PISTA].
 *
 * <p>This JAVA interface is derived from the C++ bindings using SWIG.
 *
 */

/**
 * @package org.pista
 * @brief Low level Java bindings derived from the C interface 
 *
 */

/**
 * @package org.pistax
 * @brief Java bindings derived from the C++ interface.
 * 
 * These bindings will be simpler to use than bindings derived from the C interface, 
 * with no loss of functionality.
 * Since the C++ bindings are built on top of the C interface, usage of the two 
 * binding methods can be mixed. 
 *
 */

/**
 * 
* 
* @class org.pistax.PistaCl
* @brief The main interface for initializing and interacting with PISTA through Java.
* 
* @fn  org::pistax::PistaCl::driver( int idx )
* @brief Retrieve a reference to a published device driver by sequential index.
* @param idx Sequential driver index
* @return Reference to the driver.
*
* @fn  org::pistax::PistaCl::driver( String name )
* @brief Retrieve a reference to a published device driver by short name.
* @param name A short driver name previously publised by the device driver
* @return Reference to the driver.
*
* @fn org::pistax::PistaCl::driver_count
* @brief Count of published device drives used for sequential enumeration
* The number of drivers that have been associated with PISTA. 
* 
* @fn org::pistax::PistaCl::run
* @brief Start an internal thread to manage connected devices.
* 
*  Some devices require intermittant communication from the host to maintain connectivity.  
*  The <i>run</i> facility provides a thread for PISTA to manage this communication.  Alternatively, <i>tick</i>
*  can be used.
*  
*  @sa org::pistax::PistaCl::tick
* 
* @fn org::pistax::PistaCl::tick
* @brief Pass control to each of the active device drivers.
* 
*  Some devices require intermittant communication from the host to maintain connectivity.  
*  The <i>tick</i> facility provides a method to turn control over to PISTA for device management.  
*  Device drivers typically do not create an internal thread, and expect this function to be called
*  once/second.  This function should not be used if <i>run</i> has been called.
*  
*  @sa org::pistax::PistaCl::run
*  
* @fn org::pistax::PistaCl::stop
* @brief Stop the internal thread that was started by <i>run</i>
* @sa org::pistax::PistaCl::run
* 
* 
*/

