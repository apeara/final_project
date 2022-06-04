#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"




int main() {
    coordinate a1, a2, a3, a4;
    coordinate b1, b2, b3, b4;

    a1.x = 220; a1.y = 230;
    a2.x = 350; a2.y = 230;
    a3.x = 0; a3.y = 285;
    a4.x = 515; a4.y = 285;

    b1.x = 0; b1.y = 0;
    b2.x = 515; b2.y = 0;
    b3.x = 0; b3.y = 400;
    b4.x = 515; b4.y = 400;

    image_p5* img = read_image_pgm_p5("test.pgm");
    image_p2* tmp0 = pconvert_p5_to_p2(img);
    
    image_p2* tmp1 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);
    backward_mapping(tmp1, tmp0, a1, a2, a3, a4, b1, b2, b3, b4);
    image_write("homo_trans.pgm", tmp1);


    return 0;
}