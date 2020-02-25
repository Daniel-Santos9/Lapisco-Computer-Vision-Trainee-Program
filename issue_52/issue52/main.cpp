#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/nonfree/nonfree.hpp"
#include <opencv2/features2d/features2d.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <fstream>
#include <string.h>
#include <time.h>


using namespace std;
using namespace cv;

int main(){

    Mat img_1 = imread("../img/1.jpg",0);
    Mat img_2 = imread("../img/2.jpg",0);

    SiftFeatureDetector detector(100);

    vector<KeyPoint> keypoints_1;
    vector<KeyPoint> keypoints_2;

    detector.detect(img_1,keypoints_1);
    detector.detect(img_2,keypoints_2);
    SurfDescriptorExtractor extractor;

    Mat descriptors_1, descriptors_2;

    extractor.compute(img_1, keypoints_1, descriptors_1 );
    extractor.compute(img_2, keypoints_2, descriptors_2 );

    BFMatcher matcher(NORM_L2);
    vector< DMatch > matches;
    matcher.match( descriptors_1, descriptors_2, matches );

    Mat img_matches;
    drawMatches( img_1, keypoints_1, img_2, keypoints_2, matches, img_matches );

    imshow("Matches", img_matches );
    waitKey(0);
    destroyAllWindows();
    return 0;
}
