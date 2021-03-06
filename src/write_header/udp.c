#include "udp.h"

void write_udp_header(unsigned char *buffer,
		      int size,
		      struct sockaddr_in source,
		      struct sockaddr_in dest, 
		      FILE *logfile){
  unsigned short iphdrlen;

  struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));
  iphdrlen = (iph -> ihl) * 4;

  struct udphdr *udph = (struct udphdr *)(buffer + iphdrlen + sizeof(struct ethhdr));
  write_ip_header(buffer, size, source, dest, logfile);

  fprintf(logfile, "\"udp\":{");
  fprintf(logfile, "\"src\":\"%d\",", ntohs(udph -> source));
  fprintf(logfile, "\"dst\":\"%d\",", ntohs(udph -> dest));
  fprintf(logfile, "\"len\":\"%d\",", ntohs(udph -> len));
  fprintf(logfile, "\"check\":\"%d\"", ntohs(udph -> check));
  fprintf(logfile, "}");
  
}

