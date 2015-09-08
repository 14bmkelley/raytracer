#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    double x;
    double y;
    double z;
} Point;

typedef struct {
    double x;
    double y;
    double z;
} Vector;

typedef struct {
    Point point;
    Vector direction;
} Ray;

typedef struct {
    double r;
    double g;
    double b;
} Color;

typedef struct {
    double amb;
    double diff;
    double spec;
    double rough;
} Finish;

typedef struct {
    Point center;
    double radius;
    Color color;
    Finish finish;
    Point *intersection;
} Sphere;

typedef struct {
    Point point;
    Color color;
} Light;

typedef struct {
    double minX;
    double maxX;
    double minY;
    double maxY;
    int width;
    int height;
} View;

#endif