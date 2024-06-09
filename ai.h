

void possible_move(int*** arena,snakeCell* head,int H,int L,int lastMoveInt,int* score_move);

typedef struct decision_tree_node_{
    int*** arena;
    int* move_found;
    int** arena_snake;
    snakeCell* my_head;
    int last_move;
    struct decision_tree_node_* next_moves[4]; //{north,east,south,west}

}decision_tree_node;

void new_node(decision_tree_node* root,snakeCell* my_head,snakeCell* oppenent_head,int* walls,int nbWalls,int H,int L,int last_move,int flag);

int search_move(decision_tree_node* root,snakeCell* my_head,snakeCell* oppenent_head,int* walls,int nbWalls,int H,int L,int depth,int last_move);

decision_tree_node* init_root(void);

int choose_move(decision_tree_node* root,snakeCell* my_head,snakeCell* oppenent_head,int* walls,int nbWalls,int H,int L,int depth,int last_move);