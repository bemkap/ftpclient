#include<stdlib.h>
#include<unistd.h>
#include"sock.h"

sock*sock_c(){
  sock*s=malloc(sizeof(sock));
  if(!s) return NULL;
  s->sfd=socket(AF_INET,SOCK_STREAM,0);
  if(s->sfd<0){free(s);return NULL;}
  return s;
}

int sock_a(sock*s,unsigned short p,struct sockaddr_in*sin){
  if(p>0) s->rp=p;
  sin->sin_port=htons(s->rp);
  return connect(s->sfd,(struct sockaddr*)sin,sizeof(*sin));
}

int sock_b(sock*s,unsigned short p){
  struct sockaddr_in sin;int r;
  sin.sin_family=AF_INET;
  sin.sin_addr.s_addr=INADDR_ANY;
  if(p>0) s->lp=p;
  sin.sin_port=htons(s->lp);
  r=bind(s->sfd,(struct sockaddr*)&sin,sizeof(sin));
  return r?-1:listen(s->sfd,5);
}

void sock_d(sock*s){
  close(s->sfd);
  free(s);
}
