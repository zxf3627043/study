/*=================================================================
 * Extract Background & Foreground Model by ViBe Algorithm using OpenCV Library.
 *
 * Copyright (C) 2017 Chandler Geng. All rights reserved.
 *
 *     This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 *     You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc., 59
 * Temple Place, Suite 330, Boston, MA 02111-1307 USA
===================================================================
*/

#include "Vibe.h"

int main(int argc, char* argv[])
{
    Mat frame, gray, FGModel;
    VideoCapture capture;
    capture = VideoCapture("/home/zhangxf/study/video_night2.mp4");
    if(!capture.isOpened())
    {
        capture = VideoCapture("/home/zhangxf/study/video_night2.mp4");
        if(!capture.isOpened())
        {
            capture = VideoCapture("/home/zhangxf/study/video_night2.mp4");
            if(!capture.isOpened())
            {
                cout<<"ERROR: Did't find this video!"<<endl;
                return 0;
            }
        }
    }

    capture.set(CV_CAP_PROP_FRAME_WIDTH,160);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,120);
    if (!capture.isOpened())
    {
        cout<<"No camera or video input!"<<endl;
        return -1;
    }

    // 绋嬪簭杩愯鏃堕棿缁熻鍙橀噺
    // the Time Statistical Variable of Program Running Time
    double time;
    double start;

    ViBe vibe;
    bool count = true;

    while (1)
    {
        capture >> frame;
        double gamma_ = 1;
        if (frame.empty())
            continue;
		  //! [changing-contrast-brightness-gamma-correction]
		    Mat lookUpTable(1, 256, CV_8U);
		    uchar *p = lookUpTable.ptr();
		    for (int i = 0; i < 256; ++i)
		    p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma_) * 255.0);
 
		    Mat res = frame.clone();
		    LUT(frame, lookUpTable, res);

        Mat result = res.clone();
        Mat dstImage;
        cvtColor(res, gray, CV_RGB2GRAY);
        if (count)
        {
            vibe.init(gray);
            vibe.ProcessFirstFrame(gray);
            cout<<"Training ViBe Success."<<endl;
            count=false;
        }
        else
        {
            start = static_cast<double>(getTickCount());
            vibe.Run(gray);
            time = ((double)getTickCount() - start) / getTickFrequency() * 1000;

            cout << "Time of Update ViBe Background: " << time << "ms" <<endl<<endl;

            FGModel = vibe.getFGModel();
      			//morphologyEx(FGModel, FGModel, MORPH_CLOSE, Mat());
            Mat element = getStructuringElement(MORPH_RECT, Size(15, 15)); //第一个参数MORPH_RECT表示矩形的卷积核，当然还可以选择椭圆形的、交叉型的
            
            erode(FGModel, FGModel, element);
            dilate(FGModel, FGModel, element);
            
            dilate(FGModel, FGModel, element);
            erode(FGModel, FGModel, element);
            
            imshow("FGModel", FGModel);
            vector<vector<Point> > contours;  
            
            findContours(FGModel, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);  
            drawContours(result, contours, -1, Scalar(0, 0, 255), 2);//在result上绘制轮廓  
            //7.查找正外接矩形  
            vector<Rect> boundRect(contours.size());  
            for (int i = 0; i < contours.size(); i++)  
            {  
                boundRect[i] = boundingRect(contours[i]);  
                rectangle(result, boundRect[i], Scalar(0, 255, 0), 2);//在result上绘制正外接矩形  
            }  
        }
        //equalizeHist(gray, dstImage);

        imshow("input", frame);
        imshow("detection", result);
        //imshow("gray_his", dstImage);
        if ( waitKey(25) == 27 )
            break;
    }

    return 0;
}
