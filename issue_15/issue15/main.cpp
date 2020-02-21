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

    Mat img_gray,Canny, video;

    VideoCapture cap(0);
    if(!cap.isOpened()){
      cout << "Error opening video stream or file" << endl;
      exit(0);
    }

    while(true){
        cap>>video;
        cvtColor(video,img_gray,CV_RGB2GRAY);
        Laplacian(img_gray,Canny,CV_CANNY_L2_GRADIENT);
        namedWindow("Video", CV_WINDOW_AUTOSIZE);
        imshow("Video",Canny);
        waitKey(25);

    }

    cap.release();
    destroyAllWindows();

    return 0;

}
