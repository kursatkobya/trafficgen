traffic_gen:
	gcc -o traffic_gen -g -I./inc -I./src src/traffic_gen.c -L./lib -lpcap
clean:	
	rm traffic_gen
