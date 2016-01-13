/*
 * pcap_related.h
 *
 *  Created on: Jan 13, 2016
 *      Author: kursat
 */

#ifndef PCAP_RELATED_H_
#define PCAP_RELATED_H_

#include <string.h>
#include <pcap.h>
#include <stdlib.h>
#include <sys/types.h>

#define PCAP_ITEM_CHUNK	(512)

struct _pcaps {
	unsigned char **item;
	unsigned int *byte_count;
	unsigned char *is_vlan;
	int item_count;
	int alloc_chunk;
	int biggest_frame;
};

void save_frames (unsigned char *user, const struct pcap_pkthdr *hdr,
		const unsigned char *data);

#endif /* PCAP_RELATED_H_ */
