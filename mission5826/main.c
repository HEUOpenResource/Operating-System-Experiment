#define _LIBRARY_
#include <stdio.h>
#include <unistd.h>
int main(){
 int pid;
 printf("PID:%D parent process start.\n",getpid());
 pid = fork();
 if(pid != 0 )
 {
  wait(NULL);
  printf("PID:%d parent process continue.\n",getpid());
 }
 else
 {
  printf("PID:%d child process  start.\n",getpid());
  printf("PID:%d child process exit.\n",getpid());
  return 0;
 }
 printf("PID:%d parent process exit.\n",getpid());
 return 0;
}
