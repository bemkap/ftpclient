#ifndef HAND_H
#define HAND_H

#include"senv.h"

enum { DSIZE=128 };
typedef int (*hand)(senv*);

hand hl[DSIZE];

void hini();
hand hget(char*);

#endif
