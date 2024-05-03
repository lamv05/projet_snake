#include<stdio.h>
#include"arena.h"
#include<stdlib.h>


void printTHEarena(int** arena,int H,int L){
    for (int i=0;i<H;i++){
        for (int j=0;j<L;j++){
            printf("%d ",arena[j][i]);
        }
        printf("\n");
    }
}

int** setupTHEarena(int H,int L,int nbWalls,int* walls){
    int** arena;
    // int wallprinted=0;
    arena=(int**)malloc(sizeof(int*)*L);
    for (int i=0;i<L;i++){
        arena[i]=(int*)malloc(sizeof(int)*H);
    }
    for (int i=0;i<L;i++){
        for (int j=0;j<H;j++){
            arena[i][j]=0;
        }
    }
    for (int i=0;i<4*(nbWalls);i=i+2){
            
            // arena[walls[i+1]][walls[i]] = 1; 
            // printf("%d %d\n",walls[i],walls[i+1]);
            arena[walls[i]][walls[i+1]]++; 
            // wallprinted++;
            
        }
        // printf("wall printed %d/%d\n",wallprinted/2,nbWalls);
    return arena;
}

void freeTHEarena(int** arena,int H,int L){
    for(int i=0;i<L;i++){
        free(arena[i]);
    }
    free(arena);
}

