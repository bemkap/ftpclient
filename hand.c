#include<string.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<ifaddrs.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"chec.h"
#include"hand.h"
#include"soio.h"

unsigned int hash(char*s,int l){
  unsigned int h=5381,i;
  for(i=0;i<l;++i) h=((h<<5)+h)+(unsigned int)s[i];
  return h%DSIZE;
}

hand hget(char*s){return hl[hash(s,4)];}

typedef int (*rd)(sock*);
rd getrd(tranmode tm){
  switch(tm){
  case STREAM: return sreads;
  case BLOCK : return sreadb;
  default    : return sread ;
  }
}

int hrewr(senv*s){return srewr(s->scon);}
int hpasv(senv*s){
  unsigned short p1,p2;
  char*c;
  hrewr(s);
  c=strchr(s->scon->bf,',');
  sscanf(c,",%*d,%*d,%*d,%hd,%hd",&p1,&p2);
  if(s->cm==PASSIVE){
    sock_d(s->sdat);
    s->sdat=sock_c();
  }else{
    s->cm=PASSIVE;
  }
  sock_a(s->sdat,p1*256+p2,s->sin);
  return 0;
}
int hlist(senv*s){
  int n;
  rd r=getrd(s->tm);
  hrewr(s);
  if(s->cm==ACTIVE) accept(s->scon->sfd,NULL,NULL);
  do{
    n=r(s->sdat);
    sputs(s->sdat);
  }while(n==sizeof(s->sdat->bf));
  sread(s->scon);
  sputs(s->scon);  
  return 0;
}
int hretr(senv*s){
  char fname[30];
  FILE*fout;
  int n;
  rd r=getrd(s->tm);
  hrewr(s);
  if(s->cm==ACTIVE) accept(s->scon->sfd,NULL,NULL);
  sscanf(s->scon->bf,"retr %s",fname);
  fout=fopen(fname,"w");
  do{
    n=r(s->sdat);
    fwrite(s->sdat->bf,1,sizeof(s->sdat->bf),fout);
  }while(n==sizeof(s->sdat->bf));
  fclose(fout);
  sread(s->scon);
  sputs(s->scon);
  return 0;
}
int hmode(senv*s){
  char m;
  sscanf(s->scon->bf,"mode %c",&m);
  switch(m){
  case 's': s->tm=STREAM;break;
  case 'b': s->tm=BLOCK;break;
  case 'c': s->tm=COMPRESSED;break;
  default : break;
  }
  return hrewr(s);
}
int hport(senv*s){
  struct ifaddrs*addrs,*tmp;
  unsigned int ip;
  unsigned short p;

  sscanf(s->scon->bf,"port %hu",&p);
  sock_b(s->scon,p);
  getifaddrs(&addrs);
  for(tmp=addrs;tmp;tmp=tmp->ifa_next){
    if(tmp->ifa_addr&&tmp->ifa_addr->sa_family==AF_INET&&0!=strcmp(tmp->ifa_name,"lo")){
      ip=((struct sockaddr_in*)tmp->ifa_addr)->sin_addr.s_addr;
      sprintf(s->scon->bf,"port %hd,%hd,%hd,%hd,%hd,%hd\r\n",ip&0xff,ip>>8&0xff,ip>>16&0xff,ip>>24&0xff,s->scon->lp>>8&0xff,s->scon->lp&0xff);
    }
  }
  freeifaddrs(addrs);
  puts(s->scon->bf);
  s->cm=ACTIVE;
  return hrewr(s);
}
int hquit(senv*s){hrewr(s);return 1;}

void hini(){
  int i;
  for(i=0;i<DSIZE;++i) hl[i]=hrewr;
  hl[hash("pasv",4)]=hpasv;
  hl[hash("list",4)]=hlist;
  hl[hash("quit",4)]=hquit;
  hl[hash("retr",4)]=hretr;
  hl[hash("mode",4)]=hmode;
  hl[hash("port",4)]=hport;
}
