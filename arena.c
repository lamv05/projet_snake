#include<stdio.h>
#include"arena.h"
#include<stdlib.h>
#include"snake.h"

typedef struct cell_{
    int wall_up;
    int wall_down;
    int wall_right;
    int wall_left;
    int occupied;

}cell;


// int version
void printTHEarena(int** arena,int H,int L){
    for (int i=0;i<H;i++){
        for (int j=0;j<L;j++){
            printf("%d ",arena[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

int** init_arena(int H,int L){
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
    // arena[0][0]=9;
    // arena[L-1][0]=8;
    // arena[0][H-1]=7;
    // arena[L-1][H-1]=6;
    return arena;
}

void fill_walls(int** arena,int nbWalls,int* walls){

    for (int i=0;i<4*(nbWalls);i=i+2){ //4*(nbWalls)
            
            // arena[walls[i+1]][walls[i]] = 1; 
            // printf("%d %d\n",walls[i],walls[i+1]);
            arena[walls[i]][walls[i+1]]++; 
            // wallprinted++;
            
        }
        // printf("wall printed %d/%d\n",wallprinted/2,nbWalls);
    
}

void fill_snake(int** arena,snakeCell* head,snakeCell* oppenent_head,int H,int L){
    refresh_arena(arena,H,L);
    snakeCell* head_tmp=head;
    arena[head_tmp->x][head_tmp->y]=9;
    while (head_tmp->nextCell!=NULL){
        head_tmp=head_tmp->nextCell;
        arena[head_tmp->x][head_tmp->y]=9;
        
    }
    head_tmp=oppenent_head;
    arena[head_tmp->x][head_tmp->y]=9;
    while (head_tmp->nextCell!=NULL){
        head_tmp=head_tmp->nextCell;
        arena[head_tmp->x][head_tmp->y]=9;
        
    }
}

void freeTHEarena(int** arena,int H,int L){
    for(int i=0;i<L;i++){
        free(arena[i]);
    }
    free(arena);
}

void refresh_arena(int** arena,int H,int L){
    // int wallprinted=0;
    for (int i=0;i<L;i++){
        for (int j=0;j<H;j++){
            arena[i][j]=0;
        }
    }
}

void merge_arenas(int** arenaSnake,int** arenaWall,int** arena,int H,int L){
    for(int i=0;i<L;i++){
        for(int j=0;j<H;j++){
            arena[i][j]=arenaWall[i][j];
            if (arenaSnake[i][j]!=0){
                arena[i][j]+=arenaSnake[i][j];
            }
        }
    }
}