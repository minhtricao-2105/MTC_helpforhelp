#ifndef LIB_H
#define LIB_H

#include <iostream>
#include <cmath>
#include <vector>
#include <optional>

struct Points2d 
{
    double x, y;
};

enum OffsetDirection {LEFT, RIGHT};

double crossProduct(const Points2d& a, const Points2d& b);
OffsetDirection determineTurn(const Points2d& prev, const Points2d& curr, const Points2d& next);
void offsetSegment(const Points2d& p1, const Points2d& p2, double offsetDistance, OffsetDirection direction, Points2d& newP1, Points2d& newP2);
std::vector<Points2d> offsetPolyline(const std::vector<Points2d>& points, double offsetDistance, OffsetDirection initialDirection);
int findIntersection(const Points2d& p1, const Points2d& p2, const Points2d& p3, const Points2d& p4);

#endif // LIB_H
