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
    Mat img_Canny;
    vector<vector<Point> > contours;
    cvtColor(src,img_gray, CV_RGB2GRAY);
    //blur(img_gray,img_gray,Size(5,5));

    Canny(img_gray,img_Canny,100,127,3);
    threshold(img_Canny,img_Canny,127,255,CV_THRESH_BINARY);

    namedWindow("Canny",CV_WINDOW_NORMAL);
    imshow("Canny",img_Canny);
    waitKey(0);
    destroyAllWindows();

    findContours(img_Canny, contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    cout<<"Existe "<<contours.size()<<" contornos!"<<endl;

    imwrite("../Results/contours.jpg",img_Canny);

    return 0;

}
