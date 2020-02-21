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

    Mat src = imread("../fig.jpg",0);
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

    grow.at<uchar>(x,y)=255;

    imshow("Image_semente",grow);
    waitKey(0);
    destroyWindow("imagem_semente");

    int parar=0;
    int continuar=1;
    while (continuar!=parar) {
        continuar=parar;
        parar=0;
        for (int i=0; i<grow.rows; i++) {
            for (int j=0; j<grow.cols; j++) {
                if (grow.at<uchar>(i,j)==255){
                    if (src.at<uchar>(i-1,j-1)<127){
                        grow.at<uchar>(i-1,j-1)=255;
                        parar++;
                    }
                    if (src.at<uchar>(i-1,j)<127){
                        grow.at<uchar>(i-1,j)=255;
                        parar++;
                    }
                    if (src.at<uchar>(i-1,j+1)<127){
                        grow.at<uchar>(i-1,j+1)=255;
                        parar++;
                    }

                    if (src.at<uchar>(i,j-1)<127){
                        grow.at<uchar>(i,j-1)=255;
                        parar++;
                    }
                    if (src.at<uchar>(i,j+1)<127){
                        grow.at<uchar>(i,j+1)=255;
                        parar++;
                    }
                    if (src.at<uchar>(i+1,j-1)<127){
                        grow.at<uchar>(i+1,j-1)=255;
                        parar++;
                    }
                    if (src.at<uchar>(i+1,j)<127){
                        grow.at<uchar>(i+1,j)=255;
                        parar++;
                    }
                    if (src.at<uchar>(i+1,j+1)<127){
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
