#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>
#include <string>
#include <vector>

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// Custom includes
#include "img_proc.h"

//----------------------------------------------------------------------------------
// library internal state variables:


//----------------------------------------------------------------------------------
void convert_ushort_to_uchar(unsigned short *src, unsigned int w, unsigned short h, unsigned char *dst)
{

    cv::Mat img1 = cv::Mat(h, w, CV_16UC1, src, w * sizeof(*src));
    cv::Mat img2 = cv::Mat(h, w, CV_8UC1, dst, w * sizeof(*dst));

    cv::normalize(img1, img2, 0, 255, cv::NORM_MINMAX, CV_8UC1);

}   // end of convert_ushort_to_uchar

//----------------------------------------------------------------------------------
void convert_float_to_uchar(float* src, unsigned int w, unsigned short h, unsigned char* dst)
{

    cv::Mat img1 = cv::Mat(h, w, CV_32FC1, src, w * sizeof(*src));
    cv::Mat img2 = cv::Mat(h, w, CV_8UC1, dst, w * sizeof(*dst));

    cv::normalize(img1, img2, 0, 255, cv::NORM_MINMAX, CV_8UC1);

}   // end of convert_float_to_uchar

//----------------------------------------------------------------------------------
void convert_double_to_uchar(double* src, unsigned int w, unsigned short h, unsigned char* dst)
{

    cv::Mat img1 = cv::Mat(h, w, CV_64FC1, src, w * sizeof(*src));
    cv::Mat img2 = cv::Mat(h, w, CV_8UC1, dst, w * sizeof(*dst));

    cv::normalize(img1, img2, 0, 255, cv::NORM_MINMAX, CV_8UC1);

}   // end of convert_double_to_uchar

