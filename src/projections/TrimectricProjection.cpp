/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TrimectricProjection.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:28:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 12:58:38 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/TrimetricProjection.hpp"

TrimetricProjection::~TrimetricProjection(){}

std::pair<int, int> TrimetricProjection::project(int &x, int &y, int &z) const {
	double angleX = M_PI / 6;
    double angleY = M_PI / 3;
    double angleZ = M_PI / 4;
    
    int newX = x * cos(angleX) - y * cos(angleY);
    int newY = x * sin(angleX) + y * sin(angleY) - z * sin(angleZ);
    return {newX, newY};
}