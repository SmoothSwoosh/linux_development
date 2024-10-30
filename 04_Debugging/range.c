#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void print_help() {
    printf("Usage:\n");
    printf("   range N            outputs sequence [0, 1, ... N-1]\n");
    printf("   range M N          outputs sequence [M, M+1, ... N-1]\n");
    printf("   range M N S        outputs sequence [M, M+S, M+2S, ... N-1]\n");
}

int main(int argc, char *argv[]) {
    int N = 0, M = 0, S = 1;
    if (argc == 1) {
        print_help();
        return 0;
    } else if (argc == 2) {
        M = atoi(argv[1]);
    } else if (argc == 3) {
        N = atoi(argv[1]);
        M = atoi(argv[2]);
    } else if (argc == 4) {
        N = atoi(argv[1]);
        M = atoi(argv[2]);
        S = atoi(argv[3]);
        if (S == 0) {
            printf("Step cannot be zero\n");
            return 1;
        }
    } else {
        printf("Wrong number of arguments\n");
        return 1;
    }

    if (S < 0 && N < M) {
        swap(&N, &M);
    }

    for (int num = N; (S > 0) ? num < M : num > M; num += S) {
        printf("%d\n", num);
    }

    return 0;
}
