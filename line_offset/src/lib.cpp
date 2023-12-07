#include "lib.h"

double crossProduct(const Points2d &a, const Points2d &b)
{
    return a.x * b.y - a.y * b.x;
}

OffsetDirection determineTurn(const Points2d &prev, const Points2d &curr, const Points2d &next)
{
    Points2d vec1 = {curr.x - prev.x, curr.y - prev.y};
    Points2d vec2 = {next.x - curr.x, next.y - curr.y};
    double res = crossProduct(vec1, vec2);
    return res > 0 ? OffsetDirection::LEFT : OffsetDirection::RIGHT;
}

void offsetSegment(const Points2d &p1, const Points2d &p2, double offsetDistance, OffsetDirection direction, Points2d &newP1, Points2d &newP2)
{
    // Direction vector
    Points2d dir = {p2.x - p1.x, p2.y - p1.y};
    // Normal vector (perpendicular)
    Points2d normal = {-dir.y, dir.x};

    // Depending on the direction, use the normal vector to offset the points
    double length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
    normal.x = (normal.x / length) * offsetDistance;
    normal.y = (normal.y / length) * offsetDistance;

    if (direction == OffsetDirection::RIGHT)
    {
        normal.x = -normal.x;
        normal.y = -normal.y;
    }

    newP1.x = p1.x + normal.x;
    newP1.y = p1.y + normal.y;
    newP2.x = p2.x + normal.x;
    newP2.y = p2.y + normal.y;
}

int findIntersection(const Points2d &p1, const Points2d &p2, const Points2d &p3, const Points2d &p4)
{
    double denominator = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);

    // Check if lines are parallel (denominator is zero)
    if (denominator == 0)
    {
        return 0; // No intersection (parallel lines)
    }

    double t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / denominator;
    double u = ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denominator;

    // Check if the intersection point lies on both line segments
    if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
    {
        return 1; // Intersection in the middle of both segments
    }
    else if (t < 0 || t > 1 || u < 0 || u > 1)
    {
        return 2; // Intersection outside of both segments
    }

    return 0; // No intersection
}

std::vector<Points2d> offsetPolyline(const std::vector<Points2d> &points, double offsetDistance, OffsetDirection initialDirection)
{
    std::vector<Points2d> offsetPoints;

    if (points.size() < 2)
    {
        // Not enough points to form a line
        return offsetPoints;
    }

    // Offset the first segment
    Points2d newP1, newP2;
    offsetSegment(points[0], points[1], offsetDistance, initialDirection, newP1, newP2);
    offsetPoints.push_back(newP1);

    for (size_t i = 1; i < points.size() - 1; ++i)
    {
        // Determine the turn direction at the current point
        OffsetDirection direction = determineTurn(points[i - 1], points[i], points[i + 1]);

        // For the next segment, we only need to calculate the new endpoint
        offsetSegment(points[i], points[i + 1], offsetDistance, direction, newP1, newP2);
        offsetPoints.push_back(newP1);
    }

    // Add the last offset point
    offsetPoints.push_back(newP2);

    return offsetPoints;
}