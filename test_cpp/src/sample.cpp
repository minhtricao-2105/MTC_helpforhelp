#include "sample.h"

std::vector<Points2d> offsetPolyline(const std::vector<Points2d>& points, double offsetDistance, OffsetDirection direction, ClipperLib::JoinType jt)
{
    // Scale factor for converting to integer coordinates (Clipper uses int64_t)
    const double scalingFactor = 10000.0;

    // Convert input polyline to Clipper's format and scale up
    ClipperLib::Path inputPath;
    for (const auto& point : points) {
        inputPath << ClipperLib::IntPoint(static_cast<ClipperLib::cInt>(point.x * scalingFactor), 
                                          static_cast<ClipperLib::cInt>(point.y * scalingFactor));
    }

    // Determine the offset direction
    double delta = (direction == OffsetDirection::IN) ? -offsetDistance * scalingFactor : offsetDistance * scalingFactor;

    // Perform the offset
    ClipperLib::ClipperOffset co;
    co.AddPath(inputPath, jt, ClipperLib::etOpenButt);
    ClipperLib::Paths solution;
    co.Execute(solution, delta);

    // Convert the solution back to the original format and scale down
    std::vector<Points2d> offsetPoints;
    if (!solution.empty()) {
        for (const auto& point : solution[0]) { // Assuming single contour for simplicity
            offsetPoints.push_back({static_cast<float>(point.X / scalingFactor), 
                                    static_cast<float>(point.Y / scalingFactor)});
        }
    
    return offsetPoints;
    }
    else
    {
        std::cerr << "Offset resulted in an empty solution. The offset may be too large or the polygon too small." << std::endl;
        return offsetPoints; // Exit with an error code
    }

    
}