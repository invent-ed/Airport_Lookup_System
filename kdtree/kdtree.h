#ifndef __KDTREE_H_
#define __KDTREE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../airports.h"

struct kdTree {
    struct kdNode *root;
};
typedef struct kdTree kdTree;

struct kdNode {
    int dir;
    int visited;
    double pos;
    airport *airport;
    struct kdNode *parent;
    struct kdNode *left;
    struct kdNode *right;
};
typedef struct kdNode kdNode;

struct kdParams {
    int start;
    int end;
};
typedef struct kdParams kdParams;

int cmpLatitude (const void *a_ptr, const void *b_ptr);
int cmpLongitude (const void *a_ptr, const void *b_ptr);
int cmpDistance(const void *a_ptr, const void *b_ptr);

kdTree * generateKdTree(airport *airports, int size);
void addKdNode(kdNode **node, kdNode *parent, airport *airports, int start, int end, int dir);
kdNode * genKdNode(airport *airports, kdNode *parent, int median, int dir);
void nearestNeighbor(kdNode *node, double lat, double lon, kdNode **nn, double *nn_dist);
void kNearestNeighbor(kdNode *node, int k, double lat, double lon, kdNode *nn[]);
void printKdTree(kdNode *node, int depth);

double distance(double lat1, double lon1, double lat2, double lon2, char unit);
double deg2rad(double deg);
double rad2deg(double rad);

#endif
