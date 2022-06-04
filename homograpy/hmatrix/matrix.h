#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x;
    int y;
}coordinate;


float det(float* matrix, int size);
float* homograpy(coordinate x1, coordinate x2, coordinate x3, coordinate x4,
    coordinate y1, coordinate y2, coordinate y3, coordinate y4);


float det(float* matrix, int size) { // matrix의 크기는 size x size
    float temp = 0;


    if (size == 2) {
        return matrix[0] * matrix[3] - matrix[1] * matrix[2];
    }

    else {
        for (int i = 0; i < size; i++) {
            float* tem;
            tem = (float*)malloc(sizeof(float) * (size - 1) * (size - 1));

            int te = 0;
            for (int y = 1; y < size; y++) {
                for (int x = 0; x < size; x++) {
                    if (x != i) {
                        tem[te++] = matrix[y * size + x];
                    }
                }
            }

            if ((i + 1) % 2 == 1) {
                temp = matrix[i] * det(tem, size - 1) + temp;
            }
            else {
                temp = (-1) * matrix[i] * det(tem, size - 1) + temp;
            }

            free(tem);
        }
    }

    return temp;
}


float* homograpy(coordinate c1, coordinate c2, coordinate c3, coordinate c4,
    coordinate cp1, coordinate cp2, coordinate cp3, coordinate cp4) {

    float* mat = (float*)malloc(sizeof(float) * 8 * 8);
    if (mat == NULL) {
        printf("-2-\n");
    }
    int i = 0;

    //i = 0
    mat[i * 8 + 0] = c1.x;
    mat[i * 8 + 1] = c1.y;
    mat[i * 8 + 2] = 1;
    mat[i * 8 + 3] = 0;
    mat[i * 8 + 4] = 0;
    mat[i * 8 + 5] = 0;
    mat[i * 8 + 6] = (-1) * c1.x * cp1.x;
    mat[i * 8 + 7] = (-1) * c1.y * cp1.x;
    //printf("-1- \n");

    mat[i * 8 + 8] = 0;
    mat[i * 8 + 9] = 0;
    mat[i * 8 + 10] = 0;
    mat[i * 8 + 11] = c1.x;
    mat[i * 8 + 12] = c1.y;
    mat[i * 8 + 13] = 1;
    mat[i * 8 + 14] = (-1) * c1.x * cp1.y;;
    mat[i * 8 + 15] = (-1) * c1.y * cp1.y;;
    i++;
    i++;

    //i = 1
    mat[i * 8 + 0] = c2.x;
    mat[i * 8 + 1] = c2.y;
    mat[i * 8 + 2] = 1;
    mat[i * 8 + 3] = 0;
    mat[i * 8 + 4] = 0;
    mat[i * 8 + 5] = 0;
    mat[i * 8 + 6] = (-1) * c2.x * cp2.x;
    mat[i * 8 + 7] = (-1) * c2.y * cp2.x;

    mat[i * 8 + 8] = 0;
    mat[i * 8 + 9] = 0;
    mat[i * 8 + 10] = 0;
    mat[i * 8 + 11] = c2.x;
    mat[i * 8 + 12] = c2.y;
    mat[i * 8 + 13] = 1;
    mat[i * 8 + 14] = (-1) * c2.x * cp2.y;;
    mat[i * 8 + 15] = (-1) * c2.y * cp2.y;;
    i++; i++;

    //i = 2
    mat[i * 8 + 0] = c3.x;
    mat[i * 8 + 1] = c3.y;
    mat[i * 8 + 2] = 1;
    mat[i * 8 + 3] = 0;
    mat[i * 8 + 4] = 0;
    mat[i * 8 + 5] = 0;
    mat[i * 8 + 6] = (-1) * c3.x * cp3.x;
    mat[i * 8 + 7] = (-1) * c3.y * cp3.x;

    mat[i * 8 + 8] = 0;
    mat[i * 8 + 9] = 0;
    mat[i * 8 + 10] = 0;
    mat[i * 8 + 11] = c3.x;
    mat[i * 8 + 12] = c3.y;
    mat[i * 8 + 13] = 1;
    mat[i * 8 + 14] = (-1) * c3.x * cp3.y;;
    mat[i * 8 + 15] = (-1) * c3.y * cp3.y;;
    i++; i++;

    //i = 3
    mat[i * 8 + 0] = c4.x;
    mat[i * 8 + 1] = c4.y;
    mat[i * 8 + 2] = 1;
    mat[i * 8 + 3] = 0;
    mat[i * 8 + 4] = 0;
    mat[i * 8 + 5] = 0;
    mat[i * 8 + 6] = (-1) * c4.x * cp4.x;
    mat[i * 8 + 7] = (-1) * c4.y * cp4.x;

    mat[i * 8 + 8] = 0;
    mat[i * 8 + 9] = 0;
    mat[i * 8 + 10] = 0;
    mat[i * 8 + 11] = c4.x;
    mat[i * 8 + 12] = c4.y;
    mat[i * 8 + 13] = 1;
    mat[i * 8 + 14] = (-1) * c4.x * cp4.y;;
    mat[i * 8 + 15] = (-1) * c4.y * cp4.y;;

    float mat_det = det(mat, 8);
    float homo_det[8];

    for (int i = 0; i < 8; i++) {
        float* mat_homo = (float*)malloc(sizeof(float) * 8 * 8);

        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                if (x != i) {
                    mat_homo[y * 8 + x] = mat[y * 8 + x];
                }

                else {
                    switch (y) {
                    case 0:
                        mat_homo[y * 8 + x] = cp1.x;
                        break;

                    case 1:
                        mat_homo[y * 8 + x] = cp1.y;
                        break;

                    case 2:
                        mat_homo[y * 8 + x] = cp2.x;
                        break;

                    case 3:
                        mat_homo[y * 8 + x] = cp2.y;
                        break;

                    case 4:
                        mat_homo[y * 8 + x] = cp3.x;
                        break;

                    case 5:
                        mat_homo[y * 8 + x] = cp3.y;
                        break;

                    case 6:
                        mat_homo[y * 8 + x] = cp4.x;
                        break;

                    case 7:
                        mat_homo[y * 8 + x] = cp4.y;
                        break;

                    default:
                        break;

                    }

                }
            }
        }


        homo_det[i] = det(mat_homo, 8);

        free(mat_homo);
    }

    float* homo = (float*)malloc(sizeof(float) * 9);

    for (int i = 0; i < 8; i++) {
        homo[i] = homo_det[i] / mat_det;
    }
    homo[8] = 1;

    return homo;
}