traffic_gen:
	gcc -o traffic_gen -g -I./inc -I./src src/traffic_gen.c src/pcap_related.c -L./lib -lpcap -lntapi
clean:	
	rm traffic_gen
