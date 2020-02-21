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

    //Mat src = imread("../gp.jpg",1); //Imagem normal
    Mat src = imread("../img_ruidos_sal_e_pimenta.png");
    Mat img_gray, img_blur, img_median;


    cvtColor(src, img_gray, CV_RGB2GRAY);

    namedWindow("Original image", CV_WINDOW_AUTOSIZE);
    namedWindow("Image Grayscale",CV_WINDOW_AUTOSIZE);
    imshow("Original image",src);
    imshow("Image Grayscale", img_gray);
    waitKey(0);
    destroyWindow("Original image");
    destroyWindow("Image Grayscale");

    medianBlur(img_gray,img_median, CV_MEDIAN);
    blur(img_gray, img_blur, Size(5,5));

    namedWindow("Image Median", CV_WINDOW_AUTOSIZE);
    namedWindow("Image Blur",CV_WINDOW_AUTOSIZE);
    imshow("Image Median",img_median);
    imshow("Image Blur", img_blur);
    waitKey(0);
    destroyWindow("Image Median");
    destroyWindow("Image Blur");

    imwrite("../Results/Image_Grayscale.jpg",img_gray);
    imwrite("../Results/Image_Median.jpg",img_median);
    imwrite("../Results/Image_Blur.jpg",img_blur);




    return 0;
}
