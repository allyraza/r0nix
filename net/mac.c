#include <mm.h>
#include <panic.h>
#include <crc32.h>

#include "mac.h"

/* just broadcast to all for now */
struct mac_address dest_mac = {{0xff,0xff,0xff,0xff,0xff,0xff}};

struct mac_packet mac_create_pkt(char * packet, int size, int type)
{
	struct mac_packet mcpkt;
	mcpkt.hdr.destination = dest_mac;
	mcpkt.hdr.source = our_mac;
	if(size>MAX_MAC_LENGTH)
		panic("mac packet too large");
	if(type)
		mcpkt.hdr.type=__builtin_bswap16(type);
	else
		mcpkt.hdr.type=__builtin_bswap16(size);
	int i;
	for(i=0;i<=size;i++)
		mcpkt.data[i]=packet[i];
	/* calculate the checksum and add it to end of mcpkt.data */
	/*
	uint32_t a = crc32((void *)&mcpkt,(sizeof(mcpkt)-MAX_MAC_LENGTH)+size);
	a = __builtin_bswap32(a);
	char * c = (void *)&a;
	*(mcpkt.data+i-3) = c[0];
	*(mcpkt.data+i-2) = c[1];
	*(mcpkt.data+i-1) = c[2];
	*(mcpkt.data+i)   = c[3];
	*/

	return mcpkt;
}
