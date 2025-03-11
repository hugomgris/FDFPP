/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapBuilder.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 09:39:17 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/11 15:13:52 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		//Constructors
		MapBuilder(const MapBuilder &other);

		//Operator overload
		MapBuilder &operator=(const MapBuilder &other);

		const std::string _dicPath;
		std::map<int, std::vector<std::string> > _mapDictionary;
		std::vector<std::string> _map;

	public:
		//Exception classes
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

		//Constructor and destructor
		MapBuilder(std::string &input);
		~MapBuilder();

		//Getters
		std::vector<std::string> &getMap();

		//Methods
		void feedDictionary();
		void buildMapFromString(std::string &str);
		void buildMapFromPath(std::string &str);

		//Helpers
		bool checkInputType(std::string &input);

		//Debuggers
		void mapPrinter();
};

#endif