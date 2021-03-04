#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>
#include <string>
#include <vector>

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// Custom includes
#include "img_crop.h"

//----------------------------------------------------------------------------------
// library internal state variables:


//----------------------------------------------------------------------------------
void crop_uint8_img(unsigned char* src, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *dst)
{

    cv::Rect roi(x, y, h, w);
    cv::Mat img1 = cv::Mat(height, width, CV_8UC1, src, width * sizeof(*src));
    cv::Mat img2 = img1(roi);

    std::memcpy(dst, img2.data, w * h * sizeof(*dst));

}   // end of crop_uint8_img

//----------------------------------------------------------------------------------
void crop_uint16_img(unsigned short* src, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned short *dst)
{

    cv::Rect roi(x, y, h, w);
    cv::Mat img1 = cv::Mat(height, width, CV_16UC1, src, width * sizeof(*src));
    cv::Mat img2 = img1(roi);

    std::memcpy(dst, img2.data, w * h * sizeof(*dst));

}   // end of crop_uint16_img

//----------------------------------------------------------------------------------
void crop_float_img(float* src, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, float *dst)
{

    cv::Rect roi(x, y, h, w);
    cv::Mat img1 = cv::Mat(height, width, CV_32FC1, src, width * sizeof(*src));
    cv::Mat img2 = img1(roi);

    std::memcpy(dst, img2.data, w * h * sizeof(*dst));

}   // end of crop_float_img

//----------------------------------------------------------------------------------
void crop_double_img(double* src, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, double *dst)
{

    cv::Rect roi(x, y, h, w);
    cv::Mat img1 = cv::Mat(height, width, CV_64FC1, src, width * sizeof(*src));
    cv::Mat img2 = img1(roi);

    std::memcpy(dst, img2.data, w * h * sizeof(*dst));

}   // end of crop_double_img