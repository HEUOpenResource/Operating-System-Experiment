#include <stdio.h>
int main(void)
{
int i = 0x12345678;
printf("The logical/virtual address of i is 0x%08x\n", &i);
fflush(stdout);
while(i)
;
return 0;
}