#include <stdio.h>

int main() {
    int n, r, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &r);

    int alloc[n][r], max[n][r], avail[r];
    int need[n][r], finish[n], safeSeq[n];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < r; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < r; i++) {
        scanf("%d", &avail[i]);
    }

    // Calculate Need Matrix
    for(i = 0; i < n; i++) {
        for(j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize finish = 0
    for(i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0;

    // Banker's Algorithm
    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {
            if(finish[i] == 0) {

                int flag = 0;

                for(j = 0; j < r; j++) {
                    if(need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if(flag == 0) {
                    safeSeq[count++] = i;

                    for(k = 0; k < r; k++) {
                        avail[k] += alloc[i][k];
                    }

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nSystem is NOT SAFE\n");
            return 0;
        }
    }

    // Print Safe Sequence
    printf("\nSystem is SAFE\nSafe Sequence: ");
    for(i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }

    return 0;
}