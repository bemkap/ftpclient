#ifndef SENV_H
#define SENV_H

#include<netinet/in.h>
#include"sock.h"

//typedef enum { ASCII,EBCDIC,IMAGE,LOCAL } datatype;
//typedef enum {        NOREC,RECORD,PAGE } filestru;
//typedef enum {  STREAM,BLOCK,COMPRESSED } tranmode;
typedef enum {           ACTIVE,PASSIVE } connmode;

typedef struct {
  sock*scon,*sdat;
  struct sockaddr_in*sin;
  connmode cm;
} senv;

senv*senv_c(const char*);
void senv_d(senv*);

#endif
