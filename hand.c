#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<ifaddrs.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include"hand.h"
#include"soio.h"

unsigned int hash(char*s,int l){
  unsigned int h=5381,i;
  for(i=0;i<l;++i) h=((h<<5)+h)+(unsigned int)s[i];
  return h%DSIZE;
}

hand hget(char*s){return hl[hash(s,4)];}

rd getrd(tranmode tm){
  switch(tm){
  case STREAM: return sreads;
  case BLOCK : return sreadb;
  default    : return sread ;
  }
}

int hrewr(senv*s){return srewr(s->scon);}
int hpasv(senv*s){
  unsigned short p1,p2;char*c;int r;
  if((r=hrewr(s))<0) return r;
  c=strchr(s->scon->bf,',');
  sscanf(c,",%*d,%*d,%*d,%hd,%hd",&p1,&p2);
  if(s->cm==PASSIVE){
    sock_d(s->sdat);
    if(!(s->sdat=sock_c())) return -1;
  }else{
    s->cm=PASSIVE;
  }
  return sock_a(s->sdat,p1*256+p2,s->sin);
}
int hlist(senv*s){
  int n,r;rd rd=getrd(s->tm);
  if((r=hrewr(s))<0) return r;
  if(s->cm==ACTIVE)
    if((s->sdat->sfd=accept(s->sdat->sfd,NULL,NULL))<0) return s->sdat->sfd;
  do{
    n=rd(s->sdat);
    sputs(s->sdat);
  }while(n==sizeof(s->sdat->bf));
  if((r=sread(s->scon))<0) return r;
  return sputs(s->scon);
}
int hretr(senv*s){
  char fn[30];FILE*fp;int n,r;rd rd=getrd(s->tm);
  sscanf(s->scon->bf,"RETR %s",fn);
  if(!(fp=fopen(fn,"w"))) return -1;
  if((r=hrewr(s))<0) return r;
  if(s->cm==ACTIVE)
    if((s->sdat->sfd=accept(s->sdat->sfd,NULL,NULL))<0) return s->sdat->sfd;
  do{
    n=rd(s->sdat);
    fwrite(s->sdat->bf,1,sizeof(s->sdat->bf),fp);
  }while(n==sizeof(s->sdat->bf));
  fclose(fp);
  if((r=sread(s->scon))<0) return r;
  return sputs(s->scon);
}
int hmode(senv*s){
  char m;
  sscanf(s->scon->bf,"MODE %c",&m);
  switch(m){
  case 's': s->tm=STREAM;break;
  case 'b': s->tm=BLOCK;break;
  case 'c': s->tm=COMPRESSED;break;
  default : break;
  }
  return hrewr(s);
}
int hport(senv*s){
  FILE*fp;
  short ip[4],p;
  sscanf(s->scon->bf,"PORT %hd",&p);
  sock_b(s->sdat,p);
  fp=popen("curl -s icanhazip.com","r");
  fscanf(fp,"%hd.%hd.%hd.%hd",ip,ip+1,ip+2,ip+3);
  sprintf(s->scon->bf,"PORT %hd,%hd,%hd,%hd,%hd,%hd\r\n",ip[0],ip[1],ip[2],ip[3],s->sdat->lp>>8&0xff,s->sdat->lp&0xff);
  printf("   %s",s->scon->bf);
  pclose(fp);
  s->cm=ACTIVE;
  return hrewr(s);
}  
int hquit(senv*s){hrewr(s);return 1;}

void hini(){
  int i;
  for(i=0;i<DSIZE;++i) hl[i]=hrewr;
  hl[hash("PASV",4)]=hpasv;
  hl[hash("LIST",4)]=hlist;
  hl[hash("QUIT",4)]=hquit;
  hl[hash("RETR",4)]=hretr;
  hl[hash("MODE",4)]=hmode;
  hl[hash("PORT",4)]=hport;
}
