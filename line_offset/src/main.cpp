#include "lib.h"
#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    // std::vector<Points2d> initialPath = {
    //     {100, 100},
    //     {200, 100},
    //     {200, 200},
    //     {100, 200},
    //     {100, 300},
    //     {200, 300},
    //     {400, 400},
    //     {440, 500},
    // };

    std::vector<Points2d> initialPath = {
        {100, 500},
        {150, 400},
        {200, 350},
        {250, 320},
        {300, 300},
        {350, 200},
        {400, 150},
        {440, 100},
    };

    // Offset distance and direction
    double offsetDistance = 10.0;

    // Calculate the offset path
    std::vector<Points2d> offsetPolylineRight = offsetPolyline(initialPath, offsetDistance, OffsetDirection::RIGHT);
    std::vector<Points2d> offsetPolylineLeft = offsetPolyline(initialPath, offsetDistance, OffsetDirection::LEFT);

    // Create an image to draw the polylines
    int width = 800, height = 800;
    Mat image = Mat::zeros(height, width, CV_8UC3);

    // Draw the original polyline
    for (size_t i = 0; i < initialPath.size() - 1; ++i) {
        cv::line(image, Point(initialPath[i].x, initialPath[i].y), Point(initialPath[i+1].x, initialPath[i+1].y), Scalar(255, 0, 0), 2);
    }

    for (size_t i = 0; i < offsetPolylineRight.size() - 1; ++i) {
        cv::line(image, Point(offsetPolylineRight[i].x, offsetPolylineRight[i].y), Point(offsetPolylineRight[i+1].x, offsetPolylineRight[i+1].y), Scalar(0, 255, 0), 2);
    }

    for (size_t i = 0; i < offsetPolylineLeft .size() - 1; ++i) {
        cv::line(image, Point(offsetPolylineLeft[i].x, offsetPolylineLeft[i].y), Point(offsetPolylineLeft[i+1].x, offsetPolylineLeft[i+1].y), Scalar(0, 0, 255), 2);
    }

    // Show the image
    namedWindow("Polyline", WINDOW_AUTOSIZE);
    imshow("Polyline", image);
    waitKey(0);

    return 0;
}