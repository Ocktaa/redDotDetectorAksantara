#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;


/////////////// Importing Images /////////////
void getContours(Mat imgDil, Mat img){

	vector <vector<Point>> contours;
	vector <Vec4i> hierarchy;
	

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);


	for (int i = 0; i < contours.size(); ++i) {

		vector <vector<Point>> conPoly(contours.size());
		vector<Rect> boundRect(contours.size());

		int area = contourArea(contours[i]);
		cout << area << endl;
		
		if (area > 1000) {
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			cout << conPoly[i].size() << endl;
			//boundRect[i] = boundingRect(conPoly[i]);
			//rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);

			int objCorner = (int)conPoly[i].size();

			if (objCorner == 3) {

			}


		}
	}



}


void main() {
	string path = "Resources/shapes.png";
	Mat img = imread(path);
	VideoCapture cap(0);
	Mat img;

	while (true) {
		cap.read(img);
		imshow("Video", img);
		waitKey(1);

	}
	
	Mat imgGray, imgBlur, imgCanny, imgDia;

	// Preprocessing
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDia, kernel);

	getContours(imgDia, img);

	imshow("Image", img);
	//imshow("Image Gray", imgGray);
	//imshow("Image Blur", imgBlur);
	//imshow("Image Canny", imgCanny);
	//imshow("Image Dilate", imgDia);

	waitKey(0);

}

