//
//  main.c
//  occupancyGrid
//
//  Created by Nicholas Schardt on 5/18/16.
//  Copyright © 2016 Nicky Schardt. All rights reserved.
//

#include <stdio.h>

void createCost() {
    int x = 3;
    int y = 3;
    int n = x*y;
    int map[3][3] = {{1, 0, 1}, {1, 0, 1}, {1, 1, 1}};
    int cost[9][9] = {0};
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            // Right neighbors
            if (i < x-1) {
                if (map[i][j] && map[i+1][j]) {
                    cost[(x*j)+i+1][(x*j)+i] = 1;
                }
                if (map[i][j] && (map[i+1][j] == 0)) {
                    cost[(x*j)+i+1][(x*j)+i] = 100;
                }
            }
            // Left neighbors
            if (i > 0) {
                if (map[i][j] && map[i-1][j]) {
                    cost[(x*j)+i-1][(x*j)+i] = 1;
                }
                if (map[i][j] && (map[i-1][j] == 0)) {
                    cost[(x*j)+i-1][(x*j)+i] = 100;
                }
            }
            // Up neighbors
            if (j > 0) {
                if (map[i][j] && map[i][j-1]) {
                    cost[(x*j)+i-x][(x*j)+i] = 1;
                }
                if (map[i][j] && (map[i][j-1] == 0)) {
                    cost[(x*j)+i-x][(x*j)+i] = 100;
                }
            }
            // Down neighbors
            if (j < y-1) {
                if (map[i][j] && map[i][j+1]) {
                    cost[(x*j)+i+x][(x*j)+i] = 1;
                }
                if (map[i][j] && (map[i][j+1] == 0)) {
                    cost[(x*j)+i+x][(x*j)+i] = 100;
                }
            }
        }
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < n; i++) {
            printf("%d,", cost[i][j]);
        }
        printf("\n");
    }
}

int main() {
    createCost();
    return 0;
}
