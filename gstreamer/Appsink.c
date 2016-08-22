#include <gst/gst.h>
#include <gst/app/gstappsink.h>
#include <stdlib.h>
#include <stdio.h>
#include <zmq.h>
#include <unistd.h>
#include "opencv2/opencv.hpp"
using namespace cv;


// TODO: use synchronized deque
std::deque<Mat> frameQueue;

GstFlowReturn new_preroll(GstAppSink *appsink, gpointer data) {
  g_print ("Got preroll!\n");
  return GST_FLOW_OK;
}

GstFlowReturn new_sample(GstAppSink *appsink, gpointer data) {
  static int framecount = 0;
  framecount++;

  GstSample *sample = gst_app_sink_pull_sample(appsink);
  GstCaps *caps = gst_sample_get_caps(sample);
  GstBuffer *buffer = gst_sample_get_buffer(sample);

  // ---- Read frame and convert to opencv format ---------------

  GstMapInfo map;
  gst_buffer_map (buffer, &map, GST_MAP_READ);

  // convert gstreamer data to OpenCV Mat, you could actually
  // resolve height / width from caps...
  int width = 1600;
  int height = 1200;
  int bufLen = width * height;
 
  unsigned char* pYuvBuf = new unsigned char[width * height * 3 / 2];
  unsigned char* pRgbBuf = new unsigned char[width * height * 3];
  memcpy(pYuvBuf, map.data, bufLen*3/2*sizeof(unsigned char));

  Mat rgbFrame(height, width, CV_8UC3, pRgbBuf);
  Mat yuvFrame(height*3/2, width, CV_8UC1, pYuvBuf);
  //printf("scn = %d  src_depth =%d dcn =%d dst_depth=%d\n", yuvFrame.channels(), yuvFrame.depth(), rgbFrame.channels(), rgbFrame.depth());
  
  cvtColor(yuvFrame, rgbFrame, CV_YUV2BGR_IYUV);
  
  // TODO: synchronize this....
  frameQueue.push_back(rgbFrame);

  gst_buffer_unmap(buffer, &map);


  // show caps on first frame
  if (framecount == 1) {
    g_print ("%s\n", gst_caps_to_string(caps));
  }

  gst_sample_unref (sample);
  return GST_FLOW_OK;
}

static gboolean my_bus_callback (GstBus *bus, GstMessage *message, gpointer data) {
  g_print ("Got %s message\n", GST_MESSAGE_TYPE_NAME (message));
  switch (GST_MESSAGE_TYPE (message)) {
    case GST_MESSAGE_ERROR: {
      GError *err;
      gchar *debug;

      gst_message_parse_error (message, &err, &debug);
      g_print ("Error: %s\n", err->message);
      g_error_free (err);
      g_free (debug);    
      break;
    }
    case GST_MESSAGE_EOS:
      g_print ("End Of Stream!\n");
      /* end-of-stream */
      break;
    default:
      /* unhandled message */
      break;
  }
  /* we want to be notified again the next time there is a message
   * on the bus, so returning TRUE (FALSE means we want to stop watching
   * for messages on the bus and our callback should not be called again)
   */
  return TRUE;
}

int main (int argc, char *argv[])
{
  GError *error = NULL;
  gsize size;
  static int imagecount = 0;
  gchar imagename[19]= "";
  void *context = zmq_ctx_new ();
  void *client = zmq_socket (context, ZMQ_REQ);
  zmq_connect (client, "tcp://10.113.64.54:5556");
  
  /*void *server = zmq_socket(context, ZMQ_SUB);
  zmq_connect(server,"tcp://172.17.0.10:5556");
  zmq_setsockopt(server, ZMQ_SUBSCRIBE, NULL,0);*/
  gst_init (&argc, &argv);

  gchar *descr = g_strdup(
    "v4l2src ! "
    "video/x-raw,format=I420,width=1600,height=1200,framerate=15/1 ! "
    "decodebin ! "
    "appsink name=sink " // could not set to true then i remove the true set
  );
  GstElement *pipeline = gst_parse_launch (descr, &error);

  if (error != NULL) {
    g_print ("could not construct pipeline: %s\n", error->message);
    g_error_free (error);
    exit (-1);
  }

  /* get sink */
  GstElement *sink = gst_bin_get_by_name (GST_BIN (pipeline), "sink");

  gst_app_sink_set_emit_signals((GstAppSink*)sink, true);
  gst_app_sink_set_drop((GstAppSink*)sink, true);
  gst_app_sink_set_max_buffers((GstAppSink*)sink, 1);
  GstAppSinkCallbacks callbacks = { NULL, new_preroll, new_sample };
  gst_app_sink_set_callbacks (GST_APP_SINK(sink), &callbacks, NULL, NULL);

  GstBus *bus;
  bus = gst_pipeline_get_bus (GST_PIPELINE (pipeline));
  gst_bus_add_watch (bus, my_bus_callback, NULL);
  gst_object_unref (bus);

  gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_PLAYING);

  while(1) {
    g_main_iteration(false);

      // TODO: synchronize...
    if (frameQueue.size() > 0) {
      // this lags pretty badly even when grabbing frames from webcam
      Mat frame = frameQueue.front();
      /*Mat frame;
      resize(frame1,frame,Size(640,480),0,0,CV_INTER_LINEAR); 
      imwrite("1600_1200.png",frame1);
      imwrite("640_480.png",frame);*/
      size = frame.rows * frame.cols * frame.elemSize();
      printf("row = %d, cols = %d \n",frame.rows, frame.cols);    
      imshow("client", frame);
      sprintf(imagename,"client_%08d.png",imagecount);
      imwrite(imagename,frame);
      //send image to server,wait for recving labeled image 
      zmq_send(client, frame.data, size, 0);
      g_print("client send frame!\n");
      zmq_recv(client, frame.data, size, 0);
      g_print("client received frame!\n\n");
      imshow("server", frame);
      sprintf(imagename,"server_%08d.png",imagecount);
      //imwrite(imagename,frame);
      frameQueue.clear();
      imagecount++;
    }
  }  

  gst_element_set_state (GST_ELEMENT (pipeline), GST_STATE_NULL);
  gst_object_unref (GST_OBJECT (pipeline));

  return 0;  
}
