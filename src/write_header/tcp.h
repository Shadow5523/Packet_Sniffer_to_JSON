#ifndef _TCP_H_
#define _TCP_H_

#include <stdio.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>

void write_tcp_header(unsigned char *buffer,
		      int size,
		      struct sockaddr_in source,
		      struct sockaddr_in dest, 
		      FILE *logfile);
#endif _TCP_H_
