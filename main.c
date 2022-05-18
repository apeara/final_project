#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "convolution.h"
#include "image.h"


/*
typedef struct {
    char M, N;//매직넘버
    int row_size;//넓이
    int col_size;//높이
    int scale;
    unsigned char* pixels;//픽셀 데이터
}image_p5;//p5 pgm파일이면 이거 쓰면 됩니다.

typedef struct {
    char M, N;//매직넘버
    int row_size;//넓이
    int col_size;//높이
    int scale;
    int* pixels;//픽셀 데이터
}image_p2; //p2 pgm파일은 이거 쓰면 됩니다.
*/

/*
    아래의 빈칸에 만드신 함수를 넣어주세요. 각 단계마다 처리된 이미지를 출력할 것입니다. 함수선언 하실 때
    가능하면 void function_name(image_p2* output_data, image_p2* input_data, 그 외의 필요한 변수들...){}
    식으로 선언해주세요. 보기 쉽고 일관성있게 만들려고 합니다. 만드신 함수는 헤더파일에 넣어서 참조할
    생각입니다. 위의#include "convolution.h", #include "image.h"와 같이 헤더파일로 만들어서 안에 함수를
    넣어주세요.

    그리고 convolution.h의 필터 자료형은 float로, in/out data의 자룔형은 int로 고정하여서 사용할
    생각입니다. 혹시 바꾸어서 함수를 만들었다면 이름을 바꾸어 헤더파일을 선언하여 참조해주세요.
    내부의 함수 이름들도 바꾸어야 합니다.
*/

int main() {
    int f_size;
    float sig;
    int HT, LT;
    image_p5* img = read_image_pgm_p5("ttt.pgm");
    image_p2* tmp0 = pconvert_p5_to_p2(img);    
    
    
    //평균값
    image_p2* tmp1 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);
    average_filter(tmp1, tmp0, 3);
    image_write("result1.pgm", tmp1);
    

    //가우시안
    image_p2* tmp2 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);//함수에 넣을 출력입니다.
    Gaussian_filter(tmp2, tmp0, 0.8, 3);
    image_write("result2.pgm", tmp2);
    


    //이미지 그라이언트
    image_p2* tmp3 = image_reset(tmp2->M, tmp2->N, tmp2->scale, tmp2->row_size, tmp2->col_size);//함수에 넣을 출력입니다.
    image_p2* tmp4 = image_reset(tmp2->M, tmp2->N, tmp2->scale, tmp2->row_size, tmp2->col_size);//함수에 넣을 출력입니다.
    gradient(tmp3, tmp4, tmp2, 2);
    image_write("result3.pgm", tmp3);
    image_write("result4.pgm", tmp4);


    //비최대 억제
    image_p2* tmp5 = image_reset(tmp3->M, tmp3->N, tmp3->scale, tmp3->row_size, tmp3->col_size);//함수에 넣을 출력입니다.
    image_p2* tmp6 = image_reset(tmp4->M, tmp4->N, tmp4->scale, tmp4->row_size, tmp4->col_size);//함수에 넣을 출력입니다.
    NonMax(tmp5, tmp3, tmp4,1);
    image_write("result5.pgm", tmp5);
    //image_write("result6.pgm", tmp6);
   


    //이력 현상 임계화
    image_p2* tmp7 = image_reset(tmp5->M, tmp5->N, tmp5->scale, img->row_size, img->col_size);//함수에 넣을 출력입니다.
    DoubleT(tmp7, tmp5, 200, 50);
    image_write("result7.pgm", tmp7);


    //Hysterisis
    image_p2* tmp8 = image_reset(tmp7->M, tmp7->N, tmp7->scale, tmp7->row_size, tmp7->col_size);//함수에 넣을 출력입니다.
    image_p2* tmp9 = image_reset(tmp4->M, tmp4->N, tmp4->scale, tmp4->row_size, tmp4->col_size);//함수에 넣을 출력입니다.
    //Hysterisis(tmp8,tmp9,tmp7,tmp4);
    image_write("result8.pgm", tmp8);
    image_write("result9.pgm", tmp9);  



    close_image_p5(img);
    close_image_p2(tmp0);
    close_image_p2(tmp2);
    close_image_p2(tmp3);
    close_image_p2(tmp4);
    close_image_p2(tmp5);
    close_image_p2(tmp6);
    close_image_p2(tmp7);
    close_image_p2(tmp8);
    close_image_p2(tmp9);
    

    printf("\n\n---finish---\n\n");
    return 0;
}