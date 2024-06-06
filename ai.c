#include<stdio.h>
#include"snake.h"
#include"ai.h"
#include"arena.h"
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

void new_node(int*** arena,int* move_found,int** arena_snake,snakeCell* my_head,snakeCell* oppenent_head,int* walls,int nbWalls,int H,int L,int last_move){
    decision_tree_node* root=(struct decision_tree_node_*)malloc(sizeof(struct decision_tree_node_));
    root->arena=arena;
    root->move_found=move_found;
    root->my_head=my_head;
    root->oppenent_head=oppenent_head;
    root->walls=walls;
    root->nbWalls=nbWalls;
    root->H=H;
    root->L=L;
    root->last_move=last_move;
    for(int i=0;i<4;i++){
        root->next_moves[i]=NULL;
    }
    possible_move(root->arena,root->my_head,root->H,root->L,root->last_move,root->move_found);

   
}

int search_move(decision_tree_node* root,int*** arena,int* move_found,int** arena_snake,snakeCell* my_head,snakeCell* oppenent_head,int* walls,int nbWalls,int H,int L,int depth,int last_move){
            int* score_move=(int*)malloc(sizeof(int)*4);
            new_node(arena,move_found,arena_snake,my_head,oppenent_head,walls,nbWalls,H,L,last_move);
            printf("x:%d,y:%d\n",my_head->x,my_head->y);
            // possible_move(root->arena,root->my_head,root->H,root->L,root->last_move,root->move_found);
            printf("%d,%d,%d,%d\n",move_found[0],move_found[1],move_found[2],move_found[3]);
            if (depth>0){ // mettre une cond avec %2 pour savoir c'est le tour de qui
                // if (depth%2==1){ //P1
                    // printf("P1\n");
                    for (int i=0;i<4;i++){
                        if (move_found[i]==1){

                            //copy snake and update position
                            
                            snakeCell* copy=copy_snake(my_head);
                            snake_move(copy,i);
                            // printf("copy update snake ok\n");
                            // displaySnake(copy);
                            
                            //copy and update arenas

                            int** new_arenaSnake=init_arena(H,L);
                            fill_snake(new_arenaSnake,copy,oppenent_head,H,L);
                            int*** new_arena=init_arena_tab(H,L);
                            merge_arenas_tab(new_arena,new_arenaSnake,H,L,nbWalls,walls);

                            //add node

                            printf("\ndepth : %d\nmove:%d\n",depth,i);
                            root->next_moves[i]=init_root();
                            // printf("new root ok \n\n\n");

                            // new score_move

                            int* new_move_found=(int*)malloc(sizeof(int)*4);

                            //recursion

                            search_move(root->next_moves[i],new_arena,new_move_found,new_arenaSnake,copy,oppenent_head,walls,nbWalls,H,L,depth-1,i);

                        }

                    }

            }
            // printf("\ndepth : %d\n",depth);
            // printf("%d,%d,%d,%d\n",score_move[0],score_move[1],score_move[2],score_move[3]);
            // if (depth==0){
            //         printf("bottom tree\n\n");
            //         // return 1;
            //     }
            // else if (depth==2){
            //     // trouver le max
            //     int max=score_move[0];
            //     int max_indice=0;
            //     for (int i=0;i<4;i++){
            //         if(score_move[i]>max){
            //             max=score_move[i];
            //             max_indice=i;
            //         }
            //     }
            //     return max_indice;
            // }
            // else{
            //     // sommer les possibilités
            //     int value_returned;
            //     for (int j=0;j<4;j++){
            //         if (score_move[j]==1){
            //             value_returned++;
            //         }
            //     }
            //     return value_returned;
            // }






                // }
            //     else{ //P2
            //         printf("P2\n");
            //         for (int i=0;i<4;i++){
            //             if (move_found[i]==1){

            //                 //copy snake and update position
                            
            //                 snakeCell* copy=copy_snake(my_head);
            //                 snake_move(copy,i);
            //                 // printf("copy update snake ok\n");
            //                 // displaySnake(copy);
                            
            //                 //copy and update arenas

            //                 int** new_arenaSnake=init_arena(H,L);
            //                 fill_snake(new_arenaSnake,copy,oppenent_head,H,L);
            //                 int*** new_arena=init_arena_tab(H,L);
            //                 merge_arenas_tab(new_arena,new_arenaSnake,H,L,nbWalls,walls);

            //                 //add node

            //                 root->next_moves[i]=init_root();
            //                 // printf("new root ok oui \n");

            //                 //recursion
            //                 printf("depth : %d\n",depth);
            //                 search_move(root->next_moves[i],new_arena,move_found,arena_snake,copy,oppenent_head,walls,nbWalls,H,L,depth-1,i);

            //             }

            //         }
            //     }
            // }
            

            
            
}

decision_tree_node* init_root(){
    decision_tree_node* root=(struct decision_tree_node_*)malloc(sizeof(struct decision_tree_node_));
    return root;
}