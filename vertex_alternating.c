/* PLUGIN file to use with plantri.c 

   To use this, compile plantri.c using 
       cc -o vertex_alternating -O4 '-DPLUGIN="vertex_alternating.c"' plantri.c

   This plug-in generates graphs that are vertex alternating
   planar graphs.   
*/

#define FILTER isVertexAlternating

static int isVertexAlternating(int nbtot, int nbop, int doflip) {
    
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
