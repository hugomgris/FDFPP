/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SphericalConicProjection.hpp                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:00:00 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/07/28 14:20:31 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERICALCONICPROJECTION_HPP
# define SPHERICALCONICPROJECTION_HPP

#include "./IProjection.hpp"

class SphericalConicProjection : public IProjection {
private:
    double _radius;

public:
    SphericalConicProjection(double radius);
    SphericalConicProjection();
    ~SphericalConicProjection();
    
    std::pair<int, int> project(int &x, int &y, int &z) const override;
};

#endif