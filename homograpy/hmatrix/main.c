#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "matrix.h"


int main() {
    coordinate a1, a2, a3, a4;
    coordinate b1, b2, b3, b4;

    a1.x = 0; a1.y = 0;
    a2.x = 100; a2.y = 0;
    a3.x = 0; a3.y = 100;
    a4.x = 100; a4.y = 120;

    b1.x = 0; b1.y = 0;
    b2.x = 100; b2.y = 0;
    b3.x = 0; b3.y = 100;
    b4.x = 100; b4.y = 100;

    float a[16] = {1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,0};

    float* hmatrix = homograpy(a1, a2, a3, a4, b1, b2, b3, b4);

    print_matrix_float(hmatrix, 3, 3);


    printf("\n\n\n");

    

    return 0;
}

