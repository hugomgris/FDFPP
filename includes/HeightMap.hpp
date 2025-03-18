/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HeightMap.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:40:25 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/18 17:40:36 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEIGHTMAP_HPP
#define HEIGHTMAP_HPP

#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <algorithm>

class HeightMap {
private:
    std::vector<std::vector<int>> _matrix;
    int _matrixWidth;
    int _matrixHeight;
    double _zFactor;
    int _minHeight;
    int _maxHeight;

public:
    // Constructor
    HeightMap(std::vector<std::string> &map);
    ~HeightMap();

    // Getters and setters
    std::vector<std::vector<int>> &getMatrix();
    int getMatrixWidth() const;
    int getMatrixHeight() const;
    double getZFactor() const;
    void setZFactor(double increase, int mode);
    
    // Height methods
    int getZ(int x, int y) const;
    void calculateHeightExtremes();
    float normalizeHeight(int z) const;
    
    // Debug
    void printMatrix() const;
};

#endif