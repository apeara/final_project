#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "convolution.h"
#include "image.h"


#define filter_row_size 3
#define f_size filter_row_size * filter_row_size

typedef int filter_TYPE;


/*
int main() {

    int filter[f_size] = { 1, 1, 1, 1,
                           0, 0, 0, 0,
                           1, 1, 1, 1,
                           0, 0, 0, 0};

    TYPE test_data[row_size * col_size] = { 0, 0, 0, 0, 0, 0,
                                            1,10,10,10,10,10,
                                            0, 0, 0, 0, 2, 0,
                                            1, 1, 1, 1, 1, 1,
                                            0, 0, 0, 0, 0, 0 };

    TYPE* data = (TYPE*)malloc(sizeof(TYPE) * (row_size - 3) * (col_size - 3));
    TYPE* outdata = (TYPE*)malloc(sizeof(TYPE) * row_size * col_size);

    print_matrix(test_data, row_size, col_size);
    printf("\n\n\n");

    conv(data, test_data, filter, row_size, col_size, filter_row_size);

    print_matrix(data, row_size - 3, col_size - 3);
    printf("\n\n\n");

    padding_matrix(outdata, data, (TYPE)5, row_size - 3, col_size - 3);

    print_matrix(outdata, row_size - 1, col_size - 1);

    free(data);
    free(outdata);

    return 0;
}*/

int main() {
    image* img;
    image* tmp;

    filter_TYPE filter[f_size] = { /*0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                             0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                             0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                             0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                             0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                             0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                             0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                             0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                             0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01,
                             0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01, 0.01*/
    -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1

        //0.1111,0.1111,0.1111,
        //0.1111,0.1111,0.1111,
        //0.1111,0.1111,0.1111
    };


    img = read_image_pgm_p2("test.pgm");
    tmp = image_reset(img->M, img->N, img->row_size - filter_row_size + 1, img->col_size - filter_row_size + 1);

 
    conv(tmp->pixels,img->pixels, filter, img->row_size, img->col_size, filter_row_size);


    image_write("test_light.pgm",tmp);


    close_image(img);
    close_image(tmp);



    return 0;
}

