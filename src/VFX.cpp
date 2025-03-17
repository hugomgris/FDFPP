/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VFX.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:32:18 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/17 17:28:13 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/VFX.hpp"

VFX::VFX(): _jitterIntensity(1.0f){}

VFX::~VFX(){}

//Getters
float &VFX::getJitterIntensity(){
    return (_jitterIntensity);
}

void VFX::setJitterIntensity(float intensity){
    _jitterIntensity = intensity;
}

//Effects
std::pair<int, int> VFX::jitter(std::pair <int, int> point){
    static std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-_jitterIntensity, _jitterIntensity);
    
    int jitterX = point.first + distribution(generator);
    int jitterY = point.second + distribution(generator);

    return {jitterX, jitterY};
}