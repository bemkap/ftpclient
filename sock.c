#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include"sock.h"
#include"chec.h"

sock*sock_c(){
  sock*s=malloc(sizeof(sock));
  s->sfd=0;
  s->sin=NULL;
  return s;
}

int sock_a(sock*s,const char*ad,unsigned short rp){
  struct addrinfo h,*aai;

  if(0==s->sfd) s->sfd=chec(socket(AF_INET,SOCK_STREAM,0),"socket");

  if(rp>0){
    memset(&h,0,sizeof(h));
    h.ai_family=AF_INET;
    h.ai_socktype=SOCK_STREAM;
    if(NULL==s->sin){
      s->sin=malloc(sizeof(struct sockaddr_in));
      getaddrinfo(ad,NULL,&h,&aai);
      memcpy(s->sin,aai->ai_addr,sizeof(*s->sin));
      s->sin->sin_port=htons(rp);
      chec(connect(s->sfd,(struct sockaddr*)s->sin,sizeof(*s->sin)),"connect");
      freeaddrinfo(aai);
    }else{
      chec(connect(s->sfd,(struct sockaddr*)s->sin,sizeof(*s->sin)),"connect");
    }
  }
  return 0;
}

void sock_d(sock*s){
  if(NULL!=s->sin) free (s->sin);
  if(   0!=s->sfd) close(s->sfd);
  free(s);
}
