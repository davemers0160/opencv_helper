#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>
#include <string>
#include <iostream>

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// Custom includes
#include "img_show.h"

//----------------------------------------------------------------------------------
// library internal state variables:

//----------------------------------------------------------------------------------
void imshow_gray(char *name, unsigned char* src, unsigned int w, unsigned int h, unsigned int delay)
{
    cv::Mat img = cv::Mat(h, w, CV_8UC1, src, w * sizeof(*src));

    cv::namedWindow(name, cv::WindowFlags::WINDOW_NORMAL | cv::WindowFlags::WINDOW_FREERATIO);
    cv::imshow(name, img);
    
    cv::waitKey(delay);

    cv::destroyWindow(name);

}   // end of imshow_gray

//----------------------------------------------------------------------------------
void imshow_rgb(char *name, unsigned char* src, unsigned int w, unsigned int h, unsigned int delay)
{
    cv::Mat img = cv::Mat(h, w, CV_8UC3, src, 3 * w * sizeof(*src));

    cv::namedWindow(name, cv::WindowFlags::WINDOW_NORMAL | cv::WindowFlags::WINDOW_FREERATIO);
    cv::imshow(name, img);

    cv::waitKey(delay);

    cv::destroyWindow(name);

}   // end of imshow_rgb

//----------------------------------------------------------------------------------
void close_window(char* name)
{
    cv::destroyWindow(name);
}
