#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<unistd.h>
#include"soio.h"

#define min(a,b) ((a)<(b)?(a):(b))

void valid(char*str,int sz){
  int l=strlen(str);
  if(sz>l){str[l-1]='\r';str[l]='\n';}
}

int sgets(sock*s){
  int i;
  printf("   ");
  memset(s->bf,0,sizeof(s->bf));
  fgets(s->bf,sizeof(s->bf),stdin);
  valid(s->bf,sizeof(s->bf));
  for(i=0;i<strlen(s->bf);++i) s->bf[i]=toupper(s->bf[i]);
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
  memset(s->bf,0,sizeof(s->bf));
  return read(s->sfd,s->bf,sizeof(s->bf));
}

int sreadb(sock*s){
  char d,bc[2];
  memset(s->bf,0,sizeof(s->bf));
  read(s->sfd,&d,1);
  read(s->sfd,bc,2);
  return read(s->sfd,s->bf,min(sizeof(s->bf),bc[0]*0x100+bc[1]));
}

int srewr(sock*s){
  swrit(s);
  sread(s);
  sputs(s);
  return 0;
}
