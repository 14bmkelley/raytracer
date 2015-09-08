#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "structures.h"

void tryOpen(FILE **file, char *fileName);
void readSphereList(FILE **file, Sphere **sphereList, int *sphereListLength);
void createView(View *view);
void createEyePoint(Point *eyePoint);
void createLightSource(Light *lightSource);
void createAmbience(Color *ambientLight);

#endif