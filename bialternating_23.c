/* PLUGIN file to use with plantri.c 

   To use this, compile plantri.c using 
       cc -o bialternating_23 -O4 '-DPLUGIN="bialternating_23.c"' plantri.c

   This plug-in generates graphs that can be translated to alternating
   planar graphs with degrees 2 and 3.   
*/

#define FILTER isAlternating

static int isAlternating(int nbtot, int nbop, int doflip) {
#ifdef DO_PROFILING
    isAlternatingCount++;
#endif
    
    int i;
    EDGE *e, *elast;
    
    for(i = 0; i<nv; i++){
        int degreeBegin = degree[i];
        e = elast = firstedge[i];
        do {
            if(degreeBegin == degree[e->end]) return 0;
            e = e->next;
        } while(e != elast);
    }
    
    return 1;
}
