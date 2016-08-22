#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <opencv2/opencv.hpp>
using namespace cv;
int main (void)
{
    printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *server = zmq_socket(context, ZMQ_SUB);
    //zmq_connect(server,"tcp://172.17.0.10:5556");
    zmq_connect(server,"tcp://10.113.64.54:5556");
    zmq_setsockopt(server, ZMQ_SUBSCRIBE, NULL,0);

    int width = 1600;
    int height = 1200;
    int size = width*height*3;
    char imagename[19]= "";
    int imagecount = 0;
    unsigned char* pRgbBuf = new unsigned char[width * height * 3];
    Mat frame(height, width, CV_8UC3, pRgbBuf);
    
    zmq_recv(server, frame.data, size, 0);
    printf("client received frame!\n\n");
    imshow("server", frame);
    sprintf(imagename,"server_%08d.png",imagecount);
    imwrite(imagename,frame);
    zmq_close (server);
    zmq_ctx_destroy (context);
    return 0;
}
