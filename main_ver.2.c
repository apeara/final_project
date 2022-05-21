#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "convolution.h"
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
    int f_size;
    float sig;
    int HT, LT;
    image_p5* img = read_image_pgm_p5("canny_image_5.pgm");
    image_p2* tmp0 = pconvert_p5_to_p2(img);


    //��հ�
    image_p2* tmp1 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);
    average_filter(tmp1, tmp0, 3);
    image_write("result01.pgm", tmp1);


    //����þ�
    image_p2* tmp2 = image_reset(img->M, img->N, img->scale, img->row_size, img->col_size);//�Լ��� ���� ����Դϴ�.
    Gaussian_filter(tmp2, tmp0, 0.5, 3);
    image_write("result02.pgm", tmp2);



    //�̹��� �׶��̾�Ʈ
    image_p2* tmp3 = image_reset(tmp2->M, tmp2->N, tmp2->scale, tmp2->row_size, tmp2->col_size);//�Լ��� ���� ����Դϴ�.
    image_p2* tmp4 = image_reset(tmp2->M, tmp2->N, tmp2->scale, tmp2->row_size, tmp2->col_size);//�Լ��� ���� ����Դϴ�.
    gradient(tmp3, tmp4, tmp2, 1);
    image_write("result03.pgm", tmp3);
    image_write("result04.pgm", tmp4);


    //���ִ� ����
    image_p2* tmp5 = image_reset(tmp3->M, tmp3->N, tmp3->scale, tmp3->row_size, tmp3->col_size);//�Լ��� ���� ����Դϴ�.
    image_p2* tmp6 = image_reset(tmp4->M, tmp4->N, tmp4->scale, tmp4->row_size, tmp4->col_size);//�Լ��� ���� ����Դϴ�.
    NonMax(tmp5, tmp3, tmp4, 1);
    image_write("result05.pgm", tmp5);
    //image_write("result06.pgm", tmp6);



    //�̷� ���� �Ӱ�ȭ
    image_p2* tmp7 = image_reset(tmp5->M, tmp5->N, tmp5->scale, img->row_size, img->col_size);//�Լ��� ���� ����Դϴ�.
    DoubleT(tmp7, tmp5, 120, 30);
    image_write("result07.pgm", tmp7);


    //Hysterisis
    image_p2* tmp8 = image_reset(tmp7->M, tmp7->N, tmp7->scale, tmp7->row_size, tmp7->col_size);//�Լ��� ���� ����Դϴ�.
    image_p2* tmp9 = image_reset(tmp7->M, tmp7->N, tmp7->scale, tmp7->row_size, tmp7->col_size);//�Լ��� ���� ����Դϴ�.
    preHys(tmp8,tmp9,tmp7,tmp4);
    image_write("result08.pgm", tmp8);
    image_write("result09.pgm", tmp9);

    
    image_p2* tmp10= image_reset(tmp7->M, tmp7->N, tmp7->scale, tmp7->row_size, tmp7->col_size);//�Լ��� ���� ����Դϴ�.
    Hys(tmp10, tmp7, tmp4);
    image_write("result10.pgm", tmp10);


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
    close_image_p2(tmp10);
    


    printf("\n\n---finish---\n\n");
    return 0;
}