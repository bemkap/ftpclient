#pragma once
#include"senv.h"

enum { DSIZE=128 };
typedef int (*hand)(senv*);
typedef int (*rd)(sock*);

hand hl[DSIZE];

void hini();
hand hget(char*);
