#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include"sock.h"
#include"senv.h"
#include"soio.h"
#include"hand.h"
#include"chec.h"

int scmd(senv*s){
  sgets(s->scon);
  hand f=hget(s->scon->bf);
  return f(s);
}

int main(int argc,char*argv[]){
  //if(argc<2) return 1;
  int quit=0;
  senv*senv=senv_c("ftp.microsoft.com");
  hini();  
  sock_a(senv->scon,21,senv->sin);
  sread(senv->scon);sputs(senv->scon);
  while(!quit) quit=scmd(senv);
  senv_d(senv);
  return 0;
}
