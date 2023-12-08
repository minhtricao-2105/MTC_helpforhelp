#include "lib.h"

double getLength(const Points2d& p1, const Points2d& p2)
{
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

double crossProduct(const Points2d &a, const Points2d &b)
{
    return a.x * b.y - a.y * b.x;
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

Points2d findPointAtDistance(const Points2d& p1, const Points2d& p2, double distance, bool condition)
{
    // Calculate the distance between p1 and p2
    double distanceP1P2 = getLength(p1, p2);
    double dirX = (p2.x - p1.x) / distanceP1P2;
    double dirY = (p2.y - p1.y) / distanceP1P2;

    Points2d p3;
    if (condition) {
        // P3 is at a distance from P2, in the direction of P1 to P2
        p3.x = p2.x - dirX * distance;
        p3.y = p2.y - dirY * distance;
    } else {
        // P3 is at a distance from P2, in the opposite direction of P1 to P2
        p3.x = p2.x + dirX * distance;
        p3.y = p2.y + dirY * distance;
    }
    return p3;
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
    if (t >= 0 && t <= 1)
    {
        return 1; // Intersection in the middle of first segment p1 and p2
    }
    else if (u >= 0 && u <= 1)
    {
        return 2; // Intersection in the middle of second segment p3 and p4
    }

    return 0; // No intersection
}

std::vector<Points2d> offsetPolyline(const std::vector<Points2d> &points, double offsetDistance, OffsetDirection initialDirection)
{
    std::vector<Points2d> offsetPoints;

    if (points.size() < 2)
    {
        return offsetPoints;
    }

    // Offset the first segment
    Points2d newP1, newP2;
    for(int i = 0; i < points.size() - 1; i++)
    {

        offsetSegment(points[i], points[i+1], offsetDistance, initialDirection, newP1, newP2);

        if(i == 0)
        {
            offsetPoints.push_back(newP1);
        }

        // Check condition for points 2:
        int condition = findIntersection(points[i + 1], points[i + 2], newP1, newP2);

        // if condition == 0, no intersection
        if (condition == 0)
        {
            offsetPoints.push_back(newP2);
        }
        
        // if it intersection in the middle of first segment p1 and p2
        else if (condition == 1)
        {
            Points2d p3;
            p3 = findPointAtDistance(newP1, newP2, offsetDistance, true);
            offsetPoints.push_back(p3);
        }

        // if it intersection in the middle of second segment p3 and p4
        else if (condition == 2)
        {
            Points2d p3;
            p3 = findPointAtDistance(newP1, newP2, offsetDistance, false);
            offsetPoints.push_back(p3);
        }
    }

    return offsetPoints;
}