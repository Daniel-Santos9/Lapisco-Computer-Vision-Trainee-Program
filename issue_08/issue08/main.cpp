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
    Mat img_gray, img_resiz1,img_resiz2;

    if(!src.data){
        cout<<"Image not found!"<<endl;
        exit(0);
    }

    int rows = src.rows;
    int cols = src.cols;
    cout<<"Rows: "<<rows<<endl<<"Cols: "<<cols<<endl;

    cvtColor(src, img_gray, CV_RGB2GRAY);

    namedWindow("Original image");
    namedWindow("Image Grayscale");
    imshow("Original image",src);
    imshow("Image Grayscale",img_gray);
    waitKey(0);
    destroyWindow("Original image");
    destroyWindow("Image Grayscale");

    resize(src,img_resiz1,Size((rows/2),(cols/2)));
    resize(src,img_resiz2,Size((rows*2),(cols*2)));

    namedWindow("Image Resized 1");
    namedWindow("Image Resized 2");
    imshow("Image Resized 1",img_resiz1);
    imshow("Image Resized 2", img_resiz2);
    waitKey(0);
    destroyWindow("Image Resized 1");
    destroyWindow("Image Resized 2");

    imwrite("../Results/Image_Resized_1.jpg",img_resiz1);
    imwrite("../Results/Image_Resized_2.jpg",img_resiz2);

    return 0;
}
