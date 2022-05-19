#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"



/*
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
*/

/*
    �Ʒ��� ��ĭ�� ����� �Լ��� �־��ּ���. �� �ܰ踶�� ó���� �̹����� ����� ���Դϴ�. �Լ����� �Ͻ� ��
    �����ϸ� void function_name(image_p2* output_data, image_p2* input_data, �� ���� �ʿ��� ������...){}
    ������ �������ּ���. ���� ���� �ϰ����ְ� ������� �մϴ�. ����� �Լ��� ������Ͽ� �־ ������
    �����Դϴ�. ����#include "convolution.h", #include "image.h"�� ���� ������Ϸ� ���� �ȿ� �Լ���
    �־��ּ���.

    �׸��� convolution.h�� ���� �ڷ����� float��, in/out data�� �ڷ����� int�� �����Ͽ��� �����
    �����Դϴ�. Ȥ�� �ٲپ �Լ��� ������ٸ� �̸��� �ٲپ� ��������� �����Ͽ� �������ּ���.
    ������ �Լ� �̸��鵵 �ٲپ�� �մϴ�.
*/

int main() {
    image_p5* img = read_image_pgm_p5("canny_image.pgm");//canny_image.pgm
    image_p2* tmp0 = pconvert_p5_to_p2(img);


    //��հ�
    image_p2* tmp1 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);
    average_filter(tmp1, tmp0, 3);
    image_write("result1.pgm", tmp1);


    //����þ�
    image_p2* tmp2 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);//�Լ��� ���� ����Դϴ�.
    Gaussian_filter(tmp2, tmp0, 0.8, 3);
    image_write("result2.pgm", tmp2);



    //�̹��� �׶��̾�Ʈ
    image_p2* tmp3 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);//�Լ��� ���� ����Դϴ�.
    image_p2* tmp4 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);//�Լ��� ���� ����Դϴ�.
    gradient(tmp3, tmp4, tmp2, 2);
    image_write("result3.pgm", tmp3);
    image_write("result4.pgm", tmp4);


    //���ִ� ����
    image_p2* tmp5 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);//�Լ��� ���� ����Դϴ�.
    NonMax(tmp5, tmp3, tmp4, 1);
    image_write("result5.pgm", tmp5);



    //�̷� ���� �Ӱ�ȭ
    image_p2* tmp6 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);//�Լ��� ���� ����Դϴ�.
    DoubleT(tmp6, tmp5, 200, 50);
    image_write("result6.pgm", tmp6);


    //Hysterisis
    image_p2* tmp7 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);//�Լ��� ���� ����Դϴ�.
    Hysterisis(tmp7, tmp6, tmp4, 200, 50);
    image_write("result7.pgm", tmp7);



    close_image_p5(img);
    close_image_p2(tmp0);
    close_image_p2(tmp2);
    close_image_p2(tmp3);
    close_image_p2(tmp4);
    close_image_p2(tmp5);
    close_image_p2(tmp6);
    close_image_p2(tmp7);


    printf("\n\n---finish---\n\n");
    return 0;
}