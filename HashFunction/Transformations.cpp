#include "Transformations.h"

void X(byte* a, const byte* b, byte* result) {
	for (int i = 0; i < SIZE; i++) {
		result[i] = a[i] ^ b[i];
	}
}
void S(byte* a) {
	for (int i = 0; i < SIZE; i++) {
		a[i] = Pi[a[i]];
	}
}
void P(byte* a) {
	byte temp[64];
	for (int i = 0; i < SIZE; i++) {
		temp[i] = a[Tau[i]];
	}
	memcpy(a, temp, SIZE);
}
void L(byte *result)//L не до конца понял
{
	for (int i = 0; i < 8; ++i)
	{
		unsigned long long v = 0;
		for (int k = 0; k < 8; ++k)
		{
			for (int j = 0; j < 8; ++j)
			{
				if ((result[i * 8 + k] & (1 << (7 - j))) != 0)
					v ^= A[k * 8 + j];
			}
		}
		for (int k = 0; k < 8; ++k)
		{
			result[i * 8 + k] = (v & (0xFFFFFFFFFFFFFFFF << (7 - k) * 8)) >> (7 - k) * 8;
		}
	}
}