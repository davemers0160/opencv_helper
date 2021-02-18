#ifndef OCV_TESTER_H_
#define OCV_TESTER_H_


// ----------------------------------------------------------------------------------------
typedef void (*convert_ushort_to_uchar)(unsigned short* src, unsigned int width, unsigned short height, unsigned char* dst);
typedef void (*convert_float_to_uchar)(float* src, unsigned int width, unsigned short height, unsigned char* dst);
typedef void (*convert_double_to_uchar)(double* src, unsigned int width, unsigned short height, unsigned char* dst);

#endif  // OCV_TESTER_H_
