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

typedef struct comnode {
    int len;
    int *ptr;
} comnode;

int *com_index_ptr;

int compute_com_count(int n, int k);

comnode merge_node(struct comnode node1, struct comnode node2) {
    int len1 = node1.len, len2 = node2.len, *ptr1 = node1.ptr, *ptr2 = node2.ptr, i;
    int *result = (int *)malloc(sizeof(int)*(len1+len2));

    for (i=0; i<len1; i++) {
        *(result+i) = *(ptr1+i);
    }

    for (i=0; i<len2; i++) {
        *(result+i+len1) = *(ptr2+i);
    }
        
    struct comnode resultnode;
    resultnode.len = len1 + len2;
    resultnode.ptr = result;            
    return resultnode;            
}


/*
comnode find_all_com(int a[], int len, int com_count, int s) {
	if (com_count == 1) {
		return &a[s];
	}

	int next_com_count = com_count - 1;
	int i ,j ,k;
	for (i=s; i<(len-com_count); i++) {
		comnode node = find_all_com(a, len, next_com_count, i+1);
		int len = node.len;
		int *ptr = node.ptr;
	}
	int total_size = len*com_count;

	int *res = (int *)malloc(sizeof(int)*total_size);
	for (j=0; j<(total_size/com_count); j++) {
		for (k=1; k<=next_com_count; k++) {
			*(res+j*next_com_count+k) = *(ptr+j*next_com_count+k);
		} 
	}
}
*/

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

    /*
	int k,h;
    for (i=1; i<=maxlen; i++) {
        int fac_count = compute_com_count(maxlen, i);
        com_index_ptr = (int *)malloc(sizeof(int)*fac_count*i); 

		if (i == 1) {
			for (k=0; k<maxlen; k++) 
				*(com_index_ptr+k) = k+1;
		} else {
			comnode node = find_all_com(index, maxlen, i, i-1);
			int len = node.len;
			int *p = node.ptr;
			
			for (k=0; k<len; k++) {
				for (h=i-1; h>0; h--) {
					*(com_index_ptr+k*i+h) = *(p+k*i+h-1); 
				}
			}
		}
    }
    */

    int *p = get_all_combine(4, 4, 4, 0);
    int fac = compute_com_count(4, 4);
    int i;
    for (i=0; i<fac*4; i++)
        printf("%d", *(p+i));

    printf("\n");
    
    //printf("%s\n", source_data); 
}
