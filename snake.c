#include<stdio.h>
#include"snake.h"
#include<stdlib.h>

snakeCell* init_snake(int x,int y){
    struct snakeCell_* head = (struct snakeCell_*)malloc(sizeof(struct snakeCell_));
    head->x=x;
    head->y=y;
    head->move_cnt = 1;
    head->nextCell = NULL;
    return head;
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
        // printf("snake grandi\n");
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
        new_cell->move_cnt = 99;
        new_cell->nextCell = NULL;
        head->nextCell = new_cell;
        // printf("cell added %p\n",new_cell);
    }
}

void displaySnake(snakeCell* head){
    printf("cell coords x : %d\ty : %d\tcell address : %p\tmove_cnt = %d\tnext_cell : %p\n\n",head->x,head->y,head,head->move_cnt,head->nextCell);
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

snakeCell* copy_snake(snakeCell* head){
    
    snakeCell* copy_head = (struct snakeCell_*)malloc(sizeof(struct snakeCell_));
    
    copy_head->x=head->x; 
    copy_head->y=head->y;
    copy_head->move_cnt=head->move_cnt;
    copy_head->nextCell=NULL;
    snakeCell* head_tmp=head;
    snakeCell* copy_tmp=copy_head;

    
    while(head_tmp->nextCell!=NULL){

        copy_tmp->nextCell=copy_node(head_tmp);

        head_tmp=head_tmp->nextCell;
        copy_tmp=copy_tmp->nextCell;
    }
    return copy_head;
}


snakeCell* copy_node(snakeCell* cell){
    snakeCell* new_cell = (struct snakeCell_*)malloc(sizeof(struct snakeCell_));
    new_cell->x=cell->nextCell->x;
    new_cell->y=cell->nextCell->y;
    new_cell->move_cnt=cell->nextCell->move_cnt;
    new_cell->nextCell=NULL;
    return new_cell;
}