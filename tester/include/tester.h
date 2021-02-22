#ifndef OCV_TESTER_H_
#define OCV_TESTER_H_


// ----------------------------------------------------------------------------------------
typedef void (*convert_ushort_to_uchar)(unsigned short* src, unsigned int width, unsigned int height, unsigned char* dst);
typedef void (*convert_float_to_uchar)(float* src, unsigned int width, unsigned int height, unsigned char* dst);
typedef void (*convert_double_to_uchar)(double* src, unsigned int width, unsigned int height, unsigned char* dst);

typedef void (*imshow_gray)(char* name, unsigned char* src, unsigned int w, unsigned int h, unsigned int delay);
typedef void (*imshow_rgb)(char* name, unsigned char* src, unsigned int w, unsigned int h, unsigned int delay);
typedef void (*close_win)(char* name);

typedef void (*select_roi)(unsigned char* src, unsigned int w, unsigned int h, unsigned int c, int* rx, int* ry, int* rw, int* rh);

#endif  // OCV_TESTER_H_
