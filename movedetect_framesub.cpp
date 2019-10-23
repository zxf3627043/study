///�˶������⡪��֡�  
#include"opencv2/opencv.hpp"  
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;  
#include <iostream>  
using namespace std;  
//�˶������⺯������  
Mat MoveDetect(Mat temp, Mat frame);  

int main()  
{  

//    VideoCapture video(0);
//    if(!video.isOpened())
//    return -1;
    VideoCapture capture("video_night1.mp4");
   // VideoCapture video(0);//����VideoCapture��video  
   // if (!video.isOpened())  //��video�����쳣���  
   // {  
    //    cout << "video open error!" << endl;  
    //    return 0;  
   // }  
    while(1)
{
    int frameCount = capture.get(CV_CAP_PROP_FRAME_COUNT);//��ȡ֡��  
    double FPS = capture.get(CV_CAP_PROP_FPS);//��ȡFPS  
    Mat frame;//�洢֡  
    Mat temp;//�洢ǰһ֡ͼ��  
    Mat result;//�洢���ͼ��  
    for (int i = 0; i < frameCount; i++)  
    {  

        capture >> frame;//��֡��frame  
        //imshow("frame", frame);  
        if (frame.empty())//��֡�����쳣���  
        {  
            cout << "frame is empty!" << endl;  
            break;  
        }  
        if (i == 0)//���Ϊ��һ֡��temp��Ϊ�գ�  
        {  
            result = MoveDetect(frame, frame);//����MoveDetect()�����˶������⣬����ֵ����result  
        }  
        else//�����ǵ�һ֡��temp��ֵ�ˣ�  
        {  
            result = MoveDetect(temp, frame);//����MoveDetect()�����˶������⣬����ֵ����result  

        }  
        imshow("result", result);  
        if (waitKey(1000.0 / FPS) == 27)//��ԭFPS��ʾ  
        {  
            cout << "ESC�˳�!" << endl;  
            break;  
        }  
        temp = frame.clone();  
    } 
} 
    return 0;  

}  
Mat MoveDetect(Mat temp, Mat frame)  
{  
    Mat result = frame.clone();  
    //1.��background��frameתΪ�Ҷ�ͼ  
    Mat gray1, gray2;  
    cvtColor(temp, gray1, CV_BGR2GRAY);  
    cvtColor(frame, gray2, CV_BGR2GRAY);  
    //2.��background��frame����  
    Mat diff;  
    absdiff(gray1, gray2, diff);  
    //imshow("diff", diff);  
    //3.�Բ�ֵͼdiff_thresh������ֵ������  
    Mat diff_thresh;  
    threshold(diff, diff_thresh, 25, 255, CV_THRESH_BINARY);  
    imshow("diff_thresh", diff_thresh);  
    //4.��ʴ  
    Mat kernel_erode = getStructuringElement(MORPH_RECT, Size(3, 3));  
    Mat kernel_dilate = getStructuringElement(MORPH_RECT, Size(18, 18));  
    erode(diff_thresh, diff_thresh, kernel_erode);  
    //imshow("erode", diff_thresh);  
    //5.����  
    dilate(diff_thresh, diff_thresh, kernel_dilate);  
    dilate(diff_thresh, diff_thresh, kernel_dilate);
    dilate(diff_thresh, diff_thresh, kernel_dilate);
    //imshow("dilate", diff_thresh);  
    //6.������������������  
    vector<vector<Point> > contours;  
    findContours(diff_thresh, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);  
    drawContours(result, contours, -1, Scalar(0, 0, 255), 2);//��result�ϻ�������  
    //7.��������Ӿ���  
    vector<Rect> boundRect(contours.size());  
    for (int i = 0; i < contours.size(); i++)  
    {  
        boundRect[i] = boundingRect(contours[i]);  
        rectangle(result, boundRect[i], Scalar(0, 255, 0), 2);//��result�ϻ�������Ӿ���  
    }  
    return result;//����result  
} 
