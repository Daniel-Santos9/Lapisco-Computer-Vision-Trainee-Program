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


    Mat src = imread("../img.jpg");
    Mat img_gray;

    if(!src.data){
        cout<<"Image not found!"<<endl;
        exit(0);
    }

    cvtColor(src, img_gray, CV_RGB2GRAY);

    namedWindow("Original image");
    namedWindow("Image Grayscale");
    imshow("Original image",src);
    imshow("Image Grayscale",img_gray);
    waitKey(0);
    destroyWindow("Original image");
    destroyWindow("Image Grayscale");

    Mat_<Vec3b> image(img_gray.rows,img_gray.cols,CV_8UC3);

    for(int i=0; i< img_gray.rows; i++){
        for(int j=0; j<img_gray.cols;j++){

            if((i==img_gray.rows/2)&&(j==img_gray.cols/2)){

                image(i,j)[0]=0;
                image(i,j)[1]=0;
                image(i,j)[2]=255;
            }
            else{

                image(i,j)[0]=img_gray.at<uchar>(i,j);
                image(i,j)[1]=img_gray.at<uchar>(i,j);
                image(i,j)[2]=img_gray.at<uchar>(i,j);
            }
        }
    }

    namedWindow("Center");
    imshow("Center",image);
    waitKey(0);
    destroyWindow("Center");

    imwrite("../Results/Center.jpg",image);

    return 0;

}
