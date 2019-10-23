#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
 
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
using namespace cv;
 
namespace {
/** Global Variables */
	double alpha = 1.0; /*< Simple contrast control */
	int beta = 0;       /*< Simple brightness control */
	int gamma_cor = 100;
	double getPSNR_val = 0;
 
	Mat ResizedImg, ResizedNewImg, ShaprenImg, img_gamma_corrected;
 
 
	/* Peak Signal to Noise Ratio */
	double getPSNR(const Mat &I1, const Mat &I2) {
//	the original image is I1 and the sharpen image is I2
		Mat s1;
		absdiff(I1, I2, s1);       // |I1 - I2|
		s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits
		s1 = s1.mul(s1);           // |I1 - I2|^2
 
		Scalar s = sum(s1);        // sum elements per channel
 
		double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels
 
		if (sse <= 1e-10) // for small values return zero
			return 0;
		else {
			double mse = sse / (double) (I1.channels() * I1.total());
			double psnr = 10.0 * log10((255 * 255) / mse);
			return psnr;
		}
	}
 
	void gammaCorrection(const Mat &img, const double gamma_) {
		CV_Assert(gamma_ >= 0);
		//! [changing-contrast-brightness-gamma-correction]
		Mat lookUpTable(1, 256, CV_8U);
		uchar *p = lookUpTable.ptr();
		for (int i = 0; i < 256; ++i)
			p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);
 
		Mat res = img.clone();
		LUT(img, lookUpTable, res);
		//! [changing-contrast-brightness-gamma-correction]
 
		hconcat(img, res, img_gamma_corrected);
 
		imshow("Gamma correction", img_gamma_corrected);
 
	}
 
	void on_gamma_correction_trackbar(int, void *) {
		double gamma_value = gamma_cor / 100.0;
		gammaCorrection(ResizedImg, gamma_value);
//		getPSNR_val = getPSNR(ResizedImg, img_gamma_corrected);
//		cout << "When gamma =  " << gamma_value << "    , PSNR =  " << getPSNR_val << endl;
	}
 
}
 
int main(int argc, char **argv) {
/**
 * @function main
 * @brief Main function
 */
	/// Read image given by user
	//! [basic-linear-transform-load]
//	CommandLineParser parser( argc, argv, "/Users/haowang/Standard Pictures/111548040079_.pic_hd.jpg" );
	Mat img = imread("ori1.jpg", 1);
	if (img.empty()) {
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << "inputImg" << endl;
		return -1;
	} 
    double gamma_ = 3.5;
    CV_Assert(gamma_>= 0);
		//! [changing-contrast-brightness-gamma-correction]
		Mat lookUpTable(1, 256, CV_8U);
		uchar *p = lookUpTable.ptr();
		for (int i = 0; i < 256; ++i)
		p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);
 
		Mat res = img.clone();
		LUT(img, lookUpTable, res);
		//! [changing-contrast-brightness-gamma-correction]
 
		//hconcat(img, res, img_gamma_corrected);
 
		//imshow("Gamma correction", img_gamma_corrected);
// Show stuff
 
	  namedWindow("Original Image", WINDOW_NORMAL); //creat windows
	  namedWindow("New Image", WINDOW_NORMAL);
	//namedWindow("Sharpen Image", WINDOW_NORMAL);
	//namedWindow("Gamma correction", WINDOW_NORMAL);
 
	imshow("Original Image", img);
	imshow("New Image", res);
	//imshow("Sharpen Image", ShaprenImg);
 
	//createTrackbar("Gamma correction", "Gamma correction", &gamma_cor, 200, on_gamma_correction_trackbar);
 
	//on_gamma_correction_trackbar(0, 0);
 
	/// Wait until user press some key
  while(1){
	waitKey();
}
	//! [basic-linear-transform-display]
	return 0;
}
