#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"
#include "convolution.h"
#include "matrix.h"


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
�� �������� ���Ⱚ�� ����� ���� ���� ũ�⸦ ���ϰ�, �ش� ���� ���� ũ�� �ʴٸ� 0,
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

void Hysterisis(image_p2* out_dir, image_p2* in_dir, image_p2* in_mag, int HighT, int LowT);
/*
�ռ� ũ�⸦ 0, �� edge, �� edge�� �����ߴµ�, Hysterisis �Լ����� �� edge�� �� edge�� ������踦 ����
�� edge ���� �����͸� ó���ϴ� �Լ��Դϴ�.
�Է¹��� ũ�� ������ ���ؼ� ���� ���� �Ǵ� Anchor�� �����ϰ�, �ش� ���� �ѷ��δ� 8������ ���� ����
������ ����Ͽ� Anchor ���� ���� ������ �־����� �� �ش� ���⿡ �˸´� �񱳱��� �����ϰ�
�� ũ�Ⱑ 255, ��������� �Ǵ��Ͽ� �������ִ� �۾��Դϴ�.
�ش� �Լ��� �� edge�� ���е� ���鿡 ���� �� edge���� ���Ἲ�� �ִٸ� �̸� edge�� ���Խ�Ű��
�ƴϸ� 0���� �ʱ�ȭ�ϴ°� �������� �մϴ�.
*/

void homograpy_transform(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4);

void backward_mapping(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4);

void homograpy_transform_ver2(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4);

void backward_mapping_ver2(image_p2* out, image_p2* in, coordinate x1, coordinate x2, coordinate x3, coordinate x4, coordinate y1, coordinate y2, coordinate y3, coordinate y4);








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