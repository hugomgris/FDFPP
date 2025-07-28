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