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
    waitForSnakeGame("TRAINING RANDOM_PLAYER difficulty=2 timeout=100 seed=14 start=0",gameName,&ArenasizeX,&ArenasizeY,&nbWalls);
    printf("game found\n");

    int H = ArenasizeY;
    int L = ArenasizeX;
    int** arenaSnake;
    // int** arenaWall;
    // int** arena;

     printf("game info : %s, %d*%d, %d walls\n", gameName,ArenasizeX,ArenasizeY,nbWalls);
    
    int position[2]={0,0}; //careful with odd or pair
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

// ok up to here

    snakeCell* my_snake_head=init_snake(position[0],position[1]);
    snakeCell* oppenent_snake_head=init_snake(position_opponent[0],position_opponent[1]);
    printf("init_snake ok\n");
    snakeCell* copy=copy_snake(my_snake_head);

    displaySnake(my_snake_head);
    printf("1st print ok\n");
    displaySnake(copy);



    arenaSnake=init_arena(H,L);
    // arenaWall=init_arena(H,L);
    // arena=init_arena(H,L);
    // printf("setup ok\n");
    fill_snake(arenaSnake,my_snake_head,oppenent_snake_head,H,L);
    // printTHEarena(arenaSnake,H,L);
    // fill_walls(arenaWall,nbWalls,walls);
    // printTHEarena(arenaWall,H,L);
    // printTHEarena(arena,H,L);

    int Gamestate=0;
    int moveInt=4;
    t_move move,moveOpponent;

    // int oui=0;
    //scanf("%d",&oui);

    // printf("arena tab init\n");

    int*** arena_tab=init_arena_tab(H,L);
    // print_arena_tab(arena_tab,H,L);
    // int*** arenaWall_tab=init_arena_tab(H,L);

    // fill_arena_tab(arenaWall_tab,nbWalls,walls);

    merge_arenas_tab(arena_tab,arenaSnake,H,L,nbWalls,walls);

    // arena_tab[0][0][0]=55;
    printTHEarena(arenaSnake,H,L);
    // print_arena_tab(arenaWall_tab,H,L);

    print_arena_tab(arena_tab,H,L);
    
    
    int* move_found=(int*)malloc(sizeof(int)*4);

    decision_tree_node* root=init_root();
    int** tab;
    tab=(int**)malloc(sizeof(int*)*L);
    for (int i=0;i<L;i++){
        tab[i]=(int*)malloc(sizeof(int)*H);
    }
    
    while(1){
        
        if (order==0){
            printArena();
            

            position[0]=my_snake_head->x;
            position[1]=my_snake_head->y;

            // printf("OUUUAH TOUT MARCHE\n");
            // break;

            fill_snake(arenaSnake,my_snake_head,oppenent_snake_head,H,L);
            // printTHEarena(arenaSnake,H,L);
            // print_arena_tab(arena_tab,H,L);
            merge_arenas_tab(arena_tab,arenaSnake,H,L,nbWalls,walls);
            // printTHEarena(arenaWall,H,L);
            // displaySnake(oppenent_snake_head);
            // displaySnake(my_snake_head);
            // snakeCell* copy=copy_snake(my_snake_head);

            // displaySnake(copy);

            // printf("your move : NORTH=0/EAST=1/SOUTH=2/WEST=3\n");
            

            // scanf("%d",(int*)&move);

            // scanf("%d",&moveInt);
            
            // moveInt=0;
            move=5;
            // printf("my snake head x:%d,y:%d\n",position[0],position[1]);

            // possible_move(arena_tab,my_snake_head,H,L,(int)move,score_move);
            // printf("%d,%d,%d,%d\n",score_move[0],score_move[1],score_move[2],score_move[3]);
            moveInt=search_move(root,arena_tab,move_found,arenaSnake,my_snake_head,oppenent_snake_head,walls,nbWalls,H,L,2,5);
            printf("%d\n",moveInt);
            // scanf("%d",&moveInt);
            break;
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
    // printf("free snake ok\n");
    // freeTHEarena(arena,H,L);
    // free_arena_tab(arenaWall_tab,H,L);
    free_arena_tab(arena_tab,H,L);
    // printf("free arena ok\n");
    free(walls);   
    // printf("free walls ok\n");
    printf("FREE OK\n");
    closeConnection();  
}