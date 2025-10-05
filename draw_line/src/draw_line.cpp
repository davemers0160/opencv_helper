#define _CRT_SECURE_NO_WARNINGS

#include <cstdint>
#include <string>
#include <iostream>

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

//cv::Point start_point;
//cv::Point stop_point;
//bool drawing = false;
//cv::Mat original_image;
//cv::Mat current_image;

//int font_face = cv::FONT_HERSHEY_PLAIN;
//int thickness = 1;
//int baseline = 0;
//double font_scale = 1.0;

typedef struct line_struct
{
    cv::Point start_point;
    cv::Point stop_point;
    bool drawing = false;
    cv::Mat original_image;
    cv::Mat current_image;
    cv::Size text_size;
} line_struct;

//void onMouse(int event, int x, int y, int flags, void* userdata) 
//{
//
//    line_struct *ls = (line_struct *)(userdata);
//
//    if (event == cv::EVENT_LBUTTONDOWN) 
//    {
//        ls->start_point = cv::Point(x, y);
//        ls->drawing = true;
//    } 
//    else if (event == cv::EVENT_MOUSEMOVE) 
//    {
//        if (ls->drawing) 
//        {
//            ls->stop_point = cv::Point(x, y);
//            // Copy original image to temp for real-time drawing preview
//            ls->original_image.copyTo(ls->current_image);
//            cv::line(ls->current_image, ls->start_point, ls->stop_point, cv::Scalar(0, 0, 255), 2); // Red line, thickness 2
//            cv::imshow("Image Window", ls->current_image);
//        }
//    } 
//    else if (event == cv::EVENT_LBUTTONUP) 
//    {
//        ls->drawing = false;
//        ls->stop_point = cv::Point(x, y);
//        cv::line(ls->original_image, ls->start_point, ls->stop_point, cv::Scalar(0, 0, 255), 2); // Draw on original image
//        cv::imshow("Image Window", ls->original_image);
//    }
//}

// Mouse callback function
void draw_line_callback(int event, int x, int y, int flags, void* userdata) 
{
    const int32_t font_face = cv::FONT_HERSHEY_PLAIN;
    const int32_t thickness = 1;
    int32_t baseline = 0;
    const double font_scale = 1.0;

    line_struct* ls = (line_struct*)(userdata);

    if (event == cv::EVENT_LBUTTONDOWN) 
    {
        // A left-click starts a new line
        ls->drawing = true;
        ls->start_point = cv::Point(x, y);
    }
    else if (event == cv::EVENT_MOUSEMOVE && ls->drawing)
    {
        ls->stop_point = cv::Point(x, y);

        // While the mouse is moving and drawing is active
        // 1. Copy the original image to clear the old line
        ls->original_image.copyTo(ls->current_image);

        // 2. Draw the new line on the temporary image
        cv::line(ls->current_image, ls->start_point, ls->stop_point, cv::Scalar(0, 0, 255), 2);

        std::string height_str = "  " + std::to_string(ls->stop_point.y - ls->start_point.y) + "px";
        ls->text_size = cv::getTextSize(height_str, font_face, font_scale, thickness, &baseline);

        cv::putText(ls->current_image, height_str, ls->stop_point + cv::Point(0, (ls->text_size.height + 3)), font_face, font_scale, cv::Scalar(0, 0, 255), thickness, cv::LINE_8, false);

        // 3. Display the updated image
        cv::imshow("Image Window", ls->current_image);
    }
    else if (event == cv::EVENT_LBUTTONUP) 
    {
        // A left-button release finishes the line
        ls->drawing = false;
        // The line is already drawn on current_image from the last mouse move event
    }
}

int main() 
{

    line_struct ls;
    ls.original_image = cv::Mat::zeros(500, 500, CV_8UC3); // Create a black image
    //cv::namedWindow("Image Window", cv::WINDOW_AUTOSIZE);
    //cv::setMouseCallback("Image Window", draw_line_callback);cv::WINDOW_GUI_NORMAL
    cv::namedWindow("Image Window", cv::WINDOW_OPENGL | cv::WINDOW_AUTOSIZE);
    //cv::setWindowProperty("Image Window", cv::WND_PROP_ASPECT_RATIO, cv::WINDOW_KEEPRATIO);

    // Create a mutable copy of the original image
    ls.original_image.copyTo(ls.current_image);

    // Set the mouse callback function for the window
    cv::setMouseCallback("Image Window", draw_line_callback, (void*)&ls);

    // Display the initial image
    cv::imshow("Image Window", ls.current_image);

    // Wait for a key press and close the window
    unsigned char key = 0;

    while (key != 27)
    {
        key = cv::waitKey(50);
    }
    //cv::waitKey(0);
    cv::destroyAllWindows();

    uint32_t height = abs(ls.stop_point.y - ls.start_point.y);

    std::cout << "height: " << height << std::endl;

    //cv::imshow("Image Window", original_image);
    //cv::waitKey(0); // Wait indefinitely for a key press
    std::cin.ignore();
    return 0;
}