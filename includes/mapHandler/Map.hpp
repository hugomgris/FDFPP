/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:11:32 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/04/02 14:34:38 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <vector>
# include <array>
# include <stdexcept>

class Map {
	public:
		// Structs and type definition
		struct MapPoint {
			int z;
			int color;
			bool hasCustomColor;
			
			MapPoint(int z_val = 0, int color_val = 0, bool custom = false)
				: z(z_val), color(color_val), hasCustomColor(custom) {}
		};
		
		typedef std::vector<MapPoint> MapLine;
		
		// Constructor and destructor
		Map();
		~Map();
		
		// Getters
		std::vector<MapLine> &getMapData() { return _mapData; }
		const std::vector<MapLine> &getMapData() const { return _mapData; }		
		int getWidth() const;
		int getHeight() const;
		int getZ(int x, int y) const;
		int getColor(int x, int y) const;

		// Methods
		bool hasCustomColor(int x, int y) const;
	
	private:
		std::vector<MapLine> _mapData;
};

#endif