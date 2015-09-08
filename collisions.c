#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "collisions.h"
#include "structures.h"
#include "util.h"

void findIntersectionPoints(Ray *ray, Sphere **sphereList, int *sphereListLength, Sphere **intersectionList, int *intersectionListLength) {
    
    int i;
    for (i = 0; i < *sphereListLength; i++) {
        
        Point *possibleIntersection = findIntersectionPoint(*ray, *sphereList[i]);
        
        if (possibleIntersection != (Point *) NULL) {
            sphereList[i]->intersection = possibleIntersection;
            append(sphereList[i], intersectionList, intersectionListLength);
        }
        
    }
    
}

Sphere *findClosestIntersection(Ray *ray, Sphere **intersectionList, int *intersectionListLength) {
    
    if (*intersectionListLength == 1) {
        return intersectionList[0];
    } else if (*intersectionListLength > 1) {
        
        int closestSphereIndex = 0;
        int i;
        double distanceCurrent;
        double distanceClosest;
        
        for (i = 1; i < *intersectionListLength; i++) {
            
            distanceCurrent = fromToDistance(ray->point, *intersectionList[i]->intersection);
            distanceClosest = fromToDistance(ray->point, *intersectionList[closestSphereIndex]->intersection);
            
            if (distanceCurrent < distanceClosest) {
                closestSphereIndex = i;
            }
            
        }
        
        return intersectionList[closestSphereIndex];
        
    }
    
    return (Sphere *) NULL;
    
}

Point *findIntersectionPoint(Ray ray, Sphere sphere) {
    
    Vector sphereToRay = fromToVector(sphere.center, ray.point);
    double a = dotVector(ray.direction, ray.direction);
    double b = dotVector(scaleVector(sphereToRay, 2.0), ray.direction);
    double c = dotVector(sphereToRay, sphereToRay) - sphere.radius * sphere.radius;
    
    double determinant = b * b - 4 * a * c;
    
    if (determinant >= 0) {
        
        double root1 = (-b + sqrt(determinant)) / (2.0 * a);
        double root2 = (-b - sqrt(determinant)) / (2.0 * a);
        
        if (root1 >= 0 && root2 >= 0) {
            return findPointFromRoot(min(root1, root2), ray);
        } else if (root1 >= 0 || root2 >= 0) {
            return findPointFromRoot(max(root1, root2), ray);
        }
        
        return (Point *) NULL;
        
    }
    
    return (Point *) NULL;
    
}

Point *findPointFromRoot(double root, Ray ray) {
    Point *result = (Point *) malloc(sizeof(Point));
    Vector distanceToRoot = scaleVector(ray.direction, root);
    *result = translatePoint(ray.point, distanceToRoot);
    return result;
}

int max(int a, int b) {
    if (a >= b) {
        return a;
    }
    return b;
}

int min(int a, int b) {
    if (a <= b) {
        return a;
    }
    return b;
}