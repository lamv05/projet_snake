#include"snakeAPI.h"
#include"arena.h"
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
    waitForSnakeGame("TRAINING RANDOM_PLAYER",gameName,&ArenasizeX,&ArenasizeY,&nbWalls);
    printf("game found\n");

    int H = ArenasizeY;
    int L = ArenasizeX;
    int** arena;

    // printf("game info : %s, %d*%d, %d walls\n", gameName,ArenasizeX,ArenasizeX,nbWalls);
    
    int* walls;
    walls=(int*)malloc(4*nbWalls*sizeof(int));

    int order =getSnakeArena(walls);
    if (order==0){
        printf("you start\n");
    }
    else{
        printf("bot starts\n");
    }



    arena=setupTHEarena(H,L,nbWalls,walls);
    printTHEarena(arena,H,L);





















    int Gamestate=0;
    int moveInt;
    t_move move,moveOpponent;

    // int oui=0;
    //scanf("%d",&oui);
    
    while(1){
        
        

        


        if (order==0){
            printArena();

            printf("OUUUAH TOUT MARCHE\n");
            break;

            printf("your move : NORTH=0/EAST=1/SOUTH=2/WEST=3\n");
            

            // scanf("%d",(int*)&move);
            scanf("%d",&moveInt);
            move =(t_move)moveInt;
                
            Gamestate=sendMove(move);
            
            
            
        }
        else{
            printArena();
            Gamestate=getMove(&moveOpponent);
            // order=0;
            

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


    freeTHEarena(arena,H,L);
    printf("free arena ok\n");
    free(walls);   
    printf("free walls ok\n");
    closeConnection();  
}