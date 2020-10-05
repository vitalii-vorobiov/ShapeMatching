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

void addPosition(float threshold, std::vector<float> &arr, position &position, int x, int y) {
//    Push initial values to the array
    if (arr.empty()) {
        position.bestCol.push_back(x);
        position.bestRow.push_back(y);
        arr.push_back(threshold);
    }

//    if current threshold is greater than some from the array, replace it
    for (int i = 0; i < arr.capacity(); ++i) {
        if (threshold > arr[i]) {
            position.bestCol[i] = x;
            position.bestRow[i] = y;
            arr[i] = threshold;
            break;
        }
    }

//    fill the array if we have not yet gone beyond its size (current top 3)
    if (arr.capacity() < 3) {
        position.bestCol.push_back(x);
        position.bestRow.push_back(y);
        arr.push_back(threshold);
    }
}

int main(int argc, char** argv) {
    shapeMatching::CommandLineParser commandLineParser{};
    commandLineParser.parseCommandLine(argc, argv);

//    Convert image to grayscale
    cv::Mat grayImage;
    cv::cvtColor(commandLineParser.image, grayImage, cv::COLOR_BGR2GRAY);

    cv::Mat grayShape;
    cv::cvtColor(commandLineParser.shape, grayShape, cv::COLOR_BGR2GRAY);

//    Performing edge detection in order to find direction vectors
    cv::Mat imageEdges;
    cv::Canny(grayImage, imageEdges, 20, 20);

    cv::Mat shapeEdges;
    cv::Canny(grayShape, shapeEdges, 20, 20);


    position position{};
    std::vector<float> thresholds;
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

            addPosition(s, thresholds, position, x, y);
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
