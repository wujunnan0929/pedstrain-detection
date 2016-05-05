
#include <gst/gst.h>
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
using namespace cv;

static GMainLoop *loop;
static gint framecount = 0;
static gchar imagename[19]="";
static void
cb_need_data (GstElement *appsrc, guint unused_size, gpointer user_data)
{
  //static gboolean white = FALSE;
  g_print("\nmain loop:cb_need_data Iteration:%d \n",framecount);

  static gboolean white = FALSE;
  static GstClockTime timestamp = 0;
  GstBuffer* buffer;
  GstBuffer* newbuffer;
  gsize size;
  gsize amount;
  GstFlowReturn ret;
  Mat image;
  sprintf(imagename,"image_%08d.png",framecount);
  framecount++;
  image = imread(imagename, CV_LOAD_IMAGE_COLOR);
  if(!image.data)
  {
    g_print("%s is not readable!\n",imagename);
    g_main_loop_quit (loop);
    g_print("g_main_loop_quit done\n");
    return ;
  }
  g_print("%s is loaded!\n",imagename);

  

  size = image.rows * image.cols * image.elemSize();

  g_print("image.rows = %d, image.cols = %d, image.elemSize = %lu \n", image.rows, image.cols, image.elemSize());


  buffer = gst_buffer_new_allocate (NULL, size, NULL);
  amount = gst_buffer_fill(buffer, 0, image.data, size);
  g_print("gst_buffer_new_fill filled %lu bytes.\n",amount);


  GST_BUFFER_PTS (buffer) = timestamp;
  GST_BUFFER_DURATION (buffer) = gst_util_uint64_scale_int (1, GST_SECOND, 2);

  timestamp += GST_BUFFER_DURATION (buffer);

  g_signal_emit_by_name (appsrc, "push-buffer", buffer, &ret);
  g_print("g_signal_emit_by_name done\n\n");
  if (ret != GST_FLOW_OK) {
    /* something wrong, stop pushing */
    g_print("something wrong, stop pushing.\n");
    g_main_loop_quit (loop);
    g_print("g_main_loop_quit done\n");
  }
}

gint
main (gint   argc,
      gchar *argv[])
{
  GstElement *pipeline, *appsrc, *conv, *videosink;


  /* init GStreamer */
  gst_init (&argc, &argv);
  //gint framecount = 0;


  //g_print("image = %x, image.rows = %d, image.cols = %d, image.elemSize = %lu \n", &image, image.rows, image.cols, image.elemSize());


  loop = g_main_loop_new (NULL, FALSE);

  /* setup pipeline */
  pipeline = gst_pipeline_new ("pipeline");
  appsrc = gst_element_factory_make ("appsrc", "source");
  conv = gst_element_factory_make ("videoconvert", "conv");
  videosink = gst_element_factory_make ("xvimagesink", "videosink");


  /* setup */
  g_object_set (G_OBJECT (appsrc), "caps",
      gst_caps_new_simple ("video/x-raw",
             "format", G_TYPE_STRING, "BGR",
             "width", G_TYPE_INT, 1600,
             "height", G_TYPE_INT, 1200,
             "framerate", GST_TYPE_FRACTION, 15, 1,
             NULL), NULL);

  gst_bin_add_many (GST_BIN (pipeline), appsrc, conv, videosink, NULL);
  gst_element_link_many (appsrc, conv, videosink, NULL);




  /* setup appsrc */
  g_object_set (G_OBJECT (appsrc),
    "stream-type", 0,
    "format", GST_FORMAT_TIME, NULL);
  g_signal_connect (appsrc, "need-data", G_CALLBACK (cb_need_data), NULL);

  /* play */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  g_main_loop_run (loop);

  /* clean up */
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (GST_OBJECT (pipeline));
  g_main_loop_unref (loop);

  return 0;
  }