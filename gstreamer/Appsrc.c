
#include <gst/gst.h>
#include "opencv2/opencv.hpp"
using namespace cv;
static GMainLoop *loop;

static void
cb_need_data (GstElement *appsrc, guint unused_size, gpointer user_data)
{
  //static gboolean white = FALSE;
  static GstClockTime timestamp = 0;
  GstBuffer *buffer;
  guint size;
  GstFlowReturn ret;
  Mat* pImage = (Mat *)user_data;
  size = 640 * 480 * 3;
  //size = pImage->rows * pImage->cols * pImage->elemSize();
  g_print("pImage = %x user_data =%x\n",pImage, user_data);
  g_print("pImage.rows = %d, pImage.cols = %d, pImage.elemSize = %lu \n", pImage->rows, pImage->cols, pImage->elemSize());
  buffer = gst_buffer_new_wrapped (pImage->data, size);
  g_print("gst_buffer_new_wrapped done\n");
  /* this makes the image black/white */
  //gst_buffer_memset (buffer, 0, white ? 0xff : 0x0, size);
  
  //white = !white;

  GST_BUFFER_PTS (buffer) = timestamp;
  GST_BUFFER_DURATION (buffer) = gst_util_uint64_scale_int (1, GST_SECOND, 2);

  timestamp += GST_BUFFER_DURATION (buffer);

  g_signal_emit_by_name (appsrc, "push-buffer", buffer, &ret);
  g_print("g_signal_emit_by_name done\n");
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
  //GstElement *pipeline, *appsrc, *conv, *videosink;
  GstElement *pipeline, *appsrc, *filesink;

  /* init GStreamer */
  gst_init (&argc, &argv);

  Mat image;
  image = imread("image_000.png", CV_LOAD_IMAGE_COLOR);

  namedWindow("My Window", WINDOW_AUTOSIZE);
  imshow("My Window", image);

  waitKey(100);
  destroyWindow("My Window");

  g_print("image = %x, image.rows = %d, image.cols = %d, image.elemSize = %lu \n", &image, image.rows, image.cols, image.elemSize());


  loop = g_main_loop_new (NULL, FALSE);

  /* setup pipeline */
  pipeline = gst_pipeline_new ("pipeline");
  appsrc = gst_element_factory_make ("appsrc", "source");
  //conv = gst_element_factory_make ("videoconvert", "conv");
  //videosink = gst_element_factory_make ("xvimagesink", "videosink");
  filesink = gst_element_factory_make ("multifilesink", "filesink");

  /* setup */
  g_object_set (G_OBJECT (appsrc), "caps",
      gst_caps_new_simple ("video/x-raw",
             "format", G_TYPE_STRING, "RGB16",
             "width", G_TYPE_INT, 640,
             "height", G_TYPE_INT, 480,
             "framerate", GST_TYPE_FRACTION, 0, 1,
             NULL), NULL);
  gst_bin_add_many (GST_BIN (pipeline), appsrc, filesink, NULL);
  gst_element_link_many (appsrc, filesink, NULL);

  /* setup appsrc */
  g_object_set (G_OBJECT (appsrc),
    "stream-type", 0,
    "format", GST_FORMAT_TIME, NULL);
  g_signal_connect (appsrc, "need-data", G_CALLBACK (cb_need_data), (gpointer)&image);

  /* play */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  g_main_loop_run (loop);

  /* clean up */
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (GST_OBJECT (pipeline));
  g_main_loop_unref (loop);
  image.release();

  return 0;
  }