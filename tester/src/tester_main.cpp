#define _CRT_SECURE_NO_WARNINGS


#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include <cstdint>
#include <iostream>
#include <iomanip>
#include <string>

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// Custom includes
#include "tester.h"

// ----------------------------------------------------------------------------
void print_usage(void)
{
    std::cout << "Enter the following as arguments into the program:" << std::endl;
    std::cout << "<input file name> " << std::endl;
    std::cout << std::endl;
}

// ----------------------------------------------------------------------------
int main(int argc, char** argv)
{

    std::string lib_filename;
    std::string image_filename;

    int32_t w, h;
    cv::Mat img1;
    cv::Mat img2;

    // ----------------------------------------------------------------------------------------
    if (argc == 1)
    {
        print_usage();
        std::cin.ignore();
        return 0;
    }

    lib_filename = argv[1];
    
    try {

// ----------------------------------------------------------------------------
// Load in the library
// ----------------------------------------------------------------------------
#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)
        HINSTANCE test_lib = LoadLibrary(lib_filename.c_str());

        if (test_lib == NULL)
        {
            throw std::runtime_error("error loading library");
        }
     
        convert_ushort_to_uchar cv_16UC1_8UC1 = (convert_ushort_to_uchar)GetProcAddress(test_lib, "convert_ushort_to_uchar");
        convert_float_to_uchar cv_32FC1_8UC1 = (convert_float_to_uchar)GetProcAddress(test_lib, "convert_float_to_uchar");
        convert_double_to_uchar cv_64FC1_8UC1 = (convert_double_to_uchar)GetProcAddress(test_lib, "convert_double_to_uchar");

#else
        void* test_lib = dlopen(lib_filename.c_str(), RTLD_NOW);

        if (test_lib == NULL)
        {
            throw std::runtime_error("error loading library");
        }

        convert16to8 cv16_8UC1 = (convert16to8)dlsym(test_lib, "convert16to8");

#endif

        image_filename = "../images/image_0547_16.png";

        img1 = cv::imread(image_filename, cv::IMREAD_ANYCOLOR | cv::IMREAD_ANYDEPTH);

        h = img1.rows;
        w = img1.cols;

        cv::Mat img32, img64;

        img1.convertTo(img32, CV_32FC1, 9.87, 300.5);
        img1.convertTo(img64, CV_64FC1, 1312.4, -650.0);

        uint8_t* img_data_16 = new uint8_t[h * w]{ 0 };
        uint8_t* img_data_32 = new uint8_t[h * w]{ 0 };
        uint8_t* img_data_64 = new uint8_t[h * w]{ 0 };

        // convert the image
        //conv16to8(img1.ptr<uint16_t>(0), w, h, img_data_16);
        cv_16UC1_8UC1(img1.ptr<uint16_t>(0), w, h, img_data_16);

        img2 = cv::Mat(h, w, CV_8UC1, img_data_16, w*sizeof(*img_data_16));

        cv::imshow("Test Image 16", img2);
        cv::waitKey(0);

        // ----------------------------------------------------------------------------
        cv_32FC1_8UC1(img32.ptr<float>(0), w, h, img_data_32);

        cv::Mat img3 = cv::Mat(h, w, CV_8UC1, img_data_32, w * sizeof(*img_data_32));

        cv::imshow("Test Image 32", img3);
        cv::waitKey(0);

        // ----------------------------------------------------------------------------
        cv_64FC1_8UC1(img64.ptr<double>(0), w, h, img_data_64);

        cv::Mat img4 = cv::Mat(h, w, CV_8UC1, img_data_64, w * sizeof(*img_data_64));

        cv::imshow("Test Image 64", img4);
        cv::waitKey(0);



// ----------------------------------------------------------------------------
// Close the library
// ----------------------------------------------------------------------------
#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)
        FreeLibrary(test_lib);
#else
        dlclose(test_lib);
#endif

        delete[] img_data_16;
        delete[] img_data_32;
        delete[] img_data_64;

        
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;

        std::cout << std::endl << "Press Enter to close..." << std::endl;
        std::cin.ignore();
    }

    cv::destroyAllWindows();

    std::cout << std::endl << "End of Program.  Press Enter to close..." << std::endl;
    std::cin.ignore();

    return 0;
        
}   // end of main
