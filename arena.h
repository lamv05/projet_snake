void printTHEarena(int** arena,int H,int L);

int** init_arena(int H,int L);

void freeTHEarena(int** arena,int H,int L);

void fill_walls(int** arena,int nbWalls,int* walls);

void refresh_arena(int** arena,int H,int L);

void merge_arenas(int** arenaSnake,int** arenaWall,int** arena,int H,int L);

int*** init_arena_tab(int H,int L);

void free_arena_tab(int*** arena,int H,int L);

void print_arena_tab(int*** arena,int H,int L);

void fill_arena_tab(int*** arena,int nbWalls,int* walls);

void merge_arenas_tab(int*** arena,int*** arenaWall,int** arenaSnake,int H,int L);