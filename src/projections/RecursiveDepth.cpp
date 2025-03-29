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

#include "../../includes/projections/RecursiveDepth.hpp"

RecursiveDepth::~RecursiveDepth(){}

std::pair<int, int> RecursiveDepth::project(int &x, int &y, int &z) const {
    int loopDepth = 100;  // How deep until objects "loop back"
    int wrappedZ = z % loopDepth;  // Make depth wrap around

    double scale = 1.0 / (1.0 + abs(wrappedZ) * 0.01);  // Adjust depth
    int newX = x * scale;
    int newY = y * scale;
    return {newX, newY};
}