/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:51:39 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/07 12:59:35 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPPARSER_HPP
# define MAPPARSER_HPP

# include <iostream>
# include <vector>

class MapParser{
	private:
		std::vector<std::string> &_map;

	public:
		//Exception classes
		class BadMapFormatException : public std::exception{
			const char *what () const throw();
		};
		
		//Constructor and destructor
		MapParser(std::vector<std::string> &map);
		~MapParser();

		//Methods
		bool parseMap();
};

#endif