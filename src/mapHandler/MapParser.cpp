#include "../../includes/mapHandler/MapParser.hpp"

MapParser::MapParser(std::vector<std::vector<int>> &map): _map(map){}

MapParser::~MapParser(){}

bool MapParser::parseMap(){
	size_t len = this->_map[0].size();
	for (size_t i = 0; i < _map.size(); i++){
		if (_map[i].size() != len)
			throw(BadMapFormatException());
	}
	return (true);
}

const char *MapParser::BadMapFormatException::what() const throw(){
	return ("Bad map format!");
}