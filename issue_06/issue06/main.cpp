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
    Mat img_gray, img_canny;

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


    Canny(img_gray,img_canny,100,127,3);

    namedWindow("Image Canny");
    imshow("Image Canny",img_canny);
    waitKey(0);
    destroyWindow("Image Canny");

    imwrite("../Results/Image_canny.jpg",img_canny);
    return 0;
}
