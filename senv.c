#include<stdlib.h>
#include"senv.h"

senv*senv_c(){
  senv*s=malloc(sizeof(senv));
  s->scon=sock_c();
  s->sdat=sock_c();
  return s;
}

void senv_d(senv*s){
  sock_d(s->scon);
  sock_d(s->sdat);
  free(s);
}
