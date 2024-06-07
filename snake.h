
typedef struct snakeCell_{
    int x;
    int y;
    int move_cnt;
    struct snakeCell_* nextCell;
}snakeCell;

snakeCell* init_snake(int x,int y);

void snake_move(snakeCell* head,int move);

void add_cell(snakeCell* head,int x,int y);

void fill_snake(int** arena,snakeCell* head,snakeCell* oppenent_headint,int H,int L);

void displaySnake(snakeCell* head);

void free_snake(snakeCell* head);

snakeCell* copy_snake(snakeCell* head);

void copy_snake2(snakeCell* head,snakeCell* desti);