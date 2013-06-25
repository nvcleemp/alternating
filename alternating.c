/* PLUGIN file to use with plantri.c 

   To use this, compile plantri.c using 
       cc -o alternating -O4 '-DPLUGIN="alternating.c"' plantri.c

   This plug-in generates alternating planar graphs.   
*/
static int make_dual(void);

#define FILTER isAlternating

static int isAlternating(int nbtot, int nbop, int doflip) {
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
    
    //we need the dual graph
    //nf stores the number of faces
    //(i.e. the number of vertices in the dual graph) (Duh!)
    int nf = make_dual();
    
    for(i = 0; i<nf; i++){
        int sizeBegin = facesize[i];
        e = elast = facestart[i];
        do {
            if(sizeBegin == e->left_facesize) return 0;
            e = e->invers->prev;
        } while(e != elast);
    }
    
    return 1;
}

#define FAST_FILTER_POLY checkDeletedEdge(e->start,e->end)

static int checkDeletedEdge(int v1, int v2){
    EDGE *e, *elast;
    if(degree[v1]==3){
        e = elast = firstedge[v1];
        do {
            if(degree[e->end]==3) return 0;
            e = e->next;
        } while(e != elast);
    }
    if(degree[v2]==3){
        e = elast = firstedge[v2];
        do {
            if(degree[e->end]==3) return 0;
            e = e->next;
        } while(e != elast);
    }
    return 1;
}