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
  int l=1,n=0,m;
  memset(s->bf,0,sizeof(s->bf));
  do{
    m=n;
    do{n+=read(s->sfd,s->bf+n,1);}while(s->bf[n-1]!='\n');
    l=s->bf[m+3]==' '&&0==strncmp(s->bf,s->bf+m,3);
  }while(!l);
  return n;
}
