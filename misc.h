/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

#ifndef _FB_MISC_H
#define	_FB_MISC_H

#pragma ident	"%Z%%M%	%I%	%E% SMI"

#define	LOG_ERROR 0	/* a major error */
#define	LOG_ERROR1 1	/* also major error, but turn off error reporting */
			/* for now */
#define	LOG_INFO 2	/* some useful information. Default is to print */
#define	LOG_VERBOSE 3	/* four more levels of detailed information */
#define	LOG_DEBUG_SCRIPT 4
#define	LOG_DEBUG_IMPL 6
#define	LOG_DEBUG_NEVER 10
#define	LOG_FATAL 999	/* really bad error, shut down */
#define	LOG_DUMP 1001

#endif	/* _FB_MISC_H */
