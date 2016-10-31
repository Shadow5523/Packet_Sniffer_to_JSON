
void write_icmp_header(unsigned char *buffer,
		      int size,
		      struct sockaddr_in source,
		      struct sockaddr_in dest, 
		      FILE *logfile){
  unsigned short iphdrlen;
  struct sockaddr_in gateway;
  
  struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));
  iphdrlen = (iph -> ihl) * 4;
  
  struct icmphdr *icmph = (struct icmphdr *)(buffer + iphdrlen + sizeof(struct ethhdr));
  write_ip_header(buffer, size, source, dest, logfile);
  
  gateway.sin_addr.s_addr = icmph -> un.gateway;

  fprintf(logfile, "\"icmp\":{");
  fprintf(logfile, "\"type\":\"%d\",", (unsigned int)icmph -> type);
  fprintf(logfile, "\"code\":\"%d\",", (unsigned int)icmph -> code);
  if((unsigned int)icmph -> type == ICMP_REDIRECT){
    fprintf(logfile, "\"check\":\"%d\",", ntohs(icmph -> checksum));
    fprintf(logfile, "\"gateway\":\"%s\"", inet_ntoa(gateway.sin_addr));
    
  }else{
    fprintf(logfile, "\"check\":\"%d\"", ntohs(icmph -> checksum));
    
  }
    
  fprintf(logfile, "}");
  
}

