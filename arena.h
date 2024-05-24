void printTHEarena(int** arena,int H,int L);

int** init_arena(int H,int L);

void freeTHEarena(int** arena,int H,int L);

void fill_walls(int** arena,int nbWalls,int* walls);

void refresh_arena(int** arena,int H,int L);

void merge_arenas(int** arenaSnake,int** arenaWall,int** arena,int H,int L);