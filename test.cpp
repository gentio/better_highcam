#include "test.h"

using namespace std;
using namespace cv;

void dataproc(class imgproc &procbuffer, uchar *buffer, long length, int frames, int height, int width, string videoname);

uchar *openfile(string filename, long &length)
{
    
    ifstream infile;
    infile.open(filename,ios::in | ios::binary);
    infile.seekg(0,ios::end);
    long sizes = infile.tellg();
    infile.seekg(0,ios::beg);
    length = sizes;
    int frames = sizes/( HEIGHT*WIDTH );

    uchar *buffer = (uchar *) new uchar[sizes];

    infile.seekg(0, ios::beg);
    infile.read((char*)buffer, length);
    infile.close();

    return buffer;
}
void dataproc(uchar *buffer, long length, int frames, int height, int width, string videoname)
{
    BOOL F_video = TRUE;
    BOOL F_video_bit = FALSE;
    BOOL F_img_bit = FALSE;
    BOOL F_img= FALSE;
//  BOOL F_video_bit = f_save_slow_video_bit;
    //BOOL F_img = f_save_slow_img;
    //BOOL F_img_bit = f_save_slow_img_bit;

    Mat img(Size(width, height), CV_8UC1);
    Mat img_bit(Size(width, height), CV_8UC1);

    uchar *gray = img.data;
    uchar *bit_img = img_bit.data;

    VideoWriter writer;
    VideoWriter writer_bit;
    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');

    double fps = 50.0;                          // framerate of the created video stream
    string video_filename(videoname);
//    string video_filename = "./slow_show.avi";             // name of the output video file
    string video_filename_bit = "./slow_show_bit.avi";     // name of the output video file

    writer.open(video_filename, codec, fps, img.size(), 0);

    if (!writer.isOpened()) {
        //MessageBox("Can't open the video files to write");
        cout << "Can't open the video files to write" << endl;

    }

    writer_bit.open(video_filename_bit, codec, fps, img_bit.size(), 0);


    if (!writer_bit.isOpened()) {
//      MessageBox("Can't open the bit video files to write");
        cout << "Can't open the video files to write" << endl;
    }


    uint* interval = new uint[250 * 400];
    uint* label = new uint[250 * 400];
    uchar *pulse = buffer;

    uchar q1 = 1;
    uchar q2 = 2;
    uchar q3 = 4;
    uchar q4 = 8;
    uchar q5 = 16;
    uchar q6 = 32;
    uchar q7 = 64;
    uchar q8 = 128;

    for (int jj = 0; jj < 250 * 400; jj++)
    {
        label[jj] = 0x00;
    }

    uint itemp = 0;
    uint iframe = 0;
    uint frame;
    uint framecount = 0;
    uint irow = 0;
    uint itime = 0;
//  CString filename;

 for (int jj = 0;  jj < 250 *50; jj++)
    gray[jj] = 0xff;
    writer.write(img);
    char tmp[500];


        for (iframe = 0; iframe< frames; iframe++)
        {
            framecount++;

            // cout << iframe << endl;
            memset(bit_img, 0x0, width*height);

            frame = iframe;
            for (irow = 0; irow < 250; irow++)
            {
                for (itime = 0; itime < 50; itime++)//每行52个字节
                {

                    if (pulse[iframe * 50 * 250 + irow * 50 + itime] & q1)
                    {
                        interval[8 * 50 * irow + 8 * itime] = frame - label[8 * 50 * irow + 8 * itime];
                        label[8 * 50 * irow + 8 * itime] = frame;
                        bit_img[8 * 50 * irow + 8 * itime] = 0xff;
                    }
                    if (pulse[iframe * 50 * 250 + irow * 50 + itime] & q2)
                    {
                        interval[8 * 50 * irow + 8 * itime + 1] = frame - label[8 * 50 * irow + 8 * itime + 1];
                        label[8 * 50 * irow + 8 * itime + 1] = frame;
                        bit_img[8 * 50 * irow + 8 * itime + 1] = 0xff;
                    }
                    if (pulse[iframe * 50 * 250 + irow * 50 + itime] & q3)
                    {
                        interval[8 * 50 * irow + 8 * itime + 2] = frame - label[8 * 50 * irow + 8 * itime + 2];
                        label[8 * 50 * irow + 8 * itime + 2] = frame;
                        bit_img[8 * 50 * irow + 8 * itime + 2] = 0xff;
                    }
                    if (pulse[iframe * 50 * 250 + irow * 50 + itime] & q4)
                    {
                        interval[8 * 50 * irow + 8 * itime + 3] = frame - label[8 * 50 * irow + 8 * itime + 3];
                        label[8 * 50 * irow + 8 * itime + 3] = frame;
                        bit_img[8 * 50 * irow + 8 * itime + 3] = 0xff;
                    }
                    if (pulse[iframe * 50 * 250 + irow * 50 + itime] & q5)
                    {
                        interval[8 * 50 * irow + 8 * itime + 4] = frame - label[8 * 50 * irow + 8 * itime + 4];
                        label[8 * 50 * irow + 8 * itime + 4] = frame;
                        bit_img[8 * 50 * irow + 8 * itime + 4] = 0xff;
                    }
                    if (pulse[iframe * 50 * 250 + irow * 50 + itime] & q6)
                    {
                        interval[8 * 50 * irow + 8 * itime + 5] = frame - label[8 * 50 * irow + 8 * itime + 5];
                        label[8 * 50 * irow + 8 * itime + 5] = frame;
                        bit_img[8 * 50 * irow + 8 * itime + 5] = 0xff;
                    }
                    if (pulse[iframe * 50 * 250 + irow * 50 + itime] & q7)
                    {
                        interval[8 * 50 * irow + 8 * itime + 6] = frame - label[8 * 50 * irow + 8 * itime + 6];
                        label[8 * 50 * irow + 8 * itime + 6] = frame;
                        bit_img[8 * 50 * irow + 8 * itime + 6] = 0xff;
                    }
                    if (pulse[iframe * 50 * 250 + irow * 50 + itime] & q8)
                    {
                        interval[8 * 50 * irow + 8 * itime + 7] = frame - label[8 * 50 * irow + 8 * itime + 7];
                        label[8 * 50 * irow + 8 * itime + 7] = frame;
                        bit_img[8 * 50 * irow + 8 * itime + 7] = 0xff;

                    }
                }
            }

            for (int mm = 0; mm < 250 * 400; mm++)
            {
                if (interval[mm] != (uint)0)
                {
                    gray[mm] = (3200 / interval[mm]> 255) ? 255 : ((3200 / interval[mm]) & 0xff);

                }
                if (interval[mm] == (uint)0)
                {
                    gray[mm] = 0xff;
                }
            }

            flip(img, img, 0);
            flip(img_bit, img_bit, 0);

            if (F_video) {
                writer.write(img);
            }
            if (F_video_bit) {
                writer_bit.write(img_bit);
            }

            if (F_img) {
                sprintf(tmp, "./pic/%d.jpg", framecount);
                imwrite(tmp, img);
            }
            if (F_img_bit) {
                sprintf(tmp, "./bit/%d.jpg", framecount);
                imwrite(tmp, img_bit);
            }

        }

//  delete[] pulse;
    delete[] interval;
    delete[] label;

}
int main(int argc, char *argv[])
{
    uchar *buffer = NULL;
    long length = 0;
    if ( argc != 3){
        cout << "Usage: Pragram dataname video" << endl;
        return 2;

    }
        string filename(argv[1]);
        string videoname(argv[2]);

        
    buffer = openfile(filename, length);

    if (buffer)
        cout << "Open File Success!\n" << endl;

    cout << length << endl;
    cout << "The Frames of the data is " << length * 8 / HEIGHT /WIDTH << endl;

    imgproc procbuffer;
    procbuffer.openvideo(videoname);
    dataproc(procbuffer, buffer, length, length *8 /(HEIGHT*WIDTH), HEIGHT,WIDTH, videoname);

    delete [] buffer;

}

void dataproc(class imgproc &procbuffer, uchar *buffer, long length, int frames, int height, int width, string videoname)
{
    for (int i=0; i < frames; i++)
    {
        procbuffer.get_raw(buffer+i*height*width/8);
        procbuffer.proc_raw();

        //    imshow("LLLL", procbuffer.out_buf.front());
        //waitKey(0);
    }

}
void imgproc::proc_raw()
{
    int itemp = 0;
    int iframe = 0;
    int frame;


    uint irow = 0;
    uint itime = 0;
    uchar *pulse = in_buf;

    deque<Mat>::size_type sz = out_buf.size();
    
    cout << "Hello from proc_raw function" << endl;
    for (irow = 10; irow < 240; irow++)
            {
                for (itime = 10; itime < 40; itime++)//每行52个字节
                {

                    if (pulse[irow * 50 + itime] & q1)
                    {
                        for (int ii = 0; ii< sz; ii++) {
                            uchar *data = out_buf[ii].data;
                            data[8*50*irow+8*itime] += ii*2;
                            for (int jj = ii; jj < sz;  jj++)
                                for (int kk = ii; kk < sz; kk++) {
                                    data[8*50*irow+8*itime + jj+kk] += ii;
                                    data[8*50*irow+8*itime + jj-kk] += ii;
                                    data[8*50*irow+8*itime - jj+kk] += ii;
                                    data[8*50*irow+8*itime - jj-kk] += ii;
                                }
                        }
//                      dbuffer[8 * 50 * irow + 8 * itime]++;
                    }
                    if (pulse[ irow * 50 + itime] & q2)
                    {
                        for (int ii = 0; ii< sz; ii++) {
                            uchar *data = out_buf[ii].data;
                            data[8*50*irow+8*itime+1] += ii*2;
                            for (int jj = ii; jj < sz;  jj++)
                                for (int kk = ii; kk < sz; kk++) {
                                    data[8*50*irow+8*itime + jj+kk+1] += ii;
                                    data[8*50*irow+8*itime + jj-kk+1] += ii;
                                    data[8*50*irow+8*itime - jj+kk+1] += ii;
                                    data[8*50*irow+8*itime - jj-kk+1] += ii;
                                }
                        }
//                      dbuffer[8 * 50 * irow + 8 * itime + 1]++;
                    }
                    if (pulse[ irow * 50 + itime] & q3)
                    {
                        for (int ii = 0; ii< sz; ii++) {
                            uchar *data = out_buf[ii].data;
                            data[8*50*irow+8*itime+2] += ii*2;
                            for (int jj = ii; jj < sz;  jj++)
                                for (int kk = ii; kk < sz; kk++) {
                                    data[8*50*irow+8*itime + jj+kk+2] += ii;
                                    data[8*50*irow+8*itime + jj-kk+2] += ii;
                                    data[8*50*irow+8*itime - jj+kk+2] += ii;
                                    data[8*50*irow+8*itime - jj-kk+2] += ii;
                                }
                        }
//                      dbuffer[8 * 50 * irow + 8 * itime + 2]++;
                    }
                    if (pulse[ irow * 50 + itime] & q4)
                    {
                        for (int ii = 0; ii< sz; ii++) {
                            uchar *data = out_buf[ii].data;
                            data[8*50*irow+8*itime+3] += ii*2;
                            for (int jj = ii; jj < sz;  jj++)
                                for (int kk = ii; kk < sz; kk++) {
                                    data[8*50*irow+8*itime + jj+kk+3] += ii;
                                    data[8*50*irow+8*itime + jj-kk+3] += ii;
                                    data[8*50*irow+8*itime - jj+kk+3] += ii;
                                    data[8*50*irow+8*itime - jj-kk+3] += ii;
                                }
                        }
//                      dbuffer[8 * 50 * irow + 8 * itime + 3]++;
                    }
                    if (pulse[ irow * 50 + itime] & q5)
                    {
                        for (int ii = 0; ii< sz; ii++) {
                            uchar *data = out_buf[ii].data;
                            data[8*50*irow+8*itime+4] += ii*2;
                            for (int jj = ii; jj < sz;  jj++)
                                for (int kk = ii; kk < sz; kk++) {
                                    data[8*50*irow+8*itime + jj+kk+4] += ii;
                                    data[8*50*irow+8*itime + jj-kk+4] += ii;
                                    data[8*50*irow+8*itime - jj+kk+4] += ii;
                                    data[8*50*irow+8*itime - jj-kk+4] += ii;
                                }
                        }
//                      dbuffer[8 * 50 * irow + 8 * itime + 4]++;
                    }
                    if (pulse[ irow * 50 + itime] & q6)
                    {
                        for (int ii = 0; ii< sz; ii++) {
                            uchar *data = out_buf[ii].data;
                            data[8*50*irow+8*itime+5] += ii*2;
                            for (int jj = ii; jj < sz;  jj++)
                                for (int kk = ii; kk < sz; kk++) {
                                    data[8*50*irow+8*itime + jj+kk+5] += ii;
                                    data[8*50*irow+8*itime + jj-kk+5] += ii;
                                    data[8*50*irow+8*itime - jj+kk+5] += ii;
                                    data[8*50*irow+8*itime - jj-kk+5] += ii;
                                }
                        }
//                      dbuffer[8 * 50 * irow + 8 * itime + 5]++;
                    }
                    if (pulse[ irow * 50 + itime] & q7)
                    {
                        for (int ii = 0; ii< sz; ii++) {
                            uchar *data = out_buf[ii].data;
                            data[8*50*irow+8*itime+6] += ii*2;
                            for (int jj = ii; jj < sz;  jj++)
                                for (int kk = ii; kk < sz; kk++) {
                                    data[8*50*irow+8*itime + jj+kk+6] += ii;
                                    data[8*50*irow+8*itime + jj-kk+6] += ii;
                                    data[8*50*irow+8*itime - jj+kk+6] += ii;
                                    data[8*50*irow+8*itime - jj-kk+6] += ii;
                                }
                        }
//                      dbuffer[8 * 50 * irow + 8 * itime + 6]++;
                    }
                    if (pulse[ irow * 50 + itime] & q8)
                    {
                        for (int ii = 0; ii< sz; ii++) {
                            uchar *data = out_buf[ii].data;
                            data[8*50*irow+8*itime+7] += ii*2;
                            for (int jj = ii; jj < sz;  jj++)
                                for (int kk = ii; kk < sz; kk++) {
                                    data[8*50*irow+8*itime + jj+kk+7] += ii;
                                    data[8*50*irow+8*itime + jj-kk+7] += ii;
                                    data[8*50*irow+8*itime - jj+kk+7] += ii;
                                    data[8*50*irow+8*itime - jj-kk+7] += ii;
                                }
                        }
//                      dbuffer[8 * 50 * irow + 8 * itime + 7]++;
                    }
                }
            }
}
void imgproc::get_raw(uchar *in)
{
    memcpy(in_buf, in, in_buffer_size);
    cout << "Copy Success" << endl;
    Mat  img(Size(WIDTH,HEIGHT), CV_8UC1);
    memset(img.data,0xff,img_size);
    out_buf.push_back(img);
    frames++;
    char tmp[100];
    sprintf(tmp, "pic/%d.jpg",frames);
    if (out_buf.size()>out_buf_limits){
//        imwrite(tmp,  out_buf.front());
        writer.write(out_buf.front());
        out_buf.pop_front();
        
    }
//    imwrite(tmp, img);
        
}
imgproc::imgproc()
{
    in_buf = new uchar[in_buffer_size];
}

imgproc::~imgproc()
{
    out_buf.clear();
    delete [] in_buf;
}
void imgproc::openvideo(string videoname)
{


    int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');

    double fps = 50.0;                          // framerate of the created video stream
    string video_filename(videoname);
    //string video_filename_bit = "./slow_show_bit.avi";     // name of the output video file

    writer.open(video_filename, codec, fps, Size(WIDTH,HEIGHT), 0);

    if (!writer.isOpened()) {
        cout << "Can't open the video files to write" << endl;

    }


}
