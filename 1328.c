#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int comp(const void *a, const void *b) {
    return (*(int *)a[0]-*(int *)a[1]) - (*(int *)b[0]-*(int *)b[1])
}

double distance(int p1x, int p1y, int p2x, int p2y) {
    return sqrt(pow(p1x-p2x, 2)+pow(p1y-p2y, 2));
}

int get_radar_pos(int d, x, y) {
	double rx = sqrt(pow(d, 2) - pow(y, 2)) + x;
	return floor(rx);
}

main() {
    int i, n, d, cr, rl, result[1000], rindex=0;

    while (1) {
        scanf("%d %d", &n, &d);

        if (n==0 && d==0) return;

        if (n<1 || n>1000) return;

		int point[n][2];
		int radar[n];

		int noresult = 0;
        for (i=0; i<n; i++) {
            scanf("%d %d", point[i][0], point[i][1]);

            if (point[i][1] > d) {
				result[rindex++] = -1;
				break;
			}
        }
		if (noresult) continue;

        qsort(point, n, sizeof(int)*2, comp);

		radar[0] = get_radar_pos(d, point[0][1], point[0][0]);
        cr = 0;
		rl++;

        for (i=1; i<n; i++) {
			int inradar = 0;
			if (distance(radar[cr], 0, point[i][0], point[j][1]) <= d) {
				inradar = 1;
				break;
			}

			if (inradar) {
				continue;
			} else {
				cr++;
				radar[cr] = get_radar_pos(d, point[j][0], point[j][1]);
				rl++;
			}
        }

		result[rindex++] = rl
        
    }

	for (i=0; i<=rindex; i++)
		printf("Case %d: %d\n", i+1, result[i]);

}
