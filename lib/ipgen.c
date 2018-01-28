#include "../include/ipgen.h"

char *generateRandomIp(int a, int b, int c, int d){
	char *ip = malloc(16);

	sprintf(
			ip,
			"%d.%d.%d.%d\0",
			a == -1 ? rand() / (RAND_MAX / 255 + 1) : a,
			b == -1 ? rand() / (RAND_MAX / 255 + 1) : b,
			c == -1 ? rand() / (RAND_MAX / 255 + 1) : c,
			d == -1 ? rand() / (RAND_MAX / 255 + 1) : d
	);

	return ip;
}

// http://www.concentric.net/~Ttwang/tech/inthash.htm
unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
{
	a=a-b;  a=a-c;  a=a^(c >> 13);
	b=b-c;  b=b-a;  b=b^(a << 8);
	c=c-a;  c=c-b;  c=c^(b >> 13);
	a=a-b;  a=a-c;  a=a^(c >> 12);
	b=b-c;  b=b-a;  b=b^(a << 16);
	c=c-a;  c=c-b;  c=c^(b >> 5);
	a=a-b;  a=a-c;  a=a^(c >> 3);
	b=b-c;  b=b-a;  b=b^(a << 10);
	c=c-a;  c=c-b;  c=c^(b >> 15);

	return c;
}
