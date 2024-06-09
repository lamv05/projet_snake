#include<stdio.h>
#include"snake.h"
#include"ai.h"
#include"arena.h"
#include<stdlib.h>
#include"snakeAPI.h"

void possible_move(int*** arena,snakeCell* head,int H,int L,int lastMoveInt,int* score_move){

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
}

void new_node(decision_tree_node* root,snakeCell* my_head,snakeCell* oppenent_head,int* walls,int nbWalls,int H,int L,int last_move,int flag){
    root->move_found=(int*)malloc(sizeof(int)*4);
    root->last_move=last_move;

    if (flag==0){
        root->my_head=my_head;
    }
    else{
        root->my_head=copy_snake(my_head);
    }

    if (flag==1){
        snake_move(root->my_head,last_move);
    }

    root->arena_snake=init_arena(H,L);
    fill_snake(root->arena_snake,root->my_head,oppenent_head,H,L);
         
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
            new_node(root,my_head,oppenent_head,walls,nbWalls,H,L,last_move,1);
            
            if (depth==0){
                for(int i=0;i<4;i++){
                    if(root->move_found[i]==1){
                        score_move++;
                    }
                }
            }
            else if (depth>0){ 
                for (int i=0;i<4;i++){
                    if (root->move_found[i]==1){

                        score_move=score_move+search_move(root->next_moves[i],root->my_head,oppenent_head,walls,nbWalls,H,L,depth-1,i);
                        
                    }
                }
            }
            free(root->move_found);
            free_snake(root->my_head);
            free(root);
            return score_move;         
}

decision_tree_node* init_root(){
    decision_tree_node* root=(struct decision_tree_node_*)malloc(sizeof(struct decision_tree_node_));
    return root;
}

int choose_move(decision_tree_node* root,snakeCell* my_head,snakeCell* oppenent_head,int* walls,int nbWalls,int H,int L,int depth,int last_move){
    int tab[4]={0,0,0,0};

    new_node(root,my_head,oppenent_head,walls,nbWalls,H,L,last_move,0);
    for (int i=0;i<4;i++){
        if (root->move_found[i]==1){
      
            tab[i]=search_move(root->next_moves[i],root->my_head,oppenent_head,walls,nbWalls,H,L,depth,i);            
            
            if (tab[i]>100000){
                printf("%d %d\n",i,tab[i]);
                return i;
            }
        }
    }
    free(root->move_found);
    free(root);
    
    printf("\n%d,%d,%d,%d\n",tab[0],tab[1],tab[2],tab[3]);
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