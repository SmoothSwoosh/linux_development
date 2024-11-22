#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EMPTY '.'
#define WALL  '#'
#define ROOMS_IN_ROW 6

struct DSU {
    int *parent;
};

struct Maze {
    struct DSU *dsu;              // DSU of rooms
    char empty;                   // empty cell identifier
    char wall;                    // wall identifier
    int size;                     // size of maze (number of rooms in row)
    int rooms_in_row;             // number of rooms in one row
    int walls_between_rooms_cnt;  // number of walls between rooms
    int *walls_between_rooms;     // walls between rooms
    char *maze;                   // maze itself (access (i, j) cell as (i * size + j))
};

// get random integer from [0..limit]
int get_random(int limit) {
    int divisor = RAND_MAX / (limit + 1);
    int num;
    do {
        num = rand() / divisor;
    } while (num > limit);

    return num;
}

// swap two numbers
void swap(int *a, int *b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
}

// DSU
void DSU__init(struct DSU *dsu, int v) {
    dsu->parent[v] = v;
}

int DSU__find(struct DSU *dsu, int v) {
    if (v == dsu->parent[v]) {
        return v;
    }
    return dsu->parent[v] = DSU__find(dsu, dsu->parent[v]);
}

void DSU__unite(struct DSU *dsu, int u, int v) {
    u = DSU__find(dsu, u);
    v = DSU__find(dsu, v);
    if (u != v) {
        dsu->parent[v] = u;
    }
}

struct Maze * Maze__init(char empty, char wall, int rooms_in_row) {
    struct Maze *maze             = (struct Maze *)malloc(sizeof(struct Maze));
    maze->dsu                     = (struct DSU *)malloc(sizeof(struct DSU));
    maze->dsu->parent             = NULL;
    maze->empty                   = empty;
    maze->wall                    = wall;
    maze->size                    = rooms_in_row * 2 + 1;
    maze->rooms_in_row            = rooms_in_row;
    maze->walls_between_rooms_cnt = (maze->size - 2) * (maze->size - 2) - rooms_in_row * rooms_in_row - (rooms_in_row - 1) * (rooms_in_row - 1);
    maze->walls_between_rooms     = (int *)malloc(maze->walls_between_rooms_cnt * sizeof(int));
    maze->maze                    = (char *)malloc(maze->size * maze->size * sizeof(char));

    // fill maze with walls and rooms should be empty
    for (int i = 0; i < maze->size; ++i) {
        for (int j = 0; j < maze->size; ++j) {
            maze->maze[i * maze->size + j] = (i % 2 == 1 && j % 2 == 1) ? empty : wall;
        }
    }

    // remember cells that can be empty (walls between rooms)
    int k = 0;
    for (int i = 1; i < maze->size - 1; ++i) {
        for (int j = 1; j < maze->size - 1; ++j) {
            if (i % 2 != j % 2) {
                maze->walls_between_rooms[k++] = i * maze->size + j;
            }
        }
    }

    return maze;
}

int Maze__get_room_idx_by_i_and_j(const struct Maze *maze, int i, int j) {
    return (i - 1) / 2 * maze->rooms_in_row + (j - 1) / 2;
}

void Maze__print(const struct Maze *maze) {
    for (int i = 0; i < maze->size; ++i) {
        for (int j = 0; j < maze->size; ++j) {
            printf("%c", maze->maze[i * maze->size + j]);
        }
        printf("\n");
    }
}

void Maze__build(struct Maze *maze) {
    int rooms_num = maze->rooms_in_row * maze->rooms_in_row;
    maze->dsu->parent = (int *)malloc(rooms_num * sizeof(int));

    // initialize DSU
    for (int i = 0; i < rooms_num; ++i) {
        DSU__init(maze->dsu, i);
    }

    int all_rooms_connected = 0;  // 1 if all rooms are connected (so maze is built), otherwise - 0
    while (!all_rooms_connected) {
        // choose random cell from left walls between rooms and empty it
        int cell_idx = get_random(maze->walls_between_rooms_cnt - 1);
        int cell = maze->walls_between_rooms[cell_idx];
        maze->maze[cell] = maze->empty;

        // connect the rooms if possible
        int i = cell / maze->size;
        int j = cell % maze->size;
        if (i % 2 == 0) {
            if (j % 2 == 0) {
                if (maze->maze[cell - 1] == maze->empty && maze->maze[cell + 1] == maze->empty) {
                    // connect the rooms on the left and right
                    int left_room  = Maze__get_room_idx_by_i_and_j(maze, i - 1, j - 1);
                    int right_room = Maze__get_room_idx_by_i_and_j(maze, i - 1, j + 1);
                    DSU__unite(maze->dsu, left_room, right_room);
                }
            } else {
                // connect the rooms above and below
                int above_room = Maze__get_room_idx_by_i_and_j(maze, i - 1, j);
                int below_room = Maze__get_room_idx_by_i_and_j(maze, i + 1, j);
                DSU__unite(maze->dsu, above_room, below_room);

                // connect rooms above and below with rooms on the left and right if possible
                if (j > 2 && maze->maze[cell - 1] == maze->empty && maze->maze[cell - 2] == maze->empty) {
                    // connect with rooms on the left
                    int left_room = Maze__get_room_idx_by_i_and_j(maze, i - 1, j - 2);
                    DSU__unite(maze->dsu, left_room, above_room);
                }
                if (j + 2 < maze->size && maze->maze[cell + 1] == maze->empty && maze->maze[cell + 2] == maze->empty) {
                    // connect with rooms on the right
                    int right_room = Maze__get_room_idx_by_i_and_j(maze, i - 1, j + 2);
                    DSU__unite(maze->dsu, right_room, above_room);
                }
            }
        } else {
            // connect the rooms on the left and right
            int left_room  = Maze__get_room_idx_by_i_and_j(maze, i, j - 1);
            int right_room = Maze__get_room_idx_by_i_and_j(maze, i, j + 1);
            DSU__unite(maze->dsu, left_room, right_room);

            // connect the rooms on the left and right with rooms above and below if possible
            if (i > 2 && maze->maze[cell - maze->size] == maze->empty && maze->maze[cell - 2 * maze->size] == maze->empty) {
                // connect with rooms above
                int above_room = Maze__get_room_idx_by_i_and_j(maze, i - 2, j - 1);
                DSU__unite(maze->dsu, above_room, left_room);
            }
            if (i + 2 < maze->size && maze->maze[cell + maze->size] == maze->empty && maze->maze[cell + 2 * maze->size] == maze->empty) {
                // connect with rooms below
                int below_room = Maze__get_room_idx_by_i_and_j(maze, i + 2, j - 1);
                DSU__unite(maze->dsu, below_room, left_room);
            }
        }

        // remove used cell from consideration by swaping last cell and used cell and decreasing cnt
        swap(&maze->walls_between_rooms[cell_idx], &maze->walls_between_rooms[maze->walls_between_rooms_cnt - 1]);
        --maze->walls_between_rooms_cnt;
    
        // check if all rooms are connected now (they should all have the same parent)
        int p = DSU__find(maze->dsu, 0);  // parent of the first room
        all_rooms_connected = 1;
        for (int k = 1; all_rooms_connected && k < rooms_num; ++k) {
            if (p != DSU__find(maze->dsu, k)) {
                all_rooms_connected = 0;
            }
        }
    }
}

void Maze__destruct(struct Maze *maze) {
    free(maze->dsu->parent);
    free(maze->dsu);
    free(maze->walls_between_rooms);
    free(maze->maze);
    free(maze);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    struct Maze *maze = Maze__init(EMPTY, WALL, ROOMS_IN_ROW);

    Maze__build(maze);

    Maze__print(maze);
    
    Maze__destruct(maze);

    return 0;
}
