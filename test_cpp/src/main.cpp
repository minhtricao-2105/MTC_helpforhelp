#include "clipper.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "sample.h"

using namespace ClipperLib;
using namespace cv;

int main() {
    
    std::vector<Points2d> polyline = {
        {100.0f, 100.0f},   
        {150.0f, 150.0f},  
        {120.0f, 300.0f},  
        {300.0f, 300.0f},
        {300.0f, 100.0f},
        {100.0f, 100.0f}
    };

    // std::vector<Points2d> polyline = {
    //     {100.0f, 100.0f},   
    //     {100.0f, 500.0f}, 
    //     {500.0f, 500.0f},   
    //     {500.0f, 100.0f},  
    //     {100.0f, 100.0f}
    // };

    double offsetDistance = 30.0;
    std::vector<Points2d> offsetPolylineRight = offsetPolyline(polyline, offsetDistance, OffsetDirection::OUT, ClipperLib::jtSquare);

    // Create an image to draw the polylines
    int width = 800, height = 800;
    Mat image = Mat::zeros(height, width, CV_8UC3);

    // Draw the original polyline
    for (size_t i = 0; i < polyline.size() - 1; ++i) {
        cv::line(image, Point(polyline[i].x, polyline[i].y), Point(polyline[i+1].x, polyline[i+1].y), Scalar(255, 0, 0), 2);
    }

    for (size_t i = 0; i < offsetPolylineRight.size() - 1; ++i) {
        cv::line(image, Point(offsetPolylineRight[i].x, offsetPolylineRight[i].y), Point(offsetPolylineRight[i+1].x, offsetPolylineRight[i+1].y), Scalar(0, 255, 0), 2);
    }
    // Show the image
    namedWindow("Polyline", WINDOW_AUTOSIZE);
    imshow("Polyline", image);
    waitKey(0);

    return 0;
}
