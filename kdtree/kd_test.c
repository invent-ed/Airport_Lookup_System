#include <stdio.h>
#include <stdlib.h>
#include "kdtree.h"

#define SIZE 15

void printKdTree(kdNode *node, int depth);

int main() {
    double latitude[] = { -3.73, 24.67, -78.9, -10.33, 1.02, 6.28, 45.81, -30.32, 83.28, 17.84, 63.62, 124.74, -20.25, -89.19, 1.63 };
    double longitude[] = { 110.3, -84.92, 0, 69.2, -23.64, -162.03, 6.72, -57.13, 92.56, 158.51, 97.04, -35.18, 68.13, 0.21, 1.64 };
    airport airports[SIZE];

    // test airports
    printf("Before KD:\n");
    char sea[4] = "SEA";
    char intl[50] = "Seattle Intl";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < 4; j++) airports[i].code[j] = sea[j];
        for (int j = 0; j < 50; j++) airports[i].name[j] = intl[j];
        airports[i].latitude = latitude[i];
        airports[i].longitude = longitude[i];
        airports[i].distance = 0;
        printf("Airport %d:\n", i);
        printf("    Latitude: %f\n", airports[i].latitude);
        printf("    Longitude: %f\n", airports[i].longitude);
    }
    printf("\n");

    printf("Generating KD tree...\n");
    kdTree *kd = generateKdTree(airports, SIZE);
    printf("\n");

    printf("Printing KD tree...\n");
    printKdTree(kd->root, 1);
    printf("\n");

    printf("Finding nearest...\n");
    airport *airport;
    kdNode *nearest[5];
    double lat = 16, lon = 158;
    kNearestNeighbor(kd->root, 5, lat, lon, nearest);
    printf("\n");

    printf("Check 5 nearest...\n");
    for (int i = 0; i < SIZE; i++) {
        airports[i].distance = distance(lat, lon, airports[i].latitude, airports[i].longitude, 'M');
    }
    qsort(airports, SIZE, sizeof(*airports), cmpDistance);
    for (int i = 0; i < 5; i++) {
        printf("%f %f %f\n", airports[i].latitude, airports[i].longitude, airports[i].distance);
    }
    printf("\n");

    return 0;
}
