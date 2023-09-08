/** @file
  * Standard API helper functions.
  * @internal
  */

#include "pista.h"
#include "pista-internal.h"

#include <stdlib.h>

#define LOG_PREFIX "std"

/**
 * Standard pista_driver_init() API helper.
 *
 * This function can be used to simplify most driver's init() API callback.
 *
 * It creates a new 'struct drv_context' (drvc), assigns pista_ctx to it, and
 * then 'drvc' is assigned to the 'struct pista_dev_driver' (di) that is passed.
 *
 * @param pista_ctx The pista context to assign.
 * @param di The driver instance to use.
 * @param[in] prefix A driver-specific prefix string used for log messages.
 *
 * @return PISTA_OK upon success, PISTA_ERR_ARG upon invalid arguments, or
 *         PISTA_ERR_MALLOC upon memory allocation errors.
 */
PISTA_PRIV int std_init(struct pista_context *pista_ctx, struct pista_dev_driver *di,
		     const char *prefix)
{
//	struct drv_context *drvc;
//
//	if (!di) {
//		pista_err("%s: Invalid driver, cannot initialize.", prefix);
//		return PISTA_ERR_ARG;
//	}
//
//	if (!(drvc = PISTA_MALLOC(sizeof(struct drv_context)))) {
//		pista_err("%s: Driver context malloc failed.", prefix);
//		return PISTA_ERR_MALLOC;
//	}
//
//	drvc->pista_ctx = pista_ctx;
//	drvc->instances = NULL;
//	di->priv = drvc;

	return PISTA_OK;
}

/**
 * Standard API helper for sending an PISTA_DF_HEADER packet.
 *
 * This function can be used to simplify most driver's
 * dev_acquisition_start() API callback.
 *
 * @param sdi The device instance to use.
 * @param prefix A driver-specific prefix string used for log messages.
 * 		 Must not be NULL. An empty string is allowed.
 *
 * @return PISTA_OK upon success, PISTA_ERR_ARG upon invalid arguments, or
 *         PISTA_ERR upon other errors.
 */
PISTA_PRIV int std_session_send_df_header(const struct pista_dev_inst *sdi,
				       const char *prefix)
{
/*
	int ret;
	struct pista_datafeed_packet packet;
	struct pista_datafeed_header header;

	if (!prefix) {
		pista_err("Invalid prefix.");
		return PISTA_ERR_ARG;
	}

	pista_dbg("%s: Starting acquisition.", prefix);

	// Send header packet to the session bus.
	pista_dbg("%s: Sending PISTA_DF_HEADER packet.", prefix);
	packet.type = PISTA_DF_HEADER;
	packet.payload = (uint8_t *)&header;
	header.feed_version = 1;
	gettimeofday(&header.starttime, NULL);

	if ((ret = pista_session_send(sdi, &packet)) < 0) {
		pista_err("%s: Failed to send header packet: %d.", prefix, ret);
		return ret;
	}
*/
	return PISTA_OK;
}

#ifdef HAVE_LIBSERIALPORT


/**
 * Standard pista_session_stop() API helper.
 *
 * This function can be used to simplify most (serial port based) driver's
 * dev_acquisition_stop() API callback.
 *
 * @param sdi The device instance for which acquisition should stop.
 *            Must not be NULL.
 * @param cb_data Opaque 'cb_data' pointer. Must not be NULL.
 * @param dev_close_fn Function pointer to the driver's dev_close().
 *               	  Must not be NULL.
 * @param serial The serial device instance (struct serial_dev_inst *).
 *               Must not be NULL.
 * @param[in] prefix A driver-specific prefix string used for log messages.
 *               Must not be NULL. An empty string is allowed.
 *
 * @retval PISTA_OK Success.
 * @retval PISTA_ERR_ARG Invalid arguments.
 * @retval PISTA_ERR_DEV_CLOSED Device is closed.
 * @retval PISTA_ERR Other errors.
 */
PISTA_PRIV int std_serial_dev_acquisition_stop(struct pista_dev_inst *sdi,
			void *cb_data, dev_close_callback dev_close_fn,
			struct pista_serial_dev_inst *serial, const char *prefix)
{
/*
	int ret;
	struct pista_datafeed_packet packet;

	if (!prefix) {
		pista_err("Invalid prefix.");
		return PISTA_ERR_ARG;
	}

	if (sdi->status != PISTA_ST_ACTIVE) {
		pista_err("%s: Device inactive, can't stop acquisition.", prefix);
		return PISTA_ERR_DEV_CLOSED;
	}

	pista_dbg("%s: Stopping acquisition.", prefix);

	if ((ret = serial_source_remove(serial)) < 0) {
		pista_err("%s: Failed to remove source: %d.", prefix, ret);
		return ret;
	}

	if ((ret = dev_close_fn(sdi)) < 0) {
		pista_err("%s: Failed to close device: %d.", prefix, ret);
		return ret;
	}

	// Send PISTA_DF_END packet to the session bus.
	pista_dbg("%s: Sending PISTA_DF_END packet.", prefix);
	packet.type = PISTA_DF_END;
	packet.payload = NULL;
	if ((ret = pista_session_send(cb_data, &packet)) < 0) {
		pista_err("%s: Failed to send PISTA_DF_END packet: %d.", prefix, ret);
		return ret;
	}
*/
	return PISTA_OK;
}

#endif

/**
 * Standard driver dev_clear() helper.
 *
 * Clear driver, this means, close all instances.
 *
 * This function can be used to implement the dev_clear() driver API
 * callback. dev_close() is called before every pista_dev_inst is cleared.
 *
 * The only limitation is driver-specific device contexts (sdi->priv).
 * These are freed, but any dynamic allocation within structs stored
 * there cannot be freed.
 *
 * @param driver The driver which will have its instances released.
 * @param clear_private If not NULL, this points to a function called
 * with sdi->priv as argument. The function can then clear any device
 * instance-specific resources kept there. It must also clear the struct
 * pointed to by sdi->priv.
 *
 * @return PISTA_OK on success.
 */
PISTA_PRIV int std_dev_clear(const struct pista_dev_driver *driver,
		std_dev_clear_callback clear_private)
{
		pista_err("%s: std_dev_clear not implemented: %d.", "STD", -1);
		return -1;
	
#ifdef DISABLED_WLB
	struct drv_context *drvc;
	struct pista_dev_inst *sdi;
	GSList *l;
	int ret;

	if (!(drvc = driver->priv))
		/* Driver was never initialized, nothing to do. */
		return PISTA_OK;

	ret = PISTA_OK;
	for (l = drvc->instances; l; l = l->next) {
		if (!(sdi = l->data)) {
			ret = PISTA_ERR_BUG;
			continue;
		}
		if (driver->dev_close)
			driver->dev_close(sdi);

		if (sdi->conn) {
#ifdef HAVE_LIBSERIALPORT
			if (sdi->inst_type == PISTA_INST_SERIAL)
				pista_serial_dev_inst_free(sdi->conn);
#endif
#ifdef HAVE_LIBUSB_1_0
			if (sdi->inst_type == PISTA_INST_USB)
				pista_usb_dev_inst_free(sdi->conn);
#endif
		}
		if (clear_private)
			clear_private(sdi->priv);
		else
			PISTA_FREE(sdi->priv);
		pista_dev_inst_free(sdi);
	}

	g_slist_free(drvc->instances);
	drvc->instances = NULL;

	return ret;
#endif
}
