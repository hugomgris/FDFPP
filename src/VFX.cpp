/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VFX.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:32:18 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/07/28 18:31:04 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/VFX.hpp"

VFX::VFX(): _jitterIntensity(1.0f), _vortexDistortionIntensity(1.0f){
    _jitterStatus = false;
    _waveStatus = false;
    _glitchStatus = false;
    _pulseWaveStatus = false;
    _vortexDistortionStatus = false;
    _chromaticAberrationStatus = false;
}

VFX::~VFX(){}

float &VFX::getJitterIntensity(){
    return (_jitterIntensity);
}

float &VFX::getvortexDistortionIntensity(){
    return (_vortexDistortionIntensity);
}

bool &VFX::getJitterStatus() {
    return (_jitterStatus);
}

bool &VFX::getWaveStatus() {
    return (_waveStatus);
}

bool &VFX::getGlitchStatus() {
    return (_glitchStatus);
}

bool &VFX::getPulseWaveStatus() {
    return (_pulseWaveStatus);
}

bool &VFX::getVortexDistortionStatus() {
    return (_vortexDistortionStatus);
}

bool &VFX::getChromaticAberrationStatus() {
    return (_chromaticAberrationStatus);
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

void VFX::setGlitchStatus(bool status) {
    _glitchStatus = status;
}

void VFX::setPulseWaveStatus(bool status) {
    _pulseWaveStatus = status;
}

void VFX::setVortexDistortionStatus(bool status) {
    _vortexDistortionStatus = status;
}

void VFX::setChromaticAberrationStatus(bool status) {
    _chromaticAberrationStatus = status;
}

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

std::pair<int, int> VFX::glitch(std::pair<int, int> point) {
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> displacement(-5, 5);
    if (rand() % 10 < 2) {
        point.first += displacement(generator);
        point.second += displacement(generator);
    }
    return point;
}

std::pair<int, int> VFX::pulseWave(std::pair<int, int> point, float time, int centerX, int centerY) {
    float dx = point.first - centerX;
    float dy = point.second - centerY;
    float distance = sqrt(dx*dx + dy*dy);
    
    float waveFactor = sin(distance * 0.05 - time * 2.0) * 5.0;
    
    float dirX = (dx == 0) ? 0 : dx / distance;
    float dirY = (dy == 0) ? 0 : dy / distance;

    int newX = point.first + dirX * waveFactor;
    int newY = point.second + dirY * waveFactor;
    
    return {newX, newY};
}

std::pair<int, int> VFX::vortexDistortion(std::pair<int, int> point, float time, int centerX, int centerY) {
    float dx = point.first - centerX;
    float dy = point.second - centerY;
    
    float distance = sqrt(dx*dx + dy*dy);

    if (distance < 5.0f) {
        return point;
    }
    
    float angle = _vortexDistortionIntensity * sin(time * 0.5) / (distance * 0.05);
    
    float cosA = cos(angle);
    float sinA = sin(angle);
    
    int newX = centerX + (dx * cosA - dy * sinA);
    int newY = centerY + (dx * sinA + dy * cosA);
    
    return {newX, newY};
}

std::pair<int, int> VFX::chromaticAberration(std::pair<int, int> point, int channelOffset) {
    return {point.first + channelOffset, point.second};
}