#define __LIBRARY__ 
#include <stdio.h> 
#include <unistd.h> 
int main( int argc, char * argv[] ) 
{ 
printf("PID:%d new process.\n", getpid()); 
return 0; 
} 