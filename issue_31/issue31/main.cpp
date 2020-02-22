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
    destroyWindow("Canny");

    findContours(img_Canny, contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    cout<<"Existe "<<contours.size()<<" contornos!"<<endl;
       // cout<<"psdpakspdkpaskdpa"<<endl;

    vector<vector<Point> > contours_p(contours.size());
    vector<Rect> bRect(contours.size());
    for(int i=0; i<contours.size(); i++ ){
        approxPolyDP( Mat(contours[i]), contours_p[i], 3, true );
        bRect[i] = boundingRect( Mat(contours_p[i]) );
    }


    Mat drawing = Mat::zeros( img_Canny.size(), CV_8UC3);

    for (int i=0; i<contours.size();i++){
            drawContours(drawing, contours_p, i, Scalar(0,255,0));
            rectangle(drawing, Point(bRect[i].tl().x,bRect[i].tl().y), Point(bRect[i].br().x,bRect[i].br().y), Scalar(255,0,0));
    }
    namedWindow("Contours",CV_WINDOW_NORMAL);
    imshow("Contours",drawing);
    waitKey(0);
    destroyWindow("Contours");

    imwrite("../Results/contours.jpg",img_Canny);
    imwrite("../Results/DrawingRect.jpg",drawing);

    return 0;

}
