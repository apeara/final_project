#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "convolution.h"

/*
    �̹��� ������ pgm������ ����մϴ�. pgm������ �б� ���ؼ��� �߰����� ���α׷��� �ʿ��մϴ�.
    ���� 'xnview'�� ����Ͽ� �н��ϴ�. �ٿ�ε�� https://www.xnview.com/en/xnviewmp/#downloads
    ���⼭ �����Ͻø� �˴ϴ�. ���Ϻ�ȯ�� ���⼭ �����մϴ�. �̹��� ȭ���� ��� ���� ä��
    ����->��������?��������? �� ������ ���������� pgm���� �ϸ� �˴ϴ�.
    ���α׷��� �ޱ� �������� ���� https://convertio.co/kr/ �ش� �¶��� ����Ʈ�� �̿��Ͻø�
    �̹��� �ڷ������� ��ȯ�Ͻ� �� �ֽ��ϴ�.



    �׸��� convolution.h�� ���� �ڷ����� float��, in/out data�� �ڷ����� int�� �����Ͽ��� �����
    �����Դϴ�. Ȥ�� �ٲپ �Լ��� ������ٸ� �̸��� �ٲپ� ��������� �����Ͽ� �������ּ���.


*/

typedef struct {
    char M, N;//�����ѹ� 
    int row_size;//����
    int col_size;//����
    int scale;
    unsigned char* pixels;//�ȼ� ������
}image_p5;//p5 pgm�����̸� �̰� ���� �˴ϴ�.

typedef struct {
    char M, N;//�����ѹ� 
    int row_size;//����
    int col_size;//����
    int scale;
    int* pixels;//�ȼ� ������
}image_p2; //p2 pgm������ �̰� ���� �˴ϴ�.

typedef struct {
    char M, N;//�����ѹ� 
    int row_size;//����
    int col_size;//����
    unsigned char* pixels;//�ȼ� ������
}image_pbm; //�̰Ŵ� pbm���� ����ü�Դϴ�. ����� �� ���� �̴ϴ�.

typedef struct {
    int row;//x��ǥ
    int col;//y��ǥ
    int pixels;
} pixel_data;

typedef struct {
    int x;
    int y;
}coordinate;

/*
    image_p5 : �����ѹ��� p5�� pgm������ �б����� ����ü
    image : �����ѹ��� p2�� pgm������ �б����� ����ü
    char* fileNm : �����̸�
    char M, char N : �����ѹ� ex)p2, p5
    int row_size, int col_size : �̹����� ����/���� ũ��
    int scale : gray ���� ��ܰ�� ǥ���� ��
*/

image_pbm* read_image_pbm(char* fileNm);
/*
    �̰Ŵ� pbm���� �д� ���Դϴ�. ����� �� ���� �̴ϴ�.
*/

image_p2* image_reset(char M, char N, int scale, int row_size, int col_size);
/*
    �̰��� image����ü�� �ʱ�ȭ �ϱ� ���� �Լ� �Դϴ�. pgm������ pixels data�� ������ ������ ������ pixels data�� ���� '0'����
    �ʱ�ȭ �Ͽ� ��ȯ�Ͽ� �ݴϴ�. �� ���� pgm������ Ư¡�� ��Ÿ���� �����ѹ�, ����/����ũ��, �������� �Է����� ������ �ʱ�ȭ
    �մϴ�.
*/

image_p5* read_image_pgm_p5(char* fileNm);
/*
    �� �Լ��� pgm���� �߿��� �����ѹ��� p5�� ����Ǿ� �ִ� �Լ��� ��ǥ�� ������ �Լ��Դϴ�. ó�� pgm���� ��ȯ�� ���Ͽ�����
    �����ѹ��� p5�� ����Ǿ� �ֱ⿡ �̰����� �о� ����� �մϴ�. �Ƹ� �׽�Ʈ �Ҷ��� ������ ����� �� �����̴ϴ�. �⺻������
    ó�� �ҷ��� ���� ����� ���̱� ������ ��������������� ��հ����Ϳ����� ���� �� �����ϴ�.
*/

image_p2* read_image_pgm_p2(char* fileNm);
/*
    �� �Լ��� pgm���� �߿��� �����ѹ��� p2�� ����Ǿ� �ִ� �Լ��� ��ǥ�� ������ �Լ��Դϴ�. ��հ� ���͸� ���� �̹��� �����ʹ�
    ���� �����ѹ��� p2�� �������� ����ǰ� ��������ϴ�. �׷��� �ѹ��̶� ������ ���� �̹��� ������ �� �Լ��� �о�鿩��
    �մϴ�.
*/

image_p2* pconvert_p5_to_p2(image_p5* img);
/*
    image_p5�ڷ����� image_p2�ڷ������� �ٲپ� ��ȯ���ִ� �Լ��Դϴ�. �Լ� ����� �� ������ �߻� �ϽŴٸ� p2,p5���� pixels��
    �ڷ����� ������ �� �� �ֽ��ϴ�. �� �Լ��� �ٲپ� �׽�Ʈ �Ͻñ⸦ �����մϴ�.
*/

int image_write(char* fileNm, image_p2* img);
/*
    image�� ����Ǿ� �ִ� �����ѹ��� p2�� ����ü�� ���Ϸ� �ٲپ� �����ϴ� �Լ� �Դϴ�.
 */

void close_image_p2(image_p2* img);
/*
    �ڵ带 ����� �� image_reset, read_image_pgm_p2�� ����ߴٸ� �������� �Ҵ��� ��� �޸� ������
    �ݾ��־�� �մϴ�. �� �Լ��� �Ҵ��� ������ �����ֱ� ���� �Լ��Դϴ�.
*/

void close_image_p5(image_p5* img);
/*
    �ڵ带 ����� �� read_image_pgm_p5�� ����ߴٸ� �������� �Ҵ��� ��� �޸� ������
    �ݾ��־�� �մϴ�. �� �Լ��� �Ҵ��� ������ �����ֱ� ���� �Լ��Դϴ�.
*/

void average_filter(image_p2* out, image_p2* in, int filter_row_size);
/*
��հ� ���Ͷ��ϴ�. �ռ��� ����Ǵ��� Ȯ���ϱ� ���� �Լ������ϴ�.
*/
void Gaussian_filter(image_p2* out, image_p2* in, float sigma, int filter_size);
/*
Sigma���� Filter_Size�� �Ű������� �ް� �׿� ���� ������ ����þ� ������ ������ ��,
���� �̹����� ����þ� ���͸� �ռ����� ������� ����ϴ� �Լ��Դϴ�.
*/

void gradient(image_p2* out_dir, image_p2* out_mag, image_p2* in, int filter_type);
/*
���� ���� �Լ��� ������ ���� �Է��� �����ϴ� Gradient �Լ� �Դϴ�.
������ ��ġ�� ���� �̺� ����ũ�� ��� ��Ų �� �߰����� ó���� ���� ũ��� ���� ������ ��ȯ�մϴ�.
*/

void NonMax(image_p2* out_dir, image_p2* in_dir, image_p2* in_mag, int size);
/*
Gradient �Լ��� ũ�� ���� ����� ���� ���� ����� �Է����� �ް�, ������ ���� ���� ũ�⸦
�� �������� ���Ⱚ�� ������ ���� ���� ũ�⸦ ���ϰ�, �ش� ���� ���� ũ�� �ʴٸ� 0,
���� ũ�ٸ� ũ�Ⱚ�� �״�� �δ� �Լ��̰�, ��ȯ���� ������ ũ�Ⱚ�� �������� ���� ���Ⱚ�Դϴ�.
�ش� �Լ��� �����ĺ����� �ѹ� �ɷ����°� �������� �մϴ�.
*/

void DoubleT(image_p2* out_dir, image_p2* in_dir, int HighT, int LowT);
/*
Nom-maximum �Լ��� ����� �Է����� �ް�, ������ ���� ���ؼ� �� ũ�Ⱑ �Ű������� ������
High Threshold Value, Low Threshold Value���� ������� ũ�⿡ ����
�ش� ���� ũ�⸦ ������ ( 0���� ������), �״�� �츱�� ( ������ ���� ), 8��Ʈ �׷��̽������� �ִ�ġ�� ������ �� ( ������ν� 255 )
�������ִ� �Լ��� �˴ϴ�. �̴� �� ���� ���̰ų�, �� edge�� �Ǵ��ϰų�, �� edge�� �Ǵ��ϴ� �Լ��� �˴ϴ�.
*/

void Hysterisis(image_p2* out_dir, image_p2* in_dir, image_p2* in_mag);
/*
�ռ� ũ�⸦ 0, �� edge, �� edge�� �����ߴµ�, Hysterisis �Լ����� �� edge�� �� edge�� ������踦 ����
�� edge ���� �����͸� ó���ϴ� �Լ��Դϴ�.
�Է¹��� ũ�� ������ ���ؼ� ���� ���� �Ǵ� Anchor�� �����ϰ�, �ش� ���� �ѷ��δ� 8������ ���� ����
������ ����Ͽ� Anchor ���� ���� ������ �־����� �� �ش� ���⿡ �˸´� �񱳱��� �����ϰ�
�� ũ�Ⱑ 255, ��������� �Ǵ��Ͽ� �������ִ� �۾��Դϴ�.
�ش� �Լ��� �� edge�� ���е� ���鿡 ���� �� edge���� ���Ἲ�� �ִٸ� �̸� edge�� ���Խ�Ű��
�ƴϸ� 0���� �ʱ�ȭ�ϴ°� �������� �մϴ�.
*/

float det(float* matrix, int size);
float* homograpy(coordinate x1, coordinate x2, coordinate x3, coordinate x4,
    coordinate y1, coordinate y2, coordinate y3, coordinate y4);

float my_pi = (float)3.141592; // ��� ����

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


    // <-- �޸� �Ҵ�
    img_p2->pixels = (int*)malloc(img_p2->row_size * img_p2->col_size * sizeof(int));

    if (img_p2->pixels == NULL) {//�޸� �Ҵ� ���н� 0�� ��ȯ
        return NULL;
    }

    for (int i = 0; i < img->col_size * img->row_size; i++) {//�Ҵ��� �޸� �ʱ�ȭ
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
    for (int c = 0; c < img->col_size; c++) {
        for (int r = 0; r < img->row_size; r++) {
            fscanf(fp, "%d", &tmp);
            img->pixels[r + img->row_size * c] = (unsigned char)tmp;
        }
    }
    // -->

    fclose(fp); // �� �̻� ������� �ʴ� ������ �ݾ� ��

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


    // <-- �޸� �Ҵ�
    img->pixels = (int*)malloc(img->row_size * img->col_size * sizeof(int));

    if (img->pixels == NULL) {//�޸� �Ҵ� ���н� 0�� ��ȯ
        return NULL;
    }

    for (int i = 0; i < img->col_size * img->row_size; i++) {//�Ҵ��� �޸� �ʱ�ȭ
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
    fscanf(fp, "%c %c", &img->M, &img->N);   // �����ѹ� �б�
    fscanf(fp, "%d %d", &img->row_size, &img->col_size);   // ����, ���� �б�
    fscanf(fp, "%d ", &img->scale);

    // <-- �޸� �Ҵ�
    img->pixels = (unsigned char*)malloc(img->row_size * img->col_size * sizeof(unsigned char));

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
            fread(&img->pixels[r + c * img->row_size], sizeof(unsigned char), 1, fp);
        }
    }
    // -->

    fclose(fp); // �� �̻� ������� �ʴ� ������ �ݾ� ��

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
    fscanf(fp, "%c %c", &img->M, &img->N);   // �����ѹ� �б�
    fscanf(fp, "%d %d", &img->row_size, &img->col_size);   // ����, ���� �б�
    fscanf(fp, "%d ", &img->scale);

    // <-- �޸� �Ҵ�
    img->pixels = (int*)malloc(img->row_size * img->col_size * sizeof(int));

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

int image_write(char* fileNm, image_p2* img)
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
    //�⺻ ����þ� Ŀ���� ����� ��ġ�� �°� ������.
}
}


Sum_row: for (a = 0; a < f_size; a++)
{
Sum_col: for (b = 0; b < f_size; b++)
{
    sum += filter[(a * f_size) + b];
    // ��ü �迭 �� ���ϱ�
}
}

offset = 1 - sum;
// ���� ���� ������ ���� ������ ���� ����
offset = offset / (filter_size * filter_size);
// �������� ������ �����ϰ� �����ϱ� ���� ��� ����

for (a = 0; a < f_size; a++)
{
    for (b = 0; b < f_size; b++)
    {
        filter[(a * f_size) + b] += offset;
        // ���� ���п� ������ �ݿ�
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


    if (filter_type == 0) {//������ ����
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

    else if (filter_type == 1) {//�Һ� ����
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

    else if (filter_type == 2) {//���� ����
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
    Queue* row;//x��ǥ
    Queue* col;//y��ǥ
    Queue* pixels;//������
    
    row = CreateQueue();
    col = CreateQueue();
    pixels = CreateQueue();

    //�࿧�� ����, �ʱ�ȭ
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


float det(float* matrix, int size) { // matrix�� ũ��� size x size
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