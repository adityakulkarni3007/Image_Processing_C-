#include <stdio.h>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

#include "opencv2/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 200;
int max_thresh = 250;
RNG rng(12345);
int main(int, char** argv)
{
    src = imread("1.jpg", IMREAD_COLOR);
    cvtColor(src, src_gray, cv::ColorConversionCodes::COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));
    const char* source_window = "Source";
    namedWindow(source_window, WINDOW_AUTOSIZE);
    imshow(source_window, src);
    // createTrackbar(" Threshold:", "Source", &thresh, max_thresh, thresh_callback);
     //thresh_callback(0, 0);*/
     //waitKey(0);
     //return(0);
    Mat thresh;
    threshold(src_gray, thresh, 125, 200, THRESH_BINARY);
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(thresh, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    Mat image_copy = src.clone();
    drawContours(image_copy, contours, 5, Scalar(0, 255, 0), 1);
    imshow("Img", image_copy);


    imshow("Binary mage", thresh);
    waitKey(0);
    destroyAllWindows();
}