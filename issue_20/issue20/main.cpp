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

    Mat grow(src.rows, src.cols, CV_8UC1);
    for(int i=0; i<grow.rows; i++){
        for(int j=0; j< grow.cols; j++){
            if((i == grow.rows/2) && (j==grow.cols/2)){
                grow.at<uchar>(i,j)=255;
            }
            else{
                grow.at<uchar>(i,j)=0;
            }
        }
    }

    int parar=0;
    int continuar=1;
    system("pause");
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
