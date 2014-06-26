#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int comp(const void *a, const void *b) {
    int t = ((int *)b)[0] - ((int *)a)[0];
	if (t == 0) 
		return ((int *)b)[1] - ((int *)a)[1];
}

int get_max_radar_pos(int d, int x, int y) {
	double rx = sqrt(pow(d, 2) - pow(y, 2)) + x;	
	return floor(rx);
}

int get_min_radar_pos(int d, int x, int y) {
	double rx = -sqrt(pow(d, 2) - pow(y, 2)) + x;	
	return floor(rx);
}

main() {
    int i, n, d, result[1000], rindex=0;

    while (1) {
        scanf("%d %d", &n, &d);

        if (n==0 && d==0) return;

        if (n<1 || n>1000) return;

		int point[n][2];
		int radar[n][2];

		int noresult = 0;
        for (i=0; i<n; i++) {
            scanf("%d %d", &point[i][0], &point[i][1]);

            if (point[i][1] > d) {
				noresult = 1;
				result[rindex++] = -1;
				break;
			}

			radar[i][0] = get_min_radar_pos(d, point[i][0], point[i][1]);
			radar[i][1] = get_max_radar_pos(d, point[i][0], point[i][1]);
        }
		if (noresult) continue;

        qsort(radar, n, sizeof(int)*2, comp);

		int ef = radar[0][1];

		int rs = 1;

        for (i=1; i<n; i++) {
			if (point[i][0] <= ef) continue;
			else {
				rs++;
				ef = point[i][1];
			}
        }

		result[rindex++] = rs;
        
    }

	for (i=0; i<=rindex; i++)
		printf("Case %d: %d\n", i+1, result[i]);

}
