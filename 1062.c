#include <stdio.h>
#include <malloc.h>

typedef struct node *node_pointer;
typedef struct node {
	int vertex;
	struct node *link;
} node;

main() {
	int level, item_count;
	scanf("%d %d", &level, &item_count);

	int item[item_count][3], i, j, adj_index, remain;

	node_pointer graph[item_count], head, t;

	for (i=0; i<item_count; i++) {
		graph[i] = (node_pointer)malloc(sizeof(node));
	}
		
	for (i=0; i<item_count; i++) {
		scanf("%d %d %d", &item[i][0], &item[i][1], &item[i][2]);

		graph[i]->vertex = i+1;
		graph[i]->link = NULL;

		printf("\n%d ", graph[i]->vertex);

		head = graph[i];			
		int exchange_item_count = item[i][2];
		for (j=0; j<exchange_item_count; j++) {
			scanf("%d %d", &adj_index, &remain);

			t = (node_pointer)malloc(sizeof(node));
			t->vertex = adj_index;
			t->link = NULL;
			head->link = t;

			head = head->link;
		}

	}

	for (i=0; i<item_count; i++) {
		head = graph[i];
		for(; head; head=head->link) {
			printf("%d ", head->vertex);
		}
		printf("\n");
	}
}
