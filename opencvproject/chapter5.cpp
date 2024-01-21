#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;


/////////////// Warp Prespective /////////////
const float w = 250, h = 350;
Mat matrix, imgWarp;
void main() {

	string path = "Resources/cards.jpg";

	Mat img = imread(path);

	

	Point2f src[4] = { {780,110}, {1016, 84}, {851, 352}, {1111, 326} };
	Point2f dst[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f, h}, {w, h} };

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	for (int i = 0; i < 4; ++i)
		circle(img, src[i], 10, Scalar(0, 69, 255), FILLED);



	imshow("Image", img);
	imshow("Image warp", imgWarp);
	waitKey(0);
}