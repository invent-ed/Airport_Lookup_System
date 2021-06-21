#include <stdlib.h>
#include <float.h>

#include "kdtree.h"

#define LATITUDE 0
#define LONGITUDE 1
#define pi 3.14159265358979323846
#define NEW_STRUCT(s) (s *)malloc(sizeof(s))
#define NEW_STRING(s) (char *)malloc(strlen(s)+1)
#define CPY_STRING(dst, src) dst = NEW_STRING(src); strcpy(dst, src)

int 
cmpLatitude(const void *a_ptr, const void *b_ptr) 
{
    airport a = *(airport *)a_ptr;
    airport b = *(airport *)b_ptr;
    return a.latitude < b.latitude ? -1 : a.latitude > b.latitude;
}

int 
cmpLongitude(const void *a_ptr, const void *b_ptr) 
{
    airport a = *(airport *)a_ptr;
    airport b = *(airport *)b_ptr;
    return a.longitude < b.longitude ? -1 : a.longitude > b.longitude;
}

int 
cmpDistance(const void *a_ptr, const void *b_ptr) 
{
    airport a = *(airport *)a_ptr;
    airport b = *(airport *)b_ptr;
    return a.distance - b.distance;
    // return a.distance < b.distance ? -1 : a.distance > b.distance;
}

kdTree * 
generateKdTree(airport *airports, int size) 
{
    kdTree *kd = NEW_STRUCT(kdTree);
    addKdNode(&(kd->root), NULL, airports, 0, size-1, LATITUDE);
    return kd;
}

void
addKdNode(kdNode **node, kdNode *parent, airport *airports, int start, int end, int dir)
{
    if (start <= end) {
        int size = end - start + 1;
        int median = start + floor(size/2);
        qsort(airports+start, size, sizeof(airport), dir ? cmpLongitude : cmpLatitude);
        *node = genKdNode(airports, parent, median, dir);
        addKdNode(&((*node)->left), *node, airports, start, median-1, 1-dir);
        addKdNode(&((*node)->right), *node, airports, median+1, end, 1-dir);
    }
}

kdNode *
genKdNode(airport *airports, kdNode *parent, int median, int dir) 
{
    kdNode *newNode = NEW_STRUCT(kdNode);
    airport *airport = airports + median;
    newNode->dir = dir;
    newNode->visited = 0;
	newNode->pos = dir ? airport->longitude : airport->latitude;
    newNode->airport = airport;
    newNode->parent = parent;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void
nearestNeighbor(kdNode *node, double lat, double lon, kdNode **nn, double *nn_dist) 
{
	if (node == NULL) return ;
    double dist = distance(lat, lon, node->airport->latitude, node->airport->longitude, 'M'); // distance from node to search point
	double p_dir = (node->dir ? lon : lat) - node->pos; // perpendicular direction
    double p_dist = distance(lat, lon, node->dir ? lat : node->pos, node->dir ? node->pos : lon, 'M'); // perpendicular distance
	
    if (dist < *nn_dist && node->visited == 0) {
        *nn_dist = dist;
        *nn = node;
    }

    if (*nn_dist == 0) return ;
    nearestNeighbor(p_dir < 0 ? node->left : node->right, lat, lon, nn, nn_dist);
    nearestNeighbor(p_dir < 0 ? node->right : node->left, lat, lon, nn, nn_dist);
}

void
kNearestNeighbor(kdNode *root, int k, double lat, double lon, kdNode *nn[]) 
{
    kdNode *node, *nearest;
    double *nearest_dist;
    for (int i = 0; i < k; i++) {
        nn[i] = NULL;
    }
    for (int i = 0; i < k; i++) {
        node = root;
        nearest = NULL;
        nearest_dist = (double *)malloc(sizeof(double));
        *nearest_dist = DBL_MAX;
        nearestNeighbor(node, lat, lon, &nearest, nearest_dist);
        if (nearest != NULL) {
            nearest->visited = 1;
            nearest->airport->distance = *nearest_dist;
            nn[i] = nearest;
        }
    }
    for (int i = 0; i < k; i++) {
        if (nn[i] != NULL) {
            nn[i]->visited = 0;
        }
    }
}

void 
printKdTree(kdNode *node, int depth) 
{
    airport *a;
    if (node != NULL) {
        if (node->airport != NULL) {
            a = node->airport;
            printf("%d: %s %f %f %s\n", depth, a->code, a->latitude, a->longitude, a->name);
        }
        printKdTree(node->left, depth+1);
        printKdTree(node->right, depth+1);
    }
}

double
distance(double lat1, double lon1, double lat2, double lon2, char unit)
{
    double theta, dist;
    theta = lon1 - lon2;
    dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) *
           cos(deg2rad(lat2)) * cos(deg2rad(theta));
    dist = rad2deg(acos(dist)) * 60 * 1.1515;
    switch (unit) {
        case 'M': break;
        case 'K': dist = dist * 1.609344; break;
        case 'N': dist = dist * 0.8684; break;
    }
    return dist;
}

double 
deg2rad(double deg) 
{
    return (deg * pi / 180);
}

double 
rad2deg(double rad) 
{
    return (rad * 180 / pi);
}
