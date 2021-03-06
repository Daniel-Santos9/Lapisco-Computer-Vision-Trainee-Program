#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string.h>
#include <time.h>

#include "lbp.h"
#include "histograma.h"

#include <sys/time.h>
#include <vector>

#define _WIN32_WINNT 0x050

using namespace cv;
using namespace std;

vector<float> lbp_extraction_image(Mat src){
    Mat lbp_img = lbp::OLBP(src);
    int quant_tomCinza = 12;//Quantidade de Tons de Cinza
    normalize(lbp_img, lbp_img, 0, quant_tomCinza-1, NORM_MINMAX, CV_8UC1);
    //Parametros da Função Normalize
    //1 - imagem de entrada // 2 - imagem de saida
    //3, 4 - Variacao dos tons de cinza que a imagem vai ter. Neste caso -> 0 ~ 11
    //5 - A funcao NORM_MINMAX serve para normalizar entre os valores do parametros (3,4)
    //6 - CV_8UC1 -> Imagem 8 bits Uchar, 1 canal
    Mat spatial_hist = lbp::spatial_histogram(lbp_img, quant_tomCinza, 3, 3, 0);
    // Parametros da Funcao spatial_hist
    //1 - imagem de entrada // 2 - A variacao entre os parametros (3,4) da funcao Normalize no caso 12
    //3, 4 - Tamanho da mascara(vizinhanca)  3x3
    //
    vector<float> feature_vector;
    for(int j = 0; j < spatial_hist.cols; ++j){
        if(spatial_hist.at<int>(0, j) != -1){
            feature_vector.push_back(spatial_hist.at<int>(0, j));
        }
    }
    return feature_vector;
}


int main(){

    char dir_img[500];

    for(int i=0;i<10; i++){
        sprintf(dir_img,"../img/%d.jpg",(i+1));

        Mat img = imread(dir_img,0);
        if(!img.data){
            cout<<"Image not found!"<<endl;
            exit(0);
        }
        int r = 293;
        int c = 293;

        Mat imageMat;
        Size sizeMat(c,r);
        resize(img,imageMat,sizeMat);

        clock_t Temp[2];//TEMPO

        vector <float> resul_LBP;

        Temp[0]= clock();

        resul_LBP = lbp_extraction_image(imageMat);//FUNCAO DO LBP

        Temp[1]= clock();

        printf("%d\t",(int)resul_LBP.size());//retorno.size -> Quantidade de Atributos Gerados.

        double time;
        time = (Temp[1]-Temp[0])*1000.0/CLOCKS_PER_SEC;
        FILE * tempos;

        tempos = fopen("../Results/time.txt","a");
        fprintf(tempos,"%f\n",time);
        fclose(tempos);

        FILE *fpOutOpencvGLCM;

        fpOutOpencvGLCM = fopen("../Results/LBP.txt","a");
        for (int print = 0; print < resul_LBP.size(); print+=1){
            fprintf(fpOutOpencvGLCM, "%f,",resul_LBP.at(print));
        }
        printf("\n");
        fprintf(fpOutOpencvGLCM,"\n");
        fclose(fpOutOpencvGLCM);
    }
    return 0;
}
