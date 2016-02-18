/*
 * pcap_related.c
 *
 *  Created on: Jan 13, 2016
 *      Author: kursat
 */
#include "pcap_related.h"
#include <arpa/inet.h>

int _pcap_datalink_type = 0;
struct _pcaps pcaps = {NULL, NULL, NULL, 0, 0, 0};

void save_frames (unsigned char *user, const struct pcap_pkthdr *hdr, const unsigned char *data)
{

    if ( 0 == pcaps.alloc_chunk) {
    	pcaps.item = (unsigned char **) malloc(PCAP_ITEM_CHUNK * sizeof(unsigned char *));
    	pcaps.byte_count = (unsigned int *) malloc(PCAP_ITEM_CHUNK * sizeof(int));
    	pcaps.is_vlan = (unsigned char *) malloc(PCAP_ITEM_CHUNK * sizeof(unsigned char));
    	pcaps.alloc_chunk = PCAP_ITEM_CHUNK;
    } else if (pcaps.item_count == pcaps.alloc_chunk) {
    	pcaps.alloc_chunk += PCAP_ITEM_CHUNK;
    	if (0 == (pcaps.item = (unsigned char **) realloc(pcaps.item, pcaps.alloc_chunk * sizeof(unsigned char *)))) {
    		printf("item allocation error\n");
    		exit(1);
    	}
    	if (0 == (pcaps.byte_count = (unsigned int *) realloc(pcaps.byte_count, pcaps.alloc_chunk * sizeof(unsigned int)))) {
    		printf("byte_count allocation error\n");
    		exit(1);
    	}
    	if (0 == (pcaps.is_vlan = (unsigned char *) realloc(pcaps.is_vlan, pcaps.alloc_chunk * sizeof(unsigned char)))) {
    		printf("allocation error\n");
    		exit(1);
    	}
    	memset( pcaps.is_vlan + pcaps.item_count, 0, PCAP_ITEM_CHUNK);
    }

    if (hdr->caplen < 30) {
            /* captured data is not long enough to extract IP address */
            fprintf(stderr, "Error: not enough captured packet data present to extract IP addresses.\n");
            return;
    }

    if ( pcaps.biggest_frame < hdr->len )  pcaps.biggest_frame = hdr->len;

    if ( NULL == (pcaps.item[pcaps.item_count] = (unsigned char *) malloc(hdr->len * sizeof(unsigned char)))) {
    	printf("allocation error\n");
    	exit(1);
    }
	memcpy(pcaps.item[pcaps.item_count], data, hdr->len);
	pcaps.byte_count[pcaps.item_count] = hdr->len;

	if(_pcap_datalink_type == DLT_EN10MB) {
		uint16_t ethernet_type = ntohs(*(uint16_t *)(data+12));
		if ( 0x8100 == ethernet_type) pcaps.is_vlan[pcaps.item_count] = 1;
	}

	/*only for diagnostic
	 * will be removed or commented out after saving to heap completed
	 */
/*	printf("frame %d = [%d] ", pcaps.item_count, pcaps.byte_count[pcaps.item_count]);
	int kk;
	for (kk=0; kk<pcaps.byte_count[pcaps.item_count]; kk++)
		printf(" 0x%x", pcaps.item[pcaps.item_count][kk]);
	printf("\n\n");
	 /*end of diagnostic*/

	pcaps.item_count++;
}
