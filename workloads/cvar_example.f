set $dir=/tmp
set $filesize=100m
set $iosize=cvar(type=cvar-uniform,parameters=lower:4096;upper:8192)

define file name=singlefile,path=$dir,size=$filesize,prealloc

define process name=filereader,instances=1
{
  thread name=filereader,memsize=1m,instances=1
  {
    flowop openfile name=open1,filesetname=singlefile,fd=1
    flowop read name=read1,fd=1,iosize=$iosize
    flowop closefile name=close1,fd=1
  }
}

run 60
