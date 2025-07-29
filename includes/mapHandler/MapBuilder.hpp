#/**
# * @file MapBuilder.hpp
# * @class MapBuilder
# * @brief Builds map data from input strings or files, using a dictionary for character mapping.
# *
# * Loads map data from a file or string, parses dictionary files for character maps,
# * and provides methods for building, printing, and validating map input. Includes custom exceptions for error handling.
# */

#ifndef MAPBUILDER_HPP
# define MAPBUILDER_HPP

# include <iostream>
# include <map>
# include <vector>
# include <fstream>
# include <stdexcept>
# include <sstream>
# include <cstdlib>
# include <string>

class MapBuilder{
	private:
		MapBuilder(const MapBuilder &other);

		MapBuilder &operator=(const MapBuilder &other);

		const std::string _dicPath;
		std::map<int, std::vector<std::string> > _mapDictionary;
		std::vector<std::string> _map;

	public:
		class BadDicFileException : public std::exception{
			const char *what() const throw();
		};

		class StringTooLongException : public std::exception{
			const char *what() const throw();
		};

		class BadMapFileException : public std::exception{
			const char *what () const throw();
		};

		class BadExtensionException : public std::exception{
			const char *what () const throw();
		};

		MapBuilder(std::string &input);
		~MapBuilder();

		std::vector<std::string> &getMap();

		void feedDictionary();
		void buildMapFromString(std::string &str);
		void buildMapFromPath(std::string &str);

		bool checkInputType(std::string &input);

		void mapPrinter();
		void dictionaryPrinter();
};

#endif