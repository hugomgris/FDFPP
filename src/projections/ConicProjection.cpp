#include "../../includes/projections/ConicProjection.hpp"

ConicProjection::ConicProjection(double distance, double fugueX, double fugueY) 
    : _distance(distance), _fugueX(fugueX), _fugueY(fugueY) {}

ConicProjection::ConicProjection() : _distance(500.0), _fugueX(0.0), _fugueY(0.0) {}

ConicProjection::~ConicProjection(){}

std::pair<int, int> ConicProjection::project(int &x, int &y, int &z) const {
    double viewAngle = M_PI / 6;
    
    double rotatedX = x * cos(viewAngle) - y * sin(viewAngle);
    double rotatedY = x * sin(viewAngle) + y * cos(viewAngle);
    double rotatedZ = z;
    
    double depth = rotatedY + _distance;
    if (depth <= 0.1) depth = 0.1;
    
    double scale = _distance / depth;
    
    double projectedX = _fugueX + (rotatedX - _fugueX) * scale;
    double projectedY = _fugueY + (rotatedZ * scale + rotatedY * 0.3);
    
    return {static_cast<int>(projectedX), static_cast<int>(projectedY)};
}