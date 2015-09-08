#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "cast.h"
#include "structures.h"
#include "util.h"
#include "collisions.h"

void castAllRays(View *view, Point *eyePoint, Color *ambientLight, Light *lightSource, Sphere **sphereList, int *sphereListLength, FILE **output) {
    
    double i, j;
    double di = (view->maxX - view->minX) / view->width;
    double dj = (view->maxY - view->minY) / view->height;
    Point pixelLoc;
    Vector eyeToPixel;
    Ray pixelRay;
    
    j = view->maxY;
    while (j > view->minY) {
        
        i = view->minX;
        while (i < view->maxX) {
            
            pixelLoc = (Point) {i, j, 0};
            eyeToPixel = fromToVector(*eyePoint, pixelLoc);
            pixelRay = (Ray) {*eyePoint, eyeToPixel};
            Color color = castRay(&pixelRay, eyePoint, ambientLight, lightSource, sphereList, sphereListLength);
            
            checkColor(&color);
            
            fprintf(*output, "%.0f %.0f %.0f\n", color.r, color.g, color.b);
            
            i += di;
            
        }
        
        j -= dj;
        
    }
    
}

Color castRay(Ray *pixelRay, Point *eyePoint, Color *ambientLight, Light *lightSource, Sphere **sphereList, int *sphereListLength) {
    
    Color pixelColor = (Color) {1.0, 1.0, 1.0};
    Sphere **intersectionList = (Sphere **) malloc(sizeof(Sphere *));
    int intersectionListLength = 0;
    
    findIntersectionPoints(pixelRay, sphereList, sphereListLength, intersectionList, &intersectionListLength);
    
    if (intersectionListLength == 0) {
        return pixelColor;
    }
    
    Sphere *intersectedSphere = findClosestIntersection(pixelRay, intersectionList, &intersectionListLength);
    
    if (intersectedSphere == (Sphere *) NULL) {
        return pixelColor;
    }
    
    addAmbientLight(&pixelColor, intersectedSphere, ambientLight);
    addLightInteraction(&pixelColor, eyePoint, lightSource, intersectedSphere, sphereList, sphereListLength);
    
    return pixelColor;
    
}

void addAmbientLight(Color *color, Sphere *sphere, Color *ambientLight) {
    
    color->r = sphere->color.r * sphere->finish.amb * ambientLight->r;
    color->g = sphere->color.g * sphere->finish.amb * ambientLight->g;
    color->b = sphere->color.b * sphere->finish.amb * ambientLight->b;
    
}

void addLightInteraction(Color *color, Point *eyePoint, Light *lightSource, Sphere *sphere, Sphere **sphereList, int *sphereListLength) {
    
    Vector sphereOutward = fromToVector(sphere->center, *sphere->intersection);
    Vector sphereOutwardNormal = normalizeVector(sphereOutward);
    Vector sphereOutwardScaled = scaleVector(sphereOutwardNormal, 0.01);
    Point sphereIntersection = translatePoint(*sphere->intersection, sphereOutwardScaled);
    Vector lightVector = fromToVector(sphereIntersection, lightSource->point);
    Vector lightNormal = normalizeVector(lightVector);
    double lightIntensity = dotVector(sphereOutwardNormal, lightNormal);
    Ray intersectionToLight = (Ray) {sphereIntersection, lightNormal};
    
    if (lightIntensity < 0) {
        return;
    }
    
    if (hasObstruction(lightVector, &intersectionToLight, lightSource, sphereList, sphereListLength) != 0) {
        return;
    }
    
    color->r += sphere->color.r * sphere->finish.diff * lightIntensity * lightSource->color.r;
    color->g += sphere->color.g * sphere->finish.diff * lightIntensity * lightSource->color.g;
    color->b += sphere->color.b * sphere->finish.diff * lightIntensity * lightSource->color.b;
    
    addSpecularInteraction(color, sphereOutwardNormal, lightNormal, lightIntensity, eyePoint, lightSource, sphere);
    
}

int hasObstruction(Vector lightVector, Ray *intersectionToLight, Light *lightSource, Sphere **sphereList, int *sphereListLength) {
    
    Sphere **possibleObstructionsList = (Sphere **) malloc(sizeof(Sphere *));
    int possibleObstructionsListLength = 0;
    
    findIntersectionPoints(intersectionToLight, sphereList, sphereListLength, possibleObstructionsList, &possibleObstructionsListLength);
    
    if (possibleObstructionsListLength == 0) {
        return 0;
    }
    
    Sphere *obstructionSphere = findClosestIntersection(intersectionToLight, possibleObstructionsList, &possibleObstructionsListLength);
    
    if (obstructionSphere == (Sphere *) NULL) {
        return 0;
    }
    
    double lightDistance = lengthVector(lightVector);
    double obstructionDistance = fromToDistance(*obstructionSphere->intersection, lightSource->point);
    
    if (lightDistance > obstructionDistance) {
        return 1;
    }
    return 0;
    
}

void addSpecularInteraction(Color *color, Vector sphereNormal, Vector lightNormal, double lightIntensity, Point *eyePoint, Light *lightSource, Sphere *sphere) {
    
    Vector tmp = scaleVector(sphereNormal, 2 * lightIntensity);
    Vector reflection = differenceVector(lightNormal, tmp);
    Vector eyeVector = fromToVector(*eyePoint, *sphere->intersection);
    Vector eyeNormal = normalizeVector(eyeVector);
    double specularIntensity = dotVector(reflection, eyeNormal);
    
    if (specularIntensity < 0) {
        return;
    }
    
    color->r += sphere->finish.spec * lightSource->color.r * powf(specularIntensity, 1 / (double) (sphere->finish.rough));
    color->g += sphere->finish.spec * lightSource->color.g * powf(specularIntensity, 1 / (double) (sphere->finish.rough));
    color->b += sphere->finish.spec * lightSource->color.b * powf(specularIntensity, 1 / (double) (sphere->finish.rough));
    
}

void checkColor(Color *color) {
    checkColorComponent(&color->r);
    checkColorComponent(&color->g);
    checkColorComponent(&color->b);
}

void checkColorComponent(double *component) {
    if (*component > 1) {
        *component = 1;
    }
    *component = 255 * *component;
}