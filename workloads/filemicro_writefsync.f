#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
#
# Copyright 2008 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# ident	"%Z%%M%	%I%	%E% SMI"

# Single-threaded writes to initially empty file.
# I/O size is set to 8KB. After every 1024 writes 
# (i.e., 8MB written) fsync is called.
# The run finishes after 1GB is fully written.

set $dir=/tmp
set $iosize=8k
set $writeiters=1024
set $fsynccount=128

set mode quit firstdone

define file name=bigfile,path=$dir,size=0,prealloc

define process name=filewriter,instances=1
{
  thread name=filewriterthread,memsize=10m,instances=1
  {
    flowop appendfile name=append-file,filename=bigfile,iosize=$iosize,iters=$writeiters
    flowop fsync name=sync-file
    flowop finishoncount name=finish,value=128,target=sync-file
  }
}

echo  "FileMicro-WriteFsync Version 2.1 personality successfully loaded"

run
