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
#include <vector>

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// Custom includes
#include "tester.h"

#ifdef __cplusplus
extern "C" {
#endif
    // This function 
    void crop_uint8_img(unsigned char* src, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char* dst);

#ifdef __cplusplus
}
#endif
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

    uint32_t r, c;

    std::string lib_filename;
    std::string image_filename;

    int32_t w = 256;
    int32_t h = 256;

    std::vector<uint8_t> img08(w*h);
    std::vector<uint16_t> img16(w*h);
    std::vector<float> img32(w * h);

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
            throw std::runtime_error("error loading library: " + lib_filename);
        }
     
        convert_ushort_to_uchar cv_16UC1_8UC1 = (convert_ushort_to_uchar)GetProcAddress(test_lib, "convert_ushort_to_uchar");
        convert_float_to_uchar cv_32FC1_8UC1 = (convert_float_to_uchar)GetProcAddress(test_lib, "convert_float_to_uchar");
        convert_double_to_uchar cv_64FC1_8UC1 = (convert_double_to_uchar)GetProcAddress(test_lib, "convert_double_to_uchar");

        lib_filename = "../../img_show_lib/build/Release/img_show.dll";
        HINSTANCE lib_img_show = LoadLibrary(lib_filename.c_str());

        if (lib_img_show == NULL)
        {
            throw std::runtime_error("error loading library: " + lib_filename);
        }

        imshow_gray img_show_gray = (imshow_gray)GetProcAddress(lib_img_show, "imshow_gray");
        imshow_rgb img_show_rgb = (imshow_rgb)GetProcAddress(lib_img_show, "imshow_rgb");
        close_win close_window = (close_win)GetProcAddress(lib_img_show, "close_window");

        lib_filename = "../../select_roi_lib/build/Release/select_roi.dll";
        HINSTANCE lib_select_roi = LoadLibrary(lib_filename.c_str());

        if (lib_select_roi == NULL)
        {
            throw std::runtime_error("error loading library: " + lib_filename);
        }

        select_roi cv_select_roi = (select_roi)GetProcAddress(lib_select_roi, "select_roi");

#else
        void* test_lib = dlopen(lib_filename.c_str(), RTLD_NOW);

        if (test_lib == NULL)
        {
            throw std::runtime_error("error loading library");
        }

        convert_ushort_to_uchar cv_16UC1_8UC1 = (convert_ushort_to_uchar)dlsym(test_lib, "convert_ushort_to_uchar");
        convert_float_to_uchar cv_32FC1_8UC1 = (convert_float_to_uchar)dlsym(test_lib, "convert_float_to_uchar");
        convert_double_to_uchar cv_64FC1_8UC1 = (convert_double_to_uchar)dlsym(test_lib, "convert_double_to_uchar");

        lib_filename = "../../img_show_lib/build/Release/img_show.dll";
        void* lib_img_show = LoadLibrary(lib_filename.c_str());

        if (lib_img_show == NULL)
        {
            throw std::runtime_error("error loading library");
        }

        img_show cv_img_show = (img_show)GetProcAddress(lib_img_show, "img_show");

#endif

        //image_filename = "../images/image_0547_16.png";

        //img1 = cv::imread(image_filename, cv::IMREAD_ANYCOLOR | cv::IMREAD_ANYDEPTH);

        // fill in the values of the matrix
        uint16_t v16 = 0;
        uint8_t v8 = 0;
        for (r = 0; r < h; ++r)
        {
            for (c = 0; c < w; ++c)
            {
                img08[r * w + c] = v8;
                img16[r * w + c] = v16;
                img32[r * w + c] = v16 * 32;
                ++v16;
                ++v8;
            }
        }


        //cv::Mat img32, img64;

        //img1.convertTo(img32, CV_32FC1, 9.87, 300.5);
        //img1.convertTo(img64, CV_64FC1, 1312.4, -650.0);

        uint8_t* img_data_16 = new uint8_t[h * w]{ 0 };
        uint8_t* img_data_32 = new uint8_t[h * w]{ 0 };
        uint8_t* img_data_64 = new uint8_t[h * w]{ 0 };

        uint8_t* crop_8 = new uint8_t[100 * 100]{ 0 };

        // convert the image
        //conv16to8(img1.ptr<uint16_t>(0), w, h, img_data_16);
        cv_16UC1_8UC1(img16.data(), w, h, img_data_16);
        img_show_gray("Test Image 16", img_data_16, w, h, 0);

        //cv::Rect roi(100, 100, 100, 100);
        //cv::Mat img1 = cv::Mat(h, w, CV_8UC1, img_data_16, w * sizeof(*img_data_16));
        //cv::Mat img2 = img1(roi);

        //std::memcpy(crop_8, img2.data, 100 * 100 * sizeof(*crop_8));

        crop_uint8_img(img_data_16, w, h, 100, 100, 100, 100, crop_8);


        //img2 = cv::Mat(h, w, CV_8UC1, img_data_16, w*sizeof(*img_data_16));

        int rx = 0;
        int ry = 0;
        int rw = 0;
        int rh = 0;

        cv_select_roi(img08.data(), w, h, 1, &rx, &ry, &rw, &rh);

        //img_show_gray("Test Image 16", img2.ptr<uint8_t>(0), w, h, 0);

        //close_window("Test Image 16");

        //cv::imshow("Test Image 16", img2);
        //cv::waitKey(0);

        // ----------------------------------------------------------------------------
        cv_32FC1_8UC1(img32.data(), w, h, img_data_32);

        //cv::Mat img3 = cv::Mat(h, w, CV_8UC1, img_data_32, w * sizeof(*img_data_32));

        //cv::namedWindow("Test Image 32", cv::WindowFlags::WINDOW_NORMAL | cv::WindowFlags::WINDOW_FREERATIO);
        //cv::imshow("Test Image 32", img3);
        //cv::waitKey(0);
        img_show_gray("Test Image 32", img_data_32, w, h, 0);

        // ----------------------------------------------------------------------------
        //cv_64FC1_8UC1(img64.ptr<double>(0), w, h, img_data_64);

        //cv::Mat img4 = cv::Mat(h, w, CV_8UC1, img_data_64, w * sizeof(*img_data_64));

        //cv::imshow("Test Image 64", img4);
        //cv::waitKey(0);
        //img_show_gray("Test Image 64", img2.ptr<uint8_t>(0), w, h, 0);

        // ----------------------------------------------------------------------------
        //cv::Mat img5;

        //cv::cvtColor(img4, img5, cv::COLOR_GRAY2BGR);

        //img_show_rgb("Test Image rgb", img5.ptr<uint8_t>(0), w, h, 0);

        //close_window("Test Image rgb");

// ----------------------------------------------------------------------------
// Close the library
// ----------------------------------------------------------------------------
#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)
        FreeLibrary(test_lib);
        FreeLibrary(lib_img_show);
        FreeLibrary(lib_select_roi);
#else
        dlclose(test_lib);
        dlclose(lib_img_show);
        FreeLibrary(lib_select_roi);
        dlclose(lib_select_roi);
#endif

        delete[] img_data_16;
        delete[] img_data_32;
        delete[] img_data_64;

        //cv::destroyAllWindows();
        
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;

        std::cout << std::endl << "Press Enter to close..." << std::endl;
        std::cin.ignore();
    }


    std::cout << std::endl << "End of Program.  Press Enter to close..." << std::endl;
    std::cin.ignore();

    return 0;
        
}   // end of main
