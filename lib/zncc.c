/*==========================================================
 * zncc.c
 *
 *========================================================*/

#include "mex.h"
#include "matrix.h"
#include <stdlib.h>
#include <math.h>

/* Prototypes */
void zncc(unsigned char *rightImage, unsigned char* leftImage, int corrWindowSize, int dMin, int dMax, int* dispMap, int ncols, int nrows);


/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    unsigned char *im0, *im1;       /* input scalar */
    size_t ncols, nrows;            /* size of matrix */
    int *outMatrix;                 /* output matrix */

   
    /* get the value of the scalar input  */
    im0 = (unsigned char *)mxGetPr(prhs[0]);
    im1 = (unsigned char *)mxGetPr(prhs[1]);

    /* get dimensions of the input matrix */
    const mwSize *imgdims = mxGetDimensions(prhs[0]);
    ncols = imgdims[0];
    nrows = imgdims[1];

    /* create the output matrix */
    mxArray *out = mxCreateNumericArray(2, imgdims, mxINT32_CLASS, mxREAL);
    plhs[0] = out;
    outMatrix = (int *) mxGetData(out);
   
    zncc(im0, im1, 9, 0, 50, outMatrix, ncols, nrows);

    
}




void zncc(unsigned char *rightImage, unsigned char* leftImage, int corrWindowSize, int dMin, int dMax, int* dispMap, int ncols, int nrows)
{
    // Find out how many rows and columns are to the left/right/up/down of the central pixel based on the window size
    int win = (corrWindowSize-1)/2;
    
    unsigned char *regionLeft, *regionRight;
    int *tempCorrScore;
    
    const mwSize regdims[2] = {2*win+1,2*win+1};
    mxArray *regionLeft_ = mxCreateNumericArray(2,regdims, mxUINT8_CLASS, mxREAL);
    mxArray *regionRight_ = mxCreateNumericArray(2,regdims, mxUINT8_CLASS, mxREAL);
    mxArray *tempCorrScore_ = mxCreateNumericArray(2,regdims, mxINT32_CLASS, mxREAL);
    regionLeft = (unsigned char*) mxGetData(regionLeft_);
    regionRight = (unsigned char*) mxGetData(regionRight_);
    tempCorrScore = (int *) mxGetData(tempCorrScore_);
    
    int regionSize = (2*win+1)*(2*win+1);
    //unsigned char *regionLeft = (unsigned  char *) calloc(regionSize,sizeof(unsigned char));
    //unsigned char *regionRight = (unsigned  char *) calloc(regionSize,sizeof(unsigned char));
    //int *tempCorrScore = (int *) calloc(regionSize,sizeof(int));
    
    for(int i=win; i < nrows-win; i++) {
        // For every row in Left Image
        for(int j=win; j < ncols-win-dMax; j++) {
            //% For every column in Left Image
            //% Initialize the temporary variable to hold the previous
            //% correlation score
            double prevcorrScore = 0.0;

            // % Initialize the temporary variable to store the best matched
            // % disparity score
            int bestMatchSoFar = dMin;
            
            for(int d=dMin; d < dMax; d+=5){
                
                //% For every disparity value in x-direction
                //% Construct a region with window around
                //% central/selected pixel in left image
                
                double meanLeft = 0.0;
                for(int r1 = i-win; r1 < i+win; r1++){
                    for(int r2 = j+d-win; r2 < j+d+win; r2++){
                        regionLeft[r1*(2*win+1)+r2] = leftImage[r1*nrows+r2];
                        meanLeft += (double) regionLeft[r1*(2*win+1)+r2];
                    }
                }
                meanLeft /= regionSize;
            
                //% Construct a region with window around
                //% central/selected pixel in right image
                // regionRight=rightImage(i-win : i+win, j+d-win : j+d+ win);
                
                double meanRight = 0.0;
                for(int r1 = i-win; r1 < i+win; r1++){
                    for(int r2 = j+d-win; r2 < j+d+win; r2++){
                        regionRight[r1*(2*win+1)+r2] = rightImage[r1*nrows+r2];
                        meanRight += regionRight[r1*(2*win+1)+r2];
                    }
                }
                meanRight /= regionSize;
                
                //% Calculate the local mean in left region
                //meanLeft = mean2(regionLeft);
                
                //% Calculate the local mean in right region
                //meanRight = mean2(regionRight);
                
                //% Initialize the variable to store temporarily the
                //% correlation scores
                
                
                //% Calculate the correlation score
                // % Calculate the term in the denominator (var: den)
                double den = 0.0, sum1=0.0, sum2=0.0;
                for(int k = 0; k < regionSize; k++){
                    sum1 += (regionLeft[k]-meanLeft)*(regionLeft[k]-meanLeft);
                    sum2 += (regionRight[k]-meanRight)*(regionRight[k]-meanRight);
                    tempCorrScore[k] = ( (double) regionLeft[k] - meanLeft)*( (double) regionRight[k] - meanRight);
                }
                den = sqrt(sum1*sum2);
                
                //tempCorrScore = (regionLeft - meanLeft).*(regionRight - meanRight)/den;

                //% Compute the final score by summing the values in
                //% tempCorrScore,
                //% and store it in a temporary variable signifying the
                //% distance
                //% (var: corrScore)
                double corrScore = 0.0;
                for(int k = 0; k < regionSize; k++){
                    corrScore += tempCorrScore[k];
                }
                corrScore /= den;

                if(corrScore>prevcorrScore){
                    //% If the current disparity value is greater
                    //% than
                    //% previous one, then swap them
                    prevcorrScore=corrScore;
                    bestMatchSoFar=d;
                }
                
                
            }
            //% Store the final matched value in variable dispMap
            dispMap[i+j*nrows] = bestMatchSoFar;
        }
    }
    
    mxDestroyArray(regionLeft_);
    mxDestroyArray(regionRight_);
    mxDestroyArray(tempCorrScore_);
}
