#ifndef CONICPROJECTION_HPP
# define CONICPROJECTION_HPP

#include "IProjection.hpp"

class ConicProjection : public IProjection {
private:
    double _distance;   // Distance from viewer to projection plane
    double _fugueX;     // X coordinate of vanishing point (fugue point)
    double _fugueY;     // Y coordinate of vanishing point (fugue point)

public:
    ConicProjection(double distance, double fugueX, double fugueY);
    ConicProjection(); // Default constructor with reasonable defaults
    ~ConicProjection();
    
    std::pair<int, int> project(int &x, int &y, int &z) const override;
};

#endif