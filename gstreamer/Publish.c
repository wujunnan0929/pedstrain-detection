#include <gst/gst.h>
#include <gst/app/gstappsink.h>
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


void MatToGil(Mat& frame, boost::gil::rgb8_image_t& image)
{
  rgb8_image_t::view_t temp_view = view(image);
  for (size_t i = 0; i < temp_view.height(); ++i)
    for(size_t j = 0; j < temp_view.width(); ++j)
    {
      //cv::Mat is BGR,not RGB
      temp_view(j, i)[0] = frame.at<Vec3b>(i, j)[2];
      temp_view(j, i)[1] = frame.at<Vec3b>(i, j)[1];
      temp_view(j, i)[2] = frame.at<Vec3b>(i, j)[0];
      //temp_view(i, j) = rgb8_pixel_t(frame.at<Vec3b>(i, j)[2], frame.at<Vec3b>(i, j)[1], frame.at<Vec3b>(i, j)[0]);

    }
}

void GilToMat(boost::gil::rgb8_image_t& image, Mat& frame)
{
  rgb8_image_t::view_t temp_view = view(image);
  for (size_t i = 0; i < frame.size().height; ++i)
    for(size_t j = 0; j < frame.size().width; ++j)
    {
      //cv::Mat is BGR,not RGB
      frame.at<Vec3b>(i, j)[0] = temp_view(j, i)[2];
      frame.at<Vec3b>(i, j)[1] = temp_view(j, i)[1];
      frame.at<Vec3b>(i, j)[2] = temp_view(j, i)[0];
      //temp_view(i, j) = rgb8_pixel_t(frame.at<Vec3b>(i, j)[2], frame.at<Vec3b>(i, j)[1], frame.at<Vec3b>(i, j)[0]);

    }
}

int main()
{
    void *context = zmq_ctx_new ();
    //void *client = zmq_socket (context, ZMQ_REQ);
    //zmq_connect (client, "tcp://10.113.64.54:5556");
    //zmq_connect (client, "tcp://localhost:5555");
      void *publisher = zmq_socket (context, ZMQ_PUB);
      zmq_bind (publisher, "tcp://*:5555");

	VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    Mat frame1;    
    Mat frame;
    gsize size;
    int imagecount = 0;
  	gchar imagename[19]= "";
    clock_t start, finish;
    double time, cumulated_time;
    cumulated_time = 0;
    namedWindow("Sender", 1);
    while(1)
    {
        start = clock();
        cap >> frame1; // get a new frame from camera

        resize(frame1, frame, Size(320, 240), CV_INTER_LINEAR);
        size = frame.rows * frame.cols * frame.elemSize();

      	printf("frame width= %d height= %d\n", frame.size().width, frame.size().height);
		    imshow("Sender", frame);
		    sprintf(imagename,"client_%08d.png",imagecount);
      	imwrite(imagename,frame);
      	waitKey(1);

      	rgb8_image_t image;
      	image.recreate(frame.size().width, frame.size().height);
      	MatToGil(frame, image);
      	rgb8c_view_t input_view= view(image);
      	//png_write_view("boost_gil.png", input_view);
      	//printf("image size= %lu dimensions= %lu num_channels= %lu\n", view(image).size(), view(image).num_dimensions, num_channels<rgb8_pixel_t>::value);
      
      	//zmq_send(client, view(image).begin().x(), view(image).size()*num_channels<rgb8_pixel_t>::value, 0);
      	zmq_send(publisher, view(image).begin().x(), view(image).size()*num_channels<rgb8_pixel_t>::value, 0);
        g_print("client send frame_%08d!\n", imagecount);
        finish = clock();
        time = (double)(finish - start)/CLOCKS_PER_SEC;
        printf("used %fs.\n", time);
        cumulated_time += time;
        if((imagecount%10) == 0)
        printf("Sum %d fames used average time is %lf\n", imagecount, cumulated_time/imagecount);  
        printf("-------------------------------------------------------------\n");
        /*
      	zmq_recv(client, view(image).begin().x(), size, 0);
      	GilToMat(image, frame),

      	g_print("client received frame!\n\n");
        imshow("server", frame);

        sprintf(imagename,"server_%08d.png",imagecount);
      	imwrite(imagename,frame);
        
      	waitKey(1);
        */
        ++imagecount;
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
	return 0;
}
