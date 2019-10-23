/*=================================================================
 * Calculate Background Model of a list of Frames(Normally a video stream) in the
 * method of Background Difference Method & OTSU Algorithm By OpenCV.
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

/*=================================================
 * Version:
 * v1.0: ԭ�������IplImageת��ΪMat?? * v1.1: ������ַ���װ��?? BGDiff?? * v1.2: ����ע��?? * v1.3: �÷������˹��ϱ���ģ�Ͳ�ͬ���������󣬸�Ϊ������ַ���
===================================================
*/

#include "BGDifference.h"

int main( int argc, char** argv )
{
    // ԭͼ??    
    
    Mat pFrame;
    // ԭʼOTSU�㷨���ͼ��
    
    Mat pFroundImg;
    // ����ͼ��
    
    Mat pBackgroundImg;
    // �Ľ���OTSU�㷨���ͼ��
    
    Mat pFroundImg_c;
    Mat pBackgroundImg_c;

    //��Ƶ����ȫ�ֱ���,
   // 's' ����stop
   // 'q' �˳���??   // 'p' ��ӡOTSU�㷨���ҵ�����??   
   
   char ctrl = NULL;

   BGDiff BGDif;

   VideoCapture capture;
   capture = VideoCapture("/home/zhangxf/study/BackgroundSplit-OpenCV-master/src/ViBe/video_night1.mp4");
   if(!capture.isOpened())
   {
       capture = VideoCapture("/home/zhangxf/study/BackgroundSplit-OpenCV-master/src/ViBe/video_night1.mp4");
       if(!capture.isOpened())
       {
           capture = VideoCapture("/home/zhangxf/study/BackgroundSplit-OpenCV-master/src/ViBe/video_night1.mp4");
           if(!capture.isOpened())
           {
               cout<<"ERROR: Did't find this video!"<<endl;
               return 0;
           }
       }
   }

    int nFrmNum = 0;

    // ��֡��ȡ��Ƶ
    capture >> pFrame;
    while(!pFrame.empty())
    {
        capture >> pFrame;
        nFrmNum++;

        // ��Ƶ����
        if( (ctrl = cvWaitKey(1000 / 25)) == 's' )
            waitKey(0);
        else if( ctrl == 'p')
            cout << "Current Frame = " << nFrmNum << endl;
        else if( ctrl == 'q')
            break;

        // OpenCV�Դ�OTSU
        BGDif.BackgroundDiff(pFrame, pFroundImg, pBackgroundImg, nFrmNum, CV_THRESH_OTSU);
        // ��ֵɸѡ���OTSU
        BGDif.BackgroundDiff(pFrame, pFroundImg_c, pBackgroundImg_c, nFrmNum, CV_THRESH_BINARY);

        // ��ʾͼ��
        imshow("Source Video", pFrame);
        //imshow("Background", pBackgroundImg);
        imshow("OTSU ForeGround", pFroundImg);
        //imshow("Advanced OTSU ForeGround", pFroundImg_c);
    }
    return 0;
}

