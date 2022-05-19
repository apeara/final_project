/*
    convolution ��� �����Դϴ�. ��������� �����ϰ� ����� �ּ���. //#include "convolution.h"

                ---row_size---

        []      []      []      ...     []
   |
   |    []      []      []      ...     []
   |
  col_  .       .                       .
  size  .       .                       .
   |    .       .                       .
   |
   |    []      []      []      ...     []

        []      []      []      ...     []

    filter�� row_size�� col_size�� ���ٰ� �����ϰ� ��������ϴ�. row_size�� �־��ּ���.

*/


#include <stdio.h>
#include <stdlib.h>



typedef int TYPE;// ���⼭ data type�� �����ϼ���.
typedef float filter_TYPE;


void conv(TYPE* output_data, TYPE* input_data, filter_TYPE* filter, int row_size, int col_size, int filter_row_size);
void print_matrix(TYPE* input_data, int row_size, int col_size);
void padding_matrix(TYPE* output_data, TYPE* input_data, TYPE padding_number, int row_size, int col_size);




void conv(TYPE* output_data, TYPE* input_data, filter_TYPE* filter, int row_size, int col_size, int filter_row_size) {

    // output_data�� conv������ ������ ��°��Դϴ�. �����͸� �������ּ���.
    // input_data�� ó���� �ϰ���� data�� �Է��ϼ���. 
    // �������� size�� �̾ ����  row_size�� col_size�� �־��ּ���.
    // filter�� ���������� �־��ּ���.

    int filter_size = filter_row_size * filter_row_size;
    int r, c, fr, fc;
    int out = 0;
    TYPE temp, mul;


    for (int i = 0; i < (row_size - filter_row_size + 1) * (col_size - filter_row_size + 1); i++) {
        output_data[i] = (TYPE)0;
    }

    for (c = 0; c < col_size - filter_row_size + 1; c++) { //conv_filter_trans_row
        for (r = 0; r < row_size - filter_row_size + 1; r++) { //conv_filter_trans_col
            temp = (TYPE)0;

            for (fc = 0; fc < filter_row_size; fc++) { //filter_trans_row
                for (fr = 0; fr < filter_row_size; fr++) { //filter_trans_row
                    mul = input_data[r + c * row_size + fr + fc * row_size] * filter[fr + fc * filter_row_size];
                    temp += mul;
                }
            }

            output_data[out++] = (int)temp;
        }
    }

    return;
}

void print_matrix(TYPE* input_data, int row_size, int col_size) {

    // matrix�� ����Ͽ� �������� �Լ��Դϴ�.
    // data�� size�� �־��ּ���.
    // �Ʒ��� ��� �ڷ����� ���ϴ� ������ �ٲپ� �ּ���.

    int out = 0;
    for (int i = 0; i < col_size; i++) {
        for (int j = 0; j < row_size; j++) {
            printf("%d\t", input_data[out++]);//���⼭ �ڷ����� �ٲٸ� �˴ϴ�. TYPE�� ���� �ڷ��� Ÿ������ �ٲٸ� �˴ϴ�.
        }
        printf("\n");
    }

    return;
}

void padding_matrix(TYPE* output_data, TYPE* input_data, TYPE padding_number, int row_size, int col_size) {

    // padding�� �ϴ� �Լ��Դϴ�.
    // padding�� conv ������ ���Ͽ� �پ��� row,col_size�� �������ֱ� ���� ����Դϴ�.
    // ���� ��Ʈ������ ���ϴ� ���ڸ� ���δ� ������ row,col_size�� Ű���ݴϴ�.
    // row,col_size�� ���� 1�� ������Ű�� ���� �Լ��Դϴ�.
    // in,outdata�� �����͸� �־��ּ���.
    // padding_number�� padding �ڸ��� ���� ���Դϴ�.
    // row,col_size�� input_data�� �����Դϴ�.

    for (int i = 0; i < (row_size + 2) * (col_size + 2); i++) {
        output_data[i] = (TYPE)padding_number;
    }

    for (int c = 0; c < col_size; c++) { //conv_filter_trans_row
        for (int r = 0; r < row_size; r++) { //conv_filter_trans_col
            output_data[(r + 1) + (row_size + 2) * (c + 1)] = (TYPE)input_data[r + row_size * c];

        }

    }

    return;
}