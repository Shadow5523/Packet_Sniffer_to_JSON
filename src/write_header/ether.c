#include "ether.h"

void write_ether_header(unsigned char *buffer,
			int size,
      			FILE *logfile){
  
  struct ethhdr *eth = (struct ethhdr *)buffer;
  
  fprintf(logfile, "\"ether\":{");
  fprintf(logfile, "\"dst\":\"%02x:%02x:%02x:%02x:%02x:%02x\",",
	  eth -> h_dest[0], eth -> h_dest[1], eth -> h_dest[2],
	  eth -> h_dest[3], eth -> h_dest[4], eth -> h_dest[5]);
  
  fprintf(logfile, "\"src\":\"%02x:%02x:%02x:%02x:%02x:%02x\",",
	  eth -> h_source[0], eth -> h_source[1], eth -> h_source[2],
	  eth -> h_source[3], eth -> h_source[4], eth -> h_source[5]);
  
  fprintf(logfile, "\"proto\":\"%u\"", (unsigned short)eth -> h_proto);
  fprintf(logfile, "},");
  
}


