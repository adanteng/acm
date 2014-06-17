#include <stdio.h>
#include <malloc.h>

int choose_device(int *ptr, int len, int key_b) {
	int c_index=0, i, cur_p=-1;
	for (i=0; i<len; i++) {
		int bandwidths = *(ptr+i*2);
		int price = *(ptr+i*2+1);

		if (cur_p == -1) {
			if (bandwidths < key_b) continue;
			else {
				cur_p = price;
				c_index = i;
				continue;
			}
		}			

		if (bandwidths >= key_b && price < cur_p) {
			cur_p = price;
			c_index = i;
		}
	}
	return c_index;
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
	int sys_count, device_count, pair_count;
	scanf("%d", &sys_count);
	if (sys_count < 1 || sys_count > 10) 
		return 0;

    float result[sys_count];
	int i, j, k;    
	for (i=0; i< sys_count; i++) {
	    scanf("%d", &device_count);
	    if (device_count < 1 || device_count > 100) 
			return 0;

        int chose_devices[device_count * 2];
		int *deptr[device_count];
		int pair_counts[device_count];
		for (j=0; j<device_count; j++) {
			scanf("%d", &pair_count);
			if (pair_count <= 0) 
				return 0;

			pair_counts[j] = pair_count;

            int *pair = (int *)malloc(sizeof(int)*(pair_count*2+1));
			//int pair[pair_count*2 + 1];
			int k = 0;
			for (k=0; k<pair_count; k++) {
				int bandwidths, price;
				scanf("%d %d", &bandwidths, &price);
				pair[k*2] = bandwidths;
				pair[k*2+1] = price;
			}

			deptr[j] = pair;

			/*
            int max_pair_index = get_max_pair_index(pair, pair_count);
            chose_devices[j*2] = pair[max_pair_index*2];
            chose_devices[j*2 + 1] = pair[max_pair_index*2 + 1];           
			*/

			/*
			for (k=0; k<pair_count; k++){
				printf("%d %d\n", *(deptr[j]+k*2), *(deptr[j]+k*2+1));
			}
			*/
		}

        float maxbp=-1; 
		for (j=0; j<device_count; j++) {
			int *curptr = deptr[j];
			int cur_pair_count = pair_counts[j];
			int h;
			for (h=0; h<cur_pair_count; h++) {
				int b = *(curptr+h*2);
				int p = *(curptr+h*2+1);
			    //printf("%d %d\n",b, p);

				chose_devices[j*2] = b;
				chose_devices[j*2+1] = p;					

				for (k=0; k<device_count; k++) {
					if (k == j) continue;
					
					int *chose_deptr = deptr[k];
					int c_index = choose_device(chose_deptr, pair_counts[k], b); 
					
					//printf("%d\n",c_index);

					chose_devices[k*2] = *(deptr[k]+c_index*2); 
					chose_devices[k*2+1] = *(deptr[k]+c_index*2+1);
				}

                /*
                int x;
                for (x=0; x<device_count; x++) {
                    printf("%d %d\n", chose_devices[x*2], chose_devices[x*2+1]);
                }
                */

                float cur_bp = compute_rate(chose_devices, device_count);
                if (cur_bp > maxbp)
                    maxbp = cur_bp;
			}
		}
        result[i] = maxbp;
	}

	for (i=0; i< sys_count; i++) {
        printf("%.3f\n", result[i]);
    }
	
}
