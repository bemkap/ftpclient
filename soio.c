#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include"soio.h"

void valid(char*str,int sz){
  int l=strlen(str);
  if(sz>l){str[l-1]='\r';str[l]='\n';}
}

int sgets(sock*s){
  printf("  ");
  memset(s->bf,0,sizeof(s->bf));
  fgets(s->bf,sizeof(s->bf),stdin);
  valid(s->bf,sizeof(s->bf));
  return 0;
}

int sputs(sock*s){return fputs(s->bf,stdout);}

int swrit(sock*s){return write(s->sfd,s->bf,sizeof(s->bf)-1);}

int sread(sock*s){
  int r=1,m,n=0;
  memset(s->bf,0,sizeof(s->bf));
  do{
    m=n;
    do{n+=read(s->sfd,s->bf+n,1);}while(s->bf[n-1]!='\n');
    r=s->bf[m+3]==' '&&0==strncmp(s->bf,s->bf+m,3);
  }while(!r&&0<n&&n<sizeof(s->bf));
  return n;
}

int sreads(sock*s){
  int n;
  memset(s->bf,0,sizeof(s->bf));
  n=read(s->sfd,s->bf,sizeof(s->bf));
  return n;
}

int sreadb(sock*s){
  char d,bc[2];
  memset(s->bf,0,sizeof(s->bf));
  read(s->sfd,&d,1);
  read(s->sfd,bc,2);
  printf("%x %x%x\n",d,bc[0],bc[1]);
  return 0;
}
