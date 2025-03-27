/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:34:25 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/27 12:16:58 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Map.hpp"

// Constructor and Destructor
Map::Map() {}

Map::~Map() {}

// Getters and Setters
std::vector<std::string> &Map::getMap() { return _2DMap; }
