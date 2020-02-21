#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat histograma(Mat img);

int main(){
    Mat sobel, hist, hist_sobel;
    Mat_<uchar> img_gray;
    Mat src = imread("../gp.jpg");
    int Gx, Gy;

    if(!src.data){
        cout<<"Image not found!"<<endl;
        exit(0);
    }
    cvtColor(src,img_gray,CV_RGB2GRAY);

    hist = histograma(img_gray);

    Mat_<uchar> filter_sobel(img_gray.rows,img_gray.cols,1);

    for(int i=0; i<filter_sobel.rows;i++){
        for(int j=0; j<filter_sobel.cols;j++){
            filter_sobel.at<uchar>(i,j)=0;
        }
    }

    /*

     O operador utiliza duas matrizes 3×3 (horizontal e vertical)
     usando essas matrizes parar percorrer a imagem

            Sobel Horizontal   Sobel Vertical
            // | +1 +2 +1 |    | -1 0 +1 |
            // |  0  0  0 |    | -2 0 +2 |
            // | -1 -2 -1 |    | -1 0 +1 |

    */


    for(int i=1; i<filter_sobel.rows-1;i++){
        for(int j=1; j<filter_sobel.cols-1;j++){

            Gx = (1)*img_gray.at<uchar>(i-1,j-1) + (2)*img_gray.at<uchar>(i-1,j) + (1)*img_gray.at<uchar>(i-1,j+1) + (-1)*img_gray.at<uchar>(i+1,j-1) + (-2)*img_gray.at<uchar>(i+1,j) + (-1)*img_gray.at<uchar>(i+1,j+1);
            Gy = (1)*img_gray.at<uchar>(i-1,j-1) + (-1)*img_gray.at<uchar>(i-1,j+1) + (2)*img_gray.at<uchar>(i,j-1) + (-2)*img_gray.at<uchar>(i,j+1) + (1)*img_gray.at<uchar>(i+1,j-1) + (-1)*img_gray.at<uchar>(i+1,j+1);
            filter_sobel.at<uchar>(i,j) = (int)sqrt(pow(Gx,2)+pow(Gy,2));
        }
    }

    hist_sobel = histograma(filter_sobel);

    imshow("Imagem", img_gray);
    imshow("Histograma Imagem", hist);
    imshow("Imagem Sobel", filter_sobel);
    imshow("Histograma Sobel",hist_sobel);

    imwrite("../Results/image_gray.jpg",img_gray);
    imwrite("../Results/Histograma_imageGray.jpg",hist);
    imwrite("../Results/Histograma_sobel.jpg",hist_sobel);
    imwrite("../Results/Filtro_Sobel.jpg",filter_sobel);

    waitKey(0);

    return 0;
}


Mat histograma(Mat img){

    int vet[256], n, maior=0;

    for(int i=0; i<256;i++)
        vet[i]=0;

    for(int i=0; i<img.rows;i++){
        for(int j=0; j<img.cols; j++){
            n=0;
            n=img.at<uchar>(i,j);
            vet[n]++;
        }
    }

    for(int i=0;i<256;i++){
        if(maior==0)
            maior=vet[i];
        if(vet[i]>maior)
            maior=vet[i];
    }

    int max=maior/200;

    for(int i=0; i<256; i++){
        vet[i]/=max;
    }

    Mat_<Vec3b> hist(200,256,CV_8UC3);

    for(int i=0; i<hist.rows;i++){
        for(int j=0; j<hist.cols;j++){

            if(i >= hist.rows-vet[j]){
                hist(i,j)[0]=0;
                hist(i,j)[1]=0;
                hist(i,j)[2]=0;

            }else{

                hist(i,j)[0]=255;
                hist(i,j)[1]=255;
                hist(i,j)[2]=255;

            }
        }
    }
    return hist;
}
