#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ipv4Addr{
	int a;
	int b;
	int c;
	int d;
} ipv4Addr;

void initIpv4Addr(ipv4Addr *addr);
void generateRandomIp(ipv4Addr *addr);
unsigned long int mix(unsigned long int a, unsigned long int b, unsigned long int c);
