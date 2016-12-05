#include <gst/gst.h>
#include <gst/app/gstappsink.h>
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

using namespace std;
using namespace boost::gil;

int main()
{
	rgb8_image_t image;
	//png_read_image("640_480.png", image);
	//printf("image size= %u dimensions= %u num_channels= %u\n", view(image).size(), view(image).num_dimensions, num_channels<rgb8_pixel_t>::value);

	//  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);

    image.recreate(640, 480);
    unsigned long size;
    while (1) {
        printf("Server Begin Receive...\n");
        zmq_recv (responder, view(image).begin().x(), 640*480*3, 0);
        printf ("Server Received frame!\n");
        rgb8c_view_t input_view= view(image);
        //png_write_view("boost_gil_server.png", input_view);
        printf("image size= %lu dimensions= %lu num_channels= %ld\n", view(image).size(), view(image).num_dimensions, num_channels<rgb8_pixel_t>::value);
        
        zmq_send (responder, view(image).begin().x(), 640*480*3, 0);
        printf ("Server send frame!\n\n");
    }

	return 0;
}