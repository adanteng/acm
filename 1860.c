#include <stdio.h>

int n, m, s;
float v;

main() {
	scanf("%d %d %d %f", &n, &m, &s, &v);

	if (s>n || s<1 || s>100 || n<1 || n>100 || m<1 || m>100 || v<0 || v>1000) return;

	int i, j, edge[m*2][2];
	float d[n+1], exchange[m*2][2];
	d[s] = v;
	for (i=0; i<n+1; i++) {
		if (i!=s) d[i] = -1;
	} 

	/*
	for (i=0; i<n+1; i++)
		printf("%f\n", d[i]);
	printf("\n");
	*/

	for (i=0; i<m*2; i=i+2) {
		scanf("%d %d %f %f %f %f", &edge[i][0], &edge[i][1], &exchange[i][0], &exchange[i][1], &exchange[i+1][0], &exchange[i+1][1]);
		edge[i+1][0] = edge[i][1];
		edge[i+1][1] = edge[i][0];
	}

	/*
	for (i=0; i<m*2; i++) {
		printf("%d %d\n", edge[i][0], edge[i][1]);
	}
	for (i=0; i<m*2; i++) {
		printf("%f %f\n", exchange[i][0], exchange[i][1]);
	}
	*/

	int sedge, eedge;
	float rate, commission, w;
	for (i=0; i<n-1; i++) {
		for (j=0; j<m*2; j++) {
			sedge = edge[j][0];
			eedge = edge[j][1];
			rate = exchange[j][0];
			commission = exchange[j][1];
			w = (d[sedge]-commission)*rate;
			if (w > d[eedge]) d[eedge] = w;
		}
	}

	/*
	for (j=1; j<n+1; j++) {
		printf("%f ", d[j]);
	}
	*/

	for (j=0; j<m*2; j++) {
		sedge = edge[j][0];
		eedge = edge[j][1];
		rate = exchange[j][0];
		commission = exchange[j][1];
		w = (d[sedge]-commission)*rate;
		if (w > d[eedge]) {			
			printf("YES\n");
			return;
		}
	}
	printf("NO\n");
}
