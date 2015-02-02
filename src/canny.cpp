//
//  edgeDetection.cpp
//
//
//  Created by Shashank Ranjan on 11/21/14.
//
//

#include "canny.h"

using namespace std;
float gradImage[512][512];
int eDirec[512][512], wHeight, wWidth;

void applyGradientOperator(float img[], float opX[][3], float opY[][3]){
    float Gx = 0.0, Gy = 0.0, angle;
    int row = 0, col = 0, oprow = 0, opcol = 0, rowTotal = 0, colTotal = 0, offset, i;
    cout<<"Applying gradient operator...\n";
    for(row = 0; row < wHeight - 2;row++){
        for(col = 0; col < wWidth - 2;col++){
            Gx = 0.0;
            Gy = 0.0;
            for(oprow = -1;oprow <= 1;oprow++){
                for(opcol = -1; opcol <= 1;opcol++){
                    rowTotal = row + oprow;
                    colTotal = col + opcol;
                    offset = (unsigned long)(rowTotal*3*wWidth + colTotal*3);
                    Gx = Gx + img[offset] * opX[oprow + 1][opcol + 1];
                    Gy = Gy + img[offset] * opY[oprow + 1][opcol + 1];
                }
            }
            gradImage[row][col] = sqrt(pow(Gx, 2.0) + pow(Gy, 2.0));
            angle = (atan2(Gx,Gy)/M_PI) * 180.0;
            if((angle >= 0 && angle < 22.5)||(angle >= 157.5 && angle < 180)){
                eDirec[row][col] = 0;
            }else if(angle >= 22.5 && angle < 67.5){
                eDirec[row][col] = 45;
            }else if(angle >= 67.5 && angle < 112.5){
                eDirec[row][col] = 90;
            }else{
                eDirec[row][col] = 135;
            }
        }
    }
    cout<<"Gradient Calculation Done...\n";
}

void findEdge(float img[], int rAdd, int cAdd, int row, int col, int direc, float lThreshold){
    bool edgeEnd = false;
    int nCol = 0, nRow = 0, i = 0;
    if(cAdd < 0){
        if(col > 0){
            nCol = cAdd + col;
        } else {
            edgeEnd = true;
        }
    } else if(col < wWidth - 1){
        nCol = cAdd + col;
    } else {
        edgeEnd = true;
    }
    
    if(rAdd < 0){
        if(row > 0){
            nRow = rAdd + row;
        } else {
            edgeEnd = true;
        }
    } else if(row < wHeight - 1) {
        nRow = rAdd + row;
    } else {
        edgeEnd = true;
    }
    
    while(eDirec[nRow][nCol]==direc && !edgeEnd && gradImage[nRow][nCol] > lThreshold){
        i = (unsigned long)(nRow*3*wWidth + 3*nCol);
        img[i] =
        img[i + 1] =
        img[i + 2] = 0;
        if(cAdd < 0){
            if(col > 0){
                nCol = cAdd + nCol;
            } else {
                edgeEnd = true;
            }
        } else if(col < wWidth - 1){
            nCol = cAdd + nCol;
        } else {
            edgeEnd = true;
        }
        
        if(rAdd < 0){
            if(row > 0){
                nRow = rAdd + nRow;
            } else {
                edgeEnd = true;
            }
        } else if(row < wHeight - 1) {
            nRow = rAdd + nRow;
        } else {
            edgeEnd = true;
        }
    }
}

void traceEdge(float img[], float uThreshold, float lThreshold){
    int i = 0, row = 0, col = 0;
    bool edgeEnd = false;
    cout<<"Tracing Edges...\n";
    for(row = 1; row < wHeight - 1;row++){
        for(col = 1; col < wWidth - 1; col++){
            edgeEnd = false;
            if(gradImage[row][col] > uThreshold){
                switch(eDirec[row][col]){
                    case 0 : {
                        findEdge(img, 0, 1, row, col, 0, lThreshold);
                        break;
                    }
                        
                    case 45 : {
                        findEdge(img, 1, 1, row, col, 45, lThreshold);
                        break;
                    }
                        
                    case 90 : {
                        findEdge(img, 1, 0, row, col, 90, lThreshold);
                        break;
                    }
                        
                    case 135 : {
                        findEdge(img, 1, -1, row, col, 135, lThreshold);
                        break;
                    }
                        
                    default : {
                        i = (unsigned long)(row*3*wWidth + 3*col);
                        img[i] =
                        img[i + 1] =
                        img[i + 2] = 1;
                        break;
                    }
                }
            } else {
                i = (unsigned long)(row*3*wWidth + 3*col);
                img[i] =
                img[i + 1] =
                img[i + 2] = 1;
            }
        }
    }
    
    for (row = 0; row < wHeight; row++) {
        for (col = 0; col < wWidth; col++) {
            // Recall each pixel is composed of 3 bytes
            i = (unsigned long)(row*3*wWidth + 3*col);
            // If a pixel's grayValue is not black or white make it black
            if( (img[i] != 1 && img[i] != 0) || (img[i + 1] != 1 && img[i + 1] != 0) || (img[i + 2] != 1 && img[i + 2] != 0))
                img[i] =
                img[i + 1] =
                img[i + 2] = 1; // Make pixel black
        }
    }
    cout<<"Edges Traced...\n";
}

//for debugging
void printImage(float img[]){
    cout<<"The image currently has : \n";
    for(int i = 0;i < 512*512*3;i+=3){
        if((img[i] != 0 && img[i] != 1) || (img[i+1] != 0 && img[i+1] != 1) || (img[i+2] != 0 && img[i+1] != 1)){
            cout<<"("<<img[i]<<","<<img[i+1]<<","<<img[i+2]<<")\n";
        }
    }
    cout<<"--------------------------------------------------\n\n";
}

void canny(float img[], int height, int width){
    float gFilter[5][5], sobelX[3][3], sobelY[3][3];
    wHeight = height;
    wWidth = width;
    
    
    /* Declare Sobel masks */
    sobelX[0][0] = -1; sobelX[0][1] = 0; sobelX[0][2] = 1;
    sobelX[1][0] = -2; sobelX[1][1] = 0; sobelX[1][2] = 2;
    sobelX[2][0] = -1; sobelX[2][1] = 0; sobelX[2][2] = 1;
    
    sobelY[0][0] =  1; sobelY[0][1] =  2; sobelY[0][2] =  1;
    sobelY[1][0] =  0; sobelY[1][1] =  0; sobelY[1][2] =  0;
    sobelY[2][0] = -1; sobelY[2][1] = -2; sobelY[2][2] = -1;
    
    //appy gradient operator
    applyGradientOperator(img, sobelX, sobelY);
    
    //trace the edges
    traceEdge(img, 3, 2);
    cout<<"Canny finished...\n";
}