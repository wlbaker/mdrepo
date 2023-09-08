
/** @file
  * @internal
  */

#ifndef PISTA_PISTA_INTERNAL_H
#define PISTA_PISTA_INTERNAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdint.h>
#include "config.h" /* Needed for HAVE_LIBUSB_1_0 and others. */
#ifdef HAVE_LIBUSB_1_0
#include <libusb.h>
#endif
#ifdef HAVE_LIBSERIALPORT
#include <libserialport.h>
#endif

#include "pista.h"

#include <stdlib.h>
#define PISTA_MALLOC malloc
#define PISTA_FREE   free


#ifdef _WIN32
#else
#include <pthread.h>
#endif

/*--- log.c -----------------------------------------------------------------*/

typedef int (*pista_log_callback)(void *cb_data, int loglevel,
                const char *format, va_list args);

PISTA_API int pista_log_loglevel_set(int loglevel);
PISTA_API int pista_log_loglevel_get(void);
PISTA_API int pista_log_callback_set(pista_log_callback cb, void *cb_data);
PISTA_API int pista_log_callback_set_default(void);
PISTA_API int pista_log_logdomain_set(const char *logdomain);
PISTA_API char *pista_log_logdomain_get(void);

/*--- desc mgmt -----------------------------------------------------------------*/

// PISTA_PRIV void pista_set_desc(struct pista_item_desc *pd, const char *loc, const char *code, const char *desc, const char *unit, int subtyp, int offset, int count);
PISTA_PRIV void pista_dump_long( long *src, int count );
PISTA_PRIV void pista_dump_int( int *src, int count );
PISTA_PRIV void pista_dump_float( float *src, int count );
// PISTA_PRIV void pista_dump_desc( struct pista_item_desc *desc, int ndesc, void *payload );
// PISTA_PRIV void pista_dump_jdesc( struct pista_item_desc *desc, int ndesc, void *payload );
// PISTA_PRIV struct pista_stream_desc *pista_stream_from_pkt(struct pista_data_packet *pkt );

PISTA_PRIV void pista_discovery_notify(struct pista_discovery_info *pdi );


/**
 * @file
 *
 * libsigrok private header file, only to be used internally.
 */

/*--- Macros ----------------------------------------------------------------*/

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
#endif

#ifndef ARRAY_AND_SIZE
#define ARRAY_AND_SIZE(a) (a), ARRAY_SIZE(a)
#endif

/**
 * Read a 8 bits integer out of memory.
 * @param x a pointer to the input memory
 * @return the corresponding integer
 */
#define R8(x)     ((unsigned)((const uint8_t*)(x))[0])

/**
 * Read a 16 bits big endian integer out of memory.
 * @param x a pointer to the input memory
 * @return the corresponding integer
 */
#define RB16(x)  (((unsigned)((const uint8_t*)(x))[0] <<  8) |  \
                   (unsigned)((const uint8_t*)(x))[1])

/**
 * Read a 16 bits little endian integer out of memory.
 * @param x a pointer to the input memory
 * @return the corresponding integer
 */
#define RL16(x)  (((unsigned)((const uint8_t*)(x))[1] <<  8) | \
                   (unsigned)((const uint8_t*)(x))[0])

/**
 * Read a 32 bits big endian integer out of memory.
 * @param x a pointer to the input memory
 * @return the corresponding integer
 */
#define RB32(x)  (((unsigned)((const uint8_t*)(x))[0] << 24) | \
                  ((unsigned)((const uint8_t*)(x))[1] << 16) |  \
                  ((unsigned)((const uint8_t*)(x))[2] <<  8) |  \
                   (unsigned)((const uint8_t*)(x))[3])

/**
 * Read a 32 bits little endian integer out of memory.
 * @param x a pointer to the input memory
 * @return the corresponding integer
 */
#define RL32(x)  (((unsigned)((const uint8_t*)(x))[3] << 24) | \
                  ((unsigned)((const uint8_t*)(x))[2] << 16) |  \
                  ((unsigned)((const uint8_t*)(x))[1] <<  8) |  \
                   (unsigned)((const uint8_t*)(x))[0])

/**
 * Write a 8 bits integer to memory.
 * @param p a pointer to the output memory
 * @param x the input integer
 */
#define W8(p, x)    do { ((uint8_t*)(p))[0] = (uint8_t) (x);      } while(0)

/**
 * Write a 16 bits integer to memory stored as big endian.
 * @param p a pointer to the output memory
 * @param x the input integer
 */
#define WB16(p, x)  do { ((uint8_t*)(p))[1] = (uint8_t) (x);      \
                         ((uint8_t*)(p))[0] = (uint8_t)((x)>>8);  } while(0)

/**
 * Write a 16 bits integer to memory stored as little endian.
 * @param p a pointer to the output memory
 * @param x the input integer
 */
#define WL16(p, x)  do { ((uint8_t*)(p))[0] = (uint8_t) (x);      \
                         ((uint8_t*)(p))[1] = (uint8_t)((x)>>8);  } while(0)

/**
 * Write a 32 bits integer to memory stored as big endian.
 * @param p a pointer to the output memory
 * @param x the input integer
 */
#define WB32(p, x)  do { ((uint8_t*)(p))[3] = (uint8_t) (x);      \
                         ((uint8_t*)(p))[2] = (uint8_t)((x)>>8);  \
                         ((uint8_t*)(p))[1] = (uint8_t)((x)>>16); \
                         ((uint8_t*)(p))[0] = (uint8_t)((x)>>24); } while(0)

/**
 * Write a 32 bits integer to memory stored as little endian.
 * @param p a pointer to the output memory
 * @param x the input integer
 */
#define WL32(p, x)  do { ((uint8_t*)(p))[0] = (uint8_t) (x);      \
                         ((uint8_t*)(p))[1] = (uint8_t)((x)>>8);  \
                         ((uint8_t*)(p))[2] = (uint8_t)((x)>>16); \
                         ((uint8_t*)(p))[3] = (uint8_t)((x)>>24); } while(0)

/* Portability fixes for FreeBSD. */
#ifdef __FreeBSD__
#define LIBUSB_CLASS_APPLICATION 0xfe
#define libusb_handle_events_timeout_completed(ctx, tv, c) \
	libusb_handle_events_timeout(ctx, tv)
#endif

struct pista_context {
    struct pista_dev_driver *driver_head;
    struct pista_discovery_service *service_head;
    bool run_ticker;

#ifdef HAVE_LIBUSB_1_0
	libusb_context *libusb_ctx;
	bool usb_source_present;
#ifdef _WIN32
	bool usb_thread_running;
	HANDLE usb_event;
	pista_receive_data_callback usb_cb;
	void *usb_cb_data;
#else
#endif

#endif

#ifdef _WIN32
#else
    pthread_t ticker_thread;
#endif

};

#ifdef HAVE_LIBUSB_1_0
/** USB device instance */
struct pista_usb_dev_inst {
	/** USB bus */
	uint8_t bus;
	/** Device address on USB bus */
	uint8_t address;
	/** libusb device handle */
	struct libusb_device_handle *devhdl;
};
#endif

#ifdef HAVE_LIBSERIALPORT
#define SERIAL_PARITY_NONE SP_PARITY_NONE
#define SERIAL_PARITY_EVEN SP_PARITY_EVEN
#define SERIAL_PARITY_ODD  SP_PARITY_ODD
struct pista_serial_dev_inst {
	/** Port name, e.g. '/dev/tty42'. */
	char *port;
	/** Comm params for serial_set_paramstr(). */
	char *serialcomm;
	/** Port is non-blocking. */
	int nonblocking;
	/** libserialport port handle */
	struct sp_port *data;
	/** libserialport event set */
	struct sp_event_set *event_set;
	/** FILE for event polling */
	int *pollfds;
};
#endif

/*
struct pista_usbtmc_dev_inst {
	char *device;
	int fd;
};

struct drv_context {
	struct pista_context *pista_ctx;
	void *instances; // GSList
};
*/

/**
 * Structure extensions are part of C11...maybe, but to active the feature for gcc you must use the flag
 * -fms-extensions.  All private structures implemented by drivers, devices, and services 
 * should extend an existing structure and add their own fields.  The method to do this is by adding onf of the
 * declarations as the first member of the structure:
 *
 * PISTA_SERVICE_PRIVATE
 * PISTA_DRIVER_PRIVATE
 * PISTA_DEVICE_PRIVATE
 *
 * See also: http://modelingwithdata.org/pdfs/113-composition.pdf
 */
struct pista_device_private {
    struct pista_dev_driver *next;   /// The next _driver_ in a linked list of drivers
    struct pista_dev_inst   *first;  /// The first _device_ in a linked list of devices for this driver 
};
            
struct pista_service_priv {
    struct pista_discovery_service *next;   /// The next _service_ in a linked list of services
    
	discoveryfunc_t discovery_callback;     /// All services probably need a callback handler
	void *discovery_priv;                   /// private client data passed to callback handler
};

#define PISTA_SERVICE_PRIVATE struct pista_service_priv;
#define PISTA_DRIVER_PRIVATE struct pista_driver_priv;
// #define PISTA_DEVICE_PRIVATE struct pista_device_priv;

/*--- log.c -----------------------------------------------------------------*/

PISTA_API int pista_log(int loglevel, const char *format, ...);
PISTA_API int pista_spew(const char *format, ...);
PISTA_API int pista_dbg(const char *format, ...);
PISTA_API int pista_info(const char *format, ...);
PISTA_API int pista_warn(const char *format, ...);
PISTA_API int pista_err(const char *format, ...);


/* Message logging helpers with subsystem-specific prefix string. */
#ifndef NO_LOG_WRAPPERS

// WLB
#ifdef ZERO_IGNORE_DONTKNOW_WIN32
#define pista_log(l, s, ...) pista_log(l, "%s: " s, LOG_PREFIX, __VA_ARGS__ )
#define pista_spew(s, ...) pista_spew("%s: " s, LOG_PREFIX, __VA_ARGS__ )
#define pista_dbg(s, ...) pista_dbg("%s: " s, LOG_PREFIX, __VA_ARGS__ )
#define pista_info(s, ...) pista_info("%s: " s, LOG_PREFIX, __VA_ARGS__ )
#define pista_warn(s, ...) pista_warn("%s: " s, LOG_PREFIX, __VA_ARGS__ )
#define pista_err(s, ...) pista_err("%s: " s, LOG_PREFIX, __VA_ARGS__ )
#else
#define pista_log(l, s, args...) pista_log(l, "%s: " s, LOG_PREFIX, ## args)
#define pista_spew(s, args...) pista_spew("%s: " s, LOG_PREFIX, ## args)
#define pista_dbg(s, args...) pista_dbg("%s: " s, LOG_PREFIX, ## args)
#define pista_info(s, args...) pista_info("%s: " s, LOG_PREFIX, ## args)
#define pista_warn(s, args...) pista_warn("%s: " s, LOG_PREFIX, ## args)
#define pista_err(s, args...) pista_err("%s: " s, LOG_PREFIX, ## args)
#endif

#endif

/*--- device.c --------------------------------------------------------------*/

/** Values for the changes argument of pista_dev_driver.config_channel_set. */
enum {
	/** The enabled state of the channel has been changed. */
	PISTA_CHANNEL_SET_ENABLED = 1 << 0,
	/** The trigger setup of the channel has been changed. */
	PISTA_CHANNEL_SET_TRIGGER = 1 << 1,
};

PISTA_PRIV struct pista_channel *pista_channel_new(int index, int type,
		bool enabled, const char *name);

/* Generic device instances */
PISTA_PRIV struct pista_dev_inst *pista_dev_inst_new(int index, int status,
		const char *vendor, const char *model, const char *version);
PISTA_PRIV void pista_dev_inst_free(struct pista_dev_inst *sdi);

#ifdef HAVE_LIBUSB_1_0
/* USB-specific instances */
PISTA_PRIV struct pista_usb_dev_inst *pista_usb_dev_inst_new(uint8_t bus,
		uint8_t address, struct libusb_device_handle *hdl);
PISTA_PRIV void pista_usb_dev_inst_free(struct pista_usb_dev_inst *usb);
#endif

#ifdef HAVE_LIBSERIALPORT
/* Serial-specific instances */
PISTA_PRIV struct pista_serial_dev_inst *pista_serial_dev_inst_new(const char *port,
		const char *serialcomm);
PISTA_PRIV void pista_serial_dev_inst_free(struct pista_serial_dev_inst *serial);
#endif

/* USBTMC-specific instances */
PISTA_PRIV struct pista_usbtmc_dev_inst *pista_usbtmc_dev_inst_new(const char *device);
PISTA_PRIV void pista_usbtmc_dev_inst_free(struct pista_usbtmc_dev_inst *usbtmc);

/*--- hwdriver.c ------------------------------------------------------------*/

#ifdef DISABLED_WLB
PISTA_PRIV void pista_hw_cleanup_all(void);
PISTA_PRIV struct pista_config *pista_config_new(int key, GVariant *data);
PISTA_PRIV void pista_config_free(struct pista_config *src);
PISTA_PRIV int pista_source_remove(int fd);
PISTA_PRIV int pista_source_add(int fd, int events, int timeout,
		pista_receive_data_callback cb, void *cb_data);
#endif



/*--- std.c -----------------------------------------------------------------*/

typedef int (*dev_close_callback)(struct pista_dev_inst *sdi);
typedef void (*std_dev_clear_callback)(void *priv);

PISTA_PRIV int std_init(struct pista_context *pista_ctx, struct pista_dev_driver *di,
		const char *prefix);
#ifdef HAVE_LIBSERIALPORT
PISTA_PRIV int std_serial_dev_open(struct pista_dev_inst *sdi);
PISTA_PRIV int std_serial_dev_acquisition_stop(struct pista_dev_inst *sdi,
		void *cb_data, dev_close_callback dev_close_fn,
		struct pista_serial_dev_inst *serial, const char *prefix);
#endif
PISTA_PRIV int std_session_send_df_header(const struct pista_dev_inst *sdi,
		const char *prefix);
PISTA_PRIV int std_dev_clear(const struct pista_dev_driver *driver,
		std_dev_clear_callback clear_private);
PISTA_PRIV int std_serial_dev_close(struct pista_dev_inst *sdi);

/*--- strutil.c 
// WLB: not replacing funcs for compatibility right now
PISTA_PRIV int pista_atol(const char *str, long *ret);
PISTA_PRIV int pista_atoi(const char *str, int *ret);
PISTA_PRIV int pista_atod(const char *str, double *ret);
PISTA_PRIV int pista_atof(const char *str, float *ret);
PISTA_PRIV int pista_atof_ascii(const char *str, float *ret);
-------------------------------------------------------------*/

/*--- hardware/common/serial.c ----------------------------------------------*/

#ifdef HAVE_LIBSERIALPORT
enum {
	SERIAL_RDWR = 1,
	SERIAL_RDONLY = 2,
	SERIAL_NONBLOCK = 4,
};

typedef bool (*packet_valid_callback)(const uint8_t *buf);

// PISTA_PRIV GSList *pista_serial_find_usb(uint16_t vendor_id, uint16_t product_id);
#endif

#ifdef __cplusplus
}
#endif

#endif
