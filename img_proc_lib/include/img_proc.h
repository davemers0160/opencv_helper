#ifndef IMG_PROC_LIB_H
#define IMG_PROC_LIB_H

//#define EXTERN_C
//#include <cstdint>
//#include <string>
//#include <vector>

#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)

    #ifdef IMG_DLL_EXPORTS
        #define IMG_PROC_LIB __declspec(dllexport)
    #else
        #define IMG_PROC_LIB __declspec(dllimport)
    #endif

#else
    #define IMG_PROC_LIB

#endif


// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function takes in a 16-bit single channel image and converts it to an 8-bit single channel image
    IMG_PROC_LIB void convert_ushort_to_uchar(unsigned short *src, unsigned int width, unsigned int height, unsigned char *dst);
#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function takes in a 16-bit single channel image and converts it to an 8-bit single channel image
    IMG_PROC_LIB void convert_float_to_uchar(float* src, unsigned int width, unsigned int height, unsigned char* dst);
#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function takes in a 16-bit single channel image and converts it to an 8-bit single channel image
    IMG_PROC_LIB void convert_double_to_uchar(double* src, unsigned int width, unsigned int height, unsigned char* dst);
#ifdef __cplusplus
}
#endif




#endif  // IMG_PROC_LIB_H

