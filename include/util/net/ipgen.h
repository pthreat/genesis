#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct ipv4Addr{
	int a;
	int b;
	int c;
	int d;
} ipv4Addr;

void initIpv4Addr(ipv4Addr *addr);
void generateRandomIp(ipv4Addr *addr);
char *ipv4AddrToString(ipv4Addr *addr);
void printIpv4Addr(ipv4Addr *addr);
unsigned long int mix(unsigned long int a, unsigned long int b, unsigned long int c);
