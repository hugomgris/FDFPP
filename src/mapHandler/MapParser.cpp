/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:52:29 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/11 17:22:03 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mapHandler/MapParser.hpp"

//Constructor and destructor
MapParser::MapParser(std::vector<std::vector<int>> &map): _map(map){}

MapParser::~MapParser(){}

//Methods
bool MapParser::parseMap(){
	size_t len = this->_map[0].size();
	for (size_t i = 0; i < _map.size(); i++){
		if (_map[i].size() != len)
			throw(BadMapFormatException());
	}
	return (true);
}

//Exception messages
const char *MapParser::BadMapFormatException::what() const throw(){
	return ("Bad map format!");
}