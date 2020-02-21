#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    Mat_<uchar> img_gray;
    Mat src = imread("../gp.jpg");
    int Gx, Gy;

    if(!src.data){
        cout<<"Image not found!"<<endl;
        exit(0);
    }
    cvtColor(src,img_gray,CV_RGB2GRAY);

    Mat_<uchar> sobel(img_gray.rows,img_gray.cols,1);

    namedWindow("Original image");
    namedWindow("Image Grayscale");
    imshow("Original image",src);
    imshow("Image Grayscale",img_gray);
    waitKey(0);
    destroyWindow("Original image");
    destroyWindow("Image Grayscale");


    for(int i=0; i<sobel.rows;i++){
        for(int j=0; j<sobel.cols;j++){
            sobel.at<uchar>(i,j)=0;
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


    cout<<"passou aqui"<<endl;

    for(int i=1; i<sobel.rows-1;i++){
        for(int j=1; j<sobel.cols-1;j++){

            Gx = (1)*img_gray.at<uchar>(i-1,j-1) + (2)*img_gray.at<uchar>(i-1,j) + (1)*img_gray.at<uchar>(i-1,j+1) + (-1)*img_gray.at<uchar>(i+1,j-1) + (-2)*img_gray.at<uchar>(i+1,j) + (-1)*img_gray.at<uchar>(i+1,j+1);
            Gy = (1)*img_gray.at<uchar>(i-1,j-1) + (-1)*img_gray.at<uchar>(i-1,j+1) + (2)*img_gray.at<uchar>(i,j-1) + (-2)*img_gray.at<uchar>(i,j+1) + (1)*img_gray.at<uchar>(i+1,j-1) + (-1)*img_gray.at<uchar>(i+1,j+1);
            sobel.at<uchar>(i,j) = (int)sqrt(pow(Gx,2)+pow(Gy,2));
        }
    }

    namedWindow("Filtro de Sobel");
    imshow("Filtro de Sobel",sobel);
    waitKey(0);
    destroyWindow("Filtro de Sobel");

    imwrite("../Results/Filtro_Sobel.jpg",sobel);

    return 0;
}
