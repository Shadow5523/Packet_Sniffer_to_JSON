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

void ProcessPacket(unsigned char*, int);
void error(char *);

FILE *logfile;
int tcp = 0,
    udp = 0,
    icmp = 0,
    igmp = 0,
    others = 0,
    total = 0,
    i = 0,
    j = 0,
    sock_raw = 0,
    count = 0;


struct sockaddr_in source, dest;

int main(int argc, char *argv[]){
  int saddr_size, data_size;
  struct sockaddr saddr, in;

  unsigned char *buffer = (unsigned char *)malloc(65536);    //65536バイトのメモリを確保

  if((logfile = fopen("log.json", "w")) == NULL)
    printf("unable to create file");

   if((sock_raw = socket(AF_PACKET, SOCK_RAW,  htons(ETH_P_ALL))) == -1)
    error("socket error");

  fprintf(logfile, "{");

  while(count < atoi(argv[1])){
    fprintf(logfile, "\"%d\":{", (count + 1));
    saddr_size = sizeof saddr;
    if((data_size = recvfrom(sock_raw, buffer, 65536, 0, &saddr, (socklen_t *)&saddr_size)) == -1)
      error("recvfrom() error");

    ProcessPacket(buffer, data_size);

    ++count;
    if(count == atoi(argv[1])){
      fprintf(logfile, "}");
      
    }else{
      fprintf(logfile, "},");
      
    }
  
  }close(sock_raw);
  fprintf(logfile, "}");
   
}





void ProcessPacket(unsigned char* buffer, int size){
  struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr)); //iphdrの一部を取得
  ++total;

  switch(iph -> protocol){
  case 1:  //ICMP Protocol
    ++icmp;
<<<<<<< HEAD
<<<<<<< HEAD
    //write_icmp_header(buffer, size, source, dest, logfile);
=======
    write_tcp_header(buffer, size, source, dest, logfile);
>>>>>>> ad6fd9ec88cbcc9476a62f07be7bc788c1a43f7d
=======
    write_tcp_header(buffer, size, source, dest, logfile);
>>>>>>> ad6fd9ec88cbcc9476a62f07be7bc788c1a43f7d

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
