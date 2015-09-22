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
# Copyright 2009 Sun Microsystems, Inc.  All rights reserved.
# Use is subject to license terms.
#
# Exercises the indexed attribute of the fileset_pick() function. 
# 

set $dir=/tmp
set $cached=false
set $meandirwidth=20
set $nthreads=5
set $nfiles=10000
set $sync=false

define randvar name=$wrtiosize, min=512, round=512, type=gamma, mean=16k

define randvar name=$rdiosize, type=tabular, min=8k, round=1k, randtable =
{{85,   8k,  8k},
 {15,   8k, 64k}
}

define randvar name=$filesize, type=tabular, min=1k, randtable =
{{33,   1k,    1k},
 {21,   1k,    3k},
 {13,   3k,    5k},
 {10,   5k,   11k},
 {08,  11k,   21k},
 {05,  21k,   43k},
 {04,  43k,   85k},
 {03,  85k,  171k},
 {02, 171k,  341k},
 {01, 341k, 1707k}
}

define randvar name=$fileidx, type=gamma, min=0, gamma=100

define fileset name=bigfileset,path=$dir,size=$filesize,entries=$nfiles,dirwidth=$meandirwidth,prealloc=100,cached=$cached

define process name=netclient,instances=1
{
  thread name=fileuser,memsize=10m,instances=$nthreads
  {
    flowop openfile name=openfile1,filesetname=bigfileset,indexed=$fileidx,fd=1
    flowop openfile name=openfile2,filesetname=bigfileset,indexed=$fileidx,fd=2
    flowop openfile name=openfile3,filesetname=bigfileset,indexed=$fileidx,fd=3
    flowop appendfilerand name=appendfilerand1,iosize=$wrtiosize,fd=1
    flowop closefile name=closefile1,fd=1
    flowop readwholefile name=readfile1,iosize=$rdiosize,fd=2
    flowop readwholefile name=readfile2,iosize=$rdiosize,fd=3
    flowop closefile name=closefile2,fd=2
    flowop closefile name=closefile3,fd=3
  }
}

echo  "NetworkServer Version 1.1 personality successfully loaded"
