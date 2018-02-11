#include "../../../include/util/net/ipgen.h"

void generateRandomIp(ipv4Addr *addr){
	srand(mix(clock(), time(NULL), getpid()));
	addr->a = (addr->a == -1) ? rand() / (RAND_MAX / 255 + 1) : addr->a;
	addr->b = (addr->b == -1) ? rand() / (RAND_MAX / 255 + 1) : addr->b;
	addr->c = (addr->c == -1) ? rand() / (RAND_MAX / 255 + 1) : addr->c;
	addr->d = (addr->d == -1) ? rand() / (RAND_MAX / 255 + 1) : addr->d;
}

void initIpv4Addr(ipv4Addr *addr){
	addr->a=-1;
	addr->b=-1;
	addr->c=-1;
	addr->d=-1;
}

char *ipv4AddrToString(ipv4Addr *addr){

	char *a = malloc(3);
	char *b = malloc(3);
	char *c = malloc(3);
	char *d = malloc(3);

	sprintf(a, "%d", addr->a);
	sprintf(b, "%d", addr->b);
	sprintf(c, "%d", addr->c);
	sprintf(d, "%d", addr->d);

	char *ret = malloc(strlen(a) + strlen(b) + strlen(c) + strlen(d) + 1);

	sprintf(ret, "%s.%s.%s.%s", a, b, c, d);

	free(a);
	free(b);
	free(c);
	free(d);

	return ret;
}

void printIpv4Addr(ipv4Addr *addr){
	char *str = ipv4AddrToString(addr);
	printf("%s\n", str);
	free(str);
}

// http://www.concentric.net/~Ttwang/tech/inthash.htm
unsigned long int mix(unsigned long int a, unsigned long int b, unsigned long int c){
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
