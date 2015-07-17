#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include"senv.h"

senv*senv_c(const char*ad){
  senv*s=malloc(sizeof(senv));
  if(!s) return NULL;
  s->sin=malloc(sizeof(struct sockaddr_in));
  if(!s->sin){free(s);return NULL;}
  struct addrinfo h,*aai;

  memset(&h,0,sizeof(h));
  h.ai_family=AF_INET;
  h.ai_socktype=SOCK_STREAM;
  getaddrinfo(ad,NULL,&h,&aai);
  memcpy(s->sin,aai->ai_addr,sizeof(*s->sin));
  freeaddrinfo(aai);

  s->cm=ACTIVE;
  s->tm=STREAM;
  s->scon=sock_c();
  if(s->scon<0){perror("scon failed");free(s->sin);free(s);return NULL;}
  s->sdat=sock_c();
  if(s->sdat<0){perror("sdat failed");free(s->sin);sock_d(s->scon);free(s);return NULL;}
  return s;
}

void senv_d(senv*s){
  sock_d(s->scon);
  sock_d(s->sdat);
  free(s->sin);
  free(s);
}
