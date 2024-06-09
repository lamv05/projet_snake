
typedef struct snakeCell_{
    int x;
    int y;
    int move_cnt;
    struct snakeCell_* nextCell;
}snakeCell;

snakeCell* init_snake(int x,int y);

void snake_move(snakeCell* head,int move);

void add_cell(snakeCell* head,int x,int y);

void displaySnake(snakeCell* head);

void free_snake(snakeCell* head);

snakeCell* copy_snake(snakeCell* head);

snakeCell* copy_node(snakeCell* cell);
