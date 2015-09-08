#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "util.h"
#include "structures.h"

void append(Sphere *sphere, Sphere **sphereList, int *sphereListLength) {
    int newSize = *sphereListLength + 1;
    sphereList = (Sphere **) realloc(sphereList, newSize * sizeof(Sphere *));
    sphereList[*sphereListLength] = sphere;
    *sphereListLength = newSize;
}

Vector fromToVector(Point p1, Point p2) {
    return (Vector) {p1.x - p2.x, p1.y - p2.y, p1.z - p2.z};
}

double fromToDistance(Point p1, Point p2) {
    return lengthVector(fromToVector(p1, p2));
}

double lengthVector(Vector v) {
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double dotVector(Vector v1, Vector v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector scaleVector(Vector v, double scalar) {
    return (Vector) {v.x * scalar, v.y * scalar, v.z * scalar};
}

Point translatePoint(Point p, Vector v) {
    return (Point) {p.x + v.x, p.y + v.y, p.z + v.z};
}

Vector normalizeVector(Vector v) {
    double mag = lengthVector(v);
    return (Vector) {v.x / mag, v.y / mag, v.z / mag};
}

Vector differenceVector(Vector v1, Vector v2) {
    return (Vector) {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}