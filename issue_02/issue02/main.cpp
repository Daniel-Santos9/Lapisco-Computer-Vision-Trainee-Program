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

    Mat src,dst;

    src = imread("../gp.jpg");

    if(!src.data){
        cout<<"Image not found!";
        exit(0);
    }
    cvtColor(src,dst,CV_RGB2GRAY);

    namedWindow("Original Image",CV_WINDOW_AUTOSIZE);
    namedWindow("Grayscale Image",CV_WINDOW_AUTOSIZE);
    imshow("Original Image", src);
    imshow("Grayscale Image", dst);
    waitKey(0);
    destroyAllWindows();

    imwrite("../Results/Grayscale_Image.jpg",dst);



    return 0;
}
