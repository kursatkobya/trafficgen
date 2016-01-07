/*
 * traffic_gen.c
 *
 *  Created on: Jan 5, 2016
 *      Author: kursat
 */


#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <pcap.h>
#include <string.h>


#define FNAME_SIZE	(155)

static int _pcap_datalink_type = 0;

void save_frames (unsigned char *user, const struct pcap_pkthdr *hdr, const unsigned char *data)
{
/* TODO
 * create a pcap structure, save all pcaps read
 * */

	/*only for diagnostic
	 * will be removed or commented out after saving to heap completed
	 * */
	printf("Len : %d, caplen : %d\n", hdr->len, hdr->caplen);
	int kk;
	for ( kk = 0; kk < hdr->len; kk++ )
		printf(" 0x%x", data[kk]);
	printf("\n\n");

}


int main (int argc, char *argv[])
{
  DIR *directory;
  struct dirent *ep;
  pcap_t *p;
  char errbuf[PCAP_ERRBUF_SIZE];
  char filename[FNAME_SIZE];
  int option;

/*
 * Add command line option here, take them and store in config struct
 * */

  /*
   * Read pcap files and store them in pcaps variable
   */

  directory = opendir ("./pcap");
  if (NULL != directory)
    {
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


  return 0;
}

