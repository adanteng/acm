#include <stdio.h>

int get_max_pair_index(int *p, int pair_c) {
	int index = 0, i;
	float max_rate = (float)(*p)/(float)(*(p+1));	
	for (i = 0; i < pair_c; i++) {
		float bandwidths = *(p+i*2);
		float price = *(p+i*2+1);
		float rate = bandwidths/price;
		if (rate > max_rate) {
			max_rate = rate;
			index = i;			
		}
	}
	return index;
}

float compute_rate(int *p, int pair_c) {
	int min_b=*p, sum_p=0, i;
	for (i = 0; i < pair_c; i++) {
		int bandwidths = *(p+i*2);
        int price = *(p+i*2+1);
        sum_p += price;
		if (bandwidths < min_b) {
			min_b = bandwidths;
		}
	}
    return (float)min_b/(float)sum_p;
}

main() {
	int sys_count, device_count;
	scanf("%d", &sys_count);
	if (sys_count < 1 || sys_count > 10) return 0;

	int i, j, k;    
    float result[sys_count];
	for (i=0; i< sys_count; i++) {
	    scanf("%d", &device_count);
	    if (device_count < 1 || device_count > 100) return 0;

        int chose_devices[device_count * 2];
		for (j=0; j<device_count; j++) {
			int pair_count;
			scanf("%d", &pair_count);
			if (pair_count <= 0) return 0;

			int pair[pair_count*2 + 1];
			int k = 0;
			for (k=0; k<pair_count; k++) {
				int bandwidths, price;
				scanf("%d %d", &bandwidths, &price);
				pair[k*2] = bandwidths;
				pair[k*2+1] = price;
			}

            int max_pair_index = get_max_pair_index(pair, pair_count);
            chose_devices[j*2] = pair[max_pair_index*2];
            chose_devices[j*2 + 1] = pair[max_pair_index*2 + 1];           
		}

        float maxbp = compute_rate(chose_devices, device_count);

        result[i] = maxbp;

	}

	for (i=0; i< sys_count; i++) {
        printf("%.3f\n", result[i]);
    }
}
