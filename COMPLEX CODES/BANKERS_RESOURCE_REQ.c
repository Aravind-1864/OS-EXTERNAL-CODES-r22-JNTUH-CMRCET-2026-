#include <stdio.h>

int main() {
    int n, r, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &r);

    int alloc[n][r], max[n][r], avail[r];
    int need[n][r];

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

    int p;
    printf("\nEnter process number (0 to %d): ", n-1);
    scanf("%d", &p);

    int request[r];
    printf("Enter request for process P%d:\n", p);
    for(i = 0; i < r; i++) {
        scanf("%d", &request[i]);
    }

    // Step 1: Check request <= need
    for(i = 0; i < r; i++) {
        if(request[i] > need[p][i]) {
            printf("\nError: Request exceeds maximum need\n");
            return 0;
        }
    }

    // Step 2: Check request <= available
    for(i = 0; i < r; i++) {
        if(request[i] > avail[i]) {
            printf("\nResources not available. Process must wait\n");
            return 0;
        }
    }

    // Step 3: Pretend to allocate
    for(i = 0; i < r; i++) {
        avail[i] -= request[i];
        alloc[p][i] += request[i];
        need[p][i] -= request[i];
    }

    // Step 4: Safety Check (Banker’s)
    int finish[n], safeSeq[n], count = 0;

    for(i = 0; i < n; i++)
        finish[i] = 0;

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

                    for(j = 0; j < r; j++) {
                        avail[j] += alloc[i][j];
                    }

                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if(found == 0) {
            printf("\nRequest cannot be granted (Unsafe state)\n");
            return 0;
        }
    }

    printf("\nRequest can be granted (Safe state)\nSafe Sequence: ");
    for(i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }

    return 0;
}