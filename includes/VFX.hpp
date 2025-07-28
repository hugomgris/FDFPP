#ifndef VFX_HPP
# define VFX_HPP

# include <utility>
# include <cmath>
# include <random>

class VFX{
	private:
		float _jitterIntensity;
		float _vortexDistortionIntensity;

		bool _jitterStatus;
		bool _waveStatus;
		bool _glitchStatus;
		bool _pulseWaveStatus;
		bool _vortexDistortionStatus;
		bool _chromaticAberrationStatus;

	public:
		VFX();
		~VFX();

	float &getJitterIntensity();
	float &getvortexDistortionIntensity();
	bool &getJitterStatus();
	bool &getWaveStatus();
	bool &getGlitchStatus();
	bool &getPulseWaveStatus();
	bool &getVortexDistortionStatus();
	bool &getChromaticAberrationStatus();

	void setJitterIntensity(float intensity);
	void setvortexDistortionIntensity(float intensity);
	void setJitterStatus(bool status);
	void setWaveStatus(bool status);
	void setGlitchStatus(bool status);
	void setPulseWaveStatus(bool status);
	void setVortexDistortionStatus(bool status);
	void setChromaticAberrationStatus(bool status);
	

	std::pair<int, int> jitter(std::pair<int, int> point);
	std::pair<int, int> waveDistortion(std::pair<int, int> point, float time);
	std::pair<int, int> glitch(std::pair<int, int> point);
	std::pair<int, int> pulseWave(std::pair<int, int> point, float time, int centerX, int centerY);
	std::pair<int, int> vortexDistortion(std::pair<int, int> point, float time, int centerX, int centerY);
	std::pair<int, int> chromaticAberration(std::pair<int, int> point, int channelOffset);
};

#endif