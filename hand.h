#ifndef HAND_H
#define HAND_H

#include"senv.h"

enum { DSIZE=128 };
typedef int (*hand)(senv*);
typedef int (*rd)(sock*);

hand hl[DSIZE];

void hini();
hand hget(char*);

#endif
