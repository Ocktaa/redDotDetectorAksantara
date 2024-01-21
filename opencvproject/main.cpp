#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>


using namespace std;
using namespace cv;

const int max_value_H = 360 / 2;
const int max_value = 255;
const String window_capture_name = "Video Capture";
const String window_detection_name = "Object Detection";

// Ini nanti di set sesuai yang dapet dari trackbarnya, gr" warnanya merah doang tinggal atur saturationnya, 
// tapi klo warnanya lebih banyak harus lebih ati" ngatur rangenya

int low_H = 0, low_S = 230, low_V = 0;
int high_H = 180, high_S = 255, high_V = 255;

// To create each trackbars
// Unccoment untuk bikin trackbarnya

//static void on_low_H_thresh_trackbar(int, void*)
//{
//	low_H = min(high_H - 1, low_H);
//	setTrackbarPos("Low H", window_detection_name, low_H);
//}
//static void on_high_H_thresh_trackbar(int, void*)
//{
//	high_H = max(high_H, low_H + 1);
//	setTrackbarPos("High H", window_detection_name, high_H);
//}
//static void on_low_S_thresh_trackbar(int, void*)
//{
//	low_S = min(high_S - 1, low_S);
//	setTrackbarPos("Low S", window_detection_name, low_S);
//}
//static void on_high_S_thresh_trackbar(int, void*)
//{
//	high_S = max(high_S, low_S + 1);
//	setTrackbarPos("High S", window_detection_name, high_S);
//}
//static void on_low_V_thresh_trackbar(int, void*)
//{
//	low_V = min(high_V - 1, low_V);
//	setTrackbarPos("Low V", window_detection_name, low_V);
//}
//static void on_high_V_thresh_trackbar(int, void*)
//{
//	high_V = max(high_V, low_V + 1);
//	setTrackbarPos("High V", window_detection_name, high_V);
//}


// Function to get the countours of an object and draws the contours
void getContours(Mat frame_thres, Mat frame) {

	vector <vector<Point>> contours;
	vector <Vec4i> hierarchy;

	//Finding the contour

	findContours(frame_thres, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	 //Creating the rectangle and circle
	for (int i = 0; i < contours.size(); ++i) {
		vector<Rect> boundRect(contours.size());

		boundRect[i] = boundingRect(contours[i]);
		////////// uncomment klo mau contournya sesuai sama bentuk objeknya /////////
		// drawContours(frame, contours, i, Scalar(0, 255, 0), 2);

		rectangle(frame, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5); //bikin contour yang segi empat
		circle(frame, Point(boundRect[i].x + 62, boundRect[i].y + 62), 7, Scalar(0, 255, 0), FILLED);
	}

}


// Main function to make video
int main()
{
	string path = "Resources/red_dot.mp4";
	VideoCapture cap(path);

	namedWindow(window_capture_name);

	//////////////////// Find the HSV values for the colour //////////////////////
	
	// Uncomment klo mau bikin trackbarnya
	
	/*
	namedWindow(window_detection_name);
	//Trackbars to set thresholds for HSV values
	createTrackbar("Low H", window_detection_name, &low_H, max_value_H, on_low_H_thresh_trackbar);
	createTrackbar("High H", window_detection_name, &high_H, max_value_H, on_high_H_thresh_trackbar);
	createTrackbar("Low S", window_detection_name, &low_S, max_value, on_low_S_thresh_trackbar);
	createTrackbar("High S", window_detection_name, &high_S, max_value, on_high_S_thresh_trackbar);
	createTrackbar("Low V", window_detection_name, &low_V, max_value, on_low_V_thresh_trackbar);
	createTrackbar("High V", window_detection_name, &high_V, max_value, on_high_V_thresh_trackbar);
	*/

	Mat frame, frame_preresize, frame_gray, frame_blur, frame_canny, frame_dil, frame_HSV, frame_threshold;

	while (true) {

		cap >> frame_preresize;
		if (frame_preresize.empty())
		{
			break;
		}

		//////////////IMAGE PREPROCESSING//////////////
		// Convert from BGR to HSV colorspace
		resize(frame_preresize, frame, Size(), 0.5, 0.5);
		cvtColor(frame, frame_HSV, COLOR_BGR2HSV);
		inRange(frame_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), frame_threshold);

		////////////////// DRAW CONTOURS /////////////////
		getContours(frame_threshold, frame);


		imshow(window_capture_name, frame);
		
		waitKey(1);
	}	


	return 0;
}