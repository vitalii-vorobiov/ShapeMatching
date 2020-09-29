#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "CommandLineParser.h"

int main(int argc, char** argv) {
    shapeMatching::CommandLineParser commandLineParser{};
    commandLineParser.parseCommandLine(argc, argv);

    cv::Mat grayImage;
    cv::cvtColor(commandLineParser.image, grayImage, cv::COLOR_BGR2GRAY);

    cv::Mat contours;
    cv::Canny(grayImage, contours, 10, 30);

    cv::imshow( "Image", contours);
    cv::waitKey(0);

    return 0;
}
