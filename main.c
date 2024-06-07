#include"snakeAPI.h"
#include"arena.h"
#include"snake.h"
#include"ai.h"
#include<stdlib.h>

// runCGS Snake -p 1234 -w 8080  --no-email

int main(){

    connectToServer("localhost",1234,"victor");
    printf("connection to serv succesful\n");

    char gameName[100];
    int ArenasizeX;
    int ArenasizeY;
    int nbWalls;

    // char comment[250];
    // printf("type your comment (no space)\n");
    // scanf("%s",comment);

    printf("queueing\n");
    waitForSnakeGame("TRAINING SUPER_PLAYER difficulty=2 timeout=100 seed=14 start=0",gameName,&ArenasizeX,&ArenasizeY,&nbWalls);
    printf("game found\n");

    int H = ArenasizeY;
    int L = ArenasizeX;
    int** arenaSnake;


     printf("game info : %s, %d*%d, %d walls\n", gameName,ArenasizeX,ArenasizeY,nbWalls);
    
    int position[2]={0,0}; 
    int position_opponent[2]={0,0};
    int* walls;
    walls=(int*)malloc(4*nbWalls*sizeof(int));

    int order =getSnakeArena(walls);
    if (order==0){
        printf("you start\n");
        position[0]=2;
        position_opponent[0]=L-3;
    }
    else{
        printf("bot starts\n");
        position[0]=L-3;
        position_opponent[0]=2;
    }

    if (H%2==0){
        position[1]=(H/2);
    }
    else{
        position[1]=(H-1)/2;
    }
    position_opponent[1]=position[1];

    snakeCell* my_snake_head=init_snake(position[0],position[1]);
    snakeCell* oppenent_snake_head=init_snake(position_opponent[0],position_opponent[1]);

    arenaSnake=init_arena(H,L);

    fill_snake(arenaSnake,my_snake_head,oppenent_snake_head,H,L);
    

    int Gamestate=0;
    int moveInt=4;
    t_move move,moveOpponent;

    int*** arena_tab=init_arena_tab(H,L);

    merge_arenas_tab(arena_tab,arenaSnake,H,L,nbWalls,walls);

    print_arena_tab(arena_tab,H,L);
    
    
    int* move_found=(int*)malloc(sizeof(int)*4);
    move=5;    
    
    while(1){
        
        if (order==0){
            printArena();
            
            // new_node(root,my_snake_head,oppenent_snake_head,walls,nbWalls,H,L,moveInt);
            decision_tree_node* root=init_root();
            position[0]=my_snake_head->x;
            position[1]=my_snake_head->y;

            fill_snake(arenaSnake,my_snake_head,oppenent_snake_head,H,L);
            
            merge_arenas_tab(arena_tab,arenaSnake,H,L,nbWalls,walls);
            
            possible_move(arena_tab,my_snake_head,H,L,(int)move,move_found);
            printf("%d,%d,%d,%d\n",move_found[0],move_found[1],move_found[2],move_found[3]);

            
            moveInt=choose_move(root,move_found,my_snake_head,oppenent_snake_head,walls,nbWalls,H,L,2);
            printf("%d\n",moveInt);
            // scanf("%d",&moveInt);
            free(root);
            
            move =(t_move)moveInt;
                
            Gamestate=sendMove(move);
            snake_move(my_snake_head,moveInt);
                        
        }
        else{
            Gamestate=getMove(&moveOpponent);
            snake_move(oppenent_snake_head,(int)moveOpponent);
            
        }

        if (Gamestate==1) {
            if (order==0){
                printf("you win\n");
                break;
            }
            else{
                printf("you lose\n");
                break;
            }
        }
        else if (Gamestate==-1){
            if (order==0){
                printf("you lose\n");
                break;
            }
            else{
                printf("you win\n");
                break;
            }
        }

        order=!(order);

    }

    free_snake(my_snake_head);
    free_snake(oppenent_snake_head);
    free_arena_tab(arena_tab,H,L);
    // printf("free arena ok\n");
    free(walls);   
    // printf("free walls ok\n");
    printf("FREE OK\n");
    closeConnection();  
}