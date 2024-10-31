#define __LIBRARY__ 
#include <stdio.h> 
#include <unistd.h> 
int main( int argc, char * argv[] ) 
{ 
printf("PID:%d old process start.\n", getpid()); 
execve("new", NULL, NULL ); 
printf("PID:%d old process exit.\n", getpid()); 
return 0; 
} 