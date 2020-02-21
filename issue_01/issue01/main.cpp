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
        cout<<"Image not found!";
        exit(0);
    }
    namedWindow("Image",CV_WINDOW_AUTOSIZE);
    imshow("Image", src);
    waitKey(0);
    destroyWindow("Image");

    imwrite("../Results/Image.jpg", src);

    return 0;

}
