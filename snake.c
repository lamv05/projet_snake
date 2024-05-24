#include<stdio.h>
#include"snake.h"
#include<stdlib.h>

snakeCell* init_snake(int x,int y){
    struct snakeCell_* head = (struct snakeCell_*)malloc(sizeof(struct snakeCell_));
    head->x=x;
    head->y=y;
    head->move_cnt = 1;
    head->nextCell = NULL;
}

void snake_move(snakeCell* head,int move){
    // printf("got in\n");
    int last_x=head->x;
    int last_y=head->y;
    int last_x_tmp=last_x;
    int last_y_tmp=last_y;
    snakeCell* tmp_snake=head;
    head->move_cnt--;
    if (move==0){ //north
        head->y--;
    }
    else if(move==1){ //east
        head->x++;
    }
    else if(move==2){ //south
        head->y++;
    } 
    else{ // west
        head->x--;
    }
    // printf("head update ok\n");
    while(tmp_snake->nextCell!=NULL){ // update coords

        // tmp_snake=tmp_snake->nextCell;
       

        last_x_tmp=tmp_snake->nextCell->x;
        last_y_tmp=tmp_snake->nextCell->y;

        tmp_snake->nextCell->x=last_x;
        tmp_snake->nextCell->y=last_y;

        last_x=last_x_tmp;
        last_y=last_y_tmp;

        tmp_snake=tmp_snake->nextCell;
    }
    // printf("snake update ok\n");
    if(head->move_cnt==0){
        head->move_cnt=10;
        add_cell(head, last_x_tmp,last_y_tmp);

    }
}

void add_cell(snakeCell* head,int x,int y){
    if (head->nextCell!=NULL){
        add_cell(head->nextCell,x,y);
    }
    else{
        snakeCell* new_cell = (struct snakeCell_*)malloc(sizeof(struct snakeCell_));
        new_cell->x=x;
        new_cell->y=y;
        new_cell->move_cnt = 0;
        new_cell->nextCell = NULL;
        head->nextCell = new_cell;
    }
}

void displaySnake(snakeCell* head){
    printf("cell coords \nx : %d\ny : %d\nmove_cnt = %d\nnext_cell : %p\n",head->x,head->y,head->move_cnt,head->nextCell);
    if (head->nextCell!=NULL){
        displaySnake(head->nextCell);
    }

}

void free_snake(snakeCell* head){
    if(head->nextCell!=NULL){
        free_snake(head->nextCell);
    }
    free(head);
}
