#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;


Mat Region_Growing(Mat src);
void setPoint(int e,int x,int y,int d, void*ptr);

int main(){

    Mat_<Vec3b> src = imread("../fig1.jpg");
    if(!src.data){
        cout<<"Image not found"<<endl;
        exit(0);
    }

    Mat grow = Region_Growing(src);
    imwrite("../Results/Region_Growing.jpg", grow);

}



Mat Region_Growing(Mat src){

    Point p;
    Mat grow(src.rows, src.cols, CV_8UC1);

    for(int i=0; i<grow.rows; i++){
        for(int j=0; j< grow.cols; j++){
            grow.at<uchar>(i,j)=0;
        }
    }

    imshow("Setar_Semente", src);
    setMouseCallback("Setar_Semente", setPoint, &p);
    waitKey(0);
    destroyWindow("Setar_Semente");

    int x = p.x;
    int y = p.y;

    grow.at<uchar>(y,x)=255;

    int b = src.at<Vec3b>(y,x)[0];
    int g = src.at<Vec3b>(y,x)[1];
    int r = src.at<Vec3b>(y,x)[2];
    cout<<b<<endl<<g<<endl<<r<<endl;


    int parar=0;
    int continuar=1;
    while (continuar!=parar) {
        continuar=parar;
        parar=0;
        for (int i=0; i<grow.rows; i++) {
            for (int j=0; j<grow.cols; j++) {
                if (grow.at<uchar>(i,j)==255){

                    b = src.at<Vec3b>(i,j)[0];
                    g = src.at<Vec3b>(i,j)[1];
                    r = src.at<Vec3b>(i,j)[2];

                    if (b < 60 && g > 50 && r > 150 && src.at<uchar>(i-1,j-1)!=255){
                        grow.at<uchar>(i-1,j-1)=255;
                        parar++;
                    }
                    if (b < 60 && g > 50 && r > 150 && src.at<uchar>(i-1,j)!=255){
                        grow.at<uchar>(i-1,j)=255;
                        parar++;
                    }
                    if (b < 60 && g > 50 && r > 150 && src.at<uchar>(i-1,j+1)!=255){
                        grow.at<uchar>(i-1,j+1)=255;
                        parar++;
                    }

                    if (b < 60 && g > 50 && r > 150 && src.at<uchar>(i,j-1)!=255){
                        grow.at<uchar>(i,j-1)=255;
                        parar++;
                    }
                    if (b < 60 && g > 50 && r > 150 && src.at<uchar>(i,j+1)!=255){
                        grow.at<uchar>(i,j+1)=255;
                        parar++;
                    }
                    if (b < 60 && g > 50 && r > 150 && src.at<uchar>(i+1,j-1)!=255){
                        grow.at<uchar>(i+1,j-1)=255;
                        parar++;
                    }
                    if (b < 60 && g > 50 && r > 150 && src.at<uchar>(i+1,j)!=255){
                        grow.at<uchar>(i+1,j)=255;
                        parar++;
                    }
                    if (b < 60 && g > 50 && r > 150 && src.at<uchar>(i+1,j+1)!=255){
                        grow.at<uchar>(i+1,j+1)=255;
                        parar++;
                    }
                }
            }

        }
        imshow("Region Growing",grow);
        waitKey(30);
    }

    return grow;

}

void setPoint(int e,int x,int y,int d, void*ptr){
    Point*p= (Point*)ptr;
    p->x = x;
    p->y = y;
}
