#ifndef __DEFS__
#define __DEFS__

#define MAX_OBJS 5
#define TOTAL_FRAMES 1000

// GL scale factor
#define SCALE_FACTOR 10

// Index for attributes of cvMat
#define MX_MAT_ATTR_NUM 4
#define MX_MAT_SIZE_IDX 0
#define MX_MAT_ROWS_IDX 1
#define MX_MAT_COLS_IDX 2
#define MX_MAT_TYPE_IDX 3

// SDP buf size
#define SDP_BUF_SIZE 2048

// color-print reference: http://web.theurbanpenguin.com/adding-color-to-your-output-from-c/
#define debug_print(...) do { if (__DEBUG__) { \
                              fprintf(stderr, "\033[1;31m[DEBUG] \033[0;32m[FUNC] %s \033[0m", __PRETTY_FUNCTION__); \
                              fprintf(stderr, __VA_ARGS__); \
                              fprintf(stderr, "\n"); } \
                            } while (0)

#ifdef __PROFILE__
#define profile_print(...) do { \
                            fprintf(stderr, "\033[1;34m[PROFILE] \033[0;32m[FUNC] %s \033[0m", __PRETTY_FUNCTION__); \
                            fprintf(stderr, __VA_ARGS__); \
                            fprintf(stderr, "\n");  \
                           } while (0)
#endif

#include <chrono>
#define getExeTime(a,b) ( (double)(std::chrono::duration_cast<std::chrono::microseconds>(a-b).count()) / 1000 )
#define getNow() std::chrono::high_resolution_clock::now()
typedef std::chrono::high_resolution_clock::time_point TimeVal;
typedef struct FrameStamp {
  TimeVal st;
  unsigned int index;
} FrameStamp;

#endif

