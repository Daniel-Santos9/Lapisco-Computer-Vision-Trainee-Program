#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat Region_Growing(Mat src);
void cores(int &B,int &G,int &R,int cont);

int main(){

    Mat src = imread("../img.png",1);
    if(!src.data){
        cout<<"Image not found"<<endl;
        exit(0);
    }
    Mat grow=Region_Growing(src);

    return 0;

}

void cores(int &B,int &G,int &R,int cont){
    if(cont==0){
        R = 255;
        B = 0;
        G = 0;
    }
    else if(cont==1){
        R = 0;
        B = 255;
        G = 0;
    }
    else if(cont==2){
        R=0;
        B=0;
        G=255;
    }
    else if (cont%2!=0){
        R = R + 5*cont;
        B = B + 25*cont;
        G = G + 17*cont;
    }
    else if(cont%2==0){
        R = R+ 8;
        B = B+ 17*cont;
        G = G+ 25*(cont+1);
    }
    else if(R==255||B==255||G==255){
        R=8;
        B=9;
        G=10;
    }
}


Mat Region_Growing(Mat src){
    int i,j;
    int i2,j2;
    int cont=0;
    int B=255,G=0,R=0;

    Mat grow(src.rows,src.cols,CV_8UC1);
    Mat img_gray;
    cvtColor(src, img_gray, CV_RGB2GRAY);
    Mat_<Vec3b> img_color(src.rows,src.cols,CV_8UC3);

    for(int i=0;i<grow.rows;i++){
        for(int j=0;j<grow.cols;j++){
            grow.at<uchar>(i,j)=0;
            img_color(i,j)[0]=0;
            img_color(i,j)[1]=0;
            img_color(i,j)[2]=0;
        }
    }

    for(int i2=0;i2<img_gray.rows;i2++){
        for(int j2=0;j2<img_gray.cols;j2++){
            if((img_gray.at<uchar>(i2,j2)==0)&&(grow.at<uchar>(i2,j2)==0)){
                grow.at<uchar>(i2,j2)=255;
                cores(B,G,R,cont);
                int maiori=i2,maiorj=j2,menori=i2,menorj=j2;
                cont++;

                int atual=0,anterior=1;
                while(atual!=anterior){
                    anterior=atual;
                    atual=0;

                    for(int i=0;i<grow.rows;i++){
                        for(int j=0;j<grow.cols;j++){
                            if(grow.at<uchar>(i,j)==255){
                                if((img_gray.at<uchar>(i+1,j-1)<127)&&(grow.at<uchar>(i+1,j-1)!=255)){
                                    grow.at<uchar>(i+1,j-1)=255;
                                    img_color(i+1,j-1)[0]= B;
                                    img_color(i+1,j-1)[1]= G;
                                    img_color(i+1,j-1)[2]= R;
                                    if (maiori<i+1)maiori=i+1;
                                    if (maiorj<j-1)maiorj=j-1;
                                    if (menori>i+1)menori=i+1;
                                    if (menorj>j-1)menorj=j-1;
                                    atual++;
                                }
                                if((img_gray.at<uchar>(i,j-1)<127)&&(grow.at<uchar>(i,j-1)!=255)){
                                    grow.at<uchar>(i,j-1)=255;
                                    img_color(i,j-1)[0]=B;
                                    img_color(i,j-1)[1]=G;
                                    img_color(i,j-1)[2]=R;
                                    if (maiori<i)maiori=i;
                                    if (maiorj<j-1)maiorj=j-1;
                                    if (menori>i)menori=i;
                                    if (menorj>j-1)menorj=j-1;
                                    atual++;
                                }
                                if((img_gray.at<uchar>(i-1,j-1)<127)&&(grow.at<uchar>(i-1,j-1)!=255)){
                                    grow.at<uchar>(i-1,j-1)=255;
                                    img_color(i-1,j-1)[0]=B;
                                    img_color(i-1,j-1)[1]=G;
                                    img_color(i-1,j-1)[2]=R;
                                    if (maiori<i-1)maiori=i-1;
                                    if (maiorj<j-1)maiorj=j-1;
                                    if (menori>i-1)menori=i-1;
                                    if (menorj>j-1)menorj=j-1;
                                    atual++;
                                }
                                if((img_gray.at<uchar>(i+1,j)<127)&&(grow.at<uchar>(i+1,j)!=255)){
                                    grow.at<uchar>(i+1,j)=255;
                                    img_color(i+1,j)[0]=B;
                                    img_color(i+1,j)[1]=G;
                                    img_color(i+1,j)[2]=R;
                                    if (maiori<i+1)maiori=i+1;
                                    if (maiorj<j)maiorj=j;
                                    if (menori>i+1)menori=i+1;
                                    if (menorj>j)menorj=j;
                                    atual++;
                                }
                                if((img_gray.at<uchar>(i+1,j+1)<127)&&(grow.at<uchar>(i+1,j+1)!=255)){
                                    grow.at<uchar>(i+1,j+1)=255;
                                    img_color(i+1,j+1)[0]=B;
                                    img_color(i+1,j+1)[1]=G;
                                    img_color(i+1,j+1)[2]=R;
                                    if (maiori<i+1)maiori=i+1;
                                    if (maiorj<j+1)maiorj=j+1;
                                    if (menori>i+1)menori=i+1;
                                    if (menorj>j+1)menorj=j+1;
                                    atual++;
                                }
                                if((img_gray.at<uchar>(i,j+1)<127)&&(grow.at<uchar>(i,j+1)!=255)){
                                    grow.at<uchar>(i,j+1)=255;
                                    img_color(i,j+1)[0]=B;
                                    img_color(i,j+1)[1]=G;
                                    img_color(i,j+1)[2]=R;
                                    if (maiori<i)maiori=i;
                                    if (maiorj<j+1)maiorj=j+1;
                                    if (menori>i)menori=i;
                                    if (menorj>j+1)menorj=j+1;
                                    atual++;
                                }
                                if((img_gray.at<uchar>(i-1,j+1)<127)&&(grow.at<uchar>(i-1,j+1)!=255)){
                                    grow.at<uchar>(i-1,j+1)=255;
                                    img_color(i-1,j+1)[0]=B;
                                    img_color(i-1,j+1)[1]=G;
                                    img_color(i-1,j+1)[2]=R;
                                    if (maiori<i-1)maiori=i-1;
                                    if (maiorj<j+1)maiorj=j+1;
                                    if (menori>i-1)menori=i-1;
                                    if (menorj>j+1)menorj=j+1;
                                    atual++;
                                }
                                if((img_gray.at<uchar>(i-1,j)<127)&&(grow.at<uchar>(i-1,j)!=255)){
                                    grow.at<uchar>(i-1,j)=255;
                                    img_color(i-1,j)[0]=B;
                                    img_color(i-1,j)[1]=G;
                                    img_color(i-1,j)[2]=R;
                                    if (maiori<i-1)maiori=i-1;
                                    if (maiorj<j)maiorj=j;
                                    if (menori>i-1)menori=i-1;
                                    if (menorj>j)menorj=j;
                                    atual++;
                                }
                            }
                        }
                    }
                    imshow("Region Growing",img_color);
                    waitKey(30);
                }

                cout<<maiori<<endl<<menori<<endl<<maiorj<<endl<<menorj<<endl;

                Mat window((maiori-menori),(maiorj-menorj),CV_8UC1);
                for (int a=0; a<window.rows; a++) {
                    for (int b=0; b<window.cols; b++) {
                        window.at<uchar>(a,b)=0;
                    }
                }

                int i3=0;
                for (int z=menori; z<maiori; z++) {
                    int j3=0;
                    for (int w=menorj; w<maiorj; w++) {
                        window.at<uchar>(i3,j3)=grow.at<uchar>(z,w);
                        j3++;
                    }
                    i3++;
                }
                char name[50];
                char endereco[200];
                sprintf(name, "Objeto_%d",cont);
                sprintf(endereco,"../Results/Objeto_%d.jpg",cont);
                imshow("Objeto", window);
                imwrite(endereco, window);
                waitKey(0);
            }
        }
    }
    printf("\nForam detectados %d objetos",cont);
    imwrite("../Results/Region_growing.jpg", grow);
    imwrite("../Results/Region_growing_color.jpg", img_color);
    return grow;
}
