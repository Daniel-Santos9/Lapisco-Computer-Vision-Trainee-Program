#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat laplaciano_equalizado(Mat img);

int main(){

   Mat laplaciano;
   Mat src = imread("../gp.jpg",0); // ler imagem em tons de cinza

   namedWindow("Image");
   imshow("Image",src);
   waitKey(0);
   destroyWindow("Image");

   laplaciano=laplaciano_equalizado(src);

   namedWindow("Filtro Laplaciano Equalizado");
   imshow("Filtro Laplaciano Equalizado",laplaciano);
   waitKey(0);
   destroyWindow("Filtro Laplaciano Equalizado");

   imwrite("../Results/Laplaciano_equalizado.jpg",laplaciano);
   imwrite("../Results/Imagem_cinza.jpg",src);

   return 0;

}

Mat laplaciano_equalizado(Mat img){

    int soma=0, maior=0, menor=0;

    Mat_<uchar> filtro(img.rows, img.cols,1);

    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            filtro.at<uchar>(i,j)=0;
        }
    }

    for(int i=1; i<img.rows-1; i++){
        for( int j=1; j<img.cols-1; j++){
            soma=0;
            for(int x=-1; x<2; x++){
                for(int y=-1; y<2; y++){
                    if((j == j+y) && (i == i+x)){
                        soma = (-8)*img.at<uchar>(i+x,j+y)+soma;
                    }
                    else{
                        soma = (1)*img.at<uchar>(i+x,j+y)+soma;
                    }
                }
            }

            soma = abs(soma);
            if(soma > maior)
                maior=soma;
            if(soma< menor)
                menor = soma;
            if(soma>255)
                filtro.at<uchar>(i,j)=255;
            else
                filtro.at<uchar>(i,j)=soma;
        }
    }
    namedWindow("Filtro Laplaciano");
    imshow("Filtro Laplaciano",filtro);
    waitKey(0);
    destroyWindow("Filtro Laplaciano");

    for(int i=1; i<img.rows-1; i++){
        for(int j=1; j<img.cols-1; j++){
            if(filtro.at<uchar>(i,j) == menor)
                filtro.at<uchar>(i,j)=0;
            if(filtro.at<uchar>(i,j) == maior)
                filtro.at<uchar>(i,j)=255;

            if((filtro.at<uchar>(i,j) > menor) && (filtro.at<uchar>(i,j) < maior))
                filtro.at<uchar>(i,j) = (255*(filtro.at<uchar>(i,j)-menor)/(maior-menor));

        }
    }

    return filtro;
}
