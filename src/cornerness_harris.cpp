#include <iostream>
#include <numeric>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>

using namespace std;

void cornernessHarris()
{
    // load image from file
    cv::Mat img;
    img = cv::imread("images/img1.png");
    cv::cvtColor(img, img, cv::COLOR_BGR2GRAY); // convert to grayscale

    // Detector parameters
    int blockSize = 2;     // for every pixel, a blockSize × blockSize neighborhood is considered
    int apertureSize = 3;  // aperture parameter for Sobel operator (must be odd)
    int minResponse = 100; // minimum value for a corner in the 8bit scaled response matrix
    double k = 0.04;       // Harris parameter (see equation for details)

    // Detect Harris corners and normalize output
    cv::Mat dst, dst_norm, dst_norm_scaled;
    dst = cv::Mat::zeros(img.size(), CV_32FC1);
    cv::cornerHarris(img, dst, blockSize, apertureSize, k, cv::BORDER_DEFAULT);
    cv::normalize(dst, dst_norm, 10, 255, cv::NORM_MINMAX, CV_32FC1, cv::Mat());
    cv::convertScaleAbs(dst_norm, dst_norm_scaled);
/*
    int max{}, min{20000};
     for (int x = 0;x < img.rows; x++)//To loop through all the pixels
        {
            for (int y = 0; y < img.cols; y++)
            {
                int pix = dst.at<uchar>(x,y);
                int pix2 = dst_norm.at<uchar>(x,y);
                int pix3 = dst_norm_scaled.at<uchar>(x,y);
                if(pix > max)
                    max = pix;
                if(pix < min)
                    min = pix;

                //std::cout << pix1 << " " << pix2 << " " << pix3 << std::endl;
            }

        }
        std::cout << "min : " << min << "  max : " << max << std::endl;
*/
    // visualize results
    string windowName = "Harris Corner Detector Response Matrix";
    cv::namedWindow(windowName, 4);
    cv::imshow(windowName, dst_norm);
    cv::waitKey(0);

    // TODO: Your task is to locate local maxima in the Harris response matrix 
    // and perform a non-maximum suppression (NMS) in a local neighborhood around 
    // each maximum. The resulting coordinates shall be stored in a list of keypoints 
    // of the type `vector<cv::KeyPoint>`.

}

int main()
{
    cornernessHarris();
}