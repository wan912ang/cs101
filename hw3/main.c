#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int i = 0;
void hanoi(int n, char A, char B, char C) {
    if(n == 1) {
        i++;
    }
    else {
        hanoi(n-1, A, C, B);
        hanoi(1, A, B, C);
        hanoi(n-1, B, A, C);
    }
}

int main() {

    clock_t start, end;

    int n;
    printf("請輸入盤數：");
    scanf("%d", &n);

    start = clock();

    hanoi(n, 'A', 'B', 'C');

    end = clock();

    double diff = end-start;
    printf("%d %f  sec",i, diff / CLOCKS_PER_SEC );

    return 0;
}