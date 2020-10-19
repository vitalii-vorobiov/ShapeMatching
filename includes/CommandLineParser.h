//
// Created by Vitaliy Vorobyov on 21.09.2020.
//

#ifndef SHAPEMATCHING_COMMANDLINEPARSER_H
#define SHAPEMATCHING_COMMANDLINEPARSER_H

namespace shapeMatching
{
    class CommandLineParser
    {
    public:
        cv::Mat image;
        cv::Mat shape;
        int parseCommandLine(int argc, char** argv);
    };
}

#endif //SHAPEMATCHING_COMMANDLINEPARSER_H
