#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "CommandLineParser.h"

struct position
{
    std::vector<int> bestRow {};
    std::vector<int> bestCol {};
};

int main(int argc, char** argv) {
    shapeMatching::CommandLineParser commandLineParser{};
    commandLineParser.parseCommandLine(argc, argv);

//    Convert image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(commandLineParser.image, grayImage, cv::COLOR_BGR2GRAY);

    cv::Mat grayShape;
    cv::cvtColor(commandLineParser.shape, grayShape, cv::COLOR_BGR2GRAY);

//    cv::Mat dx, dy;
//    Sobel(grayImage, dx, CV_32F, 1,0);
//    Sobel(grayImage, dy, CV_32F, 0,1);
//
//    cv::Mat angle, mag;
//    cartToPolar(dx, dy, mag, angle);


//    Performing edge detection in order to find direction vectors
    cv::Mat imageEdges;
    cv::Canny(grayImage, imageEdges, 20, 20);

    cv::Mat shapeEdges;
    cv::Canny(grayShape, shapeEdges, 20, 20);


    position position{};
    for (int x = 0; x < commandLineParser.image.cols - commandLineParser.shape.cols; ++x)
    {
        for (int y = 0; y < commandLineParser.image.rows - commandLineParser.shape.rows; ++y)
        {
            auto s = 0.0f;

//            Calculating s with the given formula from the paper
            for (int j = 0; j < commandLineParser.shape.cols; ++j)
            {
                for (int i = 0; i < commandLineParser.shape.rows; ++i)
                {
                    int pImage = imageEdges.at<uchar>(y+i, x+j);
                    int pShape = shapeEdges.at<uchar>(i, j);

                    s += pImage * pShape;
                }
            }
            s = s / (float)commandLineParser.shape.cols * (float)commandLineParser.shape.rows;

//            Thresholding our result
            if ( s > 80000000 )
            {
                position.bestRow.push_back(y);
                position.bestCol.push_back(x);
            }
        }
    }

//    Display find positions on the image
    for (int i = 0; i < position.bestRow.size(); ++i)
    {
        auto rect = cv::Rect(position.bestCol[i], position.bestRow[i], grayShape.cols, grayShape.rows);
        cv::rectangle(commandLineParser.image, rect, cv::Scalar(255,0,0),1,8,0);
    }

    cv::imshow( "Image", commandLineParser.image);
    cv::waitKey(0);

    return 0;
}
