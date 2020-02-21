#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    Mat src = imread("../img.png");
    if(!src.data){
        cout<<"Image not found"<<endl;
        exit(0);
    }
    Mat img_gray;

    cvtColor(src,img_gray, CV_RGB2GRAY);

    GaussianBlur(img_gray, img_gray, Size(7, 7), 2, 2 );

        vector <Vec3f> circles;
        HoughCircles (img_gray, circles, CV_HOUGH_GRADIENT, 1, img_gray.rows/8, 200, 100, 0, 0.);

        for(int i=0; i<circles.size(); i++){
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));

            int radius = cvRound(circles[i][2]);

            circle( src, center, 3, Scalar(0,255,0), -1, 8, 0 );

            circle( src, center, radius, Scalar(0,255,0), 3, 8, 0 );
        }

    namedWindow("Hough Transform",CV_WINDOW_NORMAL);
    imshow("Hough Transform",src);
    waitKey(0);
    destroyAllWindows();

    imwrite("../Results/Hough_Transform.jpg",src);

    return 0;

}
