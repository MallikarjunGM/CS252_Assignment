/*Mallikarjun G M 191ME243
CS252 Assignment
Question number 3.19
A program is to created that takes a command as an argument from
the terminal and display the time it takes to Run the said command.
2 versions of this program should be written, with different method of
IPC.
a) Shared-memory
b) Pipes
This program is the Pipes version
Part of this code was taken from a solution posted on chegg.com by an
unknown author.
Explainations for functions used for Pipes was taken from
OS Concepts by Silberschatz et.al
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main ( int argc, char **argv )
{
  //timeval is a structure include in time.h
  //It holds timevalue in seconds and microseconds
  struct timeval start_time_child;
  struct timeval start_time_parent;
  struct timeval end_time;

/* pipeFD is the file descriptor that will identify the ends of the pipe.
pipe(int) will take an integer array of 2 elements as argument, and uses this
array to store file descriptor of rear end (1st element)
and write end (2nd element)*/
  int pipeFD[2];
  pipe (pipeFD);

/* A child process is created and the process ID is stored in pid. if(pid==0)
makes sure that only the chils process runs the exec command*/
  pid_t pid = fork ();

  if (pid == 0)
    {
/* Time just before execvp() is stored in start_time. The pipe will later be
used to convey this variable's value into the parent process*/
      gettimeofday (&start_time_child,NULL);
/*write() takes 3 arguments: the file descriptor, the address of the variable
to be written and the number of bytes of the variable*/
      write (pipeFD[1],&start_time_child,sizeof(start_time_child));
/*execvp function replaces the current process with a new processes
specified by the arrgument. Used to construct a pathname that identifies
the new process image file. In this case, the process argument passed
will be the command which is argv from argument of main()*/
      execvp ( argv[1], argv + 1 );
    }
  /*wait() waits for the child process to be terminated before continuing*/
  wait ( NULL );
  /*time at which child process ends is recorded and stored in 'end_time'*/
  gettimeofday ( &end_time, NULL );

  read (pipeFD[0], &start_time_parent,sizeof(start_time_parent));
  float time_elapsed;

  /*following lines calculates difference in times between start_time and end_time
  and prints it in ____ Milliseconds*/
  time_elapsed = ((end_time.tv_sec * 1000 + end_time.tv_usec * 0.001) -
                  (start_time_parent.tv_sec * 1000 + start_time_parent.tv_usec * 0.001));
  printf ("\n %f Milliseconds\n",time_elapsed);
}
