#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


//typedef int TYPE;// 여기서 data type을 설정하세요.

typedef struct {
    char M, N;//매직넘버 
    int row_size;//넓이
    int col_size;//높이
    int scale;
    unsigned char* pixels;//픽셀 데이터
}image;

typedef struct {
    char M, N;//매직넘버 
    int row_size;//넓이
    int col_size;//높이
    unsigned char* pixels;//픽셀 데이터
}image_pbm;


image_pbm* read_image_pbm(char* fileNm);
image* image_reset(char M, char N, int row_size, int col_size);
image* read_image_pgm(char* fileNm);
image* read_image_pgm_p2(char* fileNm);
int image_write(char* fileNm, image* img);
void close_image(image* img);
void pbm_test(image* img);
int test_image_light(char* fileNm, image* img);




image_pbm* read_image_pbm(char* fileNm) {
    image* img;
    img = (image*)malloc(sizeof(image));
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
    for (int c = 0; c < img->col_size ; c++) {
        for (int r = 0; r < img->row_size; r++) {
            fscanf(fp, "%d", &tmp);
            img->pixels[r + img->row_size * c] = (unsigned char)tmp;
        }
    }
    // -->

    fclose(fp); // 더 이상 사용하지 않는 파일을 닫아 줌

    return img;
}


image* image_reset(char M, char N, int row_size, int col_size) {
    image* img;
    img = (image*)malloc(sizeof(image));
    if (img == NULL) {
        return NULL;
    }

    img->M = M;
    img->N = N;

    img->col_size = col_size;
    img->row_size = row_size;
   

    // <-- 메모리 할당
    img->pixels = (unsigned char*)malloc(img->row_size * img->col_size * sizeof(unsigned char*));

    if (img->pixels == NULL) {//메모리 할당 실패시 0을 반환
        return NULL;
    }

    return img;
}

image* read_image_pgm(char* fileNm) {
    image* img;
    img = (image*)malloc(sizeof(image));
    if (img == NULL) {
        return NULL;
    }

    int scale;
    FILE* fp = fopen(fileNm, "rb");
    fscanf(fp, "%c %c", &img->M, &img->N);   // 매직넘버 읽기
    fscanf(fp, "%d %d", &img->row_size, &img->col_size);   // 가로, 세로 읽기
    fscanf(fp, "%d ", &img->scale);

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
            fread(&img->pixels[r + c * img->row_size], sizeof(unsigned char),1, fp);
        }
    }
    // -->

    fclose(fp); // 더 이상 사용하지 않는 파일을 닫아 줌

    return img;
}

image* read_image_pgm_p2(char* fileNm) {
    image* img;
    img = (image*)malloc(sizeof(image));
    if (img == NULL) {
        return NULL;
    }

    int scale;
    FILE* fp = fopen(fileNm, "rb");
    fscanf(fp, "%c %c", &img->M, &img->N);   // 매직넘버 읽기
    fscanf(fp, "%d %d", &img->row_size, &img->col_size);   // 가로, 세로 읽기
    fscanf(fp, "%d ", &img->scale);

    // <-- 메모리 할당
    img->pixels = (unsigned char*)malloc(img->row_size * img->col_size * sizeof(unsigned char*));

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

int image_write(char* fileNm, image* img)
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

void close_image(image* img) {
   
    free(img->pixels);

    free(img);

    return;
}

void pbm_test(image* img) {
    for (int c = 0; c < img->col_size; c++) {
        for (int r = 0; r < img->row_size; r++) {
            if (img->pixels[r + img->row_size * c] == 1) {
                printf("■");
            }
            else {
                printf("□");
            }
        }

        printf("\n");
    }

    return;
}


int test_image_light(char* fileNm, image* img)
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
            tmp = img->pixels[r + c * img->row_size] + 50;	// 픽셀값을 밝게 변화를 줌
            //tmp = 0;
            if (tmp > 255) {					// overflow 방지
                tmp = 255;
            }

            fprintf(fp, "%d ", tmp);
        }
    }

    fclose(fp);

    return 1;
}