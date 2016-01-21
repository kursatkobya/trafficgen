/*
 * traffic_gen.c
 *
 *  Created on: Jan 5, 2016
 *      Author: kursat
 */


#include <stdio.h>
#include <dirent.h>
#include "pcap_related.h"
#include <stdint.h>
#include <signal.h>

#define FNAME_SIZE	(155)
#define LINE_SIZE	(1024 * 2)
extern int _pcap_datalink_type;
extern struct _pcaps pcaps;

/*Configuration related declarations */

typedef struct _conf {
	uint32_t start_ip;
	uint32_t end_ip;
	uint16_t start_port;
	uint16_t end_port;
	uint8_t ip_toggle;
	uint8_t port_toggle;
	uint8_t ip_checksum_toggle;
	uint8_t protocol_checksum_toggle;
	uint32_t gtp_start_ip;
	uint32_t gtp_end_ip;
	uint8_t gtpu_toggle;
	uint32_t bitrate;
	uint16_t tx_port;
} conf;

//	                 start/end IP,  start/end Port,  toggles , gtp start/endIP, --->
conf traffic_conf = {0x0, 0xFFFFFFFF, 0x0, 0xFFFF, 0, 0, 0, 0, 0x0, 0xFFFFFFFF, 0, 0, 0x0};
extern char *optarg;  // Used by getopt.


static void usage(void)
{
//TODO : write proper usage
	exit(1);
}

void read_arguments (int argc, char *argv[])
{
	int option;
	if (1 == argc) {
		  printf("No parameter set\n traffic will generate according to defaults\n"
				  "ip will be between 0x0-0xFFFF\nport randomization disabled\n" );
		  return;
	}

	while((option = getopt(argc, argv, "i:g:p:c:u:r:t:h")) > 0) {
		  switch(option) {
		  char *ptr;
		  long int tmp;
			  case 'i':
			  {
				  tmp = strtol(optarg, &ptr, 16);
				  if (tmp < 0 || tmp > 0xFFFFFFFF) {
					  printf("Wrong parameter for start ip\n");
					  usage();
				  }
				  traffic_conf.start_ip = tmp;
				  tmp = strtol(ptr+1, &ptr, 16);
				  if (tmp < traffic_conf.start_ip || tmp > 0xFFFFFFFF) {
					  printf("Wrong parameter for end ip\n");
					  printf("0xFFFFFFFF will be used instead\n");
				  } else {
					  traffic_conf.end_ip = tmp;
				  }
				  traffic_conf.ip_toggle = 1;
				  break;
			  }
			  case 'p':
			  {
				  tmp = strtol(optarg, &ptr, 16);
				  if (tmp < 0 || tmp > 0xFFFF) {
					  printf("Wrong parameter for start port\n");
					  printf("Port randomization disabled\n");
					  break;
				  }
				  traffic_conf.start_port = tmp;
				  tmp = strtol(ptr+1, &ptr, 16);
				  if (tmp < traffic_conf.start_port || tmp > 0xFFFF) {
					  printf("Wrong parameter for end port\n");
					  printf("0xFFFF will be used instead\n");
				  } else {
					  traffic_conf.end_port = tmp;
				  }
				  traffic_conf.port_toggle = 1;
				  break;
			  }
			  case 'h':
				  usage();
				  break;
			  case 'c':
				  printf("ip checksum will be calculated\n");
				  traffic_conf.ip_checksum_toggle = 1;
				  break;
			  case 'u':
				  printf("ip checksum will be calculated\n");
				  traffic_conf.protocol_checksum_toggle = 1;
				  break;
			  case 'g':
			  {
				  tmp = strtol(optarg, &ptr, 16);
				  if (tmp < 0 || tmp > 0xFFFFFFFF) {
					  printf("Wrong parameter for start gtpu ip\n");
					  usage();
				  }
				  traffic_conf.gtp_start_ip = tmp;
				  tmp = strtol(ptr+1, &ptr, 16);
				  if (tmp < traffic_conf.gtp_start_ip || tmp > 0xFFFFFFFF) {
					  printf("Wrong parameter for end gtpu ip\n");
					  printf("0xFFFFFFFF will be used instead\n");
				  } else {
					  traffic_conf.gtp_end_ip = tmp;
				  }
				  traffic_conf.gtpu_toggle = 1;
				  break;
			  }
			  case 'r':
			  {
				  tmp = strtol(optarg, &ptr, 10);
				  printf("will be send with bitrate %ld MBit\n", tmp);
				  traffic_conf.bitrate = tmp;
				  break;
			  }
			  case 't':
			  {
				  tmp = strtol(optarg, &ptr, 16);
				  if (tmp < 0 || tmp > 0xFFFF) {
					  printf("Wrong parameter for tx port\n0 will be used instead\n");
					  break;
				  }
				  traffic_conf.tx_port = tmp;
				  break;
			  }
			  default :
				  printf("[Attention] Unknown option\n");
				  usage();
				  break;
		  }
	}
	return;
}


/* manipulate template and generate data*/

int keep_running = 1;	//quit loop mechanism
void quit_handle(int dummy) {
	printf("Ready to Quit\n");
    keep_running = 0;
}

static void *generate_data (conf *traffic_conf)
{
	unsigned char *rb_obj;
	uint32_t ip_increment = traffic_conf->start_ip;
	uint32_t gtpu_ip_increment = traffic_conf->gtp_start_ip;
	uint16_t port_increment = traffic_conf->start_port;
	int i;
	int firstPacket=1;			// First packet to transmit

	signal(SIGINT, quit_handle);	//to kill infinite loop
// TODO : think about benchmarking : take timestamps to measure
	for (i = 0; keep_running; i++) {
		static uint64_t ts=0;

		if ((0 == pcaps.byte_count[i] || pcaps.byte_count[i] > LINE_SIZE) && i != pcaps.item_count)		continue;

		if (i == pcaps.item_count) { //increase ip/port/gtp in every cycle of pcap
			/*static int cycle_count = 0;
			cycle_count ++;
			if (3 == cycle_count) return 0;*/
			i=0;
			ip_increment = (ip_increment + 1) % 0xFFFFFFFF;
			if (ip_increment > traffic_conf->end_ip) ip_increment = traffic_conf->start_ip;
			if (traffic_conf->port_toggle) {
				port_increment = (port_increment + 1) % 0xFFFF;
				if (port_increment > traffic_conf->end_port)	port_increment = traffic_conf->start_port;
			}
			if (traffic_conf->gtpu_toggle) {
				gtpu_ip_increment = (gtpu_ip_increment + 1) % 0xFFFFFFFF;
				if (gtpu_ip_increment > traffic_conf->gtp_end_ip) gtpu_ip_increment = traffic_conf->gtp_start_ip;
			}
		}

/* TODO LIST:
 * Get a napa Tx buffer for this packet
 * IP manipulation
 * port manipulation
 * gtp manipulation
 * cheksum calculation
 * try to arrange transmit rate
 *
 */


	}
	return;
}



int main (int argc, char *argv[])
{
  DIR *directory;

  read_arguments(argc, argv);

  directory = opendir ("./pcap");
  if (NULL != directory)
    {
	  struct dirent *ep;
	  pcap_t *p;
	  char errbuf[PCAP_ERRBUF_SIZE];
	  char filename[FNAME_SIZE];

      while ((ep = readdir(directory))) {
    	  strcpy(filename, "./pcap/");
    	  strcat(filename, ep->d_name);
    	  puts (ep->d_name);
    	  if(strlen(ep->d_name) > 4){
			  if (!(p = pcap_open_offline(filename, errbuf))) {
					  fprintf(stderr, "Error opening file, %s, for reading: %s\n", filename, errbuf);
			  }
			  _pcap_datalink_type = pcap_datalink(p);
			  pcap_loop(p, -1, &save_frames, (unsigned char *)0);
    	  }
      }
      closedir(directory);
    }
  else {
	  fprintf(stderr,"Couldn't open the directory");
	  return -1;
  }
/* TODO LIST
  * Init Napatech here ( NT_Init)
  * Open Napatech the infostream. (NT_InfoOpen)
  * Do transmit timing related things with napa
  * Open a Transmit buffer to port tx_port
*/
// generate data to transmit
  generate_data(&traffic_conf);

// Close Napatech transmit buffer

  return 0;
}

