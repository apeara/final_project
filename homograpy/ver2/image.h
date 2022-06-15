#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "convolution.h"
#include "matrix.h"


/*
    이미지 파일은 pgm파일을 사용합니다. pgm파일을 읽기 위해서는 추가적인 프로그램이 필요합니다.
    저는 'xnview'를 사용하여 읽습니다. 다운로드는 https://www.xnview.com/en/xnviewmp/#downloads
    여기서 진행하시면 됩니다. 파일변환도 저기서 가능합니다. 이미지 화면을 띄워 놓은 채로
    파일->선택저장?새로저장? 을 누르고 파일형식을 pgm으로 하면 됩니다.
    프로그램을 받기 귀찮으신 분은 https://convertio.co/kr/ 해당 온라인 사이트를 이용하시면
    이미지 자료형식을 변환하실 수 있습니다.



    그리고 convolution.h의 필터 자료형은 float로, in/out data의 자룔형은 int로 고정하여서 사용할
    예정입니다. 혹시 바꾸어서 함수를 만들었다면 이름을 바꾸어 헤더파일을 선언하여 참조해주세요.


*/

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

typedef struct {
    char M, N;//매직넘버 
    int row_size;//넓이
    int col_size;//높이
    unsigned char* pixels;//픽셀 데이터
}image_pbm; //이거는 pbm파일 구조체입니다. 사용할 일 없을 겁니다.

typedef struct {
    int row;//x좌표
    int col;//y좌표
    int pixels;
} pixel_data;


/*
    image_p5 : 매직넘버가 p5인 pgm파일을 읽기위한 구조체
    image : 매직넘버가 p2인 pgm파일을 읽기위한 구주체
    char* fileNm : 파일이름
    char M, char N : 매직넘버 ex)p2, p5
    int row_size, int col_size : 이미지의 가로/세로 크기
    int scale : gray 색을 몇단계로 표현할 지
*/

image_pbm* read_image_pbm(char* fileNm);
/*
    이거는 pbm파일 읽는 것입니다. 사용할 일 없을 겁니다.
*/

image_p2* image_reset(char M, char N, int scale, int row_size, int col_size);
/*
    이것은 image구조체를 초기화 하기 위한 함수 입니다. pgm파일의 pixels data를 제외한 정보를 넣으면 pixels data는 전부 '0'으로
    초기화 하여 반환하여 줍니다. 그 외의 pgm파일의 특징을 나타내는 매직넘버, 가로/세로크기, 스케일은 입력해준 값으로 초기화
    합니다.
*/

image_p5* read_image_pgm_p5(char* fileNm);
/*
    이 함수는 pgm파일 중에서 매직넘버가 p5로 선언되어 있는 함수를 목표로 제작한 함수입니다. 처음 pgm으로 변환한 파일에서는
    매직넘버가 p5로 선언되어 있기에 이것으로 읽어 드려야 합니다. 아마 테스트 할때나 가끔식 사용할 수 있을겁니다. 기본적으로
    처음 불러올 때만 사용할 것이기 때문에 최종결과물에서는 평균값필터에서만 사용될 것 같습니다.
*/

image_p2* read_image_pgm_p2(char* fileNm);
/*
    이 함수는 pgm파일 중에서 매직넘버가 p2로 선언되어 있는 함수를 목표로 제작한 함수입니다. 평균값 핕터를 지난 이미지 데이터는
    전부 매직넘버가 p2인 형식으로 저장되게 만들었습니다. 그래서 한번이라도 변형을 가한 이미지 파일은 이 함수로 읽어들여야
    합니다.
*/

image_p2* pconvert_p5_to_p2(image_p5* img);
/*
    image_p5자료형을 image_p2자료형으로 바꾸어 반환해주는 함수입니다. 함수 만드실 때 에러가 발생 하신다면 p2,p5간의 pixels의
    자료형이 문제가 될 수 있습니다. 이 함수로 바꾸어 테스트 하시기를 권장합니다.
*/

int image_write(char* fileNm, image_p2* img);
/*
    image로 선언되어 있는 매직넘버가 p2인 구조체를 파일로 바꾸어 저장하는 함수 입니다.
 */

void close_image_p2(image_p2* img);
/*
    코드를 만들던 중 image_reset, read_image_pgm_p2를 사용했다면 마지막에 할당한 모든 메모리 영역을
    닫아주어야 합니다. 이 함수는 할당한 영역을 없애주기 위한 함수입니다.
*/

void close_image_p5(image_p5* img);
/*
    코드를 만들던 중 read_image_pgm_p5를 사용했다면 마지막에 할당한 모든 메모리 영역을
    닫아주어야 합니다. 이 함수는 할당한 영역을 없애주기 위한 함수입니다.
*/

void average_filter(image_p2* out, image_p2* in, int filter_row_size);
/*
평균값 필터랍니다. 합성곱 적용되는지 확인하기 위한 함수였습니다.
*/
void Gaussian_filter(image_p2* out, image_p2* in, float sigma, int filter_size);
/*
Sigma값과 Filter_Size를 매개변수로 받고 그에 따른 수정된 가우시안 분포를 형성한 후,
원본 이미지에 가우시안 필터를 합성곱한 결과물을 출력하는 함수입니다.
*/

void gradient(image_p2* out_dir, image_p2* out_mag, image_p2* in, int filter_type);
/*
이후 여러 함수의 동작을 위한 입력을 생성하는 Gradient 함수 입니다.
임의의 위치에 대해 미분 마스크를 통과 시킨 후 추가적인 처리를 통해 크기와 각도 성분을 반환합니다.
*/

void NonMax(image_p2* out_dir, image_p2* in_dir, image_p2* in_mag, int size);
/*
Gradient 함수의 크기 연산 결과와 방향 연산 결과를 입력으로 받고, 임의의 셀에 대한 크기를
그 셀에서의 방향값을 고려해 인접 셀과 크기를 비교하고, 해당 셀이 제일 크지 않다면 0,
제일 크다면 크기값을 그대로 두는 함수이고, 반환값은 수정된 크기값과 수정되지 않은 방향값입니다.
해당 함수는 직선후보군을 한번 걸러내는걸 목적으로 합니다.
*/

void DoubleT(image_p2* out_dir, image_p2* in_dir, int HighT, int LowT);
/*
Nom-maximum 함수의 결과를 입력으로 받고, 임의의 셀에 대해서 그 크기가 매개변수로 설정한
High Threshold Value, Low Threshold Value와의 상대적인 크기에 의해
해당 셀의 크기를 죽일지 ( 0으로 만들지), 그대로 살릴지 ( 기존값 유지 ), 8비트 그레이스케일의 최대치로 설정할 지 ( 흰색으로써 255 )
결정해주는 함수가 됩니다. 이는 곧 셀을 죽이거나, 약 edge로 판단하거나, 강 edge로 판단하는 함수가 됩니다.
*/

void Hysterisis(image_p2* out_dir, image_p2* in_dir, image_p2* in_mag, int HighT, int LowT);
/*
앞서 크기를 0, 약 edge, 강 edge로 설정했는데, Hysterisis 함수에선 약 edge와 강 edge의 연결관계를 통해
약 edge 셀의 데이터를 처리하는 함수입니다.
입력받은 크기 정보에 대해서 기준 셀이 되는 Anchor를 설정하고, 해당 셀을 둘러싸는 8방향의 셀에 대한
정보를 취득하여 Anchor 셀의 각도 성분이 주어졌을 때 해당 방향에 알맞는 비교군을 선택하고
그 크기가 255, 흰색인지를 판단하여 연결해주는 작업입니다.
해당 함수는 약 edge로 구분된 셀들에 대해 강 edge와의 연결성이 있다면 이를 edge로 편입시키고
아니면 0으로 초기화하는걸 목적으로 합니다.
*/

void homograpy_transform(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4);

void backward_mapping(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4);

void homograpy_transform_ver2(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4);

void backward_mapping_ver2(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4);








float my_pi = (float)3.141592; // 상수 설정

image_p2* pconvert_p5_to_p2(image_p5* img) {
    image_p2* img_p2;
    img_p2 = (image_p2*)malloc(sizeof(image_p2));
    if (img_p2 == NULL) {
        return NULL;
    }

    img_p2->M = img->M;
    img_p2->N = img->N;

    img_p2->col_size = img->col_size;
    img_p2->row_size = img->row_size;

    img_p2->scale = img->scale;


    // <-- 메모리 할당
    img_p2->pixels = (int*)malloc(img_p2->row_size * img_p2->col_size * sizeof(int));

    if (img_p2->pixels == NULL) {//메모리 할당 실패시 0을 반환
        return NULL;
    }

    for (int i = 0; i < img->col_size * img->row_size; i++) {//할당한 메모리 초기화
        img_p2->pixels[i] = (int)img->pixels[i];
    }

    return img_p2;
}

image_pbm* read_image_pbm(char* fileNm) {
    image_pbm* img;
    img = (image_pbm*)malloc(sizeof(image_pbm));
    if (img == NULL) {
        return NULL;
    }

    FILE* fp = fopen(fileNm, "r");
    fscanf(fp, "%c %c", &img->M, &img->N);   // 매직넘버 읽기
    fscanf(fp, "%d %d", &img->row_size, &img->col_size);   // 가로, 세로 읽기

    // <-- 메모리 할당
    img->pixels = (unsigned char*)malloc(img->row_size * img->col_size * sizeof(unsigned char*));

    if (img->pixels == NULL) {//메모리 할당 실패시 0을 반환
        return NULL;
    }

    for (int i = 0; i < img->col_size * img->row_size; i++) {//할당한 메모리 초기화
        img->pixels[i] = (unsigned char)0;
    }

    // <-- pbm 파일로부터 픽셀값을 읽어서 할당한 메모리에 load
    int tmp = 0;
    for (int c = 0; c < img->col_size; c++) {
        for (int r = 0; r < img->row_size; r++) {
            fscanf(fp, "%d", &tmp);
            img->pixels[r + img->row_size * c] = (unsigned char)tmp;
        }
    }
    // -->

    fclose(fp); // 더 이상 사용하지 않는 파일을 닫아 줌

    return img;
}

image_p2* image_reset(char M, char N, int scale, int row_size, int col_size) {
    image_p2* img;
    img = (image_p2*)malloc(sizeof(image_p2));
    if (img == NULL) {
        return NULL;
    }

    img->M = M;
    img->N = N;

    img->col_size = col_size;
    img->row_size = row_size;

    img->scale = 255;


    // <-- 메모리 할당
    img->pixels = (int*)malloc(img->row_size * img->col_size * sizeof(int));

    if (img->pixels == NULL) {//메모리 할당 실패시 0을 반환
        return NULL;
    }

    for (int i = 0; i < img->col_size * img->row_size; i++) {//할당한 메모리 초기화
        img->pixels[i] = (int)0;
    }

    return img;
}

image_p5* read_image_pgm_p5(char* fileNm) {
    image_p5* img;
    img = (image_p5*)malloc(sizeof(image_p5));
    if (img == NULL) {
        return NULL;
    }

    int scale;
    FILE* fp = fopen(fileNm, "rb");
    fscanf(fp, "%c %c", &img->M, &img->N);   // 매직넘버 읽기
    fscanf(fp, "%d %d", &img->row_size, &img->col_size);   // 가로, 세로 읽기
    fscanf(fp, "%d ", &img->scale);

    // <-- 메모리 할당
    img->pixels = (unsigned char*)malloc(img->row_size * img->col_size * sizeof(unsigned char));

    if (img->pixels == NULL) {//메모리 할당 실패시 0을 반환
        return NULL;
    }

    for (int i = 0; i < img->col_size * img->row_size; i++) {//할당한 메모리 초기화
        img->pixels[i] = (unsigned char)0;
    }

    // <-- pbm 파일로부터 픽셀값을 읽어서 할당한 메모리에 load
    int tmp = 0;
    for (int c = 0; c < img->col_size; c++) {
        for (int r = 0; r < img->row_size; r++) {
            fread(&img->pixels[r + c * img->row_size], sizeof(unsigned char), 1, fp);
        }
    }
    // -->

    fclose(fp); // 더 이상 사용하지 않는 파일을 닫아 줌

    return img;
}

image_p2* read_image_pgm_p2(char* fileNm) {
    image_p2* img;
    img = (image_p2*)malloc(sizeof(image_p2));
    if (img == NULL) {
        return NULL;
    }

    int scale;
    FILE* fp = fopen(fileNm, "rb");
    fscanf(fp, "%c %c", &img->M, &img->N);   // 매직넘버 읽기
    fscanf(fp, "%d %d", &img->row_size, &img->col_size);   // 가로, 세로 읽기
    fscanf(fp, "%d ", &img->scale);

    // <-- 메모리 할당
    img->pixels = (int*)malloc(img->row_size * img->col_size * sizeof(int));

    if (img->pixels == NULL) {//메모리 할당 실패시 0을 반환
        return NULL;
    }

    for (int i = 0; i < img->col_size * img->row_size; i++) {//할당한 메모리 초기화
        img->pixels[i] = (int)0;
    }

    // <-- pbm 파일로부터 픽셀값을 읽어서 할당한 메모리에 load
    int tmp = 0;
    for (int c = 0; c < img->col_size; c++) {
        for (int r = 0; r < img->row_size; r++) {
            fscanf(fp, "%d ", &img->pixels[r + c * img->row_size]);
        }//&img->pixels[r + c * img->row_size]
    }
    // -->

    fclose(fp); // 더 이상 사용하지 않는 파일을 닫아 줌

    return img;
}

int image_write(char* fileNm, image_p2* img)
{
    FILE* fp;

    fp = fopen(fileNm, "w");
    if (fp == NULL) {
        fprintf(stderr, "파일 생성에 실패하였습니다.\n");
        return 0;
    }

    fprintf(fp, "%c%c\n", 'P', '2');
    fprintf(fp, "%d %d\n", img->row_size, img->col_size);
    fprintf(fp, "%d\n", 255);

    int tmp;								// int type임에 유의

    for (int c = 0; c < img->col_size; c++) {
        for (int r = 0; r < img->row_size; r++) {
            tmp = img->pixels[r + c * img->row_size];

            fprintf(fp, "%d ", tmp);
        }
    }

    fclose(fp);

    return 1;
}

void close_image_p2(image_p2* img) {

    free(img->pixels);

    free(img);

    return;
}

void close_image_p5(image_p5* img) {

    free(img->pixels);

    free(img);

    return;
}

void average_filter(image_p2* out, image_p2* in, int filter_row_size) {
    float* filter = (float*)malloc(sizeof(float) * filter_row_size * filter_row_size);

    for (int i = 0; i < filter_row_size * filter_row_size; i++) {
        filter[i] = (float)1 / (filter_row_size * filter_row_size);
    }

    image_p2* img = image_reset(in->M, in->N, in->scale, in->row_size - filter_row_size + 1, in->col_size - filter_row_size + 1);

    conv(img->pixels, in->pixels, filter, in->row_size, in->col_size, filter_row_size);

    *out = *img;

    free(filter);
    return;
}

void Gaussian_filter(image_p2* out, image_p2* in, float sigma, int filter_size) {
    float* filter = (float*)malloc(sizeof(float) * filter_size * filter_size);

    int a, b;
    int xVal, yVal;
    int sig = sigma;
    int f_size = filter_size;

    float sum, offset;
    sum = 0;

    float k1 = (float)sigma * (float)sigma * 2;
    float k2 = (float)1.0 / ((float)k1 * (float)my_pi);

    for (int i = 0; i < filter_size * filter_size; i++)
    {
        filter[i] = 0;
    }

OG_Gaussian_row: for (xVal = 0; xVal < filter_size; xVal++)
{
OG_Gaussian_col: for (yVal = 0; yVal < filter_size; yVal++)
{
    float xInput = (float)xVal - (filter_size - 1) / 2;
    float yInput = (float)yVal - (filter_size - 1) / 2;
    float tmp = k2 * expf(-(xInput * xInput + yInput * yInput) / k1);
    filter[xVal * filter_size + yVal] = tmp;
    //기본 가우시안 커널을 행렬의 위치에 맞게 저장함.
}
}


Sum_row: for (a = 0; a < f_size; a++)
{
Sum_col: for (b = 0; b < f_size; b++)
{
    sum += filter[(a * f_size) + b];
    // 전체 배열 합 구하기
}
}

offset = 1 - sum;
// 오차 성분 보정을 위한 오프셋 변수 설정
offset = offset / (filter_size * filter_size);
// 오프셋을 전영역 동등하게 보정하기 위한 상수 재계산

for (a = 0; a < f_size; a++)
{
    for (b = 0; b < f_size; b++)
    {
        filter[(a * f_size) + b] += offset;
        // 기존 성분에 오프셋 반영
    }
}

image_p2* img = image_reset(in->M, in->N, in->scale, in->row_size - filter_size + 1, in->col_size - filter_size + 1);

conv(img->pixels, in->pixels, filter, in->row_size, in->col_size, filter_size);

*out = *img;
free(filter);
free(img);
return;

}

void gradient(image_p2* out_dir, image_p2* out_mag, image_p2* in, int filter_type) {
    float filter_x[9];
    float filter_y[9];


    if (filter_type == 0) {//프리윗 필터
        filter_x[0] = -1;
        filter_x[1] = 0;
        filter_x[2] = 1;
        filter_x[3] = -1;
        filter_x[4] = 0;
        filter_x[5] = 1;
        filter_x[6] = -1;
        filter_x[7] = 0;
        filter_x[8] = 1;

        filter_y[0] = -1;
        filter_y[1] = -1;
        filter_y[2] = -1;
        filter_y[3] = 0;
        filter_y[4] = 0;
        filter_y[5] = 0;
        filter_y[6] = 1;
        filter_y[7] = 1;
        filter_y[8] = 1;
    }

    else if (filter_type == 1) {//소벨 필터
        filter_x[0] = -1;
        filter_x[1] = 0;
        filter_x[2] = 1;
        filter_x[3] = -2;
        filter_x[4] = 0;
        filter_x[5] = 2;
        filter_x[6] = -1;
        filter_x[7] = 0;
        filter_x[8] = 1;

        filter_y[0] = -1;
        filter_y[1] = -2;
        filter_y[2] = -1;
        filter_y[3] = 0;
        filter_y[4] = 0;
        filter_y[5] = 0;
        filter_y[6] = 1;
        filter_y[7] = 2;
        filter_y[8] = 1;
    }

    else if (filter_type == 2) {//샤르 필터
        filter_x[0] = -3;
        filter_x[1] = 0;
        filter_x[2] = 3;
        filter_x[3] = -10;
        filter_x[4] = 0;
        filter_x[5] = 10;
        filter_x[6] = -3;
        filter_x[7] = 0;
        filter_x[8] = 3;

        filter_y[0] = -3;
        filter_y[1] = -10;
        filter_y[2] = -3;
        filter_y[3] = 0;
        filter_y[4] = 0;
        filter_y[5] = 0;
        filter_y[6] = 3;
        filter_y[7] = 10;
        filter_y[8] = 3;
    }

    else {
        filter_x[0] = -1;
        filter_x[1] = 0;
        filter_x[2] = 1;
        filter_x[3] = -1;
        filter_x[4] = 0;
        filter_x[5] = 1;
        filter_x[6] = -1;
        filter_x[7] = 0;
        filter_x[8] = 1;

        filter_y[0] = -1;
        filter_y[1] = -1;
        filter_y[2] = -1;
        filter_y[3] = 0;
        filter_y[4] = 0;
        filter_y[5] = 0;
        filter_y[6] = 1;
        filter_y[7] = 1;
        filter_y[8] = 1;
    }

    image_p2* img_x = image_reset(in->M, in->N, in->scale, in->row_size - 2, in->col_size - 2);
    image_p2* img_y = image_reset(in->M, in->N, in->scale, in->row_size - 2, in->col_size - 2);

    conv(img_x->pixels, in->pixels, filter_x, in->row_size, in->col_size, 3);
    conv(img_y->pixels, in->pixels, filter_y, in->row_size, in->col_size, 3);

    float tmp;

    for (int i = 0; i < img_x->row_size * img_x->col_size; i++) {

        out_dir->pixels[i] = sqrt(img_x->pixels[i] * img_x->pixels[i] + img_y->pixels[i] * img_y->pixels[i]);

        tmp = 0;
        if (img_x->pixels[i] == 0) {
            out_mag->pixels[i] = 90;
        }

        else {
            tmp = atanf((float)(img_y->pixels[i] / img_x->pixels[i]));

            if (tmp < 0.414213562 && tmp > -0.414213562) {
                out_mag->pixels[i] = 0;
            }

            else if (tmp <= 2.414213562 && tmp >= 0.414213562) {
                out_mag->pixels[i] = 45;
            }

            else if (tmp > 2.414213562 || tmp < -2.414213562) {
                out_mag->pixels[i] = 90;
            }

            else if (tmp < -0.414213562 && tmp > -2.414213562) {
                out_mag->pixels[i] = 135;
            }


        }
    }
    out_dir->row_size = img_x->row_size;
    out_dir->col_size = img_x->col_size;
    out_mag->row_size = img_x->row_size;
    out_mag->col_size = img_x->col_size;

    free(img_x);
    free(img_y);
    return;
}

void NonMax(image_p2* out_dir, image_p2* in_dir, image_p2* in_mag, int size) {
    for (int col = size; col < in_dir->col_size - size; col++) {
        for (int row = size; row < in_dir->row_size - size; row++) {
            out_dir->pixels[col * in_dir->row_size + row] = in_dir->pixels[col * in_dir->row_size + row];

            if (in_mag->pixels[col * in_dir->col_size + row] == 0) {// 0
                for (int i = -1 * size; i <= size; i++) {
                    if (in_dir->pixels[(col + i) * in_dir->row_size + (row)] >= in_dir->pixels[col * in_dir->row_size + row] && (i != 0)) {
                        out_dir->pixels[col * in_dir->row_size + row] = 0;
                        i = size + 1;
                    }
                }
            }

            else if (in_mag->pixels[col * in_dir->col_size + row] == 45) {//45
                for (int i = -1 * size; i <= size; i++) {
                    if (in_dir->pixels[(col + i) * in_dir->row_size + (row - i)] >= in_dir->pixels[col * in_dir->row_size + row] && (i != 0)) {
                        out_dir->pixels[col * in_dir->row_size + row] = 0;
                        i = size + 1;
                    }
                }
            }

            else if (in_mag->pixels[col * in_dir->col_size + row] == 90) {//90
                for (int i = -1 * size; i <= size; i++) {
                    if (in_dir->pixels[(col + i) * in_dir->row_size + (row + i)] >= in_dir->pixels[col * in_dir->row_size + row] && (i != 0)) {
                        out_dir->pixels[col * in_dir->row_size + row] = 0;
                        i = size + 1;
                    }
                }
            }

            else {//135
                for (int i = -1 * size; i <= size; i++) {
                    if (in_dir->pixels[(col)*in_dir->row_size + (row + i)] >= in_dir->pixels[col * in_dir->row_size + row] && (i != 0)) {
                        out_dir->pixels[col * in_dir->row_size + row] = 0;
                        i = size + 1;
                    }
                }
            }

        }
    }

    out_dir->col_size = in_dir->col_size;
    out_dir->row_size = in_dir->row_size;

    return;
}

void DoubleT(image_p2* out_dir, image_p2* in_dir, int HighT, int LowT) {

    for (int i = 0; i < in_dir->row_size * in_dir->col_size; i++) {

        if (in_dir->pixels[i] > HighT) {
            out_dir->pixels[i] = 255;
        }

        else if (in_dir->pixels[i] > LowT && in_dir->pixels[i] <= HighT) {
            out_dir->pixels[i] = in_dir->pixels[i];
        }

        else {
            out_dir->pixels[i] = 0;
        }
    }

    out_dir->col_size = in_dir->col_size;
    out_dir->row_size = in_dir->row_size;

    return;
}

void Hysterisis(image_p2* out_dir, image_p2* in_dir, image_p2* in_mag, int HighT, int LowT) {
    Queue* row;//x좌표
    Queue* col;//y좌표
    Queue* pixels;//데이터
    
    row = CreateQueue();
    col = CreateQueue();
    pixels = CreateQueue();

    //약엣지 검출, 초기화
    for (int col_size = 0; col_size < in_dir->col_size; col_size++) {
        for (int row_size = 0; row_size < in_dir->row_size; row_size++) {
            out_dir->pixels[row_size + col_size * in_dir->row_size] = in_dir->pixels[row_size + col_size * in_dir->row_size];

            if ((in_dir->pixels[row_size + col_size * in_dir->row_size] <= HighT) && (in_dir->pixels[row_size + col_size * in_dir->row_size] >= LowT)) {
                EnQueue(row, row_size);
                EnQueue(col, col_size);
                EnQueue(pixels, in_dir->pixels[col_size * in_dir->row_size + row_size]);
            }
            
        }
    }

    int tmp;
    int r;
    int c;
    int p;
    int flag_in;
    int flag;

    while (1) {
        flag = 0;
        tmp = CountQueue(pixels);
        if (tmp == 0) break;

        for (int i = 0; i < tmp; i++) {
            r = DeQueue(row);
            c = DeQueue(col);
            p = DeQueue(pixels);


            flag_in = 0;

            for (int col_size = 0; col_size < 3; col_size++) {
                for (int row_size = 0; row_size < 3; row_size++) {
                    // !((col_size == 1) && (row_size == 1)) && 
                    if ((in_mag->pixels[r + c * in_dir->row_size] == in_mag->pixels[(row_size + r - 1) + (col_size + c - 1) * in_dir->row_size]) && (out_dir->pixels[(row_size + r - 1) + (col_size + c - 1) * in_dir->row_size] > HighT)) {
                        out_dir->pixels[r + c * in_dir->row_size] = 255;
                        flag_in = 1;
                        flag = 1;
                    }
                }
            }

            if (flag_in == 0) {
                EnQueue(row, r);
                EnQueue(col, c);
                EnQueue(pixels, p);
            }
        }

        if (flag == 0) {
            break;
        }
    }

    tmp = CountQueue(pixels);

    for (int i = 0; i < tmp; i++) {
        r = DeQueue(row);
        c = DeQueue(col);
        p = DeQueue(pixels);

        out_dir->pixels[r + c * in_dir->row_size] = 0;
    }

    DestroyQueue(row);
    DestroyQueue(col);
    DestroyQueue(pixels);

    out_dir->col_size = in_dir->col_size;
    out_dir->row_size = in_dir->row_size;

    return;
}

void homograpy_transform(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4) {
    float* hmatrix = homomat(x1, x2, x3, x4, y1, y2, y3, y4);
    int x_size_min = in->row_size;
    int x_size_max = 0;
    int y_size_min = in->col_size;
    int y_size_max = 0;

    out->col_size = y3.y - y1.y;
    out->row_size = y2.x - y1.x;

    if (x1.x < x_size_min) x_size_min = x1.x;
    if (x2.x < x_size_min) x_size_min = x2.x;
    if (x3.x < x_size_min) x_size_min = x3.x;
    if (x4.x < x_size_min) x_size_min = x4.x;

    if (x1.x > x_size_max) x_size_max = x1.x;
    if (x2.x > x_size_max) x_size_max = x2.x;
    if (x3.x > x_size_max) x_size_max = x3.x;
    if (x4.x > x_size_max) x_size_max = x4.x;

    if (x1.y < y_size_min) y_size_min = x1.y;
    if (x2.y < y_size_min) y_size_min = x2.y;
    if (x3.y < y_size_min) y_size_min = x3.y;
    if (x4.y < y_size_min) y_size_min = x4.y;

    if (x1.y > y_size_max) y_size_max = x1.y;
    if (x2.y > y_size_max) y_size_max = x2.y;
    if (x3.y > y_size_max) y_size_max = x3.y;
    if (x4.y > y_size_max) y_size_max = x4.y;

    int* tem;

    for (int y = y_size_min; y <= y_size_max; y++) {
        for (int x = x_size_min; x <= x_size_max; x++) {
            tem = mmult(hmatrix, x, y);
            if ((tem[0] >= 0 && tem[0] < out->row_size) && (tem[1] >= 0 && tem[1] < out->col_size)) {
                if (out->pixels[tem[1] * out->row_size + tem[0]] == 0) {
                    out->pixels[tem[1] * out->row_size + tem[0]] = in->pixels[y * in->row_size + x];
                }

                else {
                    out->pixels[tem[1] * out->row_size + tem[0]] = (int)((float)in->pixels[y * in->row_size + x] + (float)out->pixels[tem[1] * out->row_size + tem[0]]) / 2.0;
                }
            }
        }
    }

    return;

}

void backward_mapping(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4) {
    float* hmatrix = homomat(y1, y2, y3, y4, x1, x2, x3, x4);
    int x_size_min = y1.x;
    int x_size_max = y4.x;
    int y_size_min = y1.y;
    int y_size_max = y4.y;

    out->col_size = y3.y;
    out->row_size = y2.x;

    int* tem;

    for (int y = y_size_min; y <= y_size_max; y++) {
        for (int x = x_size_min; x <= x_size_max; x++) {
            tem = mmult(hmatrix, x, y);
            
            out->pixels[y * out->row_size + x] = in->pixels[tem[1] * in->row_size + tem[0]];
        }
    }

    return;

}

void homograpy_transform_ver2(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4) {
    float slope1, slope2;
    int fix_x3, fix_x4;

    slope1 = ((float)x3.y - (float)x1.y) / ((float)x3.x - (float)x1.x);
    slope2 = ((float)x2.y - (float)x4.y) / ((float)x2.x - (float)x4.x);


    fix_x3 = (int)(((1.0) / (slope1)) * ((float)in->col_size - (float)x1.y) + (float)x1.x);
    fix_x4 = (int)(((1.0) / (slope2)) * ((float)in->col_size - (float)x2.y) + (float)x2.x);

    x3.x = fix_x3;
    x4.x = fix_x4;

    x3.y = in->col_size;
    x4.y = in->col_size;


    float* hmatrix = homomat(x1, x2, x3, x4, y1, y2, y3, y4);
    int x_size_min = in->row_size;
    int x_size_max = 0;
    int y_size_min = in->col_size;
    int y_size_max = 0;

    out->col_size = y3.y - y1.y;
    out->row_size = y2.x - y1.x;

    if (x1.x < x_size_min) x_size_min = x1.x;
    if (x2.x < x_size_min) x_size_min = x2.x;
    if (x3.x < x_size_min) x_size_min = x3.x;
    if (x4.x < x_size_min) x_size_min = x4.x;

    if (x1.x > x_size_max) x_size_max = x1.x;
    if (x2.x > x_size_max) x_size_max = x2.x;
    if (x3.x > x_size_max) x_size_max = x3.x;
    if (x4.x > x_size_max) x_size_max = x4.x;

    if (x1.y < y_size_min) y_size_min = x1.y;
    if (x2.y < y_size_min) y_size_min = x2.y;
    if (x3.y < y_size_min) y_size_min = x3.y;
    if (x4.y < y_size_min) y_size_min = x4.y;

    if (x1.y > y_size_max) y_size_max = x1.y;
    if (x2.y > y_size_max) y_size_max = x2.y;
    if (x3.y > y_size_max) y_size_max = x3.y;
    if (x4.y > y_size_max) y_size_max = x4.y;

    int* tem;

    for (int y = y_size_min; y <= y_size_max; y++) {
        for (int x = x_size_min; x <= x_size_max; x++) {
            if ((x >= 0) && (x < in->row_size) && (y >= 0) && (y < in->col_size)) {
                tem = mmult(hmatrix, x, y);
                if ((tem[0] >= 0 && tem[0] < out->row_size) && (tem[1] >= 0 && tem[1] < out->col_size)) {
                    if (out->pixels[tem[1] * out->row_size + tem[0]] == 0) {
                        out->pixels[tem[1] * out->row_size + tem[0]] = in->pixels[y * in->row_size + x];
                    }

                    else {
                        out->pixels[tem[1] * out->row_size + tem[0]] = (int)((float)in->pixels[y * in->row_size + x] + (float)out->pixels[tem[1] * out->row_size + tem[0]]) / 2.0;
                    }
                }
            }
        }
    }

    return;

}

void backward_mapping_ver2(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4) {

    float slope1, slope2;
    int fix_x3, fix_x4;

    slope1 = ((float)x3.y - (float)x1.y) / ((float)x3.x - (float)x1.x);
    slope2 = ((float)x2.y - (float)x4.y) / ((float)x2.x - (float)x4.x);


    fix_x3 = (int)(((1.0) / (slope1)) * ((float)in->col_size - (float)x1.y) + (float)x1.x);
    fix_x4 = (int)(((1.0) / (slope2)) * ((float)in->col_size - (float)x2.y) + (float)x2.x);

    x3.x = fix_x3;
    x4.x = fix_x4;

    x3.y = in->col_size;
    x4.y = in->col_size;


    float* hmatrix = homomat(y1, y2, y3, y4, x1, x2, x3, x4);
    int x_size_min = y1.x;
    int x_size_max = y4.x;
    int y_size_min = y1.y;
    int y_size_max = y4.y;

    out->col_size = y3.y;
    out->row_size = y2.x;

    int* tem;

    for (int y = y_size_min; y <= y_size_max; y++) {
        for (int x = x_size_min; x <= x_size_max; x++) {
            tem = mmult(hmatrix, x, y);


            if ((tem[0] > 0) && (tem[0] < in->row_size) && (tem[1] > 0) && (tem[1] < in->col_size)) {
                out->pixels[y * out->row_size + x] = in->pixels[tem[1] * in->row_size + tem[0]];
            }

        }
    }

    return;
}