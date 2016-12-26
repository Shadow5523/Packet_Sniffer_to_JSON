
void write_ip_header(unsigned char *buffer,
		     int size,
		     struct sockaddr_in source,
		     struct sockaddr_in dest,
		     FILE *logfile){
  
  unsigned short iphdrlen;

  struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));
  iphdrlen = iph ->ihl * 4;

  write_ether_header(buffer, size, logfile);

  memset(&source, 0, sizeof(source));
  source.sin_addr.s_addr = iph -> saddr;

  memset(&dest, 0, sizeof(dest));
  dest.sin_addr.s_addr = iph -> daddr;
  
  fprintf(logfile, "\"ip\":{");
  fprintf(logfile, "\"version\":\"%d\",", (unsigned int)iph->version);
  fprintf(logfile, "\"ihl\":\"%d DWORDS or %d bytes\",", (unsigned int)iph -> ihl, ((unsigned int)(iph->ihl) * 4));
  fprintf(logfile, "\"tos\":\"%d\",", (unsigned int)iph -> tos);
  fprintf(logfile, "\"tlen\":\"%d\",", ntohs(iph -> tot_len));
  fprintf(logfile, "\"id\":\"%d\",", ntohs(iph -> id));
  fprintf(logfile, "\"flag\":\"%ubyte\",", (IP_OFFMASK & ntohs(iph -> frag_off)) * 8);
  fprintf(logfile, "\"ttl\":\"%d\",", (unsigned int)iph -> ttl);
  fprintf(logfile, "\"proto\":\"%d\",", (unsigned int)iph -> protocol);
  fprintf(logfile, "\"check\":\"%d\",", ntohs(iph -> check));
  fprintf(logfile, "\"src\":\"%s\",", inet_ntoa(source.sin_addr));
  fprintf(logfile, "\"dst\":\"%s\"", inet_ntoa(dest.sin_addr));
  fprintf(logfile, "},");

}
