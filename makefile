tcp.o: src/write_header/tcp.h src/write_header/tcp.c
	gcc -c src/write_header/tcp.c

udp.o: src/write_header/udp.h src/write_header/udp.c
	gcc -c src/write_header/udp.c

ip.o: src/write_header/ip.h src/write_header/ip.c
	gcc -c src/write_header/ip.c

icmp.o: src/write_header/icmp.h src/write_header/icmp.c
	gcc -c src/write_header/icmp.c

ether.o: src/write_header/ether.h src/write_header/ether.c
	gcc -c src/write_header/ether.c

packet_sniffer.o: src/packet_sniffer.c
	gcc -c src/packet_sniffer.c

write: tcp.o ip.o icmp.o udp.o ether.o packet_sniffer.o
	gcc tcp.o ip.o icmp.o udp.o ether.o packet_sniffer.o -o write

.PHONY: clean

clean:
	rm -f write main.o tcp.o ip.o icmp.o udp.o
