#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>
#include <string>
#include <iostream>

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// Custom includes
#include "select_roi.h"

//----------------------------------------------------------------------------------
// library internal state variables:

//----------------------------------------------------------------------------------
void select_roi(
    unsigned char* src, unsigned int w, unsigned int h, unsigned int c,
    int *rx, int *ry, int *rw, int *rh)
{
    cv::Mat img;

    switch(c)
    {
    case 1:
        img = cv::Mat(h, w, CV_8UC1, src, w * sizeof(*src));
        break;
    case 3:
        img = cv::Mat(h, w, CV_8UC3, src, c * w * sizeof(*src));
        break;
    }
    
    cv::Rect roi = cv::selectROI("Select ROI", img);
    cv::destroyWindow("Select ROI");
    
    *rx = roi.x;
    *ry = roi.y;
    *rw = roi.width;
    *rh = roi.height;  

}   // end of select_roi
