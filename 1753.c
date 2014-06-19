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
#include <malloc.h>
#include <string.h>
#include <math.h>

int check_all_com(int *p, int fac, int c, char *s);
int compute_com_count(int n, int k);
char switch_piece(char c);
int can_complete(char *s, int len);
void flip(char *s, int pos);
int get_index_by_cor(int x, int y);

int *get_all_combine(int maxn, int n, int c, int s) {
    int i, len=n-c+1, end=len+s, *res, pi=0;
    if (c == 1) {
        res = (int *)malloc(sizeof(int)*(end-s));
        for (i=s; i<end; i++) {
            *(res+(pi++)) = i+1;
        }

        /*
        for (i=0; i<len-s; i++) {
            printf("%d", *(res+i));
        }
        printf("\n");
        */
        return res;
    }

    int j, k, fac;
    int *arrptr[len];
    int arrlen[len];
    int fi=0;
    int nexts = s+1;
    int nextn = n-1;
    int nextc = c-1;    
    pi=0;
    for (i=s; i<end; i++) {
        int ele = i+1;

        printf("%d %d %d %d\n", maxn, nextn, nextc, nexts);
        int *childres = get_all_combine(maxn, nextn, nextc, nexts);
        int childfac = compute_com_count(nextn, nextc);
        int *p = (int *)malloc(sizeof(int)*c*childfac);

        fi = 0;
        for (j=0; j<childfac; j++) {
            *(p+(fi++)) = ele;
            for (k=0; k<nextc; k++) {
                *(p+(fi++)) = *(childres+j*nextc+k);
            }
        }

        /*
        for (j=0; j<childfac*c; j++) {
            printf("%d", *(p+j));
        }
        printf("\n");
        */

        /*
        printf("%d\n", len);
        */

        arrptr[pi] = p;
        arrlen[pi] = childfac;

        nexts = nexts + 1;
        nextn = nextn - 1;
        pi++;
    }

    /*
    for (j=0; j<4; j++) 
        printf("%d", *(arrptr[1]+j));
    printf("\n");
    */

    fi = 0;
    fac = compute_com_count(n, c);
    res = (int *)malloc(sizeof(int)*c*fac);
    for (pi=0; pi<len; pi++) {
        int tempfac = arrlen[pi];
        for (j=0; j<tempfac; j++)
            for (k=0; k<c; k++) { 
                *(res+(fi++)) = *(arrptr[pi]+j*c+k);
            }

    }
    

    for (i=0; i<c*fac; i++) 
        printf("%d|", *(res+i));
    printf("\n");

    return res;
}

int compute_com_count(int n, int k) {
    int i = 1;
    int temp1 = 1,temp2 =1;
    if (n==k) {
        return 1;
    } else if (k == 1) {
        return n;
    } else {
        for (i=1;i<=k;i++) {
            temp1 *= n-i+1;
            temp2 *= i;
        }
        temp1 /= temp2; 
        return temp1;
    } 
}

int check_all_com(int *p, int fac, int c, char *s) {
	int i, j;
	for (i=0; i<fac; i++) {
        char *ts = (char *)malloc(sizeof(char)*16);        
        strcpy(ts, s);        

		for	(j=0; j<c; j++) {
			int pos = *(p+i*c+j);
            flip(ts, pos);
		}

        if (can_complete(ts, 16))
            return 1;
	}	
	return 0;
}

void flip(char *s, int pos) {
    printf("%d\n", pos);
    float f = (float)pos/(float)4;
    int x = (int)ceil(f);
    int y = pos%4;
    if (y == 0) y = 4;    

    int index;
    //cur
    index = get_index_by_cor(x, y) - 1;
    *(s+index) = switch_piece(*(s+index));

    //up
    if (x-1 > 0) {
        index = get_index_by_cor(x-1, y) - 1;
        *(s+index) = switch_piece(*(s+index));    
    } 
    //down
    if (x+1 > 0) {
        index = get_index_by_cor(x+1, y) - 1;
        *(s+index) = switch_piece(*(s+index));
    }
    //left
    if (y-1 > 0) {
        index = get_index_by_cor(x, y-1) - 1;
        *(s+index) = switch_piece(*(s+index));
    }
    //right
    if (y+1 > 0) {
        index = get_index_by_cor(x, y+1) - 1;
        *(s+index) = switch_piece(*(s+index));
    }

    printf("%s\n", s);
}

int get_index_by_cor(int x, int y) {
    return (x-1)*4 + y;
}

char switch_piece(char c) {
	if (c == 'b')
		return 'w';
	else if (c == 'w')
		return 'b';
}

int can_complete(char *s, int len) {
	char first = *s;
	int i;
	for (i=0; i<len; i++) {
		if (first != *(s+i))
			return 0;
	}
	return 1;
}

main() {
        /*
    int maxlen = 16, i, rows=4, columns=4;
    char source_data[16]={0}, s[columns];	

    for (i=0; i<rows; i++) {  
        scanf("%s", s);
        int sl = strlen(s);
        if (sl != 4) return 0;        
        strcat(source_data, s);
    }
    */

    /*
	int index[maxlen];
	for (i=0; i<maxlen; i++) {
		index[i] = i;
	}*/


    /*
	int max=16;
	for (i=1; i<=max; i++) {
        printf("%d\n", i);
        printf("\n");
		int *p = get_all_combine(max, max, i, 0);
		int fac = compute_com_count(max, i);

	}
    */
		int *p = get_all_combine(16, 16, 9, 0);


    /*
    int *p = (int *)malloc(sizeof(int)*2);
    *p = 1;
    *(p+1) = 2;
    *(p+2) = 3;
    int st = check_all_com(p, 1, 3, source_data);
    */


    
    //printf("%s\n", source_data); 
}
