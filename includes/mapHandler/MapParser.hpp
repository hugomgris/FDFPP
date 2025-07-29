/**
# * @file MapParser.hpp
# * @class MapParser
# * @brief Validates and parses map matrices for correct format and structure.
# *
# * Checks the format of a map matrix, ensuring consistent row lengths and valid structure.
# * Provides error handling for malformed maps.
# */

#ifndef MAPPARSER_HPP
# define MAPPARSER_HPP

# include <iostream>
# include <vector>

class MapParser{
	private:
		std::vector<std::vector<int>> &_map;

	public:
		class BadMapFormatException : public std::exception{
			const char *what () const throw();
		};
		
		MapParser(std::vector<std::vector<int>> &map);
		~MapParser();

		bool parseMap();
};

#endif