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

    Mat img_gray, video;

    VideoCapture cap(0);

    while(true){
        cap>>video;
        cvtColor(video,img_gray,CV_RGB2GRAY);
        namedWindow("Video", CV_WINDOW_AUTOSIZE);
        imshow("Video",img_gray);
        waitKey(0);
        destroyAllWindows();
    }

    return 0;

}
