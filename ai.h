

int findMove(int** arena,int* position,int H,int L,int lastMove);

void possible_move(int*** arena,snakeCell* head,int H,int L,int lastMoveInt,int* score_move);

typedef struct decision_tree_node_{
    int*** arena;
    int* move_found;
    int** arena_snake;
    snakeCell* my_head;
    snakeCell* oppenent_head;
    struct decision_tree_node_* next_moves[4]; //{north,east,south,west}
    int last_move;

}decision_tree_node;

decision_tree_node* init_root(int*** arena,int* move_found);

int search_move();

void free_tree();