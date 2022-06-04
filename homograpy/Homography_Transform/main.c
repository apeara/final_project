#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"




int main() {
    coordinate a1, a2, a3, a4;
    coordinate b1, b2, b3, b4;

    a1.x = 65; a1.y = 70;
    a2.x = 105; a2.y = 70;
    a3.x = 15; a3.y = 200;
    a4.x = 130; a4.y = 200;

    b1.x = 0; b1.y = 0;
    b2.x = 167; b2.y = 0;
    b3.x = 0; b3.y = 299;
    b4.x = 167; b4.y = 299;

    float* hmatrix = homomat(a1, a2, a3, a4, b1, b2, b3, b4);
    printf("\n\n\n");
    print_matrix_float(hmatrix, 3, 3);
    printf("\n\n\n");


    image_p5* img = read_image_pgm_p5("ttt.pgm");
    image_p2* tmp0 = pconvert_p5_to_p2(img);
    
    image_p2* tmp1 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);
    homograpy_transform(tmp1, tmp0, a1, a2, a3, a4, b1, b2, b3, b4);
    image_write("homo_trans.pgm", tmp1);


    return 0;
}