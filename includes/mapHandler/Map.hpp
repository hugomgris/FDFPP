/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:11:32 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/27 14:21:32 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

#include <vector>
#include <string>

class Map {
public:
    // Nested struct to represent each point in the map
    struct Point {
        int z;          // height/z value
        int color;      // color value (-1 if not specified)
        
        // Constructor with default color
        Point(int height = 0, int pointColor = -1) 
            : z(height), color(pointColor) {}
    };

    // Type alias for readability
    using MapLine = std::vector<Point>;

    // Constructor and Destructor
    Map();
    ~Map();

    // Getters and Setters
    std::vector<MapLine>& getMapData();
    const std::vector<MapLine>& getMapData() const;
    
    // Utility methods
    int getWidth() const;
    int getHeight() const;
    int getZ(int x, int y) const;
    int getColor(int x, int y) const;

private:
    std::vector<MapLine> _mapData;
};

#endif