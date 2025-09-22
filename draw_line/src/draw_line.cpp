#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>
#include <string>
#include <iostream>

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat originalImage;
cv::Mat tempImage; // For drawing in progress
cv::Point startPoint;
cv::Point endPoint;
bool drawing = false;

void onMouse(int event, int x, int y, int flags, void* userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN) 
    {
        startPoint = cv::Point(x, y);
        drawing = true;
    } else if (event == cv::EVENT_MOUSEMOVE) 
    {
        if (drawing) 
        {
            endPoint = cv::Point(x, y);
            // Copy original image to temp for real-time drawing preview
            originalImage.copyTo(tempImage); 
            cv::line(tempImage, startPoint, endPoint, cv::Scalar(0, 0, 255), 2); // Red line, thickness 2
            cv::imshow("Image Window", tempImage);
        }
    } else if (event == cv::EVENT_LBUTTONUP) 
    {
        drawing = false;
        endPoint = cv::Point(x, y);
        cv::line(originalImage, startPoint, endPoint, cv::Scalar(0, 0, 255), 2); // Draw on original image
        cv::imshow("Image Window", originalImage);
    }
}

int main() 
{
    originalImage = cv::Mat::zeros(500, 800, CV_8UC3); // Create a black image
    cv::namedWindow("Image Window");
    cv::setMouseCallback("Image Window", onMouse);

    cv::imshow("Image Window", originalImage);
    cv::waitKey(0); // Wait indefinitely for a key press

    return 0;
}