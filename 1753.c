/*
 * =====================================================================================
 *
 *       Filename:  1753.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  06/17/2014 02:16:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdio.h>

int chess[6][6];
int r[5] = {-1, 1, 0, 0, 0};
int c[5] = {0, 0, -1, 1, 0};
int step;
int flag=0;

int complete() {
    int i,j;
    for (i=1; i<5; i++)
        for (j=1; j<5; j++) {
            if (chess[i][j] != chess[1][1])
                return 0;
        }
    return 1;
}

void flip(int row, int col) { 
    int i;
    for (i=0; i< 5; i++)
        chess[row+r[i]][col+c[i]] = 1 - chess[row+r[i]][col+c[i]];
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
            if (c == 'b')
                chess[i][j] = 1;
            else if (c == 'w')
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
