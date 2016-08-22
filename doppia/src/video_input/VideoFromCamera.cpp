
#include "VideoFromCamera.hpp"

#include "calibration/StereoCameraCalibration.hpp"

#include "helpers/get_option_value.hpp"

#include <limits>

#include <boost/filesystem.hpp>

#include <boost/gil/image_view.hpp>
#include <boost/gil/extension/io/png_io.hpp>

#include <omp.h>

namespace doppia
{

using namespace std;
using namespace boost;

program_options::options_description VideoFromCamera::get_args_options()
{
    program_options::options_description desc("VideoFromCamera options");

    desc.add_options()

            // @param mask string containing directory and filename, except
            // an %d for sprintf to be replaced by frame number, e.g. image_%08d.pgm

            ("video_input.left_filename_mask",
             program_options::value<string>(),
             "sprintf mask for left image files input. Will receive the frame number as input. Example: the_directory/left_%05d.png")

            ("video_input.right_filename_mask",
             program_options::value<string>(),
             "sprintf mask for right image files input. Will receive the frame number as input. Example: the_directory/right_%05d.png")

            ("video_input.frame_rate",
             program_options::value<int>()->default_value(15), "video input frame rate")

            ("video_input.frame_width",
             program_options::value<int>()->default_value(640), "video input frame width in pixels")

            ("video_input.frame_height",
             program_options::value<int>()->default_value(480), "video input frame height in pixels" )

            ("video_input.start_frame",
             program_options::value<int>()->default_value(0), "first image to read")

            ("video_input.end_frame",
             program_options::value<int>(), "last image to read, if omited will read all files matching the masks")
            ;


    return desc;
}


VideoFromCamera::VideoFromCamera(const program_options::variables_map &options,
                               const shared_ptr<StereoCameraCalibration> &stereo_calibration_p)
    : AbstractVideoInput(options)
{

    total_number_of_frames = -1;

    this->stereo_calibration_p = stereo_calibration_p;
    // this->preprocessor_p is left uninitialzied until ::set_preprocessor is called

    left_filename_mask = get_option_value<string>(options, "video_input.left_filename_mask");
    right_filename_mask = get_option_value<string>(options, "video_input.right_filename_mask");

	socket_addr = get_option_value<string>(options,"video_input.socket_addr");
	frame_width = get_option_value<int>(options, "video_input.frame_width");
	frame_height = get_option_value<int>(options, "video_input.frame_height");
	frame_depth = get_option_value<int>(options, "video_input.frame_depth");
	frame_channel = get_option_value<int>(options, "video_input.frame_channel");
	frame_type = get_options_value<string>(options, "video_input.frame_type");

	left_image.recreate(frame_width, frame_height);
	context = zmq_ctx_new();
	responder = zmq_socket(context,ZMQ_REP);
	int rc = zmq_bind(responder, socket_addr);
	assert(rc);


    if(left_filename_mask.empty() or right_filename_mask.empty())
    {
        throw std::runtime_error("Left and right input filename masks should be non empty strings");
    }

    left_filename_format = boost::format(left_filename_mask);
    right_filename_format = boost::format(right_filename_mask);

#if BOOST_VERSION >= 104400 
    // expected_args was only defined in version 1.44
    if(left_filename_format.expected_args() > 1
       or right_filename_format.expected_args() > 1)
    {
        throw std::runtime_error("Found more than one \%i argument in the left (or right) input filename masks");
    }

    if(left_filename_format.expected_args() != right_filename_format.expected_args())
    {
        throw std::runtime_error("left and right input filename masks should have the same number of arguments");
    }
#endif

    // do the first acquisition
	const bool found_frames = this->pull_stream();

    if(left_image_view.dimensions() != right_image_view.dimensions())
    {
        throw std::runtime_error("Left and right input images do not have the same dimensions");
    }

    if(found_frames and ((left_image_view.size() == 0) or  (right_image_view.size() == 0)))
    {
        throw std::runtime_error("Read an empty image file");
    }

    if(found_frames==false)
    {
        throw std::runtime_error("Could not read the first input frames pair");
    }

    return;
}


VideoFromCamera::~VideoFromCamera()
{
    return;
}


const StereoCameraCalibration &VideoFromCamera::get_stereo_calibration() const
{
    if(preprocessor_p)
    {
        return preprocessor_p->get_post_processing_calibration();
    }
    else
    {
        return *stereo_calibration_p;
    }
}


void VideoFromCamera::set_preprocessor(const shared_ptr<AbstractPreprocessor> &preprocessor)
{
    this->preprocessor_p = preprocessor;
    return;
}


const shared_ptr<AbstractPreprocessor> &VideoFromCamera::get_preprocessor() const
{
    return preprocessor_p;
}


/// Advance in stream, return true if successful
bool VideoFromCamera::next_frame()
{
    return this->pull_stream;
}

void mat_to_image(const cv::Mat &m, input_image_t &img) 
{
	for (size_t i = 0; i < img.rows(); ++i)
	{
		for (size_t j = 0; j < img.cols(); ++j)
		{
			// Mat is BGR, not RGB
			img(i, j, 0) = m.at<cv::Vec3b>(i, j)[2];
			img(i, j, 1) = m.at<cv::Vec3b>(i, j)[1];
			img(i, j, 2) = m.at<cv::Vec3b>(i, j)[0];
		}
	}
}

void image_to_mat(const cv::Mat &m, input_image_t &img)
{
	for (size_t i = 0; i < img.rows(); ++i)
	{
		for (size_t j = 0; j < img.cols(); ++j)
		{
			// Mat is BGR, not RGB
			m.at<cv::Vec3b>(i, j)[2] = img(i, j, 0);
			m.at<cv::Vec3b>(i, j)[1] = img(i, j, 1);
			m.at<cv::Vec3b>(i, j)[0] = img(i, j, 2);
		}
	}
}

bool VideoFromCamera::pull_stream()
{
	assert(responder);
	Mat rgbFrame(frame_height, frame_width, CV_8UC3, Scalar::all(0));
	rgbFrame.copyTo(cvFrame);
	zmq_recv(responder, rgbFrame.data, frame_width * frame_height * 3, 0);
	mat_to_image(&rgbFrame, &left_image);
	left_view = boost::gil::const_view(left_image);
	return true;
}


const AbstractVideoInput::input_image_view_t &VideoFromCamera::get_left_image()
{

    return this->left_image_view;
}




} // end of doppia namespace


