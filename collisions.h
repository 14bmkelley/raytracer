#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "structures.h"

void findIntersectionPoints(Ray *ray, Sphere **sphereList, int *sphereListLength, Sphere **intersectionList, int *intersectionListLength);
Sphere *findClosestIntersection(Ray *ray, Sphere **intersectionList, int *intersectionListLength);
Point *findIntersectionPoint(Ray ray, Sphere sphere);
Point *findPointFromRoot(double root, Ray ray);
int max(int a, int b);
int min(int a, int b);

#endif