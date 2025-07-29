/**
# * @file MapParser.cpp
# * @brief Implements the MapParser class for validating and parsing map matrices.
# *
# * The MapParser class checks the format of a map matrix, ensuring consistent row lengths and valid structure.
# * Provides error handling for malformed maps.
# */

#include "../../includes/mapHandler/MapParser.hpp"

/**
 * @brief Constructs a MapParser object for validating a map matrix.
 * @param map Reference to the map matrix to validate.
 */
MapParser::MapParser(std::vector<std::vector<int>> &map): _map(map){}

/**
 * @brief Destructor for MapParser. Cleans up resources if needed.
 */
MapParser::~MapParser(){}

/**
 * @brief Validates the map matrix for consistent row lengths.
 * @return True if the map is valid.
 * @throws BadMapFormatException if the map format is invalid.
 */
bool MapParser::parseMap(){
	size_t len = this->_map[0].size();
	for (size_t i = 0; i < _map.size(); i++){
		if (_map[i].size() != len)
			throw(BadMapFormatException());
	}
	return (true);
}

/**
 * @brief Exception message for bad map format errors.
 * @return Error message string.
 */
const char *MapParser::BadMapFormatException::what() const throw(){
	return ("Bad map format!");
}