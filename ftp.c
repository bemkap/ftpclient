#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#include<netdb.h>
#include<arpa/inet.h>

#include"sock.h"
#include"senv.h"
#include"chec.h"

// util

int inc(char*str){
  int r=0;
  r=str[0]=='1'||str[3]=='-';
  while(NULL!=(str=strchr(str+1,'\n'))) if(str[1]) r=str[1]=='1'||str[4]=='-';
  return r;
}

void valid(char*str,int sz){
  int l=strlen(str);
  if(sz>l){str[l-1]='\r';str[l]='\n';}
}

// read/write

void swrit(sock*s){
  printf("> ");
  memset(s->bf,0,sizeof(s->bf));
  fgets(s->bf,sizeof(s->bf),stdin);
  valid(s->bf,sizeof(s->bf));
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
  s->cm=PASSIVE;
  sock_a(s->sdat,p1*256+p2,s->sin);
}

void hlist(senv*s){
  sread(s->sdat);
}

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
  /*
  int quit=0;
  senv*senv=senv_c("ftp.microsoft.com");
  sock_a(senv->scon,21,senv->sin);
  sread(senv->scon);
  while(!quit) quit=scmd(senv);
  senv_d(senv);
  */
  struct sockaddr_in sin;
  struct addrinfo h,*aai;
  
  memset(&h,0,sizeof(h));
  h.ai_family=AF_INET;
  h.ai_socktype=SOCK_STREAM;
  getaddrinfo("localhost",NULL,&h,&aai);
  memcpy(&sin,aai->ai_addr,sizeof(sin));
  freeaddrinfo(aai);
  char bu[100];
  inet_ntop(AF_INET,&sin,bu,sizeof(bu));
  printf("%s\n",bu);
  
  return 0;
}
