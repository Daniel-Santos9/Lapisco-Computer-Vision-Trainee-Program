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

    if(!src.data){
        cout<<"image not found!";
        exit(0);
    }

    Mat channel[3];
    split(src,channel);

    namedWindow("Original Image",CV_WINDOW_AUTOSIZE);
    namedWindow("Channel Red",CV_WINDOW_AUTOSIZE);
    namedWindow("Channel Green",CV_WINDOW_AUTOSIZE);
    namedWindow("Channel Blue",CV_WINDOW_AUTOSIZE);
    imshow("Original Image", src);
    imshow("Channel Red", channel[0]);
    imshow("Channel Green", channel[1]);
    imshow("Channel Blue", channel[2]);
    waitKey(0);
    destroyAllWindows();

    imwrite("../Results/Channel_Red.jpg",channel[0]);
    imwrite("../Results/Channel_Green.jpg",channel[1]);
    imwrite("../Results/Channel_Blue.jpg",channel[2]);


    return 0;
}
