####
#### Initialization stubs
####
AC_INIT([filebench], [1.5-alpha3])
AC_CONFIG_MACRO_DIRS([m4])
AM_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE([subdir-objects])

####
#### Checking for programs
####
AC_PROG_CC
AM_CONDITIONAL(GCC_USED, test "$CC" = gcc)
AC_PROG_LIBTOOL
#if test "$CC" = "gcc"; then
#	AC_DEFINE(GCC_USED,1,[ Defined if gcc was detected. ])
#fi
AC_PROG_INSTALL
AC_PROG_YACC
AC_PROG_LEX

####
#### Check for "simple" headers
####
AC_CHECK_HEADERS([stdint.h])
AC_CHECK_HEADERS([arpa/inet.h])
AC_CHECK_HEADERS([fcntl.h])
AC_CHECK_HEADERS([libintl.h])
AC_CHECK_HEADERS([limits.h])
AC_CHECK_HEADERS([locale.h])
AC_CHECK_HEADERS([malloc.h])
AC_CHECK_HEADERS([netdb.h])
AC_CHECK_HEADERS([netinet/in.h])
AC_CHECK_HEADERS([stddef.h])
AC_CHECK_HEADERS([math.h])
if test "$ac_cv_header_math_h" == no
then
	AC_MSG_ERROR([The math.h header is missing! If you use OpenIndiana b148, install "header-math" package.])
fi
AC_CHECK_HEADERS([sys/param.h])
AC_CHECK_HEADERS([sys/socket.h])
AC_CHECK_HEADERS([sys/statvfs.h])
AC_CHECK_HEADERS([sys/time.h]) 
AC_CHECK_HEADERS([sys/personality.h]) 

####
#### Check for more sophisticated headers
####
AC_HEADER_DIRENT
AC_HEADER_STDBOOL
AC_HEADER_SYS_WAIT
AC_HEADER_TIME

####
#### Check for "simple" functions
####
AC_CHECK_FUNCS([ftruncate])
# Use ftruncate64 if available
AC_CHECK_FUNCS([ftruncate64])
AC_CHECK_FUNCS([getcwd])
AC_CHECK_FUNCS([gethostname])
AC_CHECK_FUNCS([gethrtime])
AC_CHECK_FUNCS([gettimeofday])
AC_CHECK_FUNCS([memset])
AC_CHECK_FUNCS([mkdir])
AC_CHECK_FUNCS([munmap])
AC_CHECK_FUNCS([pow])
AC_CHECK_FUNCS([rmdir])
AC_CHECK_FUNCS([socket])
AC_CHECK_FUNCS([sqrt])
AC_CHECK_FUNCS([strchr])
AC_CHECK_FUNCS([strdup])
AC_CHECK_FUNCS([strerror])
AC_CHECK_FUNCS([strncasecmp])
AC_CHECK_FUNCS([strstr])
AC_CHECK_FUNCS([strlcat])
AC_CHECK_FUNCS([strlcpy])
# fork1() syscall on Solaris forks only the calling thread,
# but not all threads in the process. Usual fork() on Solaris
# under certain conditions can fork all (forkall())
# threads in the process. So, for safety, use fork1() if
# available.
AC_CHECK_FUNCS([fork1])
# We set the limit of opened files per process to
# maximum if set/getrlimit functions are availble.
AC_CHECK_FUNCS([getrlimit] [setrlimit])
# Solaris has sigsend() syscall that allows to
# specify more precisely the enity to which the
# signal is send (process, process group, session, etc.
# Use it if available instead of the kill().
AC_CHECK_FUNCS([sigsend])

# We use SYSV semaphores if available, otherwise us POSIX semaphores
AC_CHECK_FUNCS(
	[ftok semget semop],
	[AC_DEFINE(HAVE_SYSV_SEM, 1, [Define if you have SYSV sems])]
	)
# If semtimedop is available(), use it instead semop().
# XXX: looks like in the code it is not handled correctly.
AC_CHECK_FUNCS([semtimedop])
# Use cftime() if possible, otherwise use strftime()
AC_CHECK_FUNCS([cftime])
# We use _lwp_self just for logging, if it is available
AC_CHECK_FUNC(
	[_lwp_self],
        [ AC_DEFINE(HAVE_LWPS, 1, [ Define if you have lwps ])])
# Check for sigignore() function: not available on FreeBSD
AC_CHECK_FUNC(
	[sigignore],
        [ AC_DEFINE(HAVE_SIGIGNORE, 1, [ Define if you have sigignore ])])

####
#### Check for more sophisticated functions
####
AC_FUNC_MMAP
AC_FUNC_ALLOCA
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC 
AC_FUNC_STAT
AC_FUNC_STRFTIME
AC_FUNC_STRTOD
AC_FUNC_VPRINTF
# If user specifies (via --use-system=yes),
# we can use system() instead of execlp().
AC_MSG_CHECKING(whether to use system())
system_default="no"
AC_ARG_ENABLE(system, [  --enable-system=[no/yes] Use system() instead execlp()
		[default=$system_default]],, enable_system=$system_default)
if test "x$enable_system" = "xyes"; then
	AC_DEFINE(USE_SYSTEM,1,[ Define if you want support for system() ])
	AC_MSG_RESULT(yes)
else
	AC_MSG_RESULT(no)
fi

####
#### Check for libraries
####
# Check that librt is installed and supports async IO. First line
# allows to add librt to the linkers path, second one checks
# if aio_wait() is in it, third one checks if aio_waitn() is there (usually
# only on Solaris)
AC_CHECK_LIB([rt], [aio_write])
AC_CHECK_LIB(
	[rt],
	[aio_write],
	[AC_DEFINE(HAVE_AIO, 1, [Define if you have librt with aio_write support])]
	)
AC_CHECK_LIB(
	[rt],
	[aio_waitn],
	[AC_DEFINE(HAVE_AIOWAITN, 1, [Define if you have librt with aio_waitn support])
])
AC_CHECK_LIB([m],[pow])
AC_CHECK_LIB([pthread], [pthread_mutex_lock])
# Use Sun's robust mutexes if available
AC_CHECK_LIB(
	[pthread],
	[pthread_mutexattr_setrobust_np],
	[ AC_DEFINE(HAVE_ROBUST_MUTEX, 1, [ Define if you have robus POSIX mutexes ])]
	)
# Use Sun's additional mutex functionality if available
AC_CHECK_LIB(
	[pthread],
	[pthread_mutexattr_setpshared],
	[ AC_DEFINE(HAVE_PROCSCOPE_PTHREADS, 1, [ Define if you have POSIX process scope threads ])]
	)
AC_CHECK_LIB(
	[pthread],
	[pthread_mutexattr_setprotocol],
        [ AC_DEFINE(HAVE_PTHREAD_MUTEXATTR_SETPROTOCOL, 1, [ Define if you have POSIX setprotocol ])])

AC_CHECK_LIB([dl],[dlopen])

####
#### Check for files
####

# Increase the  maximum size of a shared memory segment through 
# /proc/sys/kernel/shmmax, if this file exists.
AC_CHECK_FILE(
	[/proc/sys/kernel/shmmax],
	[AC_DEFINE(HAVE_PROC_SYS_KERNEL_SHMMAX, 1, [Checking if you have /proc/sys/kernel/shmmax])]
)

####
#### Check for simple types and structures
####

####
#### Check for more sophisticated types and structures
####
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIGNAL
AC_TYPE_SIZE_T
AC_STRUCT_TM

# check for off64_t.
# FreeBSD doesn't have off64_t because off_t et al are 64 bits,
# even on 32-bit systems, and have been ever since the net4.4 release from UCB
# (at least). Consequently, there isn't a separate set of interfaces for 32-bit
# and 64-bit files or file systems, they're all 64-bit.
AC_MSG_CHECKING(for off64_t)
AC_TRY_COMPILE([
	#define _LARGEFILE64_SOURCE
	#include <sys/types.h>
	],
	[off64_t test;
	],[
	    AC_DEFINE(HAVE_OFF64_T, 1, [ Define if you have off64_t ])
	    AC_MSG_RESULT(yes)
	  ], AC_MSG_RESULT(no)
)

# check for boolean_t: Solaris defines it.
AC_MSG_CHECKING(for boolean_t)
AC_TRY_COMPILE([
	#include <sys/types.h>
	],
	[boolean_t test;
	],[
	    AC_DEFINE(HAVE_BOOLEAN_T, 1, [ Define if you have boolean_t ])
	    AC_MSG_RESULT(yes)
	  ], AC_MSG_RESULT(no)
)

# check for u_longlong_t: SUN Studio compiler defines it.
AC_MSG_CHECKING(for u_longlong_t)
AC_TRY_COMPILE([
	#include <sys/types.h>
	],
	[u_longlong_t test;
	],[
	    AC_DEFINE(HAVE_U_LONGLONG_T, 1, [ Define if you have u_longlong_t ])
	    AC_MSG_RESULT(yes)
	  ], AC_MSG_RESULT(no)
)

# check for uint_t: SUN Studio compiler defines it.
AC_MSG_CHECKING(for uint_t)
AC_TRY_COMPILE([
	#include <sys/types.h>
	],
	[uint_t test;
	],[
	    AC_DEFINE(HAVE_UINT_T, 1, [ Define if you have uint_t ])
	    AC_MSG_RESULT(yes)
	  ], AC_MSG_RESULT(no)

)

# check for struct stat64 and stat64() function. Same reason as off64_t:
# FreeBSD does not support it.
AC_MSG_CHECKING(for stat64)
AC_TRY_COMPILE([
	#define _LARGEFILE64_SOURCE
	#include <sys/stat.h>
	],
	[
		struct stat64 test;
		(void)stat64("test", &test); 
	],[
	    AC_DEFINE(HAVE_STAT64, 1, [ Define if you have stat64. ])
	    AC_MSG_RESULT(yes)
	  ], AC_MSG_RESULT(no)
)

# FreeBSD does not support posix_fadvise
AC_MSG_CHECKING(for posix_fadvise)
AC_TRY_COMPILE([
	#include <fcntl.h>
	],
	[
		int ret;
		ret = posix_fadvise(0, 0, 0, POSIX_FADV_RANDOM);
	],[
	    AC_DEFINE(HAVE_FADVISE, 1, [ Define if you have posix_fadvise. ])
	    AC_MSG_RESULT(yes)
	  ], AC_MSG_RESULT(no)
)

# FreeBSD does not support waitid
AC_CHECK_FUNCS([waitid]
	,[
	    AC_DEFINE(HAVE_WAITID, 1, [ Define if you have waitid. ])
	  ]
)

# check for function aio_error64. Same reason as off64_t. FreeBSD does not support it 
AC_CHECK_FUNCS([aio_error64]
	,[
	    AC_DEFINE(HAVE_AIO_ERROR64, 1, [ Define if you have aio_error64 is defined. ])
	  ]
)

# check for function aio_write64. Same reason as off64_t. FreeBSD does not support it 
# Whenether aio_write64 is available, we assume that aiocb64 is also available.
AC_CHECK_FUNCS([aio_write64]
	,[
	    AC_DEFINE(HAVE_AIO_WRITE64, 1, [ Define if you have aio_write64 is defined. ])
	  ]
)

# check for function aio_return64. Same reason as off64_t. FreeBSD does not support it 
AC_CHECK_FUNCS([aio_return64]
	,[
	    AC_DEFINE(HAVE_AIO_RETURN64, 1, [ Define if you have aio_return64 is defined. ])
	  ]
)

# check for function open64. Same reason as off64_t. FreeBSD does not support it 
AC_CHECK_FUNCS([open64]
	,[
	    AC_DEFINE(HAVE_OPEN64, 1, [ Define if you have open64 is defined. ])
	  ]
)

# check for function  mmap64. Same reason as off64_t. FreeBSD does not support it 
AC_CHECK_FUNCS([mmap64]
	,[
	    AC_DEFINE(HAVE_MMAP64, 1, [ Define if you have mmap64 is defined. ])
	  ]
)

# check for function fstat64. Same reason as off64_t. FreeBSD does not support it 
AC_CHECK_FUNCS([fstat64]
	,[
	    AC_DEFINE(HAVE_FSTAT64, 1, [ Define if you have fstat64 is defined. ])
	  ]
)

# check for function lseek64. Same reason as off64_t. FreeBSD does not support it 
AC_CHECK_FUNCS([lseek64]
	,[
	    AC_DEFINE(HAVE_LSEEK64, 1, [ Define if you have lseek64 is defined. ])
	  ]
)

# check for function pwrite64. Same reason as off64_t. FreeBSD does not support it 
AC_CHECK_FUNCS([pwrite64]
	,[
	    AC_DEFINE(HAVE_PWRITE64, 1, [ Define if you have pwrite64 is defined. ])
	  ]
)

# check for function pread64. Same reason as off64_t. FreeBSD does not support it 
AC_CHECK_FUNCS([pread64]
	,[
	    AC_DEFINE(HAVE_PREAD64, 1, [ Define if you have pread64 is defined. ])
	  ]
)

# check for IPC_RMID control for semctl()
AC_MSG_CHECKING(for IPC_RMID control for semctl())
AC_TRY_COMPILE([
       #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/sem.h>],
	[(void) semctl(0, 0, IPC_RMID);
	],[
	    AC_DEFINE(HAVE_SEM_RMID, 1, [ Define if you have the IPC_RMID control. ])
	    AC_MSG_RESULT(yes)
	  ], AC_MSG_RESULT(no)
)

# check for I/O priority system calls
AC_MSG_CHECKING(for I/O priority system calls)
AC_TRY_COMPILE([
	#include <syscall.h>],
  	[(void)syscall(__NR_ioprio_set, 0, 0, 0);
	],[
	    AC_DEFINE(HAVE_IOPRIO, 1, [ Define if you have I/O priority syscalls. ])
	    AC_MSG_RESULT(yes)
	  ], AC_MSG_RESULT(no)
)

# checking for availability of SHM_SHARE_MMU on Solaris
AC_MSG_CHECKING(for SHM_SHARE_MMU)
AC_TRY_COMPILE([
#include <sys/shm.h>
],
[ int flag = SHM_SHARE_MMU;
  if(flag == 0)
  return 0;
  else return 1;
],[
    AC_DEFINE(HAVE_SHM_SHARE_MMU,1,[ Define if you have SHM_SHARE_MMU in sys/shm.h. ])
    AC_MSG_RESULT(yes)
  ], AC_MSG_RESULT(no)
)

#
# Sometimes personality() function exists but ADDR_NO_RANDOMIZE is not defined
# (e.g, in CentOS 5.11)
#
AC_MSG_CHECKING(for ADDR_NO_RANDOMIZE)
AC_TRY_COMPILE([
	#include <sys/personality.h>
	],
	[
		int ret;
		ret = personality(0xffffffff | ADDR_NO_RANDOMIZE);
	],[
	    AC_DEFINE(HAVE_ADDR_NO_RANDOMIZE, 1, [ Define if you have ADDR_NO_RANDOMIZE. ])
	    AC_MSG_RESULT(yes)
	  ], AC_MSG_RESULT(no)
)

#
# Configuring direct I/O. There are 3 main options:
# 1) O_DIRECT open flag is supported (Linux and FreeBSD)
# 2) directio() call is supported (Solaris)
# 3) O_NOCACHE is supported (MacOS X)
#
# O_DIRECT open flag:
AC_MSG_CHECKING(for DIRECT open flag)
AC_TRY_COMPILE([
#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
],
[ int oflag = O_DIRECT;
],[
    AC_DEFINE(HAVE_O_DIRECT,1,[ Define if DIRECT open flag is supported])
    AC_MSG_RESULT(yes)
  ], AC_MSG_RESULT(no)
)
# directio() call:
AC_CHECK_FUNCS([directio])
# F_NOCACHE fcntl():
AC_MSG_CHECKING(for NOCACHE fcntl)
AC_TRY_COMPILE([
#include <fcntl.h>
],
[ int cmd = F_NOCACHE;
],[
    AC_DEFINE(HAVE_NOCACHE_FCNTL,1,[ Define if NOCACHE fcntl() is supported])
    AC_MSG_RESULT(yes)
  ], AC_MSG_RESULT(no)
)

####
#### Check for structure members
####
AC_CHECK_MEMBERS([struct stat.st_rdev])

####
#### Check for C compiler features
####
AC_C_CONST 

####
#### Final steps
####
AC_OUTPUT([Makefile] [workloads/Makefile] [cvars/Makefile])
