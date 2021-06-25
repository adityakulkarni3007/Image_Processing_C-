#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

void main() {
	Mat src = imread("6.jpg", IMREAD_COLOR);
	resize(src, src, cv::Size(), 0.3, 0.3);
	Mat thresh, src_gray, image_copy;
	cvtColor(src, src_gray, COLOR_BGR2GRAY);
	medianBlur(src_gray, src_gray, 3);
	Mat dst,src_copy;
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
	clahe->setClipLimit(4);
	clahe->apply(src_gray, dst);

	cv::Rect myROI(20,50,370,370);
	cv::Mat croppedImage = dst(myROI);
	src = src(myROI);
	image_copy = croppedImage.clone();

	threshold(croppedImage, thresh, 50, 250, THRESH_BINARY_INV);
	src_copy = src.clone();
	vector<vector<Point>> contours;
	vector<Vec4i> hierarcy;
	findContours(thresh, contours, hierarcy, RETR_TREE, CHAIN_APPROX_SIMPLE);
	drawContours(image_copy, contours,-1, Scalar(0, 255, 0), 2, 8);
	vector<vector<Point> > contours_poly(contours.size());
	vector<Rect> boundRect(contours.size());
	for (size_t i = 0; i < contours.size(); i++)
	{
		approxPolyDP(contours[i], contours_poly[i], 3, true);
		boundRect[i] = boundingRect(contours_poly[i]);
	}
	for (size_t i = 0; i < contours.size(); i++)
	{
		//drawContours(image_copy, contours_poly, (int)i, color);
		rectangle(src, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,0), 2);
	}

	imshow("Og", src_copy);
	imshow("Box", src);
	imshow("Mask",thresh);
	imshow("Contour", image_copy);
	waitKey(0);
}