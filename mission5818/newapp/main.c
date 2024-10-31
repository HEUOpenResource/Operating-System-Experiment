#include<stdio.h>
int add(int x,int y);
int main(){
int a;
int b;
int sum;
printf("Please input two number:\n");
scanf("%d %d",&a,&b);
sum=add(a,b);
printf("The result is:%d\n",sum);
return 0;
}
