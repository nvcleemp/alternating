all: plantri alternating bialternating_23 bialternating_23_to_graph

clean: 

plantri: plantri.c
	$(CC) -o plantri -O4 plantri.c

alternating: alternating.c plantri.c
	$(CC) -o alternating -O4 '-DPLUGIN="alternating.c"' plantri.c

bounding_test: alternating.c plantri.c
	$(CC) -o bounding_test -O4 '-DPLUGIN="alternating.c"' -DNO_FINAL_FILTER plantri.c

only_fast: alternating.c plantri.c
	$(CC) -o only_fast -O4 '-DPLUGIN="alternating.c"' -DNO_FINAL_FILTER -DNO_PRE_FILTER_POLY plantri.c

only_pre: alternating.c plantri.c
	$(CC) -o only_pre -O4 '-DPLUGIN="alternating.c"' -DNO_FINAL_FILTER -DNO_FAST_FILTER_POLY plantri.c

bialternating_23: bialternating_23.c plantri.c
	$(CC) -o bialternating_23 -O4 '-DPLUGIN="bialternating_23.c"' plantri.c

bialternating_23_to_graph: bialternating_23_to_graph.c
	$(CC) -o bialternating_23_to_graph -O4 bialternating_23_to_graph.c