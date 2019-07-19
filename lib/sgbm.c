/*==========================================================
 * sgbm.c - Semi-global block matching
 *
 *========================================================*/

#include "mex.h"
#include "matrix.h"

#include <math.h>

#define PATHS_PER_SCAN 8
#define SMALL_PENALTY 3
#define LARGE_PENALTY 20
#define window_height 9
#define window_width 9

#define C_TYPE unsigned int  
#define S_TYPE unsigned int
#define A_TYPE unsigned int

struct path {
    short rowDiff;
    short colDiff;
    short index;
};


struct limits
{
    int start_pt_x; int start_pt_y;
    int end_pt_x; int end_pt_y;
    int direction_x; int direction_y;
};

/* Prototypes */
void init_paths(int image_height, int image_width, struct limits *paths);
void calculateCostHamming(unsigned char *firstImage, unsigned char *secondImage, int disparityRange, C_TYPE ***C, S_TYPE ***S, int nrows, int ncols);
void disprange_aggregation(int disparityRange,C_TYPE ***C, A_TYPE ****A, long unsigned last_aggregated_k, int direction_x, int direction_y, int curx, int cury, int current_path, int image_width, int image_height);
void aggregation(unsigned char *firstImage, unsigned char *secondImage, int disparityRange, C_TYPE ***C, S_TYPE ***S, A_TYPE ****A, struct limits *paths, int image_width, int image_height);
void computeDisparity(int disparityRange, int rows, int cols, S_TYPE ***S, short* out_file_name);
void GaussianBlur(unsigned char *im0, int radius, int mu, int sigma) {}
unsigned int min(unsigned int i1, unsigned int i2) {return (i1 < i2) ? i1 : i2;};

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    unsigned char *im0, *im1;       /* input scalar */
    size_t ncols, nrows;            /* size of matrix */
    short *outMatrix;                 /* output matrix */

   
    /* get the value of the scalar input  */
    im0 = (unsigned char *)mxGetPr(prhs[0]);
    im1 = (unsigned char *)mxGetPr(prhs[1]);

    /* get dimensions of the input matrix */
    const mwSize *imgdims = mxGetDimensions(prhs[0]);
    ncols = imgdims[0];
    nrows = imgdims[1];

    /* create the output matrix */
    mxArray *out = mxCreateNumericArray(2, imgdims, mxINT16_CLASS, mxREAL);
    plhs[0] = out;
    outMatrix = (short *) mxGetData(out);
   
    // "Global" Variables
    struct limits paths[PATHS_PER_SCAN];
    init_paths(nrows, ncols, paths);

    // Define additional variables
    int disparityRange = 2*((int) ncols/4); // Go 1/4 of picture width in each direction
    
    C_TYPE ***C; // pixel cost array W x H x D
    S_TYPE ***S; // aggregated cost array W x H x D
    A_TYPE ****A; // single path cost array path_nos x W x H x D
    
    
    C = (C_TYPE***) mxCalloc(nrows, sizeof(C_TYPE**));
    S = (S_TYPE***) mxCalloc(nrows, sizeof(S_TYPE**));
    for (int row = 0; row < nrows; ++row) {
        C[row] = (C_TYPE**) mxCalloc(ncols,sizeof(C_TYPE*));
        S[row] = (S_TYPE**) mxCalloc(ncols,sizeof(S_TYPE*));
        for (int col = 0; col < ncols; ++col) {
            C[row][col] = (C_TYPE*)mxCalloc(disparityRange,sizeof(C_TYPE));
            S[row][col] = (S_TYPE*)mxCalloc(disparityRange,sizeof(S_TYPE));
        }
    }


    A = (A_TYPE ****) mxCalloc(PATHS_PER_SCAN,sizeof(A_TYPE***));
    for(int path = 0; path < PATHS_PER_SCAN; ++path) {
        A[path] = (A_TYPE ***) mxCalloc(nrows,sizeof(A_TYPE**));
        for (int row = 0; row < nrows; ++row) {
            A[path][row] = (A_TYPE**)mxCalloc(ncols,sizeof(A_TYPE*));
            for (int col = 0; col < ncols; ++col) {
                A[path][row][col] = (A_TYPE*) mxCalloc(disparityRange,sizeof(A_TYPE));
                for (unsigned int d = 0; d < disparityRange; ++d) {
                    A[path][row][col][d] = 0;
                }
            } 
        }
    }

    //Initial Smoothing
    GaussianBlur( im0, 3, 0, 0);
    GaussianBlur( im1, 3, 0, 0);

    // Calculate costs
    calculateCostHamming(im0, im1, disparityRange, C, S, (int) nrows, (int) ncols);

    // Aggregation
    aggregation(im0, im1, disparityRange, C ,S, A, paths, ncols, nrows);

    computeDisparity(disparityRange, nrows, ncols,  S, outMatrix);
}





void init_paths(int image_height, int image_width, struct limits *paths)
{
    //8 paths from center pixel based on change in X and Y coordinates
    for(int i =0 ; i< PATHS_PER_SCAN; i++)
    {
        switch(i)
        {
            case 1:
            paths[i].direction_x = 0;
            paths[i].direction_y = 1;
            paths[i].start_pt_y = window_width/2;
            paths[i].end_pt_y = image_width - window_width/2;
            paths[i].start_pt_x = window_height/2;
            paths[i].end_pt_x = image_height - window_height/2;
            break;

            case 3:
            paths[i].direction_x = 0;
            paths[i].direction_y = -1;
            paths[i].start_pt_y = image_width - window_width/2;
            paths[i].end_pt_y = window_width/2;
            paths[i].start_pt_x = window_height/2;
            paths[i].end_pt_x = image_height - window_height/2;
            break;

            case 5:
            paths[i].direction_x = 1;
            paths[i].direction_y = -1;
            paths[i].start_pt_y = image_width - window_width/2;
            paths[i].end_pt_y = window_width/2;
            paths[i].start_pt_x = window_height/2;
            paths[i].end_pt_x = image_height - window_height/2;
            break;

            case 7:
            paths[i].direction_x = -1;
            paths[i].direction_y = -1;
            paths[i].start_pt_y = image_width - window_width/2;
            paths[i].end_pt_y = window_width/2;
            paths[i].start_pt_x = image_height - window_height/2;
            paths[i].end_pt_x = window_height/2;
            break;


            case 0:
            paths[i].direction_x = 1;
            paths[i].direction_y = 0;
            paths[i].start_pt_y = window_width/2;
            paths[i].end_pt_y = image_width - window_width/2;
            paths[i].start_pt_x = window_height/2;
            paths[i].end_pt_x = image_height - window_height/2;
            break;

            case 2:
            paths[i].direction_x = -1;
            paths[i].direction_y = 0;
            paths[i].start_pt_y = window_width/2;
            paths[i].end_pt_y = image_width - window_width/2;
            paths[i].start_pt_x = image_height - window_height/2;
            paths[i].end_pt_x = window_height/2;
            break;

            case 4:
            paths[i].direction_x = 1;
            paths[i].direction_y = 1;
            paths[i].start_pt_y = window_width/2;
            paths[i].end_pt_y = image_width - window_width/2;
            paths[i].start_pt_x = window_height/2;
            paths[i].end_pt_x = image_height - window_height/2;
            break;

            case 6:
            paths[i].direction_x = -1;
            paths[i].direction_y = 1;
            paths[i].start_pt_y = window_width/2;
            paths[i].end_pt_y = image_width - window_width/2;
            paths[i].start_pt_x = image_height - window_height/2;
            paths[i].end_pt_x = window_height/2;
            break;
        }
    }
}

void calculateCostHamming(unsigned char *firstImage, unsigned char *secondImage, int disparityRange,C_TYPE ***C, S_TYPE ***S, int nrows, int ncols)
{
    unsigned long census_left = 0;
    unsigned long census_right = 0;
    unsigned int bit = 0;

    int bit_field = window_width*window_height-1;
    int i,j,x,y;
    int d=0;
    int shiftCount = 0;
    const int image_height=(int)nrows;
    const int image_width=(int)ncols;

    unsigned char imgTemp_left[image_height][image_width]; // = 0
    unsigned char imgTemp_right[image_height][image_width]; // = 0
    short disparityMapstage1[nrows][ncols]; // = 0


    long census_vleft[image_height][image_width];
    long census_vright[image_height][image_width];

    for (x = window_height/2; x < image_height - window_height/2; x++)
    {
        for(y = window_width/2; y < image_width - window_width/2; y++)
        {
            census_left = 0;
            shiftCount = 0;
            int bit_counter = 0;
            int census_array_left[bit_field];
            for (i = x - window_height/2; i <= x + window_height/2; i++)
            {
                for (j = y - window_width/2; j <= y + window_width/2; j++)
                {
                    if( shiftCount != window_width*window_height/2 )//skip the center pixel
                    {
                        census_left <<= 1;
                        if( firstImage[i*nrows+j] < firstImage[x*nrows+y] ){ //compare pixel values in the neighborhood
                            bit = 1;
                        }
                        else{
                            bit = 0;
                        }
                        census_left = census_left | bit;
                        census_array_left[bit_counter]=bit;
                        bit_counter++;
                    }
                    shiftCount ++;
                }
            }

            imgTemp_left[x][y] = (short)census_left;
            census_vleft[x][y] = census_left;

            census_right = 0;
            shiftCount   = 0;
            bit_counter  = 0;
            int census_array_right[bit_field];
            for (i = x - window_height/2; i <= x + window_height/2; i++)
            {
                for (j = y - window_width/2; j <= y + window_width/2; j++)
                {
                    if( shiftCount != window_width*window_height/2 )//skip the center pixel
                    {
                        census_right <<= 1;
                        if(secondImage[i*nrows+j] < secondImage[x*nrows+y]){ //compare pixel values in the neighborhood
                            bit = 1;
                        }
                        else{
                            bit = 0;
                        }
                        census_right = census_right | bit;
                        census_array_right[bit_counter]=bit;bit_counter++;
                    }
                    shiftCount ++;

                }
            }

            imgTemp_right[x][y] = (short)census_right;
            census_vright[x][y]=census_right;
        }

    }

    for(x = window_height/2; x < image_height - window_height/2; x++)
    {
        for(y = window_width/2; y < image_width - window_width/2; y++)
        {
            for(int d=0;d<disparityRange;d++)
            {
                int census_left = 0;
                int  census_right = 0;
                shiftCount = 0;
                int bit_counter=0;
                census_left = census_vleft[x][y];
                if (y-disparityRange/2+d<image_width - window_width/2)
                    census_right= census_vright[x][y+d];
                else census_right= census_vright[x][y-disparityRange+d];
                long answer=(long)(census_left^census_right); //Hamming Distance
                short dist=0;
                while(answer)
                {
                    ++dist;
                    answer&=answer-1;
                }
                C[x][y][d]=dist;
            }
        }
    }

    for (int row = 0; row < nrows; ++row)
    {
        for (int col = 0; col < ncols; ++col)
        {
            unsigned long smallest_cost=C[row][col][0];
            long smallest_disparity=0;
            for(d=disparityRange-1;d>=0;d--)
            {
                if(C[row][col][d]<smallest_cost)
                {
                    smallest_cost=C[row][col][d];
                    smallest_disparity=d-disparityRange/2;
                }
            }

            disparityMapstage1[row][col] = (short) smallest_disparity*255.0/disparityRange; //Least cost Disparity
        }
    }
}

void disprange_aggregation(int disparityRange,C_TYPE ***C, A_TYPE ****A, long unsigned last_aggregated_k, int direction_x, int direction_y, int curx, int cury, int current_path, int image_width, int image_height)
{
    long unsigned last_aggregated_i=C[curx][cury][0];

    for(int d=0;d<disparityRange;d++)
    {
        long unsigned term_1=A[current_path][curx-direction_x][cury-direction_y][0];
        long unsigned term_2=term_1;
        if(cury == window_width/2 || cury == image_width - window_width/2 || curx == window_height/2 || curx == image_height - window_height/2)
        {
            A[current_path][curx][cury][d]=C[curx][cury][d];
        }
        else
        {
            term_1=A[current_path][curx - direction_x][cury-direction_y][d];
            int limit_1,limit_2;
            if(d==0){
                term_2=A[current_path][curx - direction_x][cury - direction_y][d+1]+SMALL_PENALTY;
            }else if(d==disparityRange-1){
                term_2=A[current_path][curx - direction_x][cury-direction_y][d-1]+SMALL_PENALTY;
            }else{
               term_2=min(A[current_path][curx - direction_x][cury-direction_y][d-1]+SMALL_PENALTY,
                          A[current_path][curx - direction_x][cury-direction_y][d+1]+SMALL_PENALTY);
            }
            for(int pdisp=0;pdisp<disparityRange;pdisp++)
            {

                if((A[current_path][curx][cury-direction_y][pdisp]+LARGE_PENALTY)<term_1){
                    term_1=A[current_path][curx- direction_x][cury-direction_y][pdisp]+LARGE_PENALTY;
                }
            }
            A[current_path][curx][cury][d]=C[curx][cury][d]+min(term_1,term_2)-last_aggregated_k;
        }
        if(A[current_path][curx][cury][d]<last_aggregated_i){
            last_aggregated_i=A[current_path][curx][cury][d];
        }

    }
    last_aggregated_k=last_aggregated_i;
}


void aggregation(unsigned char *firstImage, unsigned char *secondImage, int disparityRange, C_TYPE ***C, S_TYPE ***S, A_TYPE ****A, struct limits *paths, int image_width, int image_height)
{
    //Even and Odd paths based on change in X and Y coordinates

    for(int ch_path = 0; ch_path < PATHS_PER_SCAN; ++ch_path)
    {
        long unsigned last_aggregated_k = 0;

        if(ch_path %2 !=0)
        {
            int dirx = paths[ch_path].direction_x;
            int diry = paths[ch_path].direction_y;
            int next_dim = 0;
            if(dirx == 0){
                next_dim = 1;
            }else{
                next_dim = dirx;
            }
            
            for(int x=paths[ch_path].start_pt_x; x!=paths[ch_path].end_pt_x ;x+=next_dim)
            {
                for(int y=paths[ch_path].start_pt_y;( y!=paths[ch_path].end_pt_y);y+=diry)
                {
                    disprange_aggregation(disparityRange,C, A, last_aggregated_k, dirx, diry, x, y, ch_path, image_width, image_height);
                }
            }
        }


        else if(ch_path%2 == 0)
        {
            int dirx = paths[ch_path].direction_x;
            int diry = paths[ch_path].direction_y;
            int next_dim = 0;
            if(diry == 0){
                next_dim = 1;
            }else{
                next_dim = diry;
            }
            for(int y=paths[ch_path].start_pt_y; y!=paths[ch_path].end_pt_y ;y+=next_dim)
            {
                for(int x=paths[ch_path].start_pt_x;( x!=paths[ch_path].end_pt_x);x+=dirx)
                {
                    disprange_aggregation(disparityRange,C, A, last_aggregated_k, dirx, diry, x, y, ch_path, image_width, image_height);
                }
            }

        }
    }

    for (int row = 0; row < image_height; ++row)
    {
        for (int col = 0; col < image_width; ++col)
        {
            for(int d = 0; d<disparityRange; d++)
            {
                for(int path = 0; path < PATHS_PER_SCAN; path ++)
                    S[row][col][d] += A[path][row][col][d]; //Aggregation
            }
        }
    }

}

void computeDisparity(int disparityRange, int rows, int cols, S_TYPE ***S, short* out_file_name)
{
    // short disparityMapstage2[cols][rows]; // = 0
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            unsigned long smallest_cost=S[row][col][0];
            int smallest_disparity=0;
            for(int d=disparityRange-1;d>=0;d--)
            {
                if(S[row][col][d]<smallest_cost)
                {
                    smallest_cost=S[row][col][d];
                    smallest_disparity=d-disparityRange/2; //Least cost disparity after Aggregation
                }
            }
            //disparityMapstage2[col][row] = (short) smallest_disparity*255.0/disparityRange;
            out_file_name[col*rows+row] = (short) smallest_disparity*255.0/disparityRange;
        }
    }
}

