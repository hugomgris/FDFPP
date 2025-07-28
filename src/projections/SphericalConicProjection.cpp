/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SphericalConicProjection.cpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:20:07 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/07/28 18:22:56 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/SphericalConicProjection.hpp"

SphericalConicProjection::SphericalConicProjection(double radius) : _radius(radius) {}
SphericalConicProjection::SphericalConicProjection() : _radius(400.0) {}
SphericalConicProjection::~SphericalConicProjection(){}

std::pair<int, int> SphericalConicProjection::project(int &x, int &y, int &z) const {
    double distance = sqrt(x*x + y*y + z*z);
    if (distance == 0) distance = 1;
    
    double sphereX = x * _radius / distance;
    double sphereY = y * _radius / distance;
    double sphereZ = z * _radius / distance;
    
    double depth = _radius + sphereY;
    if (depth <= 0.1) depth = 0.1;
    double scale = _radius / depth;
    
    int newX = sphereX * scale;
    int newY = sphereZ * scale;

    return {newX, newY};
}