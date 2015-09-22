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
# Copyright 2007 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#

set $dir=/tmp
set $filesize=1g
set $nthreads=1
set $iosize=1m

define file name=largefile1,path=$dir,size=$filesize,prealloc,reuse
define file name=largefile2,path=$dir,size=$filesize,prealloc,reuse
define file name=largefile3,path=$dir,size=$filesize,prealloc,reuse
define file name=largefile4,path=$dir,size=$filesize,prealloc,reuse
define file name=largefile5,path=$dir,size=$filesize,prealloc,reuse

define process name=seqwrite,instances=1
{
  thread name=seqwrite1,memsize=10m,instances=$nthreads
  {
    flowop write name=seqwrite1,filename=largefile1,iosize=$iosize,directio
  }
  thread name=seqwrite2,memsize=10m,instances=$nthreads
  {
    flowop write name=seqwrite2,filename=largefile2,iosize=$iosize,directio
  }
  thread name=seqwrite3,memsize=10m,instances=$nthreads
  {
    flowop write name=seqwrite3,filename=largefile3,iosize=$iosize,directio
  }
  thread name=seqwrite4,memsize=10m,instances=$nthreads
  {
    flowop write name=seqwrite4,filename=largefile4,iosize=$iosize,directio
  }
  thread name=seqwrite5,memsize=10m,instances=$nthreads
  {
    flowop write name=seqwrite5,filename=largefile5,iosize=$iosize,directio
  }
}

echo  "Five Stream Direct Write Version 3.0 personality successfully loaded"
