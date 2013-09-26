all: build/plantri build/alternating build/vertex_alternating\
     build/bialternating_to_graph build/filter_vertex_alternating\
     build/filter_balanced

clean: 

build/plantri: plantri.c
	mkdir -p build
	$(CC) -o build/plantri -O4 plantri.c

build/alternating: alternating.c plantri.c
	mkdir -p build
	$(CC) -o build/alternating -O4 '-DPLUGIN="alternating.c"' plantri.c

build/bounding_test: alternating.c plantri.c
	mkdir -p build
	$(CC) -o build/bounding_test -O4 '-DPLUGIN="alternating.c"' -DNO_FINAL_FILTER plantri.c

build/only_fast: alternating.c plantri.c
	mkdir -p build
	$(CC) -o build/only_fast -O4 '-DPLUGIN="alternating.c"' -DNO_FINAL_FILTER -DNO_PRE_FILTER_POLY plantri.c

build/only_pre: alternating.c plantri.c
	mkdir -p build
	$(CC) -o build/only_pre -O4 '-DPLUGIN="alternating.c"' -DNO_FINAL_FILTER -DNO_FAST_FILTER_POLY plantri.c

build/vertex_alternating: vertex_alternating.c plantri.c
	mkdir -p build
	$(CC) -o build/vertex_alternating -O4 '-DPLUGIN="vertex_alternating.c"' plantri.c

build/bialternating_to_graph: bialternating_to_graph.c
	mkdir -p build
	$(CC) -o build/bialternating_to_graph -O4 bialternating_to_graph.c
	
build/filter_vertex_alternating: filter_vertex_alternating.c
	mkdir -p build
	$(CC) -o build/filter_vertex_alternating -O4 filter_vertex_alternating.c
	
build/filter_balanced: filter_balanced.c
	mkdir -p build
	$(CC) -o build/filter_balanced -O4 filter_balanced.c