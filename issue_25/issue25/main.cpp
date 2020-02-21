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
int Sel_Canal(int Canal,int cont);

int main(){
    Mat img_gray;
    Mat_<Vec3b> src = imread("../img.png");
    if(!src.data){
        cout<<"Image not found"<<endl;
        exit(0);
    }
    cvtColor(src,img_gray,CV_RGB2GRAY);
    Mat grow = Region_Growing(img_gray);
    imwrite("../Results/Region_Growing.jpg", grow);

}



Mat Region_Growing(Mat src) {

    int x,y;
    Mat_<Vec3b> grow(src.rows,src.cols,CV_8UC3);
    for(int i=0;i<grow.rows;i++){
        for(int j=0;j<grow.cols;j++){
            grow(i,j)[0]=0;
            grow(i,j)[1]=0;
            grow(i,j)[2]=0;
        }
    }
    cout<<"admsdomoamsd"<<endl;
    int canal;
    int cont=0;
    while(cont<3)
    {
        canal=Sel_Canal(canal, cont);
        Point p;

        imshow("Aplicar_Semente",src);
        setMouseCallback("Aplicar_Semente",setPoint, &p );
        waitKey(0);
        x= p.x ;
        y= p.y ;
        grow(y,x)[canal]=255;
        int Continuar=1;
        int Parar=0;
        while(Continuar!=Parar)
        {
            Continuar=Parar;
            Parar=0;
            for(int i=0;i<src.rows;i++)
            {
                for(int j=0;j<src.cols;j++)
                {
                    if(grow(i,j)[canal]==255)
                    {
                        if(src.at<uchar>(i+1,j-1)<127)
                        {
                            grow(i+1,j-1)[canal]=255;
                            Parar++;
                        }
                        if(src.at<uchar>(i,j-1)<127)
                        {
                            grow(i,j-1)[canal]=255;
                            Parar++;
                        }
                        if(src.at<uchar>(i-1,j-1)<127)
                        {
                            grow(i-1,j-1)[canal]=255;
                            Parar++;
                        }
                        if(src.at<uchar>(i+1,j)<127)
                        {
                            grow(i+1,j)[canal]=255;
                            Parar++;
                        }
                        if(src.at<uchar>(i+1,j+1)<127)
                        {
                            grow(i+1,j+1)[canal]=255;
                            Parar++;
                        }
                        if(src.at<uchar>(i,j+1)<127)
                        {
                            grow(i,j+1)[canal]=255;
                            Parar++;
                        }
                        if(src.at<uchar>(i-1,j+1)<127)
                        {
                            grow(i-1,j+1)[canal]=255;
                            Parar++;
                        }
                        if(src.at<uchar>(i-1,j)<127)
                        {
                            grow(i-1,j)[canal]=255;
                            Parar++;
                        }
                    }
                }
            }
            imshow("Region Growing",grow);
            waitKey(30);

        }
        destroyWindow("Region Growing");
        cont++;
    }
    return grow;
}

void setPoint(int e,int x,int y,int d, void*ptr){
    Point*p= (Point*)ptr;
    p->x = x;
    p->y = y;
}

int Sel_Canal(int Canal,int cont){
    if (cont==0){
        Canal=2;
        return Canal;
    }
    if (cont==1){
        Canal=0;
        return Canal;
    }
    if (cont==2){
        Canal=1;
        return Canal;
    }
    return 0;
}
