#include <stdio.h>
#include <stdlib.h>

#include "raycaster.h"
#include "structures.h"
#include "util.h"
#include "cast.h"

int main(int argc, char *argv[]) {
    
    FILE *input;
    char *fileName = argv[1];
    Sphere **sphereList = (Sphere **) malloc(sizeof(Sphere *));
    int sphereListLength = 0;
    View view;
    Point eyePoint;
    Light lightSource;
    Color ambientLight;
    FILE *output;
    
    tryOpen(&input, fileName);
    readSphereList(&input, sphereList, &sphereListLength);
    
    createView(&view);
    createEyePoint(&eyePoint);
    createLightSource(&lightSource);
    createAmbience(&ambientLight);
    
    output = fopen("image.ppm", "w");
    
    fprintf(output, "P3\n");
    fprintf(output, "%d %d\n", view.width, view.height);
    fprintf(output, "%d\n\n", 255);
    
    castAllRays(&view, &eyePoint, &ambientLight, &lightSource, sphereList, &sphereListLength, &output);
    
    free(sphereList);
    fclose(output);
    
}

void tryOpen(FILE **file, char *fileName) {
    
    if (fileName == NULL) {
        printf("Please include a list of spheres.\n");
        exit(1);
    }
    
    *file = fopen(fileName, "r");
    
    if (*file == NULL) {
        printf("Could not open the specified file.\n");
        exit(1);
    }
    
}

void readSphereList(FILE **file, Sphere **sphereList, int *sphereListLength) {
    
    double x, y, z, rad, r, g, b, amb, diff, spec, rough;
    Point center;
    Color color;
    Finish finish;
    Sphere *sphere = (Sphere *) malloc(sizeof(Sphere));
    const char *readTemplate = "%f %f %f %f %f %f %f %f %f %f %f\n";
    
    while (!feof(*file)) {
        
        fscanf(*file, readTemplate, &x, &y, &z, &rad, &r, &g, &b, &amb, &diff, &spec, &rough);
        
        center = (Point) {x, y, z};
        color = (Color) {r, g, b};
        finish = (Finish) {amb, diff, spec, rough};
        *sphere = (Sphere) {center, rad, color, finish};
        
        append(sphere, sphereList, sphereListLength);
        
    }
    
}

void createView(View *view) {
    double minX = -10.0;
    double maxX = 10.0;
    double minY = -7.5;
    double maxY = 7.5;
    int width = 1024;
    int height = 786;
    *view = (View) {minX, maxX, minY, maxY, width, height};
}

void createEyePoint(Point *eyePoint) {
    double eyePointX = 0.0;
    double eyePointY = 0.0;
    double eyePointZ = -14.0;
    *eyePoint = (Point) {eyePointX, eyePointY, eyePointZ};
}

void createLightSource(Light *lightSource) {
    double lightPointX = -100.0;
    double lightPointY = 100.0;
    double lightPointZ = -100.0;
    double lightColorR = 1.5;
    double lightColorG = 1.5;
    double lightColorB = 1.5;
    Point lightPoint = (Point) {lightPointX, lightPointY, lightPointZ};
    Color lightColor = (Color) {lightColorR, lightColorG, lightColorB};
    *lightSource = (Light) {lightPoint, lightColor};
}

void createAmbience(Color *ambientLight) {
    double ambientLightR = 1.0;
    double ambientLightG = 1.0;
    double ambientLightB = 1.0;
    *ambientLight = (Color) {ambientLightR, ambientLightG, ambientLightB};
}