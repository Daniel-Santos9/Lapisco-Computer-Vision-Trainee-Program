#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main(){

    Mat src = imread("../img.png");
    if(!src.data){
        cout<<"Image not found"<<endl;
        exit(0);
    }
    Mat img_gray;
    Mat img_Canny;
    double area;
    vector<vector<Point> > contours;

    cvtColor(src,img_gray, CV_RGB2GRAY);
    //blur(img_gray,img_gray,Size(5,5));

    Canny(img_gray,img_Canny,100,127,3);
    threshold(img_Canny,img_Canny,127,255,CV_THRESH_BINARY);
    namedWindow("Canny",CV_WINDOW_NORMAL);
    imshow("Canny",img_Canny);
    waitKey(0);
    destroyWindow("Canny");

    findContours(img_Canny, contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
    cout<<"Existe "<<contours.size()<<" contornos!"<<endl;

    vector<vector<Point> > contours_p(contours.size());
    vector<Rect> bRect(contours.size());
    for(int i=0; i<contours.size(); i++ ){
        approxPolyDP( Mat(contours[i]), contours_p[i], 3, true );
        bRect[i] = boundingRect( Mat(contours_p[i]) );
    }


    Mat drawing = Mat::zeros( img_Canny.size(), CV_8UC3);
    int cont=0;
    char nome[100];
    char namefile[200];
    for (int i=0; i<contours.size();i++){
            drawContours(drawing, contours_p, i, Scalar(0,255,0));
            rectangle(drawing, Point(bRect[i].tl().x,bRect[i].tl().y), Point(bRect[i].br().x,bRect[i].br().y), Scalar(255,0,0));
            area = contourArea(contours_p[i]);
            cout<<"Area do contorno "<< (i+1) <<" = "<<area<<endl;


            //rectangle( drawing, bRect[i].tl(), bRect[i].br(),Scalar(255,0,0), 2, 2, 0 );

            Mat_<uchar> gray;
            cvtColor(drawing,gray,CV_RGB2GRAY);
            Mat_<uchar> janela(bRect[i].br().y-bRect[i].tl().y,bRect[i].br().x-bRect[i].tl().x,1);
            int y,x;
            int y2=0,x2=0;
            for(x=bRect[i].tl().y;x< bRect[i].br().y;x++){
                y2=0;
                for(y=bRect[i].tl().x;y< bRect[i].br().x;y++){
                    janela.at<uchar>(x2,y2)=gray.at<uchar>(x,y);
                    y2++;
                }
                x2++;
            }
            cont++;
            sprintf(nome,"obejto_%d.jpg",cont);
            imshow(nome,janela);
            sprintf(namefile,"../Results/objeto_%d.jpg",cont);
            imwrite(namefile,janela);
    }
    namedWindow("Contours",CV_WINDOW_NORMAL);
    imshow("Contours",drawing);
    waitKey(0);
    destroyWindow("Contours");

    imwrite("../Results/contours.jpg",img_Canny);
    imwrite("../Results/DrawingRect.jpg",drawing);

    return 0;

}
