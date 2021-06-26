

#include<opencv2/opencv.hpp>
#include<iostream>

    using namespace std;
    using namespace cv;

    void main()
    {
        Mat srcImg = imread("1.jpg", IMREAD_COLOR);
        Mat src_gray;

        Mat thresh, image_copy;
        cvtColor(srcImg, src_gray, COLOR_BGR2GRAY);
        medianBlur(src_gray, src_gray, 3);
        threshold(src_gray, thresh,100,150,THRESH_BINARY);

        Mat kernel = getStructuringElement(MORPH_RECT, Size(2,2));
        erode(thresh, thresh, kernel);
        vector<vector<Point>> contours;
        vector<Vec4i> hierarcy;
        findContours(thresh, contours, hierarcy, RETR_TREE, CHAIN_APPROX_SIMPLE);
        vector<vector<Point>> contours_poly(contours.size());//for storing polyline points
        for (int i = 0; i < contours.size(); i++)
        {
            int area = contourArea(contours[i]);
            if (area >500)  {           
                approxPolyDP(Mat(contours[i]), contours_poly[i], 10, true);
                cout << contours_poly[i].size() << endl;
                image_copy = srcImg.clone();
                if (contours_poly[i].size() == 2) {
                    drawContours(srcImg, contours, i, Scalar(255, 0, 0), 2, 8); //Draw
                }
            }
        }
        imshow("approx", srcImg);
        imshow("s", image_copy);
        imshow("Mask", thresh);
        waitKey(0);
    }

