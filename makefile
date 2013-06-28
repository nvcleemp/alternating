all: plantri alternating

clean: 

plantri: plantri.c
	$(CC) -o plantri -O4 plantri.c

alternating: alternating.c plantri.c
	$(CC) -o alternating -O4 '-DPLUGIN="alternating.c"' plantri.c

bounding_test: alternating.c plantri.c
	$(CC) -o bounding_test -O4 '-DPLUGIN="alternating.c"' -DNO_FINAL_FILTER plantri.c