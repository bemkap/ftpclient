#ifndef SOCK_H
#define SOCK_H

#include<netinet/in.h>

typedef struct {int sfd;char bf[1024];unsigned short lp,rp;} sock;

sock*sock_c(void);
void sock_d(sock*);
void sock_a(sock*,unsigned short,struct sockaddr_in*);
void sock_b(sock*,unsigned short);

#endif
