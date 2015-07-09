#ifndef SOIO_H
#define SOIO_H

#include"sock.h"

int sgets(sock*);
int sputs(sock*);
int swrit(sock*);
int srewr(sock*);
int sread(sock*);  // read connection
int sreads(sock*); // read stream
int sreadb(sock*); // read block

#endif
