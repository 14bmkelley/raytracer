#ifndef CAST_H
#define CAST_H

#include <stdio.h>

#include "structures.h"

void castAllRays(View *view, Point *eyePoint, Color *ambientLight, Light *light, Sphere **sphereList, int *sphereListLength, FILE **output);
Color castRay(Ray *pixelRay, Point *eyePoint, Color *ambientLight, Light *lightSource, Sphere **sphereList, int *sphereListLength);
void addAmbientLight(Color *color, Sphere *sphere, Color *ambientLight);
void addLightInteraction(Color *color, Point *eyePoint, Light *lightSource, Sphere *sphere, Sphere **sphereList, int *sphereListLength);
int hasObstruction(Vector lightVector, Ray *intersectionToLight, Light *lightSource, Sphere **sphereList, int *sphereListLength);
void addSpecularInteraction(Color *color, Vector sphereNormal, Vector lightNormal, double lightIntensity, Point *eyePoint, Light *lightSource, Sphere *sphere);
void checkColor(Color *color);
void checkColorComponent(double *component);

#endif