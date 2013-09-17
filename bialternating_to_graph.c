/*
 * Main developer: Nico Van Cleemput
 * 
 * Copyright (C) 2013 Ghent University.
 * Licensed under the GNU GPL, read the file LICENSE.txt for details.
 */

/* This program reads edgecode from standard in,
 * inserts a vertex of degree 2 in each edge and
 * then outputs the graph again in planar code.   
 * 
 * 
 * Compile with:
 *     
 *     cc -o bialternating_23_to_graph -O4 bialternating_23_to_graph.c
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define MAXN 100
#define MAXVAL 20
#define MAXE 100

int numberOfGraphs = 0;

int readEdgeCode(FILE *fileIn, FILE *fileOut) {
    static int first = 1;
    unsigned char c;
    char testheader[20];
    int codeLength;
    int i, j;
    int currentVertex = 0;
    int edgeCount = 0;
    int vertexCount;
    
    int graph[MAXN][MAXVAL];
    int degrees[MAXN];
    
    int edges[MAXE][2];
    int edgeDegrees[MAXE];
    
    for(i=0; i<MAXN; i++){
        degrees[i] = 0;
    }
    for(i=0; i<MAXE; i++){
        edgeDegrees[i] = 0;
    }

    if (first) {
        first = 0;

        if (fread(&testheader, sizeof (unsigned char), 11, fileIn) != 11) {
            fprintf(stderr, "can't read header ((1)file too small)-- exiting\n");
            exit(1);
        }
        testheader[11] = 0;
        if (strcmp(testheader, ">>edge_code") == 0) {

        } else {
            fprintf(stderr, "No edgecode header detected -- exiting!\n");
            exit(1);
        }
        //read reminder of header (either empty or le/be specification)
        if (fread(&c, sizeof (unsigned char), 1, fileIn) == 0) {
            return FALSE;
        }
        while (c!='<'){
            if (fread(&c, sizeof (unsigned char), 1, fileIn) == 0) {
                return FALSE;
            }
        }
        //read one more character
        if (fread(&c, sizeof (unsigned char), 1, fileIn) == 0) {
            return FALSE;
        }
        
        //write header for output file
        fprintf(fileOut, ">>planar_code<<");
    }

    if (fread(&c, sizeof (unsigned char), 1, fileIn) == 0) {
        //nothing left in file
        return (0);
    }
    
    if(c == 0){
        fprintf(stderr, "Not yet supported -- exiting!\n");
        exit(1);
    }
    
    codeLength = c;
    
    for(i=0; i<codeLength; i++){
        int next = getc(fileIn);
        if(next==255){
            currentVertex++;
        } else {
            graph[currentVertex][degrees[currentVertex]] = next;
            degrees[currentVertex]++;
            edges[next][edgeDegrees[next]] = currentVertex;
            edgeDegrees[next]++;
            edgeCount++;
        }
    }
    edgeCount /=2;
    
    vertexCount = currentVertex + 1;
    
    //write planar code
    fputc(vertexCount+edgeCount, fileOut);
    for(i=0; i<vertexCount; i++){
        for(j=0; j<degrees[i];j++){
            fputc(vertexCount + graph[i][j] + 1, fileOut);
        }
        fputc(0, fileOut);
    }
    for(i=0; i<edgeCount; i++){
        fputc(edges[i][0] + 1, fileOut);
        fputc(edges[i][1] + 1, fileOut);
        fputc(0, fileOut);
    }

    return (1);
}

int main(int argc, char *argv[]) {

    while (readEdgeCode(stdin, stdout)) {
        numberOfGraphs++;
    }
    
    

}
