#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string.h>
#include <time.h>

using namespace std;
using namespace cv;

void glcm(Mat &img, char *address){
    FILE *file;

    float energy=0,contrast=0,homogenity=0;
    float IDM=0,entropy=0, dissimilarity=0;
    float asm1=0, correlation=0;
    float mean1=0, mean2=0, omegai=0, omegaj=0;
    float variance=0,sumEntropy=0,sumVariance=0,sumAverage=0;
    float diferenceEntropy=0,diferenceVariance=0;

    int row=img.rows,col=img.cols;
    Mat gl=Mat::zeros(256,256,CV_32FC1);

    //creating glcm matrix with 256 levels,radius=1 and in the horizontal direction
    for(int i=0;i<row;i++)
        for(int j=0;j<col-1;j++)
            gl.at<float>(img.at<uchar>(i,j),img.at<uchar>(i,j+1))=gl.at<float>(img.at<uchar>(i,j),img.at<uchar>(i,j+1))+1;

    // normalizing glcm matrix for parameter determination
    gl=gl+gl.t();
    gl=gl/sum(gl)[0];


    for(int i=0;i<256;i++){
        for(int j=0;j<256;j++){
            contrast=contrast+(i-j)*(i-j)*gl.at<float>(i,j);
            homogenity=homogenity+gl.at<float>(i,j)/(1+abs(i-j)); // No denominador È ( i - j ) ao quadrado //
            dissimilarity=dissimilarity+gl.at<float>(i,j)*(abs(i-j));
            asm1=asm1+(gl.at<float>(i,j)*gl.at<float>(i,j));
            energy=energy+sqrt(asm1);

            if(i!=j){
                IDM=IDM+gl.at<float>(i,j)/((i-j)*(i-j)); //Taking k=2; // IDM no artigo o denominador È (1 + (i-j)^2)
            }
            if(gl.at<float>(i,j)!=0){
                entropy=entropy-gl.at<float>(i,j)*log10(gl.at<float>(i,j));
            }
            mean1=mean1+i*gl.at<float>(i,j);
            mean2=mean2+j*gl.at<float>(i,j);
            omegai=omegai+sqrt(gl.at<float>(i,j)*(i-mean1)*(i-mean2));
            omegaj=omegaj+sqrt(gl.at<float>(i,j)*(j-mean2)*(j-mean2));
            if (omegai!=0 && omegaj!=0){
                correlation=correlation+((((i*j)*(gl.at<float>(i,j)))-(mean1*mean2))/(omegai*omegaj));
            }
            variance+=((i-(mean1+mean2)/2)*(i-(mean1+mean2)/2))*gl.at<float>(i,j);
            for (int s=2; s<513; s++) {
                if (i+j==s && gl.at<float>(s)>0) {
                    sumEntropy+=(-1)*(gl.at<float>(s))*log10((gl.at<float>(s)));
                    sumVariance+=(i-sumEntropy)*(i-sumEntropy)*(gl.at<float>(s));
                    sumAverage+=i*(gl.at<float>(s));
                }
            }
            for (int s=0; s<256; s++) {
                if (i-j==s && gl.at<float>(s)>0) {
                    diferenceEntropy+=(-1)*(gl.at<float>(s))*log10(gl.at<float>(s));
                    diferenceVariance+=((i-(mean1+mean2)/2)*(i-(mean1+mean2)/2))*gl.at<float>(s);
                }
            }
        }
    }
    //Results
    cout<<"energy="<<energy<<endl;
    cout<<"contrast="<<contrast<<endl;
    cout<<"homogenity="<<homogenity<<endl;
    cout<<"IDM="<<IDM<<endl;
    cout<<"entropy="<<entropy<<endl;
    cout<<"dissimilarity="<<dissimilarity<<endl;
    cout<<"AngularSecondMoment="<<asm1<<endl;
    cout<<"correlation="<<correlation<<endl;
    cout<<"variance="<<variance<<endl;
    cout<<"sumEntropy="<<sumEntropy<<endl;
    cout<<"sumVariance="<<sumVariance<<endl;
    cout<<"sumAverage="<<sumAverage<<endl;
    cout<<"diferenceEntropy="<<diferenceEntropy<<endl;
    cout<<"diferenceVariance="<<diferenceVariance<<endl<<endl<<endl;

    file=fopen(address, "a");
    fprintf(file,"%f,",entropy);
    fprintf(file,"%f,",energy);
    fprintf(file,"%f,",homogenity);
    fprintf(file,"%f,",contrast);
    fprintf(file,"%f,",IDM);
    fprintf(file,"%f,",dissimilarity);
    fprintf(file,"%f,",asm1);
    fprintf(file,"%f,",correlation);
    fprintf(file,"%f,", variance);
    fprintf(file,"%f,", sumEntropy);
    fprintf(file,"%f,", sumVariance);
    fprintf(file,"%f,", sumAverage);
    fprintf(file,"%f,", diferenceEntropy);
    fprintf(file,"%f\n", diferenceVariance);
    fclose(file);
}

void abrirFileGLCM(char *addr){

    FILE *file = fopen(addr, "w");
    fclose(file);

}

void abrirFileTime(char *addr){

    FILE *file = fopen(addr, "w");
    fclose(file);

}


int main(){
    FILE *tempo;
    char addr_GLCM[100] = "../Results/GLCM.txt";
    char addr_times[100] = "../Results/Times.txt";
    clock_t temp[2];
    abrirFileGLCM(addr_GLCM);
    abrirFileTime(addr_times);
    Mat image;
    int x=0;
    while (x<10) {
        temp[0]=clock();
        x++;
        char add[200];
        sprintf(add, "../img/%d.jpg",x);
        image= imread(add,IMREAD_COLOR);
        if(!image.data){
            cout<<"Image not found!"<<endl;
            exit(0);
        }
        cvtColor(image, image, CV_RGB2GRAY);

        glcm(image,addr_GLCM);

        temp[1]=clock();
        double Time= (temp[1]-temp[0])*1000.0/CLOCKS_PER_SEC;
        tempo=fopen(addr_times, "a");
        fprintf(tempo, "%f\n",Time);
        fclose(tempo);
    }
}
