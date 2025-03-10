/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapParser.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:52:29 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 13:09:35 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mapHandler/MapParser.hpp"

//Constructor and destructor
MapParser::MapParser(std::vector<std::string> &map): _map(map){}

MapParser::~MapParser(){}

//Methods
bool MapParser::parseMap(){
	size_t len = this->_map[0].length();
	for (std::vector<std::string>::iterator it = this->_map.begin(); it != this->_map.end(); it++){
		if ((*it).length() != len)
			throw(BadMapFormatException());
	}
	return (true);
}

//Exception messages
const char *MapParser::BadMapFormatException::what() const throw(){
	return ("Bad map format!");
}