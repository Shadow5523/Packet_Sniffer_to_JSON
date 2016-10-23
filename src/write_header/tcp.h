//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<netinet/tcp.h>
//#include<arpa/inet.h>
//#include "ip.h"

void write_tcp_header(unsigned char *buffer,
		      int size,
		      struct sockaddr_in source,
		      struct sockaddr_in dest, 
		      FILE *logfile){
  unsigned short iphdrlen;

  struct iphdr *iph = (struct iphdr *)(buffer + sizeof(struct ethhdr));
  iphdrlen = (iph -> ihl) * 4;

  struct tcphdr *tcph = (struct tcphdr *)(buffer + iphdrlen + sizeof(struct ethhdr));
  write_ip_header(buffer, size, source, dest, logfile);

  fprintf(logfile, "\"tcp\":{");
  fprintf(logfile, "\"src\":\"%u\",", ntohs(tcph -> source));
  fprintf(logfile, "\"dst\":\"%u\",", ntohs(tcph -> dest));
  fprintf(logfile, "\"seq\":\"%u\",", ntohl(tcph -> seq));
  fprintf(logfile, "\"ack_seq\":\"%u\",", ntohl(tcph -> ack_seq));
  fprintf(logfile, "\"thl\":\"%d DWORDS or %d Bytes\",", (unsigned int)tcph -> doff, (unsigned int)tcph -> doff*4);
  fprintf(logfile, "\"urg\":\"%d\",", (unsigned int)tcph -> urg);
  fprintf(logfile, "\"ack\":\"%d\",", (unsigned int)tcph -> ack);
  fprintf(logfile, "\"psh\":\"%d\",", (unsigned int)tcph -> psh);
  fprintf(logfile, "\"rst\":\"%d\",", (unsigned int)tcph -> rst);
  fprintf(logfile, "\"syn\":\"%d\",", (unsigned int)tcph -> syn);
  fprintf(logfile, "\"fin\":\"%d\",", (unsigned int)tcph -> fin);
  fprintf(logfile, "\"window\":\"%d\",", ntohs(tcph -> window));
  fprintf(logfile, "\"check\":\"%d\",", ntohs(tcph -> check));
  fprintf(logfile, "\"urgptr\":\"%d\"",tcph -> urg_ptr);
  fprintf(logfile, "}");
  
}

