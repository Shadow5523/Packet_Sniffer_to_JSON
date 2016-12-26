#ifndef _UDP_H_
#define _UDP_H_

#include <stdio.h>
#include <netinet/udp.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>

void write_udp_header(unsigned char *buffer,
		      int size,
		      struct sockaddr_in source,
		      struct sockaddr_in dest,
		      FILE *logfile);
#endif _UDP_H_


