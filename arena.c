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

// int tab[5] version

int*** init_arena_tab(int H,int L){
    int***arena;
    arena=(int***)malloc(sizeof(int**)*L);
    for (int i=0;i<L;i++){
        arena[i]=(int**)malloc(sizeof(int*)*H);
        for (int j=0;j<H;j++){
            arena[i][j]=(int*)malloc(sizeof(int)*5);
        }
    }
    for (int i=0;i<L;i++){
        for (int j=0;j<H;j++){
            for(int k=0;k<5;k++){
                arena[i][j][k]=0;
            }
        }
    }
    return arena;
}


void free_arena_tab(int*** arena,int H,int L){
    for(int i=0;i<L;i++){
        for(int j=0;j<H;j++){
            free(arena[i][j]);
        }
        free(arena[i]);
    }
    free(arena);
}

void print_arena_tab(int*** arena,int H,int L){
    for (int i=0;i<H;i++){
        for (int j=0;j<L;j++){
            printf("{%d,%d,%d,%d,%d} ",arena[j][i][0],arena[j][i][1],arena[j][i][2],arena[j][i][3],arena[j][i][4]);
        }
        printf("\n");
    }
    printf("\n");
}

// {wall up, wall right, wall down, wall left, occupied by snake}

void fill_arena_tab(int*** arena,int nbWalls,int* walls){
    int xi,yi,xi_1,yi_1,flag=0;
    for (int i=0;i< 4*(nbWalls);i=i+2){ // 4*(nbWalls)
        if(flag==0){
            xi=walls[i];
            yi=walls[i+1];
            xi_1=walls[i+2];
            yi_1=walls[i+3];
            flag=1;

            // printf("xi:%d,yi:%d,xi_1:%d,yi_1:%d\n",xi,yi,xi_1,yi_1);
        }
        else{
            xi=walls[i];
            yi=walls[i+1];
            xi_1=walls[i-2];
            yi_1=walls[i-1];
            flag=0;
        }
        
        if (yi>yi_1){ // wall up case
            arena[xi][yi][0]=1;
        }
        else if (xi<xi_1){ // wall right case
            arena[xi][yi][1]=2;
        }
        else if (yi<yi_1){ // wall down case
            arena[xi][yi][2]=3;
        }
        else if(xi>xi_1){ // wall left case
            arena[xi][yi][3]=4; 
        }
          
    }

    
}

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