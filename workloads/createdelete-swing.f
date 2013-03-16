#
# GPL HEADER START
#
# This file is free software: you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This file is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see
# <http://www.gnu.org/licenses/>.
#
# GPL HEADER END
#
# Copyright 2012 Vasily Tarasov <tarasov@vasily.name>
#

#
# Create-Delete Swing personality creates $nfiles, then
# deletes them, then creates again, and so on until the
# time is up or a user interrupts the run.
#

set $path=/tmp
set $nfiles=10000

set $meanfilesize=500k
set $filesizegamma=0

# We want a flat directory (i.e., no subdirectories), so we set the
# mean directory equal to the number of files. In addition, we set
# gamma parameter for the directory width distribution to 0 to avoid
# deviation from the mean.

set $meandirwidth=$nfiles
set $dirgamma=0

# the rate should be set to an approriate value of required
# creates/sec. 0 means not limit on the create rate.

eventgen rate=0

define fileset name=manyfiles,
	       path=$path,
	       entries=$nfiles,
	       size=$meanfilesize,
	       filesizegamma=$filesizegamma,
	       dirwidth=$meandirwidth,
	       dirgamma=$dirgamma

# a composite flowop that creates a file, then writes
# to it, and closes a corresponding file descriptor.
# The rate of this flowop is also throttled
# by the eventgen rate (if set).

define flowop name=createandclose
{
	flowop createfile name=createfile,
			  filesetname=manyfiles,
			  fd=1
	flowop writewholefile name=whritewholefile,
			      filesetname=manyfiles,
			      fd=1
	flowop closefile name=closefile,
			 fd=1
	flowop eventlimit name=crlimit
}

# the process that creates $nfiles files,
# wakes up a deletion process, and then blocks.

define process name=crproc {
	thread name=crthread {
		flowop createandclose name=createandclose,
				      iters=$nfiles
		flowop wakeup name=wakeupdelproc,
			      target=delprocblock
		flowop block name=crprocblock
	}
}

# the process that deletes $nfiles files,
# wakes up a creation process, and then blocks.

define process name=delproc {
	thread name=delthread {
		flowop block name=delprocblock
		flowop deletefile name=dodelete,
				  filesetname=manyfiles,
				  iters=$nfiles
		flowop wakeup name=crprocwake,
			      target=crprocblock
	}
}

echo  "Create-Delete Swing personality Ver. 1.0 successfully loaded"
