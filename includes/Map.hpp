/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:11:32 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/27 12:17:19 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <vector>
# include <array>
# include <stdexcept>

# define MODE2D 0
# define MODE3D 1

class Map {
	private:
		std::vector<std::string> _2DMap;

	public:
		// Constructor and destructor
		Map();
		~Map();

		// Getters and Setters
		std::vector<std::string> &getMap();
};

#endif