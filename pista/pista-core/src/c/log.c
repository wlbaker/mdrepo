#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "pista.h"
/** @cond PRIVATE */
#define NO_LOG_WRAPPERS
/** @endcond */
#include "pista-internal.h"

/**
 * @file
 *
 * Controlling the pista message logging functionality.
 */

/**
 * @defgroup grp_logging Logging
 *
 * Controlling the pista message logging functionality.
 *
 * @{
 */

/* Currently selected pista loglevel. Default: PISTA_LOG_WARN. */
static int cur_loglevel = PISTA_LOG_WARN; /* Show errors+warnings per default. */

/* Function prototype. */
static int pista_logv(void *cb_data, int loglevel, const char *format,
		   va_list args);

/* Pointer to the currently selected log callback. Default: pista_logv(). */
static pista_log_callback pista_log_cb = pista_logv;

/*
 * Pointer to private data that can be passed to the log callback.
 * This can be used (for example) by C++ GUIs to pass a "this" pointer.
 */
static void *pista_log_cb_data = NULL;

/* Log domain (a short string that is used as prefix for all messages). */
/** @cond PRIVATE */
#define LOGDOMAIN_MAXLEN 30
#define LOGDOMAIN_DEFAULT "sr: "
/** @endcond */
static char pista_log_domain[LOGDOMAIN_MAXLEN + 1] = LOGDOMAIN_DEFAULT;

/**
 * Set the pista loglevel.
 *
 * This influences the amount of log messages (debug messages, error messages,
 * and so on) pista will output. Using PISTA_LOG_NONE disables all messages.
 *
 * Note that this function itself will also output log messages. After the
 * loglevel has changed, it will output a debug message with PISTA_LOG_DBG for
 * example. Whether this message is shown depends on the (new) loglevel.
 *
 * @param loglevel The loglevel to set (PISTA_LOG_NONE, PISTA_LOG_ERR, PISTA_LOG_WARN,
 *                 PISTA_LOG_INFO, PISTA_LOG_DBG, or PISTA_LOG_SPEW).
 *
 * @return PISTA_OK upon success, PISTA_ERR_ARG upon invalid loglevel.
 *
 * @since 0.1.0
 */
PISTA_API int pista_log_loglevel_set(int loglevel)
{
	if (loglevel < PISTA_LOG_NONE || loglevel > PISTA_LOG_SPEW) {
		pista_err("Invalid loglevel %d.", loglevel);
		return PISTA_ERR_ARG;
	}

	cur_loglevel = loglevel;

	pista_dbg("pista loglevel set to %d.", loglevel);

	return PISTA_OK;
}

/**
 * Get the pista loglevel.
 *
 * @return The currently configured pista loglevel.
 *
 * @since 0.1.0
 */
PISTA_API int pista_log_loglevel_get(void)
{
	return cur_loglevel;
}

/**
 * Set the pista logdomain string.
 *
 * @param logdomain The string to use as logdomain for pista log
 *                  messages from now on. Must not be NULL. The maximum
 *                  length of the string is 30 characters (this does not
 *                  include the trailing NUL-byte). Longer strings are
 *                  silently truncated.
 *                  In order to not use a logdomain, pass an empty string.
 *                  The function makes its own copy of the input string, i.e.
 *                  the caller does not need to keep it around.
 *
 * @return PISTA_OK upon success, PISTA_ERR_ARG upon invalid logdomain.
 *
 * @since 0.1.0
 */
PISTA_API int pista_log_logdomain_set(const char *logdomain)
{
	if (!logdomain) {
		pista_err("log: %s: logdomain was NULL", __func__);
		return PISTA_ERR_ARG;
	}

	/* TODO: Error handling. */
	snprintf((char *)&pista_log_domain, LOGDOMAIN_MAXLEN, "%s", logdomain);

	pista_dbg("Log domain set to '%s'.", (const char *)&pista_log_domain);

	return PISTA_OK;
}

/**
 * Get the currently configured pista logdomain.
 *
 * @return A copy of the currently configured pista logdomain
 *         string. The caller is responsible for g_free()ing the string when
 *         it is no longer needed.
 *
 * @since 0.1.0
 */
PISTA_API char *pista_log_logdomain_get(void)
{
	return strdup((const char *)&pista_log_domain);
}

/**
 * Set the pista log callback to the specified function.
 *
 * @param cb Function pointer to the log callback function to use.
 *           Must not be NULL.
 * @param cb_data Pointer to private data to be passed on. This can be used by
 *                the caller to pass arbitrary data to the log functions. This
 *                pointer is only stored or passed on by pista, and is
 *                never used or interpreted in any way. The pointer is allowed
 *                to be NULL if the caller doesn't need/want to pass any data.
 *
 * @return PISTA_OK upon success, PISTA_ERR_ARG upon invalid arguments.
 *
 * @since 0.3.0
 */
PISTA_API int pista_log_callback_set(pista_log_callback cb, void *cb_data)
{
	if (!cb) {
		pista_err("log: %s: cb was NULL", __func__);
		return PISTA_ERR_ARG;
	}

	/* Note: 'cb_data' is allowed to be NULL. */

	pista_log_cb = cb;
	pista_log_cb_data = cb_data;

	return PISTA_OK;
}

/**
 * Set the pista log callback to the default built-in one.
 *
 * Additionally, the internal 'pista_log_cb_data' pointer is set to NULL.
 *
 * @return PISTA_OK upon success, a negative error code otherwise.
 *
 * @since 0.1.0
 */
PISTA_API int pista_log_callback_set_default(void)
{
	/*
	 * Note: No log output in this function, as it should safely work
	 * even if the currently set log callback is buggy/broken.
	 */
	pista_log_cb = pista_logv;
	pista_log_cb_data = NULL;

	return PISTA_OK;
}

static int pista_logv(void *cb_data, int loglevel, const char *format, va_list args)
{
	int ret;

	/* This specific log callback doesn't need the void pointer data. */
	(void)cb_data;

	/* Only output messages of at least the selected loglevel(s). */
	if (loglevel > cur_loglevel)
		return PISTA_OK; /* TODO? */

	if (pista_log_domain[0] != '\0')
		fprintf(stderr, "%s", pista_log_domain);
	ret = vfprintf(stderr, format, args);
	fprintf(stderr, "\n");

	return ret;
}

/** @private */
PISTA_API int pista_log(int loglevel, const char *format, ...)
{
	int ret;
	va_list args;

	va_start(args, format);
	ret = pista_log_cb(pista_log_cb_data, loglevel, format, args);
	va_end(args);

	return ret;
}

/** @private */
PISTA_API int pista_spew(const char *format, ...)
{
	int ret;
	va_list args;

	va_start(args, format);
	ret = pista_log_cb(pista_log_cb_data, PISTA_LOG_SPEW, format, args);
	va_end(args);

	return ret;
}

/** @private */
PISTA_API int pista_dbg(const char *format, ...)
{
	int ret;
	va_list args;

	va_start(args, format);
	ret = pista_log_cb(pista_log_cb_data, PISTA_LOG_DBG, format, args);
	va_end(args);

	return ret;
}

/** @private */
PISTA_API int pista_info(const char *format, ...)
{
	int ret;
	va_list args;

	va_start(args, format);
	ret = pista_log_cb(pista_log_cb_data, PISTA_LOG_INFO, format, args);
	va_end(args);

	return ret;
}

/** @private */
PISTA_API int pista_warn(const char *format, ...)
{
	int ret;
	va_list args;

	va_start(args, format);
	ret = pista_log_cb(pista_log_cb_data, PISTA_LOG_WARN, format, args);
	va_end(args);

	return ret;
}

/** @private */
PISTA_API int pista_err(const char *format, ...)
{
	int ret;
	va_list args;

	va_start(args, format);
	ret = pista_log_cb(pista_log_cb_data, PISTA_LOG_ERR, format, args);
	va_end(args);

	return ret;
}

/** @} */
