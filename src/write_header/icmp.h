#ifndef _ICMP_H_
#define _ICMP_H_

#include <stdio.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>

void write_icmp_header(unsigned char *buffer,
		      int size,
		      struct sockaddr_in source,
		      struct sockaddr_in dest, 
		       FILE *logfile);

#endif _ICMP_H_

