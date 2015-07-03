#include<string.h>
#include<stdio.h>
#include"hand.h"
#include"soio.h"

unsigned int hash(char*s,int l){
  unsigned int h=5381,i;
  for(i=0;i<l;++i) h=((h<<5)+h)+(unsigned int)s[i];
  return h%DSIZE;
}

hand hget(char*s){return hl[hash(s,4)];}

int hrewr(senv*s){
  swrit(s->scon);
  sread(s->scon);
  sputs(s->scon);
  return 0;
}
int hpasv(senv*s){
  int p1,p2;
  char*c;
  hrewr(s);
  c=strchr(s->scon->bf,',');
  sscanf(c,",%*d,%*d,%*d,%d,%d",&p1,&p2);
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
  hrewr(s);
  do{
    n=sread(s->sdat);
    sputs(s->sdat);
  }while(n==sizeof(s->sdat->bf)-1);
  return 0;
}
int hretr(senv*s){
  char fname[30];
  FILE*fout;
  int n;
  hrewr(s);  
  sscanf(fname,"retr %s",s->scon->bf);  
  fout=fopen(fname,"w");
  do{
    n=sread(s->sdat);  
    fwrite(s->sdat->bf,1,sizeof(s->sdat->bf),fout);
  }while(n==sizeof(s->sdat->bf)-1);
  fclose(fout);
  return 0;
}
int hquit(senv*s){hrewr(s);return 1;}

void hini(){
  hl[hash("user",4)]=hrewr;
  hl[hash("pass",4)]=hrewr;
  hl[hash("cwd ",4)]=hrewr;
  hl[hash("pasv",4)]=hpasv;
  hl[hash("list",4)]=hlist;
  hl[hash("quit",4)]=hquit;
  hl[hash("retr",4)]=hretr;
}
