#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include"chec.h"

int chec(int c,const char*str){
  if(c<0){perror(str);exit(errno);}
  else return c;
}
