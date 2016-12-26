#ifndef _ETH_H_
#define _ETH_H_

#include <stdio.h>
#include <netinet/if_ether.h>

void write_ether_header(unsigned char *buffer,
			int size,
      			FILE *logfile);

#endif _ETH_H_


