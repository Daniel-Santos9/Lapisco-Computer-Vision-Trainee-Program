#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    Mat src = imread("../img.jpg",1);
    if(!src.data){
        cout<<"Image not found"<<endl;
        exit(0);
    }
    Mat img_gray, img_bin;

    cvtColor(src,img_gray, CV_RGB2GRAY);
    adaptiveThreshold(img_gray,img_bin,200,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,5,-20);
    namedWindow("Image Thresholded",CV_WINDOW_NORMAL);
    imshow("Image Thresholded",img_bin);
    waitKey(0);
    destroyAllWindows();

    imwrite("../Results/Image_thresholded.jpg",img_bin);

    return 0;

}
