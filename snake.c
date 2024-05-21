#include<stdio.h>
#include"snake.h"
#include<stdlib.h>

void init_snake(snakeCell* head,int x,int y){
    snakeCell* head = (struct snakeCell_*)malloc(sizeof(struct snakeCell_));
    head->x=x;
    head->y=y;
    head->move_cnt = 0;
    head->nextCell = NULL;
}

void snake_move(snakeCell* head,int move){
    int last_x=head->x;
    int last_y=head->y;
    int last_x_tmp=head;
    int last_y_tmp=head;
    snakeCell* tmp_snake;
    head->move_cnt--;
    if (move==0){ //north
        head->y++;
    }
    else if(move==1){ //east
        head->x++;
    }
    else if(move==2){ //south
        head->y--;
    } 
    else{ // west
        head->x--;
    }
    while(tmp_snake->nextCell!=NULL){

        // tmp_snake=tmp_snake->nextCell;

        last_x_tmp=tmp_snake->nextCell->x;
        last_y_tmp=tmp_snake->nextCell->y;

        tmp_snake->nextCell->y=last_x;
        tmp_snake->nextCell->y=last_y;

        last_x=last_x_tmp;
        last_y=last_y_tmp;

        tmp_snake=tmp_snake->nextCell;
    }
    if(head->move_cnt==0){
        head->move_cnt=10;

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

void update_coords(snakeCell* head);