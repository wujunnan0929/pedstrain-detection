#include <stdio.h>
#include "opencv2/opencv.hpp"
using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
        printf(" Usage: display_image ImageToLoadAndDisplay \n");
     return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        printf( "Could not open or find the image\n");
        return -1;
    }
    Mat image100;
    resize(image,image100,Size(100,100),0,0,CV_INTER_LINEAR);
    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", image100 );                   // Show our image inside it.
    imwrite("lena_100_100.jpg",image100);

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
