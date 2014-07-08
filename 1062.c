#include <stdio.h>
#include <malloc.h>
#include <math.h>

typedef struct node *node_pointer;
typedef struct node {
	int vertex;
	int remain;
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
		*(cindex + dindex[min]) = min;
		*(cindex + dindex[i]) = i;
		min_heapify(dindex, dvalue, cindex, min);
	}
}

main() {
	scanf("%d %d", &level, &item_count);

	if (item_count < 1 || item_count > 100) return;

	heap_size = item_count;

	int item[item_count][3], i, j, adj_index, remain, dvalue[item_count+1], dindex[item_count+1], cindex[item_count+1];

	node_pointer graph[item_count], head, t;

	for (i=0; i<item_count; i++) {
		graph[i] = (node_pointer)malloc(sizeof(node));
	}
		
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
			t->remain = remain;
			t->link = NULL;
			head->link = t;

			head = head->link;
		}

	}

	for (i=1; i<=item_count; i++) {
		dindex[i] = i;
		dvalue[i] = item[0][0];
	}

	for (i=1; i<=item_count; i++) {
		cindex[i] = i;
	}

	int u, v, desv, adj, current_base;
	node_pointer current;
	while (heap_size > 0) {
		u = 1;
		v = heap_size;

		adj = dindex[u] - 1;
		head = graph[adj];
		current = head->link;
		current_base = dvalue[u] - item[dindex[u]-1][0];
		for (; current; current=current->link) {
				if (fabs(item[current->vertex-1][1]-item[adj][1]) <= level && fabs(item[current->vertex-1][1] - item[0][1]) <= level) {
					desv = current_base + current->remain + item[current->vertex-1][0];
					if (desv < dvalue[cindex[current->vertex]])
						dvalue[cindex[current->vertex]] = desv;
				}
		}

		exchange(dindex, u, v);
		exchange(dvalue, u, v);
		cindex[dindex[u]] = u;
		cindex[dindex[v]] = v;

		heap_size--;
		min_heapify(dindex, dvalue, cindex, 1);

		/*
		for (i=1; i<=item_count; i++)
			printf("%d ", dindex[i]);
		printf("\n");
		for (i=1; i<=item_count; i++)
			printf("%d ", cindex[i]);
		printf("\n");
		printf("\n");
		for (i=1; i<=item_count; i++)
			printf("%d ", dvalue[i]);
		printf("\n");
		*/

	}
	
	int min_coins = dvalue[1];
	for (i=1; i<=item_count; i++) {
		if (i == cindex[1]) continue;
		if (dvalue[i] < min_coins) {
			min_coins = dvalue[i];
		}
	}

	printf("%d\n", min_coins);
}
