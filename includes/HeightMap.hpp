/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeightMap.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:40:25 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/31 10:32:26 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEIGHTMAP_HPP
# define HEIGHTMAP_HPP

# include <vector>
# include <string>
# include <sstream>
# include <climits>
# include <algorithm>
# include "mapHandler/Map.hpp"

class HeightMap {
public:
    HeightMap(std::vector<std::string> &map);
    ~HeightMap();
    
    std::vector<std::vector<int>> &getMatrix() { return _matrix; }
    int getMatrixWidth() const;
    int getMatrixHeight() const;
    int getZ(int x, int y) const;
    int getColor(int x, int y) const;
    bool hasCustomColor(int x, int y) const;
    float normalizeHeight(int z) const;
    void setZFactor(double factor, int mode);
    double getZFactor() const;
    
private:
    Map _map;
    std::vector<std::vector<int>> _matrix;
    int _matrixHeight;
    int _matrixWidth;
    int _minHeight;
    int _maxHeight;
    double _zFactor;
    
    void parseMapLine(const std::string &line, std::vector<Map::MapPoint> &points);
    void calculateMinMaxHeight();
};

#endif