#ifndef IMG_SHOW_LIB_H
#define IMG_SHOW_LIB_H

#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)

    #ifdef IMG_DLL_EXPORTS
        #define IMG_DLL_API __declspec(dllexport)
    #else
        #define IMG_DLL_API __declspec(dllimport)
    #endif

#else
    #define IMG_DLL_API

#endif


// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function takes in an 8-bit 1- or 3-channel image and displays it
    IMG_DLL_API void imshow_gray(char* name, unsigned char* src, unsigned int w, unsigned int h, unsigned int delay);
#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function takes in an 8-bit 1- or 3-channel image and displays it
    IMG_DLL_API void imshow_rgb(char* name, unsigned char* src, unsigned int w, unsigned int h, unsigned int delay);
#ifdef __cplusplus
}
#endif


// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function takes in an 8-bit 1- or 3-channel image and displays it
    IMG_DLL_API void close_window(char* name);
#ifdef __cplusplus
}
#endif

#endif  // IMG_SHOW_LIB_H
