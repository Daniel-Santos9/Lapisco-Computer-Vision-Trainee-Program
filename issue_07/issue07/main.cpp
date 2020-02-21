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
    Mat img_gray, img_bin;

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

    threshold(img_gray,img_bin,127,200,CV_THRESH_BINARY);
    namedWindow("Image Thresholded");
    imshow("Image Thresholded",img_bin);
    waitKey(0);
    destroyWindow("Image Thresholded");

    imwrite("../Results/Image_Thresholded.jpg",img_bin);
    return 0;
}
