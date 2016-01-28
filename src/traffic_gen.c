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
//napatect api
#include <nt.h>
//#define BENCHMARK

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

//globals for using napa cards
NtNetStreamTx_t hNetTx;           			// Handle to the TX stream
enum NtTxTimingMethod_e txTiming; 			// TX mode - Do we use absolut or relative mode

static void usage(void)
{
	  printf("Syntax:\n");
	  printf("./traffic_gen [-h][-i <start_ip:end_ip>][-g <gtp_start_ip:gtp_end_ip>][-p <start_port:end:port>][-c <on>][-u <on>][-r <bitrate>][-t <transmit_port>]\n");
	  printf("\n");
	  printf("traffic_gen commands:\n");
	  printf(" -h:  Prints the help.\n");
	  printf(" -p:  start/end ports as range of randomization\n");
	  printf("\texample : -p 0x0:0xFFFF\n");
	  printf(" -i:  start/end ip addresses as range of randomization\n");
	  printf("\texample : -i 0x0:0xF5A2B3D1\n");
	  printf(" -g:  start/end gtpu ip addresses as range of randomization\n");
	  printf("\texample : -g 0x0A1B2C3D:0xF4E51023\n");
	  printf(" -c:  [default:off] on to calculate ip header checksums with randomized data\n");
	  printf("\texample : -c on\n");
	  printf(" -u:  [default:off] on to calculate protocol(udp or tcp) header checksums with randomized data\n");
	  printf("\texample : -u on\n");
	  printf(" -r:  [default:line rate] enter bitrate here to determine how many megabit per seconds\n");
	  printf("\texample : -r 100\n");
	  printf(" -t:  [default:0] enter port number for transmit port\n");
	  printf("\texample : -t 1245\n");
	  printf("==========\tEXAMPLES\t==========\n");
	  printf("./traffic_gen -g 0x0A1B2C3D:0xF4E51023\tonly changes inner gtp ip adresses between given range\n");
	  printf("./traffic_gen -i 0x0A1B2C3D:0xF4E51023\tonly changes outer ip adresses between given range\n");
	  printf("./traffic_gen -i 0x0A1B2C3D:0xF4E51023 -p 0x0:0xFFFF\tchanges outer ip adresses and outer ports\n");
	  printf("./traffic_gen -i 0x0A1B2C3D:0xF4E51023 -g 0x0A1B2C3D:0xF4E51023 -p 0x0:0xFFFF\tchanges outer ip adresses and outer ports and inner gtp adresses\n");
	  printf("./traffic_gen -i 0x0A1B2C3D:0xF4E51023 -g 0x0A1B2C3D:0xF4E51023 -p 0x0:0xFFFF -c on -u on\tchanges adresses and ports and calculate checksums for L3-L4\n");
	  printf("./traffic_gen -i 0x0A1B2C3D:0xF4E51023 -g 0x0A1B2C3D:0xF4E51023 -p 0x0:0xFFFF -c on -u on -r 10000\tsends generated data with bitrate 10000Mbit per sec\n");
	  printf("./traffic_gen -i 0x0A1B2C3D:0xF4E51023 -g 0x0A1B2C3D:0xF4E51023 -p 0x0:0xFFFF -c on -u on -r 10000 -t 1245\t+ sends everything from transmit port 1245\n");
	  exit(1);
}

void read_arguments (int argc, char *argv[])
{
	int option;
	if (1 == argc) {
		  printf("No parameter set\n\tTraffic will generate according to defaults\n"
				  "\tip will be between 0x0-0xFFFF\n\tport randomization disabled\n" );
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
	int status;                     		//ntapi Status variable
	NtNetBuf_t hNetBufTx;             		// Net buffer container. Used when getting a transmit buffer
	char errorBuffer[NT_ERRBUF_SIZE];       // Error buffer
	int firstPacket=1;			// First packet to transmit

	signal(SIGINT, quit_handle);	//to kill infinite loop
#ifdef BENCHMARK
	unsigned long total_bytes = 0;
	unsigned long gb_bytes = 0;
	unsigned long packet_count = 0;
	unsigned long gb_packet = 0;
	int gbit = 0;
	struct timespec tstart={0,0}, tend={0,0}, tgb_start= {0,0};
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	tgb_start.tv_sec = tstart.tv_sec; tgb_start.tv_nsec = tstart.tv_nsec;
#endif

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

	    // Get a TX buffer for this packet
	    if((status = NT_NetTxGet(hNetTx, &hNetBufTx, traffic_conf->tx_port, /*LINE_SIZE*/pcaps.byte_count[i]+4, NT_NETTX_PACKET_OPTION_DEFAULT, -1 /* wait forever */)) != NT_SUCCESS) {
	      // Get the status code as text
	      NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
	      fprintf(stderr, "NT_NetFileGet() failed: %s - %d -  %d\n", errorBuffer, i, pcaps.byte_count[i]);
	      continue;
	    }
	    rb_obj = (unsigned char *) NT_NET_GET_PKT_L2_PTR(hNetBufTx);

		memcpy(rb_obj, (unsigned char *) (pcaps.item[i]), pcaps.byte_count[i]);

#ifdef BENCHMARK
		packet_count++; gb_packet++;
		if (total_bytes + pcaps.byte_count[i] < ULONG_MAX ) total_bytes += pcaps.byte_count[i];
		gb_bytes += pcaps.byte_count[i];
		printf("byte_count =%d\n", 	pcaps.byte_count[i]);
#endif

		{ // algorithm to generate from template frame
			int offset = 14;  			// 14 bytes for MAC header
			if (pcaps.is_vlan[i])	offset+=4;		// 4 bytes Vlan
			if ( traffic_conf->ip_toggle ) {
				// 12 byte offset into IP header for IP addresses
				//change source ip
				rb_obj[offset+12] = (rb_obj[offset+12] + (ip_increment >> 24) & 0xFF) % 0xFF;
				rb_obj[offset+13] = (rb_obj[offset+13] + (ip_increment >> 16) & 0xFF) % 0xFF;
				rb_obj[offset+14] = (rb_obj[offset+14] + (ip_increment >> 8) & 0xFF) % 0xFF;
				rb_obj[offset+15] = (rb_obj[offset+15] + (ip_increment & 0xFF)) % 0xFF;
				//change dst ip
				rb_obj[offset+16] = (rb_obj[offset+16] + (ip_increment >> 24) & 0xFF) % 0xFF;
				rb_obj[offset+17] = (rb_obj[offset+17] + (ip_increment >> 16) & 0xFF) % 0xFF;
				rb_obj[offset+18] = (rb_obj[offset+18] + (ip_increment >> 8) & 0xFF) % 0xFF;
				rb_obj[offset+19] = (rb_obj[offset+19] + (ip_increment & 0xFF)) % 0xFF;
			}

			if (traffic_conf->port_toggle) {
				//change src port
				rb_obj[offset+20] = (rb_obj[offset+20] + (port_increment >> 8) & 0xFF) % 0xFF;
				rb_obj[offset+21] = (rb_obj[offset+21] + port_increment & 0xFF) % 0xFF;
				//change dst port
				rb_obj[offset+22] = (rb_obj[offset+22] + (port_increment >> 8) & 0xFF) % 0xFF;
				rb_obj[offset+23] = (rb_obj[offset+23] + (port_increment & 0xFF)) % 0xFF;
			}
/*
 * offset = start of ip layer
 * offset + 9 = protocol
 * offset + 10 = ip cheksum
 * offset + 12 = source ip
 * offset + 20 = start of protocol (source port)
 * offset + 22 = dst port
 * offset + 24 = udp len
 * offset + 26 = udp checksum
 * offset + 28 = udp payload (gtp)
 */

		}

/* TODO LIST:
 * udp manipulation
 * gtp manipulation
 * cheksum calculation
 * try to arrange transmit rate
 * packet send
 */


	}
#ifdef BENCHMARK
clock_gettime(CLOCK_MONOTONIC, &tend);
printf("\n=====\tSTATS\t=====\n");
printf("Packet Count\t:\t%u\n", packet_count);
printf("Total Bytes\t:\t%u GBytes + ", gbit*5);
format_bytes(total_bytes);
printf("\ntook about %.5f seconds\n",
			   ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) -
			   ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
#endif
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

  int status;
  char errorBuffer[NT_ERRBUF_SIZE];           	// Error buffer
  NtInfoStream_t hInfo;           				// Handle to a info stream
  NtInfo_t infoRead;              				// Buffer to hold data from infostream

  // Initialize the NTAPI library and thereby check if NTAPI_VERSION can be used together with this library
  if((status = NT_Init(NTAPI_VERSION)) != NT_SUCCESS) {
    // Get the status code as text
    NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
    fprintf(stderr, "NT_Init() failed: %s\n", errorBuffer);
    return -1;
  }

  // Open the infostream.
  if((status = NT_InfoOpen(&hInfo, "replay")) != NT_SUCCESS) {
    NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
    fprintf(stderr, "NT_InfoOpen() failed: %s\n", errorBuffer);
    return -1;
  }

  // Check whether or not absolut TX timing is supported
  infoRead.cmd = NT_INFO_CMD_READ_ADAPTER_V3;
  infoRead.u.adapter_v3.adapterNo=0;  // Adapter is hardcoded to adapter 0 as the TX port is hardcoded to port 0
  if((status = NT_InfoRead(hInfo, &infoRead)) != NT_SUCCESS) {
    NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
    fprintf(stderr, "NT_InfoOpen() failed: %s\n", errorBuffer);
    NT_InfoClose(hInfo);
    return -1;
  }
  // Get the TX mode
  txTiming = infoRead.u.adapter_v3.data.txTiming;

  NT_InfoClose(hInfo);

  // Open a TX hostbuffer on NUMA node 0 that can transmit to port 0
  if((status = NT_NetTxOpen(&hNetTx, "TxStreamPort0", 0x1<<traffic_conf.tx_port, 0, 0)) != NT_SUCCESS) {
    // Get the status code as text
    NT_ExplainError(status, errorBuffer, sizeof(errorBuffer));
    fprintf(stderr, "NT_NetTxOpen() failed: %s\n", errorBuffer);
    return -1;
  }

// generate data to transmit
  generate_data(&traffic_conf);
  NT_NetTxClose(hNetTx);

  return 0;
}

