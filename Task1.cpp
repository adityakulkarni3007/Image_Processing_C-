#include <iostream>
#include <stdio.h>
#include <vector>
#include <thread>
#include <opencv2/opencv.hpp>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
using namespace std;


using namespace cv;

Mat src, src_gray;
Mat dst, detected_edges;

int threshold_value = 11;
int threshold_type = 0;;
int  max_value = 255;
int  max_type = 4;

const char* window_name = "CCC";

int main(int argc, char* argv[])
{
        Mat src = imread("1.jpg", IMREAD_COLOR);
        namedWindow(window_name);
        //cvMoveWindow(window_name, 5, 5);

        int MAX = 56;
        //createTrackbar("MAX", window_name, &MAX, 300);
        int MIN = 52;
        //createTrackbar("MIN", window_name, &MIN, 300);
        int BLACKLEVEL = 47;

        cvtColor(src, src_gray, COLOR_RGB2GRAY);

        medianBlur(src_gray, src_gray, 1);


        threshold(src_gray, dst, 11, 255, 0); //tareshold
        vector<Vec3f> circles;
        HoughCircles(dst, circles, HOUGH_GRADIENT, 1, dst.rows/8, 20, 7, MIN, MAX);

        for (size_t i = 0; i < circles.size(); i++)
        {

            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            
            int radius = cvRound(circles[0][2]);
            circle(src, center, 2, Scalar(30, 255, 140), -1, 1, 0);
            circle(src, center, radius, Scalar(30, 255, 0), 1, 10, 0);
                
            break;
        }

        imshow(window_name, src);
        //imshow("HSV", dst);
        waitKey(0);

 


    return 0;

}
