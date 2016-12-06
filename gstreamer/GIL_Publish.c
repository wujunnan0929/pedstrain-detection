#include <stdlib.h>
#include <stdio.h>
#include <zmq.h>
#include <unistd.h>
#include <boost/gil/image_view.hpp>
#include <boost/gil/image.hpp>
#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include <time.h>

using namespace std;
using namespace boost::gil;

int main()
{
    void *context = zmq_ctx_new ();
    //void *client = zmq_socket (context, ZMQ_REQ);
    //zmq_connect (client, "tcp://10.113.64.54:5556");
    //zmq_connect (client, "tcp://localhost:5555");
    void *publisher = zmq_socket (context, ZMQ_PUB);
    zmq_bind (publisher, "tcp://*:5556");
    int imagecount = 0;
    char imagename[19]= "";
    clock_t start, finish;
    double time, cumulated_time;
    cumulated_time = 0;
    rgb8_image_t image;
    png_read_image("buffer.png", image);
    rgb8c_view_t input_view= view(image);
    while(imagecount <460)
    {
        start = clock();
        sprintf(imagename,"client_%08d.png",imagecount);
     
      	//zmq_send(client, view(image).begin().x(), view(image).size()*num_channels<rgb8_pixel_t>::value, 0);
      	zmq_send(publisher, view(image).begin().x(), view(image).size()*num_channels<rgb8_pixel_t>::value, 0);
        printf("client send frame_%08d!\n", imagecount);
        finish = clock();
        time = (double)(finish - start)/CLOCKS_PER_SEC;
        printf("used %fs.\n", time);
        cumulated_time += time;
	++imagecount;
        if((imagecount%20) == 0)
        printf("Sum %d fames used average time is %.4lf. %.4lf[HZ].\n", imagecount, cumulated_time/imagecount, imagecount/cumulated_time);  
        printf("-------------------------------------------------------------\n");
        /*
      	zmq_recv(client, view(image).begin().x(), size, 0);
      	GilToMat(image, frame),

      	printf("client received frame!\n\n");
        imshow("server", frame);

        sprintf(imagename,"server_%08d.png",imagecount);
      	imwrite(imagename,frame);
        
      	waitKey(1);
        */
    }
    printf("press any key to end.\n");
    char ch;
    scanf("%c",&ch);
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}
