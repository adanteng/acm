#include <stdio.h>
#include <malloc.h>

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

void min_heapify(int *dindex, int *dvalue, int i) { 
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
		temp1 = dindex[min];
		temp2 = dvalue[min];
		dindex[min] = dindex[i];
		dvalue[min] = dvalue[i];
		dindex[i] = temp1;
		dvalue[i] = temp2;
		min_heapify(dindex, dvalue, min);
	}
}

main() {
	scanf("%d %d", &level, &item_count);

	heap_size = item_count;

	int item[item_count][3], i, j, adj_index, remain, remain_arr[item_count+1], dvalue[item_count+1], dindex[item_count+1];

	node_pointer graph[item_count], head, t;

	for (i=0; i<item_count; i++) {
		graph[i] = (node_pointer)malloc(sizeof(node));
	}

	remain_arr[1] = 0;
		
	for (i=0; i<item_count; i++) {
		scanf("%d %d %d", &item[i][0], &item[i][1], &item[i][2]);

		graph[i]->vertex = i+1;
		graph[i]->link = NULL;

		//printf("\n%d ", graph[i]->vertex);

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

	for (i=1; i<item_count+1; i++)
		printf("%d ", dindex[i]);
	printf("\n");
	for (i=1; i<item_count+1; i++)
		printf("%d ", dvalue[i]);
	printf("\n");
	for (i=1; i<item_count+1; i++)
		printf("%d ", remain_arr[i]);
	printf("\n");

	int temp1, temp2, u, v, desv, adj;
	while (heap_size > 0) {
		u = 1;
		v = heap_size;

		adj = dindex[u] - 1;
		head = graph[adj]->link;
		for (; head; head=head->link) {			
			desv = remain_arr[u] + remain_arr[head->vertex] + item[head->vertex-1][0];

			printf("%d \n", head->vertex-1);

			if (desv < dvalue[head->vertex])
				dvalue[head->vertex] = desv;
		}

	for (i=1; i<=item_count; i++)
		printf("%d ", dvalue[i]);
	printf("\n");


		temp1 = dindex[u];
		dindex[u] = dindex[v];
		dindex[v] = temp1;

		temp2 = dvalue[u];
		dvalue[u] = dvalue[v];
		dvalue[v] = temp2;

		heap_size--;
		min_heapify(dindex, dvalue, 1);

		if (heap_size == 2) break;

	}


	/*
	for (i=0; i<item_count; i++) {
		head = graph[i];
		for(; head; head=head->link) {
			printf("%d ", head->vertex);
		}
		printf("\n");
	}
	*/
}
