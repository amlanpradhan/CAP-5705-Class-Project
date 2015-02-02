//
//  canny.h
//  
//
//  Created by Shashank Ranjan on 11/23/14.
//
//

#ifndef _canny_h
#define _canny_h

#include <stdio.h>
#include <iostream>
#include <math.h>

void gSmoothImage(float img[], float mask[][5]);
void applyGradientOperator(float img[], float opX[][3], float opY[][3]);
void findEdge(float img[], int rAdd, int cAdd, int row, int col, int direc, float lThreshold);
void traceEdge(float img[], float uThreshold, float lThreshold);
void canny(float img[], int height, int width);

#endif
