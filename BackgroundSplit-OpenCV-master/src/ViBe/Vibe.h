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

// æ¯ä¸ªåƒç´ ç‚¹çš„æ ·æœ¬ä¸ªæ•°é»˜è®¤å€?
// the Default Number of pixel's samples
#define DEFAULT_NUM_SAMPLES  19

// #minæŒ‡æ•°é»˜è®¤å€?
// the Default Match Number of make pixel as Background
#define DEFAULT_MIN_MATCHES  4

// SqthereåŠå¾„é»˜è®¤å€?
// the Default Radius of pixel value
#define DEFAULT_RADIUS 5

// å­é‡‡æ ·æ¦‚çŽ‡é»˜è®¤å€?
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

    // èƒŒæ™¯æ¨¡åž‹åˆå§‹åŒ?
    // Init Background Model.
    void init(Mat img);

    // å¤„ç†ç¬¬ä¸€å¸§å›¾åƒ?
    // Process First Frame of Video Query
    void ProcessFirstFrame(Mat img);

    // è¿è¡Œ ViBe ç®—æ³•ï¼Œæå–å‰æ™¯åŒºåŸŸå¹¶æ›´æ–°èƒŒæ™¯æ¨¡åž‹æ ·æœ¬åº?
    // Run the ViBe Algorithm: Extract Foreground Areas & Update Background Model Sample Library.
    void Run(Mat img);

    // èŽ·å–å‰æ™¯æ¨¡åž‹äºŒå€¼å›¾åƒ?
    // get Foreground Model Binary Image.
    Mat getFGModel();

    // åˆ é™¤æ ·æœ¬åº?
    // Delete Sample Library.
    void deleteSamples();

    // xçš„é‚»å±…ç‚¹
    // x's neighborhood points
    int c_xoff[9];

    // yçš„é‚»å±…ç‚¹
    // y's neighborhood points
    int c_yoff[9];

private:
    // æ ·æœ¬åº?
    // Sample Library, size = img.rows * img.cols *  DEFAULT_NUM_SAMPLES
    unsigned char ***samples;

    // å‰æ™¯æ¨¡åž‹äºŒå€¼å›¾åƒ?
    // Foreground Model Binary Image
    Mat FGModel;

    // æ¯ä¸ªåƒç´ ç‚¹çš„æ ·æœ¬ä¸ªæ•°
    // Number of pixel's samples
    int num_samples;

    // #minæŒ‡æ•°
    // Match Number of make pixel as Background
    int num_min_matches;

    // SqthereåŠå¾„
    // Radius of pixel value
    int radius;

    // å­é‡‡æ ·æ¦‚çŽ?
    // the probability of random sample
    int random_sample;
};

