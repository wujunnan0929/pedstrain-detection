#ifndef VIDEOFROMCAMERA_HPP
#define VIDEOFROMCAMERA_HPP


#include "AbstractVideoInput.hpp"

#include "preprocessing/AbstractPreprocessor.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/format.hpp>

#include <boost/thread.hpp>

#include <zmq.h>
#include "opencv2/opencv.hpp"


namespace doppia
{

using boost::shared_ptr;

///
/// Loads images from a video stream stored as a set of images.
/// Supports a preprocessor object for things like unbayering, rectification, etc ...
///
/// Based on Andreas Ess code
///
class VideoFromCamera : public AbstractVideoInput
{
public:


    static boost::program_options::options_description get_args_options();

    VideoFromCamera(const boost::program_options::variables_map &options,
                   const shared_ptr<StereoCameraCalibration> &stereo_calibration_p);
    ~VideoFromCamera();

    bool next_frame();

    const input_image_view_t &get_left_image();

	bool pull_stream();
	void mat_to_image(const cv::Mat &m, input_image_t &img);
	void image_to_mat(const cv::Mat &m, input_image_t &img);

    /// VideoFromCamera will take ownership over the preprocessor object.
    /// When VideoFromCamera object is destroyed, AbstractPreprocessor will probably be destroyed too..
    void set_preprocessor(const shared_ptr<AbstractPreprocessor> &preprocessor);
    const shared_ptr<AbstractPreprocessor> &get_preprocessor() const;

    const StereoCameraCalibration& get_stereo_calibration() const;

protected:

    /// Base for directory and filename
    std::string left_filename_mask, right_filename_mask;
    boost::format left_filename_format, right_filename_format;

    int start_frame, end_frame, total_number_of_frames;

    shared_ptr<StereoCameraCalibration> stereo_calibration_p;

    /// Optional preprocessor object
    shared_ptr<AbstractPreprocessor> preprocessor_p;

    input_image_t left_image, right_image;
    input_image_view_t left_image_view, right_image_view;

	Mat cvFrame;

	std::string socket_addr;
	void *context, *responder;
	int frame_width, frame_height, frame_depth, frame_channel;
	std::string frame_type;

};

} // end of namespace doppia

#endif
