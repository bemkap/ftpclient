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

int hpasv(senv*s){
  int p1,p2;
  char*c;
  swrit(s->scon);
  sread(s->scon);
  sputs(s->scon);
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
int hlist(senv*s){sread(s->sdat);sputs(s->sdat);return 0;}
/*
void hretr(senv*s){
  char fname[30];
  sread(s->sdat);
  sscanf(fname,"retr %s",s->scon->bf);  
  FILE*fout=fopen(fname,"w");
  fwrite(s->sdat->bf,1,sizeof(s->sdat->bf),fout);
  fclose(fout);
}
*/
int hrewr(senv*s){
  swrit(s->scon);
  sread(s->scon);
  sputs(s->scon);
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
  //hl[hash("retr")]=hretr;
}
