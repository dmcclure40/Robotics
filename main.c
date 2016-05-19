//
//  main.c
//  occupancyGrid
//
//  Created by Nicholas Schardt on 5/18/16.
//  Copyright © 2016 Nicky Schardt. All rights reserved.
//

#include <stdio.h>

void createCost() {
    int x = 2;
    int y = 2;
    int n = x*y;
    int map[2][2] = {{1, 1}, {0, 1}};
    int cost[4][4] = {0};
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            // Right neighbors
            if (i < x-1) {
                if (map[i][j] && map[i+1][j]) {
                    cost[(x*j)+i+1][(x*j)+i] = 1;
                }
            }
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 4; i++) {
                    printf("%d", cost[i][j]);
                }
                printf("\n");
            }
            printf("\n");
            // Left neighbors
            if (i > 0) {
                if (map[i][j] && map[i-1][j]) {
                    cost[(x*j)+i-1][(x*j)+i] = 1;
                }
            }
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 4; i++) {
                    printf("%d", cost[i][j]);
                }
                printf("\n");
            }
            printf("\n");
            // Up neighbors
            if (j > 0) {
                if (map[i][j] && map[i][j-1]) {
                    cost[(x*j)+i-x][(x*j)+i] = 1;
                }
            }
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 4; i++) {
                    printf("%d", cost[i][j]);
                }
                printf("\n");
            }
            printf("\n");
            // Down neighbors
            if (j < y-1) {
                if (map[i][j] && map[i][j+1]) {
                    cost[(x*j)+i+x][(x*j)+i] = 1;
                }
            }
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 4; i++) {
                    printf("%d", cost[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}

int main() {
    createCost();
    return 0;
}