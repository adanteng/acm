#include <stdio.h>

typedef struct node *node_pointer
typedef struct node {
	int vertex;
	struct node *link;
}

main() {
	int level, item_count;
	scanf("%d %d", &level, &item_count);

	int item[item_count][3], i;
	int itemr[item_count];
	
	for (i=1; i<item_count; i++) {
		itemr[i] = -1;
	}

	node_pointer graph[item_count];
	
	for (i=0; i<item_count; i++) {
		scanf("%d %d %d", &item[i][0], &item[i][1], &item[2]);			

		graph[i]->vertex = i;
		graph[i]->
	}

	for (i=0; i<item_count; i++) {
		
	}
	

}
