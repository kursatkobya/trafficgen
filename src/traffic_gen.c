/*
 * traffic_gen.c
 *
 *  Created on: Jan 5, 2016
 *      Author: kursat
 */


#include <stdio.h>
#include <dirent.h>
#include "pcap_related.h"


#define FNAME_SIZE	(155)
extern int _pcap_datalink_type;

int main (int argc, char *argv[])
{
  DIR *directory;
//  int option;
/*
 * Add command line option here, take them and store in config struct
 * */

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


  return 0;
}

