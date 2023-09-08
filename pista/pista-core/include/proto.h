
#ifndef PISTA_PROTO_H
#define PISTA_PROTO_H

#include "pista.h"

/**
 * @file
 *
 * Header file containing API function prototypes.
 */

/*--- backend.c -------------------------------------------------------------*/

PISTA_API int pista_init(struct pista_context **ctx);
PISTA_API int pista_exit(struct pista_context *ctx);

/*--- log.c -----------------------------------------------------------------*/

typedef int (*pista_log_callback)(void *cb_data, int loglevel,
				const char *format, va_list args);

PISTA_API int pista_log_loglevel_set(int loglevel);
PISTA_API int pista_log_loglevel_get(void);
PISTA_API int pista_log_callback_set(pista_log_callback cb, void *cb_data);
PISTA_API int pista_log_callback_set_default(void);
PISTA_API int pista_log_logdomain_set(const char *logdomain);
PISTA_API char *pista_log_logdomain_get(void);

/*--- device.c --------------------------------------------------------------*/

#ifdef DISABLE_WLB
PISTA_API int pista_dev_channel_name_set(const struct pista_dev_inst *sdi,
		int channelnum, const char *name);
PISTA_API int pista_dev_channel_enable(const struct pista_dev_inst *sdi, int channelnum,
		bool state);
PISTA_API int pista_dev_trigger_set(const struct pista_dev_inst *sdi, int channelnum,
		const char *trigger);
PISTA_API bool pista_dev_has_option(const struct pista_dev_inst *sdi, int key);
PISTA_API GSList *pista_dev_list(const struct pista_dev_driver *driver);
PISTA_API int pista_dev_clear(const struct pista_dev_driver *driver);
PISTA_API int pista_dev_open(struct pista_dev_inst *sdi);
PISTA_API int pista_dev_close(struct pista_dev_inst *sdi);
#endif

/*--- hwdriver.c ------------------------------------------------------------*/

#ifdef DISABLE_WLB
PISTA_API struct pista_dev_driver **pista_driver_list(void);
PISTA_API int pista_driver_init(struct pista_context *ctx,
		struct pista_dev_driver *driver);
PISTA_API GSList *pista_driver_scan(struct pista_dev_driver *driver, GSList *options);
PISTA_API int pista_dump(
		const struct pista_dev_inst *sdi,
		pista_dump_flags flags );
PISTA_API int pista_config_get(const struct pista_dev_driver *driver,
		const struct pista_dev_inst *sdi,
		const struct pista_channel_group *cg,
		int key, GVariant **data);
PISTA_API int pista_config_set(const struct pista_dev_inst *sdi,
		const struct pista_channel_group *cg,
		int key, GVariant *data);
PISTA_API int pista_config_commit(const struct pista_dev_inst *sdi);
PISTA_API int pista_config_list(const struct pista_dev_driver *driver,
		const struct pista_dev_inst *sdi,
		const struct pista_channel_group *cg,
		int key, GVariant **data);
PISTA_API const struct pista_config_info *pista_config_info_get(int key);
PISTA_API const struct pista_config_info *pista_config_info_name_get(const char *optname);
#endif

/*--- session.c -------------------------------------------------------------*/

#ifdef DISABLE_WLB
typedef void (*pista_datafeed_callback)(const struct pista_dev_inst *sdi,
		const struct pista_datafeed_packet *packet, void *cb_data);

/* Session setup */
PISTA_API int pista_session_load(const char *filename);
PISTA_API struct pista_session *pista_session_new(void);
PISTA_API int pista_session_destroy(void);
PISTA_API int pista_session_dev_remove_all(void);
PISTA_API int pista_session_dev_add(const struct pista_dev_inst *sdi);
PISTA_API int pista_session_dev_list(GSList **devlist);

/* Datafeed setup */
PISTA_API int pista_session_datafeed_callback_remove_all(void);
PISTA_API int pista_session_datafeed_callback_add(pista_datafeed_callback cb,
		void *cb_data);

/* Session control */
PISTA_API int pista_session_start(void);
PISTA_API int pista_session_run(void);
PISTA_API int pista_session_stop(void);
PISTA_API int pista_session_save(const char *filename, const struct pista_dev_inst *sdi,
		unsigned char *buf, int unitsize, int units);
PISTA_API int pista_session_save_init(const char *filename, uint64_t samplerate,
		char **channels);
PISTA_API int pista_session_append(const char *filename, unsigned char *buf,
		int unitsize, int units);
PISTA_API int pista_session_source_add(int fd, int events, int timeout,
		pista_receive_data_callback cb, void *cb_data);
PISTA_API int pista_session_source_add_pollfd(GPollFD *pollfd, int timeout,
		pista_receive_data_callback cb, void *cb_data);
PISTA_API int pista_session_source_add_channel(GIOChannel *channel, int events,
		int timeout, pista_receive_data_callback cb, void *cb_data);
PISTA_API int pista_session_source_remove(int fd);
PISTA_API int pista_session_source_remove_pollfd(GPollFD *pollfd);
PISTA_API int pista_session_source_remove_channel(GIOChannel *channel);
#endif

/*--- input/input.c ---------------------------------------------------------*/

PISTA_API struct pista_input_format **pista_input_list(void);

/*--- output/output.c -------------------------------------------------------*/

#ifdef DISABLE_WLB
PISTA_API struct pista_output_format **pista_output_list(void);
PISTA_API struct pista_output *pista_output_new(struct pista_output_format *of,
		GHashTable *params, const struct pista_dev_inst *sdi);
PISTA_API int pista_output_send(struct pista_output *o,
		const struct pista_datafeed_packet *packet, GString **out);
PISTA_API int pista_output_free(struct pista_output *o);
#endif

/*--- strutil.c -------------------------------------------------------------*/

PISTA_API char *pista_si_string_u64(uint64_t x, const char *unit);
PISTA_API char *pista_samplerate_string(uint64_t samplerate);
PISTA_API char *pista_period_string(uint64_t frequency);
PISTA_API char *pista_voltage_string(uint64_t v_p, uint64_t v_q);
PISTA_API char **pista_parse_triggerstring(const struct pista_dev_inst *sdi,
		const char *triggerstring);
PISTA_API int pista_parse_sizestring(const char *sizestring, uint64_t *size);
PISTA_API uint64_t pista_parse_timestring(const char *timestring);
PISTA_API bool pista_parse_boolstring(const char *boolstring);
PISTA_API int pista_parse_period(const char *periodstr, uint64_t *p, uint64_t *q);
PISTA_API int pista_parse_voltage(const char *voltstr, uint64_t *p, uint64_t *q);

/*--- version.c -------------------------------------------------------------*/

PISTA_API int pista_package_version_major_get(void);
PISTA_API int pista_package_version_minor_get(void);
PISTA_API int pista_package_version_micro_get(void);
PISTA_API const char *pista_package_version_string_get(void);

PISTA_API int pista_lib_version_current_get(void);
PISTA_API int pista_lib_version_revision_get(void);
PISTA_API int pista_lib_version_age_get(void);
PISTA_API const char *pista_lib_version_string_get(void);

/*--- error.c ---------------------------------------------------------------*/

PISTA_API const char *pista_strerror(int error_code);
PISTA_API const char *pista_strerror_name(int error_code);

#endif
