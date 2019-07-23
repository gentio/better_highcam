#ifndef TEST_H
#define TEST_H

#include <fstream>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/video.hpp>
#include <opencv2/highgui.hpp>
#include <vector>
#include <deque>

#define HEIGHT 250
#define WIDTH 400
#define TRUE 1
#define FALSE 0

typedef unsigned char uchar;
typedef unsigned int uint;
typedef bool BOOL;

using namespace cv;
using namespace std;

class imgproc{
public:
    imgproc();
    ~imgproc();
    void get_raw(uchar *);
    void proc_raw();
    
    void openvideo(string filename);

    deque<Mat> out_buf;
    uchar *in_buf;

    VideoWriter writer;
private:
    int in_buffer_size = HEIGHT * WIDTH / 8;
    int out_buf_limits  = 7;
    int img_size  = HEIGHT*WIDTH;
    int frames = 0;
    uchar q1 = 1;
    uchar q2 = 2;
    uchar q3 = 4;
    uchar q4 = 8;
    uchar q5 = 16;
    uchar q6 = 32;
    uchar q7 = 64;
    uchar q8 = 128;

    BOOL F_video = TRUE;
    BOOL F_video_bit = FALSE;
    BOOL F_img_bit = FALSE;
    BOOL F_img= FALSE;
};


#endif
