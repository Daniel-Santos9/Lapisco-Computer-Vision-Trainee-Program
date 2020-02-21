#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    FILE *arq;
    char val2[5000];
    int val, rows=-1,cols=-1;
    arq=fopen("../Image.txt","r");


    if(arq == NULL){
       cout<<"Problema na abertura do arquivo"<<endl;
       exit(0);
    }

    while(!feof(arq)){
        fgets(val2,5000,arq);
        rows++;
    }
    fclose(arq);


    arq=fopen("../Image.txt","r");


    if(arq == NULL){
       cout<<"Problema na abertura do arquivo"<<endl;
        exit(0);
    }

    while(!feof(arq)){
        fscanf(arq,"%d",&val);
        cols++;
    }

    cols=cols/rows;

    fclose(arq);
    cout<<"Linhas: "<<rows<<endl<<"Colunas: "<<cols<<endl;
    system("pause");
    arq=fopen("../Image.txt","r");

    if(arq == NULL){
       cout<<"Problema na abertura do arquivo"<<endl;
        exit(0);
    }

    Mat_<uchar> image(rows,cols,1);

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){

            fscanf(arq,"%d",&val);
            image.at<uchar>(i,j)=val;

        }
    }

    fclose(arq);

    namedWindow("Imagem lida");
    imshow("Imagem lida", image);
    waitKey(0);
    destroyWindow("Imagem linda");

    imwrite("../Results/imagem_lida.jpg",image);


    return 0;
}
