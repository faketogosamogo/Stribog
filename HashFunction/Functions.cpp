#include "Functions.h"

void KeySchedule(byte* K, int i) {
	X(K, C[i], K);
	S(K);
	P(K);
	L(K);
}
void E(byte* K, byte *m, byte* state) {
	X(K, m, state);
	for (int i = 0; i < 12; i++) {
		S(state);
		P(state);
		L(state);
		KeySchedule(K, i);
		X(state, K, state);
	}
}

void g(byte* N, byte* m, byte* h) {
	byte K[SIZE], t[SIZE];

	X(h, N, K);

	S(K);
	P(K);
	L(K);

	E(K, m, t);

	X(h, t, t);
	X(t, m, h);

}

void mod(byte *a, byte *b, byte *result)
{
	int temp = 0, sum = 0;
	for (int i = 63; i >=0; i--) {
		sum = (int)a[i] + (int)b[i] + temp;
		if (sum > 256)
			temp = (sum >> 8);
		else
			temp = 0;
		result[i] = (char)(sum & 0xFF);
	}	
}
void hash512(byte *message, byte *out)
{

	byte h[SIZE], iv[SIZE], N[SIZE], Sigma[SIZE];
	for (int i = 0; i < SIZE; i++) {
		h[i] = 0x00;
		iv[i] = 0x00;
		N[i] = 0;
		Sigma[i] = 0;
	}

	byte m[64];

	unsigned long long length = strlen((char*)message);

	iv[63] = 0x00;//эти строки есть в реализациях но их смысл понять не могу
	iv[62] = 0x02; //

	while (length >= SIZE)
	{
		memcpy(m, message + length - 63 - ((length & 0x7) == 0), 64);
		g(N, m, h);
		mod(N, iv, N);
		mod(Sigma, m, Sigma);
		length -= 64;
	}
	memset(m, 0, 64);
	memcpy(m + 63 - length + ((length << 3 & 0x7) == 0), message, length + 1 - ((length << 3 & 0x7) == 0));//смысл не понятен

	m[63 - length] = 1;
	g(N, m, h);

	unsigned long long length_b = (length << 3);

	iv[63] = (length_b >> 0) & 0xFF;//смысл не понятен
	iv[62] = (length_b >> 8) & 0xFF; //смысл не понятен
	mod(N, iv, N);

	mod(Sigma, m, Sigma);

	memset(iv, 0x00, 64);
	g(iv, N, h);
	g(iv, Sigma, h);

	
	memcpy(out, h, 64);
	
}