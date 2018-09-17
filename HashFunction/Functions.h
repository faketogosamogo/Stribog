#pragma once
#include "Transformations.h"
void KeySchedule(byte* K, int i);
void E(byte* K, byte* m, byte* state);
void g(byte* N, byte* m, byte* h);
void hash512(byte *message, byte *out);
void mod(byte *a, byte *b, byte *result);