#include <stdlib.h>
#include <stdio.h>
#include <zmq.h>
#include <unistd.h>
#include "opencv2/opencv.hpp"
#include <opencv2/core/core.hpp>
#include <boost/gil/image_view.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include <time.h>

using namespace std;
using namespace cv;
using namespace boost::gil;


void GilToMat(boost::gil::rgb8_image_t& image, Mat& frame)
{
  rgb8_image_t::view_t temp_view = view(image);
  for (size_t i = 0; i < temp_view.height(); ++i)
    for(size_t j = 0; j < temp_view.width(); ++j)
    {
      //cv::Mat is BGR,not RGB
      frame.at<Vec3b>(i, j)[0] = temp_view(j, i)[2];
      frame.at<Vec3b>(i, j)[1] = temp_view(j, i)[1];
      frame.at<Vec3b>(i, j)[2] = temp_view(j, i)[0];
      //temp_view(i, j) = rgb8_pixel_t(frame.at<Vec3b>(i, j)[2], frame.at<Vec3b>(i, j)[1], frame.at<Vec3b>(i, j)[0]);

    }
}

int main (void)
{
    printf ("Connecting to doopia server…\n");
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket(context, ZMQ_SUB);
    //zmq_connect(subscriber,"tcp://172.17.0.10:5556");
    zmq_connect(subscriber,"tcp://10.113.64.54:5556");
    //zmq_connect(subscriber,"tcp://10.113.64.38:5556");
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, NULL,0);
  
    int size;
    int width = 640;
    int height = 480;
    size = width*height*3;
    int imagecount = 0;
    char imagename[19]= "";
    Mat frame(Size(width, height), CV_8UC3);

    clock_t start, finish;
    double time, cumulated_time;
    cumulated_time = 0;

    rgb8_image_t image;
    image.recreate(width, height);
    namedWindow("Receiver", 1);
    while(imagecount < 460)
    {
        start = clock();
        zmq_recv(subscriber, view(image).begin().x(), width*height*3, 0);
        GilToMat(image, frame);

        printf("client received frame_%08d!\n", imagecount);
        imshow("Receiver", frame);

        sprintf(imagename,"server_%08d.png", imagecount);
        //imwrite(imagename,frame);
        finish = clock();
        time = (double)(finish - start)/CLOCKS_PER_SEC;
        printf("used %fs.\n", time);
        cumulated_time += time;
        ++imagecount;
        if((imagecount%10) == 0)
        printf("Sum %d fames used average time is %.4lf. %.4lf[HZ]\n", imagecount, cumulated_time/imagecount, imagecount/cumulated_time);
        printf("-------------------------------------------------------------\n");
        waitKey(1);
    }

    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}
