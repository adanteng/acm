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

int *com_index_ptr;
int compute_com_count(int n, int k);

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
    

    /*
    for (i=0; i<c*fac; i++) 
        printf("%d\n", *(res+i));
     */

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

bool can_complete(int *p, int fac, int c, char *s) {
	int i, j;
	for (i=0; i<fac; i++) {
		int *cur = (int *)malloc(sizeof(int)*c);
		for	(j=0; j<c; j++) {
			*(cur+j) = *(p+i*c+j);	
		}

	}	
	return false;
}

char *flip(int *p, int c, char *s) {
	int i;
	for (i=0; i<c; i++) {
		
	}
}

char switch_piece(char c) {
	if (c == 'b')
		return 'w';
	else if (c == 'w')
		return 'b';
}

bool check_complete(char *s, int len) {
	char first = *s;
	int i;
	for (i=0; i<len; i++) {
		if (first != *(s+i))
			return false;
	}
	return true;
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

	int index[maxlen];
	for (i=0; i<maxlen; i++) {
		index[i] = i;
	}
    */


	int max=16, i;
	for (i=1; i<=max; i++) {
		int *p = get_all_combine(max, max, i, 0);	
		int fac = compute_com_count(max, i);
	}
    
    //printf("%s\n", source_data); 
}
