/*
    convolution 헤더 파일입니다. 헤더파일을 선언하고 사용해 주세요. //#include "convolution.h"

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

    filter는 row_size와 col_size가 같다고 생각하고 만들었습니다. row_size를 넣어주세요.

*/


#include <stdio.h>
#include <stdlib.h>



typedef int TYPE;// 여기서 data type을 설정하세요.
typedef float filter_TYPE;


void conv(TYPE* output_data, TYPE* input_data, filter_TYPE* filter, int row_size, int col_size, int filter_row_size);
void print_matrix(TYPE* input_data, int row_size, int col_size);
void padding_matrix(TYPE* output_data, TYPE* input_data, TYPE padding_number, int row_size, int col_size);




void conv(TYPE* output_data, TYPE* input_data, filter_TYPE* filter, int row_size, int col_size, int filter_row_size) {

    // output_data는 conv연산을 시행한 출력값입니다. 포인터를 지정해주세요.
    // input_data에 처리를 하고싶은 data를 입력하세요. 
    // 데이터의 size는 이어서 오는  row_size와 col_size에 넣어주세요.
    // filter도 마찬가지로 넣어주세요.

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

    // matrix를 출력하여 보기위한 함수입니다.
    // data와 size를 넣어주세요.
    // 아래의 출력 자료형을 원하는 것으로 바꾸어 주세요.

    int out = 0;
    for (int i = 0; i < col_size; i++) {
        for (int j = 0; j < row_size; j++) {
            printf("%d\t", input_data[out++]);//여기서 자료형을 바꾸면 됩니다. TYPE와 같은 자료형 타입으로 바꾸면 됩니다.
        }
        printf("\n");
    }

    return;
}

void padding_matrix(TYPE* output_data, TYPE* input_data, TYPE padding_number, int row_size, int col_size) {

    // padding을 하는 함수입니다.
    // padding는 conv 등으로 인하여 줄어드는 row,col_size를 보상해주기 위한 방법입니다.
    // 기존 매트릭스에 원하는 숫자를 감싸는 식으로 row,col_size를 키워줍니다.
    // row,col_size를 각각 1식 증가시키기 위한 함수입니다.
    // in,outdata는 포인터를 넣어주세요.
    // padding_number는 padding 자리에 넣을 값입니다.
    // row,col_size는 input_data가 기준입니다.

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