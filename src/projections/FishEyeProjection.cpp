/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FishEyeProjection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:28:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/14 17:44:27 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/FishEyeProjection.hpp"

FishEyeProjection::~FishEyeProjection(){}

std::pair<int, int> FishEyeProjection::project(int &x, int &y, int &z) const {
    // Calculate distance from center
    double r = sqrt(x*x + y*y);

    // Avoid division by zero
    if (r < 0.001) return {x, y - z};

    // Use a more appropriate strength value (lower = stronger effect)
    double strength = 200.0;

    // Fish-eye equation: r_new = r * (1 - k*r²)
    // where k controls the distortion amount
    double k = 1.0 / (strength * strength);
    double distortionFactor = 1.0 - k * r * r;

    // Don't let the distortion go negative
    distortionFactor = std::max(0.2, distortionFactor);

    // Apply distortion to coordinates
    int newX = x * distortionFactor;
    int newY = y * distortionFactor - z;

    return {newX, newY};
}