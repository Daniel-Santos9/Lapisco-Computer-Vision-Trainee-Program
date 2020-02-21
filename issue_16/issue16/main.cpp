#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat histograma(Mat img);

int main(){

    Mat hist, equal,hist_equal;
    Mat src = imread("../gp.jpg",0);;

    if(!src.data){
        cout<<"Image not found!"<<endl;
        exit(0);
    }
    equalizeHist(src,equal);

    hist = histograma(src);
    hist_equal = histograma(equal);

    imshow("Imagem",src);
    imshow("Imagem Equalizada",equal);
    imshow("Histograma da imagem",hist);
    imshow("Histograma da imagem equalizada",hist_equal);
    waitKey(0);

    imwrite("../Results/Imagem_cinza.jpg",src);
    imwrite("../Results/Imagem_equalizada.jpg",equal);
    imwrite("../Results/Histograma_imagem_cinza.jpg",hist);
    imwrite("../Results/Histograma_imagem_equalizada.jpg",hist_equal);


    return 0;
}



Mat histograma(Mat img){

    int vet[256], n, maior=0;

    for(int i=0; i<256;i++)
        vet[i]=0;

    for(int i=0; i<img.rows;i++){
        for(int j=0; j<img.cols; j++){
            n=0;
            n=img.at<uchar>(i,j);
            vet[n]++;
        }
    }

    for(int i=0;i<256;i++){
        if(maior==0)
            maior=vet[i];
        if(vet[i]>maior)
            maior=vet[i];
    }

    int max=maior/200;

    for(int i=0; i<256; i++){
        vet[i]/=max;
    }

    Mat_<Vec3b> hist(200,256,CV_8UC3);

    for(int i=0; i<hist.rows;i++){
        for(int j=0; j<hist.cols;j++){

            if(i >= hist.rows-vet[j]){
                hist(i,j)[0]=0;
                hist(i,j)[1]=0;
                hist(i,j)[2]=0;

            }else{

                hist(i,j)[0]=255;
                hist(i,j)[1]=255;
                hist(i,j)[2]=255;

            }
        }
    }
    return hist;
}
