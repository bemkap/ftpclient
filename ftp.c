#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<errno.h>
#include"sock.h"
#include"senv.h"

// util

int inc(char*str){
  int r=0;
  r=str[0]=='1'||str[3]=='-';
  while(NULL!=(str=strchr(str+1,'\n'))) if(str[1]) r=str[1]=='1'||str[4]=='-';
  return r;
}

void valid(char*str){
  str[strlen(str)-1]='\r';
  str[strlen(str)  ]='\n';
}

// read/write

void swrit(sock*s){
  printf("> ");
  memset(s->bf,0,sizeof(s->bf));
  fgets(s->bf,sizeof(s->bf),stdin);
  valid(s->bf);
  write(s->sfd,s->bf,sizeof(s->bf)-1);
}

void sread(sock*s){
  int n;
  do{
    memset(s->bf,0,sizeof(s->bf));
    n=read(s->sfd,s->bf,sizeof(s->bf)-1);
    s->bf[n]=0;
    fputs(s->bf,stdout);
  }while(inc(s->bf));
}

// handle

void hpasv(senv*s){
  int p1,p2;
  char*c;
  c=strchr(s->scon->bf,',');
  sscanf(c,",%*d,%*d,%*d,%d,%d",&p1,&p2);
  if(NULL==s->sdat->sin){
    s->sdat->sin=malloc(sizeof(struct sockaddr_in));
    memcpy(s->sdat->sin,s->scon->sin,sizeof(*s->scon->sin));
  }
  sock_a(s->sdat,NULL,p1*256+p2);
}

void hlist(senv*s){return;}

int shand(senv*s){
  int rc;
  sscanf(s->scon->bf,"%d",&rc);
  switch(rc){
  case 221: return 1;
  case 226: hlist(s);break;
  case 227: hpasv(s);break;
  default : break;
  }
  return 0;
}

int scmd(senv*s){
  swrit(s->scon);
  sread(s->scon);
  return shand(s);
}

// main

int main(int argc,char*argv[]){
  //if(argc<2) return 1;
  int quit=0;
  senv*senv=senv_c();
  sock_a(senv->scon,"ftp.microsoft.com",21);
  sread(senv->scon);
  while(!quit) quit=scmd(senv);
  senv_d(senv);
  return 0;
}
