/* PLUGIN file to use with plantri.c 

   To use this, compile plantri.c using 
       cc -o alternating -O4 '-DPLUGIN="alternating.c"' plantri.c

   This plug-in generates alternating planar graphs.   
*/
static int make_dual(void);

#ifdef DO_PROFILING
unsigned long long int isAlternatingCount = 0; 

unsigned long long int fastFilterCalled = 0; 
unsigned long long int fastFilterPassed = 0; 
int fastFilterCalls[MAXE/2+1];
int fastFilterPruned[MAXE/2+1];

unsigned long long int preFilterCalled = 0; 
unsigned long long int preFilterPassed = 0; 
int preFilterCalls[MAXE/2+1];
int preFilterPruned[MAXE/2+1];
#endif

#ifndef NO_FINAL_FILTER

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

#endif //NO_FINAL_FILTER

#ifndef NO_FAST_FILTER_POLY

#define FAST_FILTER_POLY checkDeletedEdge(e->start,e->end)

static int checkDeletedEdge(int v1, int v2){
#ifdef DO_PROFILING
    fastFilterCalled++;
    fastFilterCalls[ne/2]++;
#endif
    EDGE *e, *elast;
    if(degree[v1]==3){
        e = elast = firstedge[v1];
        do {
            if(degree[e->end]==3){
#ifdef DO_PROFILING
                fastFilterPruned[ne/2]++;
#endif
                return 0;
            }
            e = e->next;
        } while(e != elast);
    }
    if(degree[v2]==3){
        e = elast = firstedge[v2];
        do {
            if(degree[e->end]==3){
#ifdef DO_PROFILING
                fastFilterPruned[ne/2]++;
#endif
                return 0;
            }
            e = e->next;
        } while(e != elast);
    }
#ifdef DO_PROFILING
    fastFilterPassed++;
#endif
    return 1;
}

#endif //NO_FAST_FILTER_POLY

#ifndef NO_PRE_FILTER_POLY

#define PRE_FILTER_POLY preFilterPoly()

static int preFilterPoly(){
    /*
     * No need to check for neighbouring edges of degree 3 at this point.
     * For the initial triangulation it is not possible that this happens,
     * and as soon as deleting an edge leads to two neighbouring edges of
     * degree 3, that operation is rejected by FAST_FILTER_POLY
     * 
     * We first look for any (3,4,4)-triangles
     */
    int i;
    EDGE *e, *elast;

#ifdef DO_PROFILING
    preFilterCalled++;
    preFilterCalls[ne/2]++;
#endif

    for(i = 0; i<nv; i++){
        if(degree[i]==4){
            e = elast = firstedge[i];
            do {
                if(degree[e->end]==4){
                    if(e->next->end == e->invers->prev->end && degree[e->next->end]==3){
#ifdef DO_PROFILING
                        preFilterPruned[ne/2]++;
#endif
                        return 0;
                    }
                    //other direction will be handle, when we're looking at the other vertex
                }
                e = e->next;
            } while(e != elast);
        }
    }

#ifdef DO_PROFILING
    preFilterPassed++;
#endif
        
    return 1;
}

#endif //NO_PRE_FILTER_POLY

#ifdef DO_PROFILING

#define SUMMARY alternating_summary

void alternating_summary() {  
    fprintf(stderr, "Calls to isAlternating: %llu\n", isAlternatingCount);
    fprintf(stderr, "\nPRE_FILTER_POLY\n===============\n\n");
    fprintf(stderr, "Calls to preFilterPoly: %llu\n", preFilterCalled);
    fprintf(stderr, "Passed to preFilterPoly: %llu\n", preFilterPassed);
    int i;
    for(i=3*nv/2;i<3*nv-6;i++){
        if(preFilterCalls[i])
                fprintf(stderr, "pruned after removing %2d edges: %d/%d (%.2f%%)\n", 3*nv-6-i, preFilterPruned[i], preFilterCalls[i], preFilterPruned[i]*100.0/preFilterCalls[i]);
    }
    fprintf(stderr, "\nFAST_FILTER_POLY\n================\n\n");
    fprintf(stderr, "Calls to fastFilterPoly: %llu\n", fastFilterCalled);
    fprintf(stderr, "Passed to fastFilterPoly: %llu\n", fastFilterPassed);
    for(i=3*nv/2;i<3*nv-6+1;i++){
        if(fastFilterCalls[i])
                fprintf(stderr, "pruned after removing %2d edges: %d/%d (%.2f%%)\n", 3*nv-6-i, fastFilterPruned[i], fastFilterCalls[i], fastFilterPruned[i]*100.0/fastFilterCalls[i]);
    }
    fprintf(stderr, "\n\n");
}

#define PLUGIN_INIT initPlugin()

static void initPlugin(){
    int i;
    for(i=0;i<3*nv-6+1;i++){
        preFilterPruned[i]=0;
        preFilterCalls[i]=0;
        fastFilterPruned[i]=0;
        fastFilterCalls[i]=0;
    }
}
#endif