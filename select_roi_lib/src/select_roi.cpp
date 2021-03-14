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
typedef struct mouse_params
{
    bool is_drawing = false;
    cv::Rect roi;

} mouse_params;


// ----------------------------------------------------------------------------------------
void mouse_click(int event, int x, int y, int flags, void* param)
{
    mouse_params* mp = (mouse_params*)param;

    switch (event)
    {
    case cv::EVENT_LBUTTONDOWN:
        (*mp).is_drawing = true;
        (*mp).roi = cv::Rect(x, y, 0, 0);
        break;

    case cv::EVENT_MOUSEMOVE:
        if ((*mp).is_drawing)
        {
            (*mp).roi = cv::Rect(std::min((*mp).roi.x, x), std::min((*mp).roi.y, y), std::abs(x - (*mp).roi.x), std::abs(y - (*mp).roi.y));
        }
        break;

    case cv::EVENT_LBUTTONUP:
        (*mp).roi = cv::Rect(std::min((*mp).roi.x, x), std::min((*mp).roi.y, y), std::abs(x - (*mp).roi.x), std::abs(y - (*mp).roi.y));
        (*mp).is_drawing = false;
        break;
    }

}   // end of mouse_click

//----------------------------------------------------------------------------------
void select_roi(
    unsigned char* src, 
    unsigned int w, unsigned int h, unsigned int c,
    int *rx, int *ry, int *rw, int *rh
)
{
    std::string win_name = "Select ROI";

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
    
    cv::Mat img2 = img.clone();

    mouse_params mp;

    cv::namedWindow(win_name, cv::WINDOW_NORMAL);

    cv::setMouseCallback(win_name, mouse_click, (void*)&mp);

    char key = 0;

    // end selection process on SPACE (32) ESC (27) or ENTER (13)
    while (!(key == 32 || key == 27 || key == 13))
    {
        cv::rectangle(img2, mp.roi, cv::Scalar(255, 0, 0), 2, 1);

        cv::imshow(win_name, img2);

        img2 = img.clone();

        key = cv::waitKey(10);
    }

    cv::destroyWindow(win_name);

    //cv::Rect roi = cv::selectROI(std::string(win_name), img2);
    
    //cv::waitKey(1);

    //cv::destroyWindow(std::string(win_name));
    //cv::destroyAllWindows();

    *rx = mp.roi.x;
    *ry = mp.roi.y;
    *rw = mp.roi.width;
    *rh = mp.roi.height;

}   // end of select_roi
