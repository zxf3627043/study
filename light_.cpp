#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
int main()
{
Mat src = imread("ori1.jpg", 1);
Mat dst = Mat(src.size(), src.type());
for (int i = 0; i < src.rows; i++) {
 
			for (int j = 0; j < src.cols; j++) {
				double B = src.at<vec3b>(i, j)[0];
				double G = src.at<vec3b>(i, j)[1];
				double R = src.at<vec3b>(i, j)[2];
 
				double alpha_r = R / (R + G + B);
				double alpha_g = G / (R + G + B);
				double alpha_b = B / (R + G + B);
 
				double alpha = Math.max(Math.max(alpha_r, alpha_g), alpha_b);
				double MaxC = Math.max(Math.max(R, G), B);
				double minalpha = Math.min(Math.min(alpha_r, alpha_g), alpha_b);
				double beta_r = 1 - (alpha - alpha_r) / (3 * alpha - 1);
				double beta_g = 1 - (alpha - alpha_g) / (3 * alpha - 1);
				double beta_b = 1 - (alpha - alpha_b) / (3 * alpha - 1);
				double beta = Math.max(Math.max(beta_r, beta_g), beta_b);
				double gama_r = (alpha_r - minalpha) / (1 - 3 * minalpha);
				double gama_g = (alpha_g - minalpha) / (1 - 3 * minalpha);
				double gama_b = (alpha_b - minalpha) / (1 - 3 * minalpha);
				double gama = Math.max(Math.max(gama_r, gama_g), gama_b);
 
				double temp = (gama * (R + G + B) - MaxC) / (3 * gama - 1);
 
				double[] data = new double[3];
				data[0] = B - (temp + 0.5);
				data[1] = G - (temp + 0.5);
				data[2] = R - (temp + 0.5);
				dst.put(i, j, data);
			}
		}
     imshow("res", dst);
     while(1){
     waitKey();
}
 return 0;
}

 