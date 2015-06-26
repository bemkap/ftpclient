#ifndef SOCK_H
#define SOCK_H

typedef struct {int sfd;char bf[1024];struct sockaddr_in*sin;} sock;

sock*sock_c(void);
void sock_d(sock*);
int  sock_a(sock*,const char*,unsigned short);

#endif
