#ifndef _TCP_H_
#define _TCP_H_

#include <stdio.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>

void write_ip_header(unsigned char *buffer,
		     int size,
		     struct sockaddr_in source,
		     struct sockaddr_in dest,
		     FILE *logfile);

#endif _IP_H_
