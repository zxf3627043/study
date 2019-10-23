#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;
int main( )
{
    Mat image;
    image = imread("/home/zhangxf/opencv-2.4.13/modules/ocl/doc/images/adaptiveBilateralFilter.jpg", 1 );//目录按照自己的目录
    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}
