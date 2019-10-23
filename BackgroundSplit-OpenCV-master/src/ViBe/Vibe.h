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

#include <iostream>
#include <cstdio>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

// 每个像素点的样本个数默认�?
// the Default Number of pixel's samples
#define DEFAULT_NUM_SAMPLES  20

// #min指数默认�?
// the Default Match Number of make pixel as Background
#define DEFAULT_MIN_MATCHES  4

// Sqthere半径默认�?
// the Default Radius of pixel value
#define DEFAULT_RADIUS 4

// 子采样概率默认�?
// the Default the probability of random sample
#define DEFAULT_RANDOM_SAMPLE 16

class ViBe
{
public:
    ViBe(int num_sam = DEFAULT_NUM_SAMPLES,
         int min_match = DEFAULT_MIN_MATCHES,
         int r = DEFAULT_RADIUS,
         int rand_sam = DEFAULT_RANDOM_SAMPLE);
    ~ViBe(void);

    // 背景模型初始�?
    // Init Background Model.
    void init(Mat img);

    // 处理第一帧图�?
    // Process First Frame of Video Query
    void ProcessFirstFrame(Mat img);

    // 运行 ViBe 算法，提取前景区域并更新背景模型样本�?
    // Run the ViBe Algorithm: Extract Foreground Areas & Update Background Model Sample Library.
    void Run(Mat img);

    // 获取前景模型二值图�?
    // get Foreground Model Binary Image.
    Mat getFGModel();

    // 删除样本�?
    // Delete Sample Library.
    void deleteSamples();

    // x的邻居点
    // x's neighborhood points
    int c_xoff[9];

    // y的邻居点
    // y's neighborhood points
    int c_yoff[9];

private:
    // 样本�?
    // Sample Library, size = img.rows * img.cols *  DEFAULT_NUM_SAMPLES
    unsigned char ***samples;

    // 前景模型二值图�?
    // Foreground Model Binary Image
    Mat FGModel;

    // 每个像素点的样本个数
    // Number of pixel's samples
    int num_samples;

    // #min指数
    // Match Number of make pixel as Background
    int num_min_matches;

    // Sqthere半径
    // Radius of pixel value
    int radius;

    // 子采样概�?
    // the probability of random sample
    int random_sample;
};

