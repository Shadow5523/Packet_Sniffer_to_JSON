#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/ip_icmp.h>
#include<netinet/if_ether.h>
#include<net/ethernet.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<netinet/udp.h>
#include<arpa/inet.h>
#include<errno.h>

#include "write_header/ether.h"
#include "write_header/ip.h"
#include "write_header/tcp.h"
#include "write_header/udp.h"
#include "write_header/icmp.h"

void ProcessPacket(unsigned char*, int);
void error(char *);
void capture(int, unsigned char *, int);

FILE *logfile;
int tcp = 0,
    udp = 0,
    icmp = 0,
    igmp = 0,
    others = 0,
    total = 0,
    i = 0,
    j = 0,
    sock_raw = 0;


struct sockaddr_in source, dest;

int main(int argc, char *argv[]){
  int count = 0;
  int count_input = atoi(argv[1]);

  unsigned char *buffer = (unsigned char *)malloc(65536);    //65536バイトのメモリを確保

  if((logfile = fopen("log.json", "w")) == NULL)
    error("unable to create file");

   if((sock_raw = socket(AF_PACKET, SOCK_RAW,  htons(ETH_P_ALL))) == -1)
    error("socket error");

  fprintf(logfile, "{");

  while(count < atoi(argv[1])){
    capture(count, buffer, count_input);
    count++;
    
  }
  close(sock_raw);
  fprintf(logfile, "}");
   
}





void ProcessPacket(unsigned char* buffer, int size){
  struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr)); //iphdrの一部を取得
  ++total;

  switch(iph -> protocol){
    case 1:  //ICMP Protocol
      ++icmp;
      write_icmp_header(buffer, size, source, dest, logfile);
      break;

    case 2:  //IGMP Protocol
      ++igmp;
      break;

    case 6:  //TCP  Protocol
      ++tcp;
      write_tcp_header(buffer, size, source, dest, logfile);
      break;

    case 17: //UDP  Protocol
      ++udp;
      write_udp_header(buffer, size, source, dest, logfile);
      break;

    default:
      ++others;
      break;
    
  }
  printf("TCP : %d UDP : %d ICMP : %d Others : %d Total %d\n", tcp, udp, icmp, igmp, total);

}





void error(char *msg){
  fprintf(stderr, "%s : %s \n", msg, strerror(errno));
  exit(1);
  
}




void capture(int count, unsigned char *buffer, int count_input){
  struct sockaddr saddr, in;
  int saddr_size, data_size;
  
  fprintf(logfile, "\"%d\":{", (count + 1));
  saddr_size = sizeof saddr;
  if((data_size = recvfrom(sock_raw, buffer, 65536, 0, &saddr, (socklen_t *)&saddr_size)) == -1)
    error("recvfrom() error");

  ProcessPacket(buffer, data_size);

  if(count == (count_input - 1)){
    fprintf(logfile, "}");

  }else{
    fprintf(logfile, "},");

  }

}

