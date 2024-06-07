#include<stdio.h>
#include"snake.h"
#include"ai.h"
#include"arena.h"
#include<stdlib.h>
#include"snakeAPI.h"


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

void possible_move(int*** arena,snakeCell* head,int H,int L,int lastMoveInt,int* score_move){

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
    int position[2];
    position[0]=head->x;
    position[1]=head->y;
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
    // printf("got in snake check\n");
    if (position[0]==0 && position[1]==0){ //position[0]==0 || position[0]==L-1 || position[1]==0 || position[1]==H-1
        // printf("up left\n");
        if(arena[position[0]+1][position[1]][4]){
            scoreMove[1]=0; //right
        }
        if(arena[position[0]][position[1]+1][4]){
            scoreMove[2]=0; //down
        }
    }
    else if (position[0]==0 && position[1]==H-1){
        // printf("down left\n");
        if (arena[position[0]][position[1]-1][4]){
            scoreMove[0]=0; //up
        }
        if(arena[position[0]+1][position[1]][4]){
            scoreMove[1]=0; //right
        }
    }
    else if(position[0]==L-1 && position[1]==0){
        // printf("up right\n");
        if(arena[position[0]][position[1]+1][4]){
            scoreMove[2]=0; //down
        }
        if(arena[position[0]-1][position[1]][4]){
            scoreMove[3]=0; //left
        }
    }
    else if (position[0]==L-1 && position[1]==H-1){
        // printf("down right\n");
        if (arena[position[0]][position[1]-1][4]){
            scoreMove[0]=0; //up
        }
        if(arena[position[0]-1][position[1]][4]){
            scoreMove[3]=0; //left
        }
    }
    else if(position[0]==0){
        // printf("left\n");
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
        // printf("right\n");
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
        // printf("up\n");
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
        // printf("down\n");
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
        // printf("else case\n");
        // printf("up position:{%d,%d,%d,%d,%d}\nright position:{%d,%d,%d,%d,%d}\ndown position:{%d,%d,%d,%d,%d}\nleft position:{%d,%d,%d,%d,%d}\n",
        //     arena[position[0]][position[1]-1][0],arena[position[0]][position[1]-1][1],
        //     arena[position[0]][position[1]-1][2],arena[position[0]][position[1]-1][3],
        //     arena[position[0]][position[1]-1][4],arena[position[0]+1][position[1]][0],
        //     arena[position[0]+1][position[1]][1],arena[position[0]+1][position[1]][2],
        //     arena[position[0]+1][position[1]][3],arena[position[0]+1][position[1]][4],
        //     arena[position[0]][position[1]+1][0],arena[position[0]][position[1]+1][1],
        //     arena[position[0]][position[1]+1][2],arena[position[0]][position[1]+1][3],
        //     arena[position[0]][position[1]+1][4],arena[position[0]-1][position[1]][0],
        //     arena[position[0]-1][position[1]][1],arena[position[0]-1][position[1]][2],
        //     arena[position[0]-1][position[1]][3],arena[position[0]-1][position[1]][4]);
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
    // recopie des scores
    for (int i=0;i<4;i++){
        score_move[i]=scoreMove[i];
    }

    // int max=scoreMove[0];
    // int max_indice=0;
    // for (int i=0;i<4;i++){
    //     if(scoreMove[i]>max){
    //         max=scoreMove[i];
    //         max_indice=i;
    //     }
    // }
    // printf("north:%d,east:%d,south:%d,west:%d\n",scoreMove[0],scoreMove[1],scoreMove[2],scoreMove[3]);

    // if (max_indice==0)
    //     printf("ai would go north (0)\n");
    // else if (max_indice==1)
    //     printf("ai would go east (1)\n");
    // else if (max_indice==2)
    //     printf("ai would go south (2)\n");
    // else   
    //     printf("ai would go west (3)\n");
    
    // return max_indice;
}

void new_node(decision_tree_node* root,snakeCell* my_head,snakeCell* oppenent_head,int* walls,int nbWalls,int H,int L,int last_move){
    root->move_found=(int*)malloc(sizeof(int)*4);
    root->last_move=last_move;

    root->my_head=copy_snake(my_head);
    snake_move(root->my_head,last_move);
    // root->my_head->move_cnt=10;
    displaySnake(root->my_head);
    //pb quand le snake grandi 
    //le snake degenère
            

    root->arena_snake=init_arena(H,L);
    fill_snake(root->arena_snake,root->my_head,oppenent_head,H,L);
    printTHEarena(root->arena_snake,H,L);
         
    root->arena=init_arena_tab(H,L);
    merge_arenas_tab(root->arena,root->arena_snake,H,L,nbWalls,walls);

    possible_move(root->arena,root->my_head,H,L,root->last_move,root->move_found);
    for(int i=0;i<4;i++){
        if (root->move_found[i]==1){
            root->next_moves[i]=init_root();
        }
    }
    freeTHEarena(root->arena_snake,H,L);
    free_arena_tab(root->arena,H,L);
    
   
}

int search_move(decision_tree_node* root,snakeCell* my_head,snakeCell* oppenent_head,int* walls,int nbWalls,int H,int L,int depth,int last_move){
            int score_move=0;
            
            new_node(root,my_head,oppenent_head,walls,nbWalls,H,L,last_move);

            if (depth==0){
                for(int i=0;i<4;i++){
                    if(root->move_found[i]==1){
                        score_move++;
                    }
                }
                free(root->my_head);
                return score_move;
            }
            else if (depth>0){ 
                    for (int i=0;i<4;i++){
                        if (root->move_found[i]==1){

                            //recursion

                            score_move=score_move+search_move(root->next_moves[i],root->my_head,oppenent_head,walls,nbWalls,H,L,depth-1,i);
                            
                            //free root->next move[i]
                        }
                    }
                    return score_move;
            }         
}

decision_tree_node* init_root(){
    decision_tree_node* root=(struct decision_tree_node_*)malloc(sizeof(struct decision_tree_node_));
    return root;
}

int choose_move(decision_tree_node* root,int* move_found,snakeCell* my_head,snakeCell* oppenent_head,int* walls,int nbWalls,int H,int L,int depth){
    int tab[4]={0,0,0,0};

    for (int i=0;i<4;i++){
        if (move_found[i]==1){
                        
            root->next_moves[i]=init_root();

            tab[i]=search_move(root->next_moves[i],my_head,oppenent_head,walls,nbWalls,H,L,depth,i);

            //free root->next move[i]
            
        }
    }
    printf("%d,%d,%d,%d\n",tab[0],tab[1],tab[2],tab[3]);
    int max=tab[0];
    int max_indice=0;
    for (int i=0;i<4;i++){
        if(tab[i]>max){
            max=tab[i];
            max_indice=i;
        }
    }
    return max_indice;

}

void free_tree(decision_tree_node* root){
    for(int i=0;i<4;i++){
        if (root->next_moves[i]!=NULL){
            free_tree(root->next_moves[i]);
        }
    }
    
}