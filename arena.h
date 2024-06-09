void printTHEarena(int** arena,int H,int L);

int** init_arena(int H,int L);

void freeTHEarena(int** arena,int H,int L);

void fill_snake(int** arena,snakeCell* head,snakeCell* oppenent_head,int H,int L);

void refresh_arena(int** arena,int H,int L);

int*** init_arena_tab(int H,int L);

void free_arena_tab(int*** arena,int H,int L);

void print_arena_tab(int*** arena,int H,int L);

void fill_arena_tab(int*** arena,int nbWalls,int* walls);

void merge_arenas_tab(int*** arena,int** arenaSnake,int H,int L,int nbWalls,int* walls);

void refresh_arena_tab(int*** arena,int H,int L);
