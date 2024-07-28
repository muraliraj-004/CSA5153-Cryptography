#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 5
#define COLS 5
#define CAPACITY_COLS 2

typedef unsigned long long ull;

void print_state(ull state[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%016llx ", state[i][j]);
        }
        printf("\n");
    }
}

int check_capacity_nonzero(ull state[ROWS][CAPACITY_COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < CAPACITY_COLS; j++) {
            if (state[i][j] != 0) {
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    ull state[ROWS][COLS] = {0};
    int count = 0;
    srand(time(NULL));

    while (!check_capacity_nonzero(state)) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                state[i][j] = rand();
            }
        }
        count++;
    }

    printf("Number of iterations: %d\n", count);
    print_state(state);

    return 0;
}