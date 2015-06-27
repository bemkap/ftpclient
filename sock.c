#include<stdlib.h>
#include<unistd.h>
#include"sock.h"
#include"chec.h"

sock*sock_c(){
  sock*s=malloc(sizeof(sock));
  s->sfd=chec(socket(AF_INET,SOCK_STREAM,0),"socket");
  return s;
}

void sock_a(sock*s,unsigned short p,struct sockaddr_in*sin){
  if(p>0) s->rp=p;
  sin->sin_port=htons(s->rp);
  chec(connect(s->sfd,(struct sockaddr*)sin,sizeof(*sin)),"connect");
}

void sock_b(sock*s,unsigned short p){
  struct sockaddr_in sin;
  sin.sin_family=AF_INET;
  sin.sin_addr.s_addr=INADDR_ANY;
  if(p>0) s->lp=p;
  sin.sin_port=htons(s->lp);
  chec(bind(s->sfd,(struct sockaddr*)&sin,sizeof(sin)),"bind");
  chec(listen(s->sfd,5),"listen");
}

void sock_d(sock*s){
  close(s->sfd);
  free(s);
}
