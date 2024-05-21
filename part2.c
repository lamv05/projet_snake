#include"snakeAPI.h"
#include<stdlib.h>

int main(){

    connectToServer("localhost",1234,"victor");
    printf("connection to serv succesful\n");

    char gameName[100];
    int ArenasizeX;
    int ArenasizeY;
    int nbWalls;

    char comment[250];
    printf("type your comment (no space)\n");
    scanf("%s",comment);

    printf("queueing\n");
    waitForSnakeGame("TRAINING RANDOM_PLAYER",gameName,&ArenasizeX,&ArenasizeY,&nbWalls);
    printf("game found\n");
    //printf("game info : %s, %d*%d, %d walls\n", gameName,*ArenasizeX,*ArenasizeX,*nbWalls);
    
    int* walls;
    walls=(int*)malloc(nbWalls*sizeof(int));

    int order =getSnakeArena(walls);
    if (order==0){
        printf("you start\n");
    }
    else{
        printf("bot starts\n");
    }


    // free(walls);


    // int H = ArenasizeY;
    // int L = ArenasizeX;
    // int** arena;
    // arena=(int**)malloc(sizeof(int*)*L);
    // for (int i=0;i<H;i++){
    //     // arena[i]=(int*)malloc(sizeof(int)*H);
    // }

    // for (int j=0;j<H;j++){
    //     for (int i=0;i<L;i++){
    //         printf("0 ");
    //     }
    //     printf("\n");
    // }



    // for(int i=0;i<H;i++)
    //     free(arena[i]);
    // free(arena);





    int Gamestate=0;
    int moveInt;
    t_move move,moveOpponent;

    // int oui=0;
    //scanf("%d",&oui);
    
    while(1){
        

        if (order==0){
            printArena();
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

    // if ((state==-1 && order==0) || (state==-1 && order==1)){
    //     printf("you lose\n");
    // }
    // else{
    //     printf("you win\n");
    // }

    free(walls);    
    closeConnection();  
}