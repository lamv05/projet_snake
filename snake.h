
typedef struct snakeCell_{
    int x;
    int y;
    int move_cnt;
    struct snakeCell_* nextCell;
}snakeCell;

void init_snake(snakeCell* head,int x,int y);

void snake_move(snakeCell* head,int move);

void add_cell(snakeCell* head,int x,int y);
