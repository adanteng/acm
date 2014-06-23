#include <stdio.h>

int chess[6][6];
int step;
int flag=0;

int complete() {
    int i,j;
    for (i=1; i<5; i++)
        for (j=1; j<5; j++) {
            if (chess[i][j] != 1)
                return 0;
        }
    return 1;
}

void flip(int row, int col) { 
    int i;
    for (i=1; i<5; i++)
        chess[row][i] = 1 - chess[row][i];
    for (i=1; i<5; i++)
        chess[i][col] = 1 - chess[i][col];
    chess[row][col] = 1 - chess[row][col];
}

void dfs(int row, int col, int deep) {
    if (deep == step) {
        flag = complete();
        return;
    } 

    if (flag == 1 || row == 5) return;

    flip(row, col);
    if (col < 4)
        dfs(row, col+1, deep+1);
    else
        dfs(row+1, 1, deep+1);

    flip(row, col);
    if (col < 4)
        dfs(row, col+1, deep);
    else
        dfs(row+1, 1, deep);
}

main() {
    int i, j;
    char c, nouse;
    for (i=1; i<5; i++)
        for (j=1; j<5; j++) {
            scanf("%c", &c);
            if (c == '-')
                chess[i][j] = 1;
            else if (c == '+')
                chess[i][j] = 0;
            if (j == 4)
                nouse = getchar();
        } 

    for (i=0; i<=16; i++) {
        step = i;
        dfs(1, 1, 0);
        if (flag == 1) break;
    }

    if (flag == 1)
        printf("%d\n", step);
    else
        printf("%s\n", "Impossible");

    /*
    for (i=1; i<5; i++)
        for (j=1; j<5; j++) {
            printf("%d\n", chess[i][j]);
        }
    */

}
