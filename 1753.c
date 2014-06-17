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


comnode *find_all_com(int a[], int len, int com_count, int start, int *final_node) {
    int i;
    for (i=start; i<(len-com_count); i++) {
        struct comnode node = find_all_com(a, len, com_count, i+1, final_node);

        struct comnode cur_node;
        cur_node.len = 1;
        cur_node.ptr = (int *)malloc(sizeof(int)*1);
        cur_node.ptr[0] = i;

        comnode result = merge_node(cur_node, node);
        if (result.len == com_count)
           merge_node(result, final_node, *final_node); 
    } 
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
    int maxlen = 16, i, rows=4, columns=4;
    char source_data[17]={0}, s[columns];

    for (i=0; i<rows; i++) {  
        scanf("%s", s);
        int sl = strlen(s);
        if (sl != 4) return 0;        
        strcat(source_data, s);
    }

    for (i=1; i<=maxlen; i++) {
        //find_all_com(source_data, i, 0, &node);
        int fac_count = compute_com_count(16, 2);
        com_index_ptr = (int *)malloc(sizeof(int)*fac_count*i);                
    }
    
    printf("%s\n", source_data); 
}
