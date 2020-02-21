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
    Mat hsv;

    if(!src.data){
        cout<<"image not found!";
        exit(0);
    }
    cvtColor(src,hsv,CV_RGB2HSV);

    Mat channel[3];
    split(hsv,channel);

    namedWindow("Original Image RGB",CV_WINDOW_AUTOSIZE);
    namedWindow("Original Image HSV",CV_WINDOW_AUTOSIZE);
    namedWindow("Channel H (Tonalidade)",CV_WINDOW_AUTOSIZE);
    namedWindow("Channel S (Saturacao)",CV_WINDOW_AUTOSIZE);
    namedWindow("Channel V (Brilho)",CV_WINDOW_AUTOSIZE);
    imshow("Original Image RGB", src);
    imshow("Original Image HSV", hsv);
    imshow("Channel H (Tonalidade)", channel[0]);
    imshow("Channel S (Saturacao)", channel[1]);
    imshow("Channel V (Brilho)", channel[2]);
    waitKey(0);
    destroyAllWindows();
    imwrite("../Results/Image HSV.jpg",hsv);
    imwrite("../Results/Channel_H(Tonalidade).jpg",channel[0]);
    imwrite("../Results/Channel_S(Saturacao).jpg",channel[1]);
    imwrite("../Results/Channel_V(Brilho).jpg",channel[2]);


    return 0;
}

