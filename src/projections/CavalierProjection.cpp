/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CavalierProjection.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:28:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 13:38:58 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/projections/CavalierProjection.hpp"

CavalierProjection::~CavalierProjection(){}

std::pair<int, int> CavalierProjection::project(int &x, int &y, int &z) const {
    double angle = M_PI / 4; // 45 degrees
    int newX = x + z * cos(angle);
    int newY = y - z * sin(angle);
    return {newX, newY};
}