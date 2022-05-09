#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


//typedef int TYPE;// ���⼭ data type�� �����ϼ���.

typedef struct {
    char M, N;//�����ѹ� 
    int row_size;//����
    int col_size;//����
    int scale;
    unsigned char* pixels;//�ȼ� ������
}image;

typedef struct {
    char M, N;//�����ѹ� 
    int row_size;//����
    int col_size;//����
    unsigned char* pixels;//�ȼ� ������
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
    fscanf(fp, "%c %c", &img->M, &img->N);   // �����ѹ� �б�
    fscanf(fp, "%d %d", &img->row_size, &img->col_size);   // ����, ���� �б�

    // <-- �޸� �Ҵ�
    img->pixels = (unsigned char*)malloc(img->row_size * img->col_size * sizeof(unsigned char*));

    if (img->pixels == NULL) {//�޸� �Ҵ� ���н� 0�� ��ȯ
        return NULL;
    }

    for (int i = 0; i < img->col_size * img->row_size; i++) {//�Ҵ��� �޸� �ʱ�ȭ
        img->pixels[i] = (unsigned char)0;
    }

    // <-- pbm ���Ϸκ��� �ȼ����� �о �Ҵ��� �޸𸮿� load
    int tmp = 0;
    for (int c = 0; c < img->col_size ; c++) {
        for (int r = 0; r < img->row_size; r++) {
            fscanf(fp, "%d", &tmp);
            img->pixels[r + img->row_size * c] = (unsigned char)tmp;
        }
    }
    // -->

    fclose(fp); // �� �̻� ������� �ʴ� ������ �ݾ� ��

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
   

    // <-- �޸� �Ҵ�
    img->pixels = (unsigned char*)malloc(img->row_size * img->col_size * sizeof(unsigned char*));

    if (img->pixels == NULL) {//�޸� �Ҵ� ���н� 0�� ��ȯ
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
    fscanf(fp, "%c %c", &img->M, &img->N);   // �����ѹ� �б�
    fscanf(fp, "%d %d", &img->row_size, &img->col_size);   // ����, ���� �б�
    fscanf(fp, "%d ", &img->scale);

    // <-- �޸� �Ҵ�
    img->pixels = (unsigned char*)malloc(img->row_size * img->col_size * sizeof(unsigned char*));

    if (img->pixels == NULL) {//�޸� �Ҵ� ���н� 0�� ��ȯ
        return NULL;
    }

    for (int i = 0; i < img->col_size * img->row_size; i++) {//�Ҵ��� �޸� �ʱ�ȭ
        img->pixels[i] = (unsigned char)0;
    }

    // <-- pbm ���Ϸκ��� �ȼ����� �о �Ҵ��� �޸𸮿� load
    int tmp = 0;
    for (int c = 0; c < img->col_size; c++) {
        for (int r = 0; r < img->row_size; r++) {
            fread(&img->pixels[r + c * img->row_size], sizeof(unsigned char),1, fp);
        }
    }
    // -->

    fclose(fp); // �� �̻� ������� �ʴ� ������ �ݾ� ��

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
    fscanf(fp, "%c %c", &img->M, &img->N);   // �����ѹ� �б�
    fscanf(fp, "%d %d", &img->row_size, &img->col_size);   // ����, ���� �б�
    fscanf(fp, "%d ", &img->scale);

    // <-- �޸� �Ҵ�
    img->pixels = (unsigned char*)malloc(img->row_size * img->col_size * sizeof(unsigned char*));

    if (img->pixels == NULL) {//�޸� �Ҵ� ���н� 0�� ��ȯ
        return NULL;
    }

    for (int i = 0; i < img->col_size * img->row_size; i++) {//�Ҵ��� �޸� �ʱ�ȭ
        img->pixels[i] = (int)0;
    }

    // <-- pbm ���Ϸκ��� �ȼ����� �о �Ҵ��� �޸𸮿� load
    int tmp = 0;
    for (int c = 0; c < img->col_size; c++) {
        for (int r = 0; r < img->row_size; r++) {
            fscanf(fp, "%d ", &img->pixels[r + c * img->row_size]);
        }//&img->pixels[r + c * img->row_size]
    }
    // -->

    fclose(fp); // �� �̻� ������� �ʴ� ������ �ݾ� ��

    return img;
}

int image_write(char* fileNm, image* img)
{
    FILE* fp;

    fp = fopen(fileNm, "w");
    if (fp == NULL) {
        fprintf(stderr, "���� ������ �����Ͽ����ϴ�.\n");
        return 0;
    }

    fprintf(fp, "%c%c\n", 'P', '2');
    fprintf(fp, "%d %d\n", img->row_size, img->col_size);
    fprintf(fp, "%d\n", 255);

    int tmp;								// int type�ӿ� ����

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
                printf("��");
            }
            else {
                printf("��");
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
        fprintf(stderr, "���� ������ �����Ͽ����ϴ�.\n");
        return 0;
    }

    fprintf(fp, "%c%c\n", 'P', '2');
    fprintf(fp, "%d %d\n", img->row_size, img->col_size);
    fprintf(fp, "%d\n", 255);

    int tmp;								// int type�ӿ� ����

    for (int c = 0; c < img->col_size; c++) {
        for (int r = 0; r < img->row_size; r++) {
            tmp = img->pixels[r + c * img->row_size] + 50;	// �ȼ����� ��� ��ȭ�� ��
            //tmp = 0;
            if (tmp > 255) {					// overflow ����
                tmp = 255;
            }

            fprintf(fp, "%d ", tmp);
        }
    }

    fclose(fp);

    return 1;
}