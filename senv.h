#ifndef SENV_H
#define SENV_H

#include"sock.h"

typedef struct {sock*scon,*sdat;} senv;

senv*senv_c();
void senv_d(senv*);

#endif
