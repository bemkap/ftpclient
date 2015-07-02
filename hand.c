#include<string.h>
#include<stdio.h>
#include"hand.h"
#include"soio.h"

unsigned int hash(char*s){
  unsigned int h=5381,c;
  while((c=*s++)&&c!='\r'&&c!='\n'&&c!=' ') h=((h<<5)+h)+(unsigned int)c;
  return h%DSIZE;
}

hand hget(char*s){return hl[hash(s)];}

int hpasv(senv*s){
  int p1,p2;
  char*c;
  sgets(s->scon);swrit(s->scon);
  sread(s->scon);sputs(s->scon);
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
  sgets(s->scon);swrit(s->scon);
  sread(s->scon);sputs(s->scon);
  return 0;
}
int hquit(senv*s){hrewr(s);return 1;}

void hini(){
  hl[hash("user")]=hrewr;
  hl[hash("pass")]=hrewr;
  hl[hash( "cwd")]=hrewr;
  hl[hash("pasv")]=hpasv;
  hl[hash("list")]=hlist;
  hl[hash("quit")]=hquit;
  //hl[hash("retr")]=hretr;
}
