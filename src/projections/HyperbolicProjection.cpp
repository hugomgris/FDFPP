/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LayeredProjection.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:28:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/14 17:41:05 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/HyperbolicProjection.hpp"

HyperbolicProjection::HyperbolicProjection(double distance) : _distance(distance) {}

HyperbolicProjection::~HyperbolicProjection(){}

std::pair<int, int> HyperbolicProjection::project(int &x, int &y, int &z) const {
    double scale = 1.0 / (1.0 + fabs(z) * 0.05);
    int newX = x * scale;
    int newY = y * scale;
    return {newX, newY};
}