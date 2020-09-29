//
// Created by Vitaliy Vorobyov on 21.09.2020.
//

#include <iostream>
#include <boost/program_options.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/stitching.hpp>

#include "CommandLineParser.h"

namespace po = boost::program_options;

int shapeMatching::CommandLineParser::parseCommandLine(int argc, char **argv)
{
    po::options_description desc("General options");
    desc.add_options()
            ("help,h", "Show help")
            ("image,i", po::value<std::string>(), "Input image in which you want to find a shape")
            ("shape,t", po::value<std::string>(), "A shape that you will search for")
            ;

    po::variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc << std::endl;
        return EXIT_SUCCESS;
    }

    if (vm.count("image"))
    {
        std::string image_name = vm["image"].as<std::string>();
        image = cv::imread(cv::samples::findFile(image_name));
        if (image.empty())
        {
            std::cout << "Can't read image '" << image_name << std::endl;
            return EXIT_FAILURE;
        }
    }

    if (vm.count("shape"))
    {
        std::string template_name = vm["shape"].as<std::string>();
        shape = cv::imread(cv::samples::findFile(template_name));
        if (shape.empty())
        {
            std::cout << "Can't read image '" << template_name << std::endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}