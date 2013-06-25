all: plantri alternating

plantri: plantri.c
	$(CC) -o plantri -O4 plantri.c

alternating: alternating.c plantri.c
	$(CC) -o alternating -O4 '-DPLUGIN="alternating.c"' plantri.c
