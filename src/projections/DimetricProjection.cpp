/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DimetricProjection.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:28:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 14:25:15 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/DimetricProjection.hpp"

DimetricProjection::~DimetricProjection(){}

std::pair<int, int> DimetricProjection::project(int &x, int &y, int &z) const {
    double alpha = M_PI / 8;
    double beta = M_PI / 4;
    int newX = x * cos(alpha) + y * cos(beta);
    int newY = x * sin(alpha) + y * sin(beta) - z;
    return {newX, newY};
}