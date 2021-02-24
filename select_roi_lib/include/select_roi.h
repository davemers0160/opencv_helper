#ifndef SELECT_ROI_LIB_H
#define SELECT_ROI_LIB_H

#if defined(_WIN32) | defined(__WIN32__) | defined(__WIN32) | defined(_WIN64) | defined(__WIN64)

    #ifdef IMG_DLL_EXPORTS
        #define SELECT_ROI_LIB __declspec(dllexport)
    #else
        #define SELECT_ROI_LIB __declspec(dllimport)
    #endif

#else
    #define SELECT_ROI_LIB

#endif


// ----------------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
    // This function takes in an 8-bit 1- or 3-channel image and displays it
    SELECT_ROI_LIB void select_roi(unsigned char* src, unsigned int w, unsigned int h, unsigned int c, int *rx, int *ry, int *rw, int *rh);
#ifdef __cplusplus
}
#endif

#endif  // SELECT_ROI_LIB_H
