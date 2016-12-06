#include <zmq.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

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
    clock_t start1, finish1, start2, finish2;
    double time, cumulated_recv_time, cumulated_send_time, cumulated_sum_time;
    time = 0;
    cumulated_recv_time = 0;
    cumulated_send_time = 0;
    cumulated_sum_time = 0;

    rgb8_image_t image;
    int frame_width, frame_height, count;
    frame_width = 640;
    frame_height = 480;
    count = 0;
    //png_read_image("640_480.png", image);
    //printf("image size= %u dimensions= %u num_channels= %u\n", view(image).size(), view(image).num_dimensions, num_channels<rgb8_pixel_t>::value);

    //  Socket to talk to clients
    void *context, *subscriber, *publisher;
    int rc;
    context = zmq_ctx_new ();
    subscriber = zmq_socket(context, ZMQ_SUB);
    rc = zmq_connect(subscriber, "tcp://10.113.64.38:5555");  
    assert (rc == 0);
    zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, NULL, 0);
    
    publisher = zmq_socket(context, ZMQ_PUB);
    rc = zmq_bind(publisher, "tcp://*:5556");
    assert(rc==0);

    image.recreate(frame_width, frame_height);
    unsigned long size;
    while (count<460) {
	//printf("-------------------------------------------------------------------------------------------\n");
	start1 = clock();
        printf("Server Begin Receive...\n");
        zmq_recv (subscriber, view(image).begin().x(), frame_width*frame_height*3, 0);
        printf ("Server Received frame!\n");
	finish1 = clock();
	time = (double)(finish1-start1)/CLOCKS_PER_SEC;
        cumulated_recv_time += time;
        count++;
        if(count%20==0)
	    printf("%d frames zmq_recv used average time:%.4lfs. %.4lf[HZ].\n", count, cumulated_recv_time/count, count/cumulated_recv_time);
        
        //rgb8c_view_t input_view= view(image);
        //png_write_view("boost_gil_server.png", input_view);
        //printf("image size= %lu dimensions= %lu num_channels= %ld\n", view(image).size(), view(image).num_dimensions, num_channels<rgb8_pixel_t>::value);
        
        start2 = clock();
        printf("Server Begin send...\n");
        zmq_send (publisher, view(image).begin().x(), frame_width*frame_height*3, 0);
        printf ("Server sent frame!\n\n");
        finish2 = clock();
        time = (double)(finish2-start2)/CLOCKS_PER_SEC;
        cumulated_recv_time += time;
        if(count%20==0)
            printf("%d frames zmq_send used average time:%.4lfs. %.4lf[HZ].\n", count, cumulated_send_time/count, count/cumulated_send_time);
	
        time = (double)(finish2-start1)/CLOCKS_PER_SEC;
        cumulated_sum_time += time;
	if(count%20==0)
            printf("%d frames zmq Sum used average time:%.4lfs. %.4lf[HZ].\n", count, cumulated_sum_time/count, count/cumulated_sum_time);
        printf("-------------------------------------------------------------------------------------------\n");
    }
    char ch;
    printf("press any key to exit");
    scanf("%c",&ch);
    zmq_close(publisher);
    zmq_close(subscriber);
    zmq_ctx_destroy(context);
    return 0;
}
