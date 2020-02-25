#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace cv;
using namespace std;

void abrirFileMoments(char *addr){

    FILE *file = fopen(addr, "w");
    fclose(file);

}

void abrirFileTime(char *addr){

    FILE *file = fopen(addr, "w");
    fclose(file);

}


int main(){

    FILE *file, *tempos;
    char addr_moments[100] = "../Results/Moments.txt";
    char addr_times[100] = "../Results/Times.txt";
    double moments_HU[7];
    clock_t temp[2];
    abrirFileMoments(addr_moments);
    abrirFileTime(addr_times);

    Mat src,img_gray;
    int x =0;
    while(x<10){

        temp[0]=clock();
        x++;

        char add[10];
        sprintf(add,"../img/%d.jpg",x);
        cout<<add<<endl;

        src = imread(add);
        if(!src.data){
            cout<<"Image not found"<<endl;
            exit(0);
        }

        cvtColor(src, img_gray, CV_RGB2GRAY);
        file = fopen(addr_moments,"a");
        Moments momentos = moments(img_gray, true);
        HuMoments(momentos,moments_HU);
        for(int i=0; i<7; i++){

            if(i!=6){
                fprintf(file, "%f,",moments_HU[i]);
                cout<<moments_HU[i]<<endl;
            }
            else{
                fprintf(file, "%f", moments_HU[i]);
                cout<<moments_HU[i]<<endl;
            }
        }

        fprintf(file, "\n");
        cout<<"\n";
        fclose(file);
        temp[1]=clock();
        double time = (temp[0]-temp[1])*1000.0/CLOCKS_PER_SEC;
        tempos=fopen(addr_times,"a");
        fprintf(tempos, "%f\n",time);
        fclose(tempos);
    }
    return 0;
}
