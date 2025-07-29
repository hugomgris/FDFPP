/**
 * @file VFX.cpp
 * @brief Implements the VFX class, which provides visual effects for map rendering.
 *
 * The VFX class enables and configures effects such as jitter, wave distortion, glitch, pulse wave,
 * vortex distortion, and chromatic aberration. It provides transformation methods for points and
 * manages effect intensities and toggles for real-time rendering.
 */

#include "../includes/VFX.hpp"

/**
 * @brief Constructs a VFX object for managing visual effects.
 *
 * Initializes effect intensities and toggles for all supported effects.
 */
VFX::VFX(): _jitterIntensity(1.0f), _vortexDistortionIntensity(1.0f){
    _jitterStatus = false;
    _waveStatus = false;
    _glitchStatus = false;
    _pulseWaveStatus = false;
    _vortexDistortionStatus = false;
    _chromaticAberrationStatus = false;
}

/**
 * @brief Destructor for VFX. Cleans up effect resources if needed.
 */
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

/**
 * @brief Applies jitter effect to a point, randomly displacing its coordinates.
 *
 * Uses a random distribution based on jitter intensity.
 *
 * @param point Input screen coordinates (x, y).
 * @return Jittered screen coordinates (x, y).
 */
std::pair<int, int> VFX::jitter(std::pair <int, int> point){
    static std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-_jitterIntensity, _jitterIntensity);
    
    int jitterX = point.first + distribution(generator);
    int jitterY = point.second + distribution(generator);

    return {jitterX, jitterY};
}

/**
 * @brief Applies wave distortion effect to a point, displacing it in a sinusoidal pattern.
 *
 * Uses time and position to compute the wave offset.
 *
 * @param point Input screen coordinates (x, y).
 * @param time Animation time value.
 * @return Distorted screen coordinates (x, y).
 */
std::pair<int, int> VFX::waveDistortion(std::pair<int, int> point, float time) {
    int waveX = point.first + sin(time + point.second * 0.1) * 5;
    int waveY = point.second + cos(time + point.first * 0.1) * 5;
    return {waveX, waveY};
}

/**
 * @brief Applies glitch effect to a point, occasionally displacing its coordinates randomly.
 *
 * Uses a random chance to apply a displacement.
 *
 * @param point Input screen coordinates (x, y).
 * @return Glitched screen coordinates (x, y).
 */
std::pair<int, int> VFX::glitch(std::pair<int, int> point) {
    static std::default_random_engine generator;
    std::uniform_int_distribution<int> displacement(-5, 5);
    if (rand() % 10 < 2) {
        point.first += displacement(generator);
        point.second += displacement(generator);
    }
    return point;
}

/**
 * @brief Applies pulse wave effect to a point, displacing it radially in a wave pattern.
 *
 * Uses distance from center and time to compute the wave offset.
 *
 * @param point Input screen coordinates (x, y).
 * @param time Animation time value.
 * @param centerX X coordinate of the wave center.
 * @param centerY Y coordinate of the wave center.
 * @return Distorted screen coordinates (x, y).
 */
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

/**
 * @brief Applies vortex distortion effect to a point, rotating it around a center.
 *
 * Uses distance from center and time to compute the rotation angle.
 *
 * @param point Input screen coordinates (x, y).
 * @param time Animation time value.
 * @param centerX X coordinate of the vortex center.
 * @param centerY Y coordinate of the vortex center.
 * @return Distorted screen coordinates (x, y).
 */
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

/**
 * @brief Applies chromatic aberration effect to a point, offsetting its position for color channels.
 *
 * Used for rendering color channel separation effects.
 *
 * @param point Input screen coordinates (x, y).
 * @param channelOffset Offset to apply for the color channel.
 * @return Offset screen coordinates (x, y).
 */
std::pair<int, int> VFX::chromaticAberration(std::pair<int, int> point, int channelOffset) {
    return {point.first + channelOffset, point.second};
}