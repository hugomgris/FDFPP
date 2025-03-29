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

VFX::VFX(): _jitterIntensity(1.0f){
    _jitterStatus = false;
    _waveStatus = false;
}

VFX::~VFX(){}

//Getters
float &VFX::getJitterIntensity(){
    return (_jitterIntensity);
}

bool &VFX::getJitterStatus() {
    return (_jitterStatus);
}

bool &VFX::getWaveStatus() {
    return (_waveStatus);
}

void VFX::setJitterIntensity(float intensity){
    _jitterIntensity = intensity;
}

void VFX::setJitterStatus(bool status) {
    _jitterStatus = status;
}

void VFX::setWaveStatus(bool status) {
    _waveStatus = status;
}

//Effects
std::pair<int, int> VFX::jitter(std::pair <int, int> point){
    static std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-_jitterIntensity, _jitterIntensity);
    
    int jitterX = point.first + distribution(generator);
    int jitterY = point.second + distribution(generator);

    return {jitterX, jitterY};
}

std::pair<int, int> VFX::waveDistortion(std::pair<int, int> point, float time) {
    int waveX = point.first + sin(time + point.second * 0.1) * 5;
    int waveY = point.second + cos(time + point.first * 0.1) * 5;
    return {waveX, waveY};
}