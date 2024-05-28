#include<stdio.h>
#include"ai.h"
#include<stdlib.h>
#include"snakeAPI.h"

/* Rules :

1 : do not turn back



methode :

calcul de score





*/

int findMove(int** arena,int* position,int H,int L,int lastMoveInt){
    if (lastMoveInt==0)
        printf("last move was north (0)\n");
    else if (lastMoveInt==1)
        printf("last move was east (1)\n");
    else if (lastMoveInt==2)
        printf("last move was south (2)\n");
    else   
        printf("last move was west (3)\n");
    int scoreMove[4]; // [north,east,south,west]
    for (int i=0;i<4;i++){
        scoreMove[i]=1;
    }
    int currentPosition=arena[position[0]][position[1]]-9;
    
    
    // CHECK FORBIDDEN MOVES

    // no backward
    if (lastMoveInt==0){
        scoreMove[2]=0;
    }
    else if (lastMoveInt==1){
        scoreMove[3]=0;
    }
    else if (lastMoveInt==2){
        scoreMove[0]=0;
    }
    else if (lastMoveInt==3){
        scoreMove[1]=0;
    }

    printf("post forbidden move precessing\nnorth : %d\neast : %d\nsouth : %d\nwest : %d\n\n",scoreMove[0],scoreMove[1],scoreMove[2],scoreMove[3]);

    printf("current position : x:%d y:%d\n",position[0],position[1]);

    // boundaries
    if (position[0]==0){
        scoreMove[3]=0;
    }
    if (position[0]==L-1){
        scoreMove[1]=0;
    }
    if (position[1]==0){
        scoreMove[0]=0;
    }
    if (position[1]==H-1){
        scoreMove[2]=0;
    }

    printf("post boundaries processing\nnorth : %d\neast : %d\nsouth : %d\nwest : %d\n\n",scoreMove[0],scoreMove[1],scoreMove[2],scoreMove[3]);

    printf("current position : %d\n",currentPosition);
    printf("north position %d\n",arena[position[0]][position[1]-1]);
    printf("east position %d\n",arena[position[0]+1][position[1]]);
    printf("south position %d\n",arena[position[0]][position[1]+1]);
    printf("west position %d\n",arena[position[0]-1][position[1]]);

    for (int i=0;i<4;i++){
        if (scoreMove[i]!=0){
            if (i==0){
                if(arena[position[0]][position[1]-1]<currentPosition){
                    scoreMove[i]++;
                }
            }
            else if (i==1){
                if(arena[position[0]+1][position[1]]<currentPosition){
                    scoreMove[i]++;
                }
            }
            else if (i==2){
                if(arena[position[0]][position[1]+1]<currentPosition){
                    scoreMove[i]++;
                }
            }
            else{
                if(arena[position[0]][position[1]-1]<currentPosition){
                    scoreMove[i]++;
                }
            }
            
        }
        
        
    }
    
    printf("post map analysing\nnorth : %d\neast : %d\nsouth : %d\nwest : %d\n\n",scoreMove[0],scoreMove[1],scoreMove[2],scoreMove[3]);
    
    
    int max=scoreMove[0];
    int max_indice=0;
    for (int i=0;i<4;i++){
        printf("max=%d\n",max_indice);
        if(scoreMove[i]>max){
            max=scoreMove[i];
            max_indice=i;
        }
    }
    printf("north:%d,east:%d,south:%d,west:%d\n",scoreMove[0],scoreMove[1],scoreMove[2],scoreMove[3]);
    
    if (max_indice==0)
        printf("ai would go north (0)\n");
    else if (max_indice==1)
        printf("ai would go east (1)\n");
    else if (max_indice==2)
        printf("ai would go south (2)\n");
    else   
        printf("ai would go west (3)\n");
    
    return max;
}

int find_move_v2(int*** arena,int* position,int H,int L,int lastMoveInt){

    // if (lastMoveInt==0)
    //     printf("last move was north (0)\n");
    // else if (lastMoveInt==1)
    //     printf("last move was east (1)\n");
    // else if (lastMoveInt==2)
    //     printf("last move was south (2)\n");
    // else   
    //     printf("last move was west (3)\n");
    int scoreMove[4]; // [north,east,south,west]
    for (int i=0;i<4;i++){
        scoreMove[i]=1;
    }
    int* currentPosition=arena[position[0]][position[1]];
    
    
    // CHECK FORBIDDEN MOVES

    // no backward
    if (lastMoveInt==0){
        scoreMove[2]=0;
    }
    else if (lastMoveInt==1){
        scoreMove[3]=0;
    }
    else if (lastMoveInt==2){
        scoreMove[0]=0;
    }
    else if (lastMoveInt==3){
        scoreMove[1]=0;
    }

    // no wall

    for(int i=0;i<4;i++){
        if (currentPosition[i]==1){
            scoreMove[i]=0;
        }
    }
        
    // no snake
    printf("got in snake check\n");
    if (position[0]==0 && position[1]==0){ //position[0]==0 || position[0]==L-1 || position[1]==0 || position[1]==H-1
        printf("up left\n");
        if(arena[position[0]+1][position[1]][4]){
            scoreMove[1]=0; //right
        }
        if(arena[position[0]][position[1]+1][4]){
            scoreMove[2]=0; //down
        }
    }
    else if (position[0]==0 && position[1]==H-1){
        printf("down left\n");
        if (arena[position[0]][position[1]-1][4]){
            scoreMove[0]=0; //up
        }
        if(arena[position[0]+1][position[1]][4]){
            scoreMove[1]=0; //right
        }
    }
    else if(position[0]==L-1 && position[1]==0){
        printf("up right\n");
        if(arena[position[0]][position[1]+1][4]){
            scoreMove[2]=0; //down
        }
        if(arena[position[0]-1][position[1]][4]){
            scoreMove[3]=0; //left
        }
    }
    else if (position[0]==L-1 && position[1]==H-1){
        printf("down right\n");
        if (arena[position[0]][position[1]-1][4]){
            scoreMove[0]=0; //up
        }
        if(arena[position[0]-1][position[1]][4]){
            scoreMove[3]=0; //left
        }
    }
    else if(position[0]==0){
        printf("left\n");
        if (arena[position[0]][position[1]-1][4]){
            scoreMove[0]=0; //up
        }
        if(arena[position[0]+1][position[1]][4]){
            scoreMove[1]=0; //right
        }
        if(arena[position[0]][position[1]+1][4]){
            scoreMove[2]=0; //down
        }
    }
    else if(position[0]==L-1){
        printf("right\n");
        if (arena[position[0]][position[1]-1][4]){
            scoreMove[0]=0; //up
        }
        if(arena[position[0]][position[1]+1][4]){
            scoreMove[2]=0; //down
        }
        if(arena[position[0]-1][position[1]][4]){
            scoreMove[3]=0; //left
        }
    }
    else if(position[1]==0){
        printf("up\n");
        if(arena[position[0]+1][position[1]][4]){
            scoreMove[1]=0; //right
        }
        if(arena[position[0]][position[1]+1][4]){
            scoreMove[2]=0; //down
        }
        if(arena[position[0]-1][position[1]][4]){
            scoreMove[3]=0; //left
        }
    }
    else if(position[1]==H-1){
        printf("down\n");
        if (arena[position[0]][position[1]-1][4]){
            scoreMove[0]=0; //up
        }
        if(arena[position[0]+1][position[1]][4]){
            scoreMove[1]=0; //right
        }
        if(arena[position[0]-1][position[1]][4]){
            scoreMove[3]=0; //left
        }
    }
    else{
        printf("else case\n");
        printf("up position:{%d,%d,%d,%d,%d}\nright position:{%d,%d,%d,%d,%d}\ndown position:{%d,%d,%d,%d,%d}\nleft position:{%d,%d,%d,%d,%d}\n",
            arena[position[0]][position[1]-1][0],arena[position[0]][position[1]-1][1],
            arena[position[0]][position[1]-1][2],arena[position[0]][position[1]-1][3],
            arena[position[0]][position[1]-1][4],arena[position[0]+1][position[1]][0],
            arena[position[0]+1][position[1]][1],arena[position[0]+1][position[1]][2],
            arena[position[0]+1][position[1]][3],arena[position[0]+1][position[1]][4],
            arena[position[0]][position[1]+1][0],arena[position[0]][position[1]+1][1],
            arena[position[0]][position[1]+1][2],arena[position[0]][position[1]+1][3],
            arena[position[0]][position[1]+1][4],arena[position[0]-1][position[1]][0],
            arena[position[0]-1][position[1]][1],arena[position[0]-1][position[1]][2],
            arena[position[0]-1][position[1]][3],arena[position[0]-1][position[1]][4]);
        // printf("up:x:%d,y:%d\nright:x:%d,y:%d\ndown:x:%d,y:%d\nleft:x:%d,y:%d\n",position[0]
        // ,position[1]-1,position[0]+1,position[1],position[0],position[1]+1,
        // position[0]-1,position[1]);
        // printf("up:%d\nright:%d\ndown:%d\nleft:%d\n",arena[position[0]][position[1]-1][4]
        // ,arena[position[0]+1][position[1]][4],arena[position[0]][position[1]+1][4]
        // ,arena[position[0]-1][position[1]][4]);
        
        if (arena[position[0]][position[1]-1][4]){
            scoreMove[0]=0; //up
        }
        if(arena[position[0]+1][position[1]][4]){
            scoreMove[1]=0; //right
        }
        if(arena[position[0]][position[1]+1][4]){
            scoreMove[2]=0; //down
        }
        if(arena[position[0]-1][position[1]][4]){
            scoreMove[3]=0; //left
        }
    }
    

    int max=scoreMove[0];
    int max_indice=0;
    for (int i=0;i<4;i++){
        if(scoreMove[i]>max){
            max=scoreMove[i];
            max_indice=i;
        }
    }
    printf("north:%d,east:%d,south:%d,west:%d\n",scoreMove[0],scoreMove[1],scoreMove[2],scoreMove[3]);

    if (max_indice==0)
        printf("ai would go north (0)\n");
    else if (max_indice==1)
        printf("ai would go east (1)\n");
    else if (max_indice==2)
        printf("ai would go south (2)\n");
    else   
        printf("ai would go west (3)\n");
    
    return max_indice;
}