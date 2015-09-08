#ifndef APPEND_H
#define APPEND_H

#include "structures.h"

void append(Sphere *sphere, Sphere **sphereList, int *sphereListLength);
Vector fromToVector(Point p1, Point p2);
double fromToDistance(Point p1, Point p2);
double lengthVector(Vector v);
double dotVector(Vector v1, Vector v2);
Vector scaleVector(Vector v, double scalar);
Point translatePoint(Point p, Vector v);
Vector normalizeVector(Vector v);
Vector differenceVector(Vector v1, Vector v2);

#endif