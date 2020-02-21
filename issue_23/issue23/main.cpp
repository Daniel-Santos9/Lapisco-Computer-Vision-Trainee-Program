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
Mat Centroide(Mat grow);
void setPoint(int e,int x,int y,int d, void*ptr);

int main(){

    Mat src = imread("../fig.jpg",0);
    if(!src.data){
        cout<<"Image not found"<<endl;
        exit(0);
    }

    Mat grow = Region_Growing(src);
    Mat centroide = Centroide(grow);

    imwrite("../Results/Region_Growing.jpg", grow);
    imwrite("../Results/Imagem_Centroide.jpg", centroide);

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
            cout<<"passojso"<<endl;

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

Mat Centroide(Mat grow){
    int maiorx,menorx,maiory,menory;
    int centrox=0,centroy=0;
    int cont=0;

    for (int i=0; i<grow.rows; i++) {
        for (int j=0; j<grow.cols; j++) {
            if (grow.at<uchar>(i,j)==255){
                if (cont==0){
                    maiorx=i;
                    menorx=i;
                    maiory=j;
                    menory=j;
                    cont++;
                }
                if(i>maiorx)
                    maiorx=i;
                if(i<menorx)
                    menorx=i;
                if(j>maiory)
                    maiory=j;
                if(j<menory)
                    menory=j;
            }
        }
    }
    centrox=((maiorx-menorx)/2+menorx);
    centroy=((maiory-menory)/2+menory);

    Mat_<Vec3b> centroide(grow.rows,grow.cols,CV_8UC3);
    for (int i=0; i<grow.rows; i++) {
        for (int j=0; j<grow.cols; j++) {
            if (grow.at<uchar>(i,j)==255){
                centroide.at<Vec3b>(i,j)[0]=255;
                centroide.at<Vec3b>(i,j)[1]=0;
                centroide.at<Vec3b>(i,j)[2]=0;
            }
            else{
                centroide.at<Vec3b>(i,j)[0]=255;
                centroide.at<Vec3b>(i,j)[1]=255;
                centroide.at<Vec3b>(i,j)[2]=255;
            }
        }
    }
    circle(centroide, Point(centroy,centrox),3, CV_RGB(0,255,0),5,2,0);
    imshow("Centroide", centroide);

    return centroide;
}


