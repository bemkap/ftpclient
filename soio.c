#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include"soio.h"

int inc(char*str){
  int r=0;
  r=str[0]=='1'||str[3]=='-';
  while(NULL!=(str=strchr(str+1,'\n')))
    if(str[1]) r=str[1]=='1'||str[4]=='-';
  return r;
}

void valid(char*str,int sz){
  int l=strlen(str);
  if(sz>l){str[l-1]='\r';str[l]='\n';}
}

int sgets(sock*s){
  printf("> ");
  memset(s->bf,0,sizeof(s->bf));
  fgets(s->bf,sizeof(s->bf),stdin);
  valid(s->bf,sizeof(s->bf));
  return 0;
}

int sputs(sock*s){return fputs(s->bf,stdout);}

int swrit(sock*s){return write(s->sfd,s->bf,sizeof(s->bf)-1);}

int sread(sock*s){
  int n=0;
  memset(s->bf,0,sizeof(s->bf));
  do{n+=read(s->sfd,s->bf,sizeof(s->bf)-1);}while(inc(s->bf)&&0<n&&n<sizeof(s->bf)-1);
  s->bf[n]=0;
  return n;
}
