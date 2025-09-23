#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>
#include <string>
#include <iostream>

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::Point start_point;
cv::Point stop_point;
bool drawing = false;
cv::Mat original_image;
cv::Mat current_image;

int font_face = cv::FONT_HERSHEY_PLAIN;
int thickness = 1;
int baseline = 0;
double font_scale = 1.0;
cv::Size text_size;

void onMouse(int event, int x, int y, int flags, void* userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN) 
    {
        start_point = cv::Point(x, y);
        drawing = true;
    } 
    else if (event == cv::EVENT_MOUSEMOVE) 
    {
        if (drawing) 
        {
            stop_point = cv::Point(x, y);
            // Copy original image to temp for real-time drawing preview
            original_image.copyTo(current_image);
            cv::line(current_image, start_point, stop_point, cv::Scalar(0, 0, 255), 2); // Red line, thickness 2
            cv::imshow("Image Window", current_image);
        }
    } 
    else if (event == cv::EVENT_LBUTTONUP) 
    {
        drawing = false;
        stop_point = cv::Point(x, y);
        cv::line(original_image, start_point, stop_point, cv::Scalar(0, 0, 255), 2); // Draw on original image
        cv::imshow("Image Window", original_image);
    }
}

// Mouse callback function
void draw_line_callback(int event, int x, int y, int flags, void* userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN) 
    {
        // A left-click starts a new line
        drawing = true;
        start_point = cv::Point(x, y);
    }
    else if (event == cv::EVENT_MOUSEMOVE && drawing) 
    {
        stop_point = cv::Point(x, y);

        // While the mouse is moving and drawing is active
        // 1. Copy the original image to clear the old line
        original_image.copyTo(current_image);

        // 2. Draw the new line on the temporary image
        cv::line(current_image, start_point, stop_point, cv::Scalar(0, 0, 255), 2);

        std::string height_str = "  " + std::to_string(stop_point.y - start_point.y) + "px";
        text_size = cv::getTextSize(height_str, font_face, font_scale, thickness, &baseline);

        cv::putText(current_image, height_str, stop_point + cv::Point(0, (text_size.height + 3)), font_face, font_scale, cv::Scalar(0, 0, 255), thickness, cv::LINE_8, false);

        // 3. Display the updated image
        cv::imshow("Image Window", current_image);
    }
    else if (event == cv::EVENT_LBUTTONUP) 
    {
        // A left-button release finishes the line
        drawing = false;
        // The line is already drawn on current_image from the last mouse move event
    }
}

int main() 
{
    original_image = cv::Mat::zeros(500, 500, CV_8UC3); // Create a black image
    cv::namedWindow("Image Window", cv::WINDOW_AUTOSIZE);
    //cv::setMouseCallback("Image Window", draw_line_callback);

    // Create a mutable copy of the original image
    original_image.copyTo(current_image);

    // Set the mouse callback function for the window
    cv::setMouseCallback("Image Window", draw_line_callback);

    // Display the initial image
    cv::imshow("Image Window", current_image);

    // Wait for a key press and close the window
    cv::waitKey(0);
    cv::destroyAllWindows();

    uint32_t height = abs(stop_point.y - start_point.y);

    std::cout << "height: " << height << std::endl;

    //cv::imshow("Image Window", original_image);
    //cv::waitKey(0); // Wait indefinitely for a key press
    std::cin.ignore();
    return 0;
}