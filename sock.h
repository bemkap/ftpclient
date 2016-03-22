#pragma once
#include<netinet/in.h>

typedef struct {int sfd;char bf[1024];unsigned short lp,rp;} sock;

sock*sock_c(void);
void sock_d(sock*);
int  sock_a(sock*,unsigned short,struct sockaddr_in*);
int  sock_b(sock*,unsigned short);
