#ifndef SAMPLE_H
#define SAMPLE_H

#include <vector>   
#include <iostream>
#include <opencv2/opencv.hpp>
#include "clipper.hpp"

struct Points2d
{
    float x, y;
};

// enum JoinType {jtSquare, jtRound, jtMiter};
enum OffsetDirection {IN, OUT};

std::vector<Points2d> offsetPolyline(const std::vector<Points2d>& points, double offsetDistance, OffsetDirection direction, ClipperLib::JoinType jt);

#endif // SAMPLE_H