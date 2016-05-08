#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);
    Mat rgbFrame(1200, 1600, CV_8UC3, Scalar::all(0));
    Mat blurFrame;
    unsigned long size;
    while (1) {
        zmq_recv (responder, rgbFrame.data, 1200*1600*3, 0);
        printf ("Server Received frame!\n");
        //cvtColor(rgbFrame,grayFrame,CV_BGR2GRAY);
        blur(rgbFrame, blurFrame, Size(7,7));
        //imshow("server", blurFrame);
        printf("%d,%d,%lu\n",blurFrame.rows,blurFrame.cols,blurFrame.elemSize());
        zmq_send (responder, blurFrame.data, 1200*1600*3, 0);
        printf ("Server send frame!\n\n");
    }
    return 0;
}