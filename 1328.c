#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int comp(const void *a, const void *b) {
    double t = ((double *)a)[0] - ((double *)b)[0];
	if (t > 0)
		return 1;
	else if (t < 0)
		return -1;
	return 0;
}

double get_max_radar_pos(int d, int x, int y) {
	double rx = sqrt(pow(d, 2) - pow(y, 2)) + x;
	return rx;
	//return floor(rx);
}

double get_min_radar_pos(int d, int x, int y) {
	double rx = -sqrt(pow(d, 2) - pow(y, 2)) + x;	
	return rx;
	//return ceil(rx);
}

main() {
    int i, n, d, result[1000], rindex=0;

    while (1) {
        scanf("%d %d", &n, &d);

        if (n==0 && d==0) break;

        if (n<1 || n>1000) return;

		int point[n][2];
		double radar[n][2];

		int noresult = 0;
        for (i=0; i<n; i++) {
            scanf("%d %d", &point[i][0], &point[i][1]);

            if (point[i][1] > d) {
				noresult = 1;
				result[rindex] = -1;
				continue;
			}

			radar[i][0] = get_min_radar_pos(d, point[i][0], point[i][1]);
			radar[i][1] = get_max_radar_pos(d, point[i][0], point[i][1]);

        }
		if (noresult) {
			printf("Case %d: %d\n\n", rindex+1, -1);
			rindex++;
			continue;
		}

        qsort(radar, n, sizeof(double)*2, comp);
		
		/*
		for (i=0; i<n; i++)
			printf("%f %f\n", radar[i][0], radar[i][1]);
		*/

		int ef = radar[0][1];

		int rs = 1;

        for (i=1; i<n; i++) {
			if (radar[i][0] > ef) {
				rs++;
				ef = radar[i][1];
			} else if (radar[i][1] < ef) {
				ef = radar[i][1];
			}
        }

		printf("Case %d: %d\n\n", rindex+1, rs);

		result[rindex++] = rs;

    }

	/*
	for (i=0; i<rindex; i++)
		printf("Case %d: %d\n", i+1, result[i]);
	*/

}
