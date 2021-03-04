#ifndef IMG_CROP_LIB_H
#define IMG_CROP_LIB_H

//#define EXTERN_C
//#include <cstdint>
//#include <string>
//#include <vector>

#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)

    #ifdef IMG_DLL_EXPORTS
        #define IMG_CROP_LIB __declspec(dllexport)
    #else
        #define IMG_CROP_LIB __declspec(dllimport)
    #endif

#else
    #define IMG_CROP_LIB

#endif


// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function 
    IMG_CROP_LIB void crop_uint8_img(unsigned char* src, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *dst);

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function 
    IMG_CROP_LIB void crop_uint16_img(unsigned short* src, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned short *dst);

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function 
    IMG_CROP_LIB void crop_float_img(float* src, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, float *dst);

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function 
    IMG_CROP_LIB void crop_double_img(double* src, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, double *dst);

#ifdef __cplusplus
}
#endif

// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function 
    IMG_CROP_LIB void crop_rbg_img(unsigned char* src, unsigned int width, unsigned int height, unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned char *dst);

#ifdef __cplusplus
}
#endif



#endif  // IMG_CROP_LIB_H

