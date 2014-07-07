#include <stdio.h>
#include <malloc.h>
#include <math.h>

typedef struct node *node_pointer;
typedef struct node {
	int vertex;
	struct node *link;
} node;

int level, item_count, heap_size;

int left(int i) {	
	return 2*i;
}

int right(int i) {
	return 2*i+1;
}

void exchange(int *a, int u, int v) {
	int temp;
	temp = *(a+u);
	*(a+u) = *(a+v);
	*(a+v) = temp;
}

void min_heapify(int *dindex, int *dvalue, int *cindex, int i) { 
	int l = left(i);
	int r = right(i);
	int min;
	if (l<=heap_size && *(dvalue+l)<*(dvalue+i)) {
		min = l;
	} else {
		min = i;
	}
	if (r<=heap_size && *(dvalue+r)<*(dvalue+min))
		min = r;

	int temp1, temp2;
	if (min != i) {
		exchange(dindex, min, i);
		exchange(dvalue, min, i);
		*(cindex + dindex[min]) = *(dindex + i);
		*(cindex + dindex[i]) = *(dindex + min);
		min_heapify(dindex, dvalue, cindex, min);
	}
}

main() {
	scanf("%d %d", &level, &item_count);

	if (item_count < 1 || item_count > 100) return;

	heap_size = item_count;

	int item[item_count][3], i, j, adj_index, remain, remain_arr[item_count+1], dvalue[item_count+1], dindex[item_count+1], cindex[item_count+1];

	node_pointer graph[item_count], head, t;

	for (i=0; i<item_count; i++) {
		graph[i] = (node_pointer)malloc(sizeof(node));
	}

	remain_arr[1] = 0;
		
	for (i=0; i<item_count; i++) {
		scanf("%d %d %d", &item[i][0], &item[i][1], &item[i][2]);

		graph[i]->vertex = i+1;
		graph[i]->link = NULL;

		head = graph[i];			
		int exchange_item_count = item[i][2];
		for (j=0; j<exchange_item_count; j++) {
			scanf("%d %d", &adj_index, &remain);

			t = (node_pointer)malloc(sizeof(node));
			t->vertex = adj_index;
			t->link = NULL;
			head->link = t;

			remain_arr[adj_index] = remain;

			head = head->link;
		}

	}

	dindex[1] = 1;
	dvalue[1] = 0;
	for (i=2; i<=item_count; i++) {
		dindex[i] = i;
		dvalue[i] = item[0][0];
	}

	for (i=1; i<=item_count; i++) {
		cindex[i] = i;
	}
		for (i=1; i<=item_count; i++)
			printf("%d ", remain_arr[i]);
		printf("\n");

	int u, v, desv, adj;
	while (heap_size > 0) {
		u = 1;
		v = heap_size;

		adj = dindex[u] - 1;
		head = graph[adj]->link;
		for (; head; head=head->link) {
			if (fabs(item[head->vertex-1][1]-item[adj][1]) <= level && fabs(item[head->vertex-1][1] - item[0][1]) <= level) {
				desv = remain_arr[dindex[u]] + remain_arr[head->vertex] + item[head->vertex-1][0];				
				if (desv < dvalue[dindex[head->vertex]])
					dvalue[dindex[head->vertex]] = desv;
			}
		}

		exchange(dindex, u, v);
		exchange(dvalue, u, v);
		cindex[u] = dindex[u];
		cindex[v] = dindex[v];

		heap_size--;
		min_heapify(dindex, dvalue, cindex, 1);
		for (i=1; i<=item_count; i++)
			printf("%d ", dindex[i]);
		printf("\n");
		for (i=1; i<=item_count; i++)
			printf("%d ", dvalue[i]);
		printf("\n");
		for (i=1; i<=item_count; i++)
			printf("%d ", cindex[i]);
		printf("\n");

	}
	
	int min_coins;
	if (item_count == 1) {
		min_coins = item[0][0];
	} else {
		for (i=2; i<=item_count; i++) {
			if (dvalue[i] < min_coins) {
				min_coins = dvalue[i];
			}
		}
	}

	printf("%d\n", min_coins);
}
