/*
 * cvar_trace.h
 *
 * Tracing and logging utilities.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _CVAR_TRACE_H
#define _CVAR_TRACE_H

#include <stdio.h>
#include <stdlib.h>

#define cvar_log_error(fmt, ...) fprintf(stderr, fmt ".\n", ##__VA_ARGS__)

#ifdef DEBUG

#define cvar_trace(fmt, ...) fprintf(stdout, "%s: %d: %s: " fmt ".\n",\
		__FILE__, __LINE__, __func__, ##__VA_ARGS__)

/* Tracing functions */
static inline void cvar_tracebuf(const void *buff, unsigned int len)
{
	char *buf = (char *)buff;
	unsigned int i;
	char *sbuf = NULL;

	if (len == 0)
		return;

	sbuf = (char *)malloc(2 + 2*len + 1);
	if (sbuf == NULL) {
		fprintf(stdout, "out of memory. unable to print "
				"buffer in hex.");
		return;
	}

	sbuf[2*len + 2] = '\0';

	sprintf(sbuf, "%s", "0x");

	for (i = 0; i < len; i++) {
		if (((buf[i] & 0xF0) >> 4) < 0x0A)
			sprintf(sbuf + 2 + 2*i, "%c", '0' +
					(int)((buf[i] & 0xF0) >> 4));
		else
			sprintf(sbuf + 2 + 2*i, "%c", 'a' +
					(char) (((buf[i] & 0xF0) >> 4) - 0x0A));

		if ((buf[i] & 0x0F) < 0x0A)
			sprintf(sbuf + 2 + 2*i + 1, "%c", '0' +
					(int)(buf[i] & 0x0F));
		else
			sprintf(sbuf + 2 + 2*i + 1, "%c", 'a' +
					(char) ((buf[i] & 0x0F) - 0x0A));
	}

	fprintf(stdout, "%s.\n", sbuf);
	free(sbuf);

	return;
}

#else

#define cvar_trace(fmt, ...)

static inline void cvar_tracebuf(const void *buff, unsigned int len)
{
	return;
}

#endif /* DEBUG */

#endif /* _CVAR_TRACE_H */
