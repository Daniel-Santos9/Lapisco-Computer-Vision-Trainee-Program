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


    Mat src = imread("../gp.jpg");
    Mat img_gray;
    FILE *arq;

    if(!src.data){
        cout<<"Image not found!"<<endl;
        exit(0);
    }

    int rows = src.rows;
    int cols = src.cols;

    int matriz[rows][cols];

    cout<<"Rows: "<<rows<<endl<<"Cols: "<<cols<<endl;

    cvtColor(src, img_gray, CV_RGB2GRAY);

    namedWindow("Original image");
    namedWindow("Image Grayscale");
    imshow("Original image",src);
    imshow("Image Grayscale",img_gray);
    waitKey(0);
    destroyWindow("Original image");
    destroyWindow("Image Grayscale");


    for(int i=0; i<img_gray.rows;i++){
        for(int j=0; j<img_gray.cols;j++){
            if(img_gray.at<uchar>(i,j) < 127){
                matriz[i][j] = 0;
            }else{
                matriz[i][j] = 255;
            }
        }
    }

    arq = fopen("../Results/Image.txt","w");

    if (arq == NULL){
        cout<<"Problem creating the file"<<endl;
        exit(0);
    }
    for(int i=0; i<img_gray.rows;i++){
        for(int j=0; j<img_gray.cols;j++){
            fprintf(arq, "%d ", matriz[i][j]);
        }
        fprintf(arq,"\n");
    }
    fclose(arq);
    return 0;
}
