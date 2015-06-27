#ifndef SENV_H
#define SENV_H

#include<netinet/in.h>
#include"sock.h"

typedef struct {sock*scon,*sdat;struct sockaddr_in*sin;} senv;

senv*senv_c(const char*);
void senv_d(senv*);

#endif
