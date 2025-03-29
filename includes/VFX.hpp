/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VFX.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 09:20:41 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/14 10:01:38 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VFX_HPP
# define VFX_HPP

# include <utility>
# include <cmath>
# include <random>

class VFX{
	private:
		float _jitterIntensity;
		bool _jitterStatus;
		bool _waveStatus;

	public:
		VFX();
		~VFX();

	//Getters & seters
	float &getJitterIntensity();
	bool &getJitterStatus();
	bool &getWaveStatus();

	void setJitterIntensity(float intensity);
	void setJitterStatus(bool status);
	void setWaveStatus(bool status);
	

	//Effects
	std::pair<int, int> jitter(std::pair<int, int> point);
	std::pair<int, int> waveDistortion(std::pair<int, int> point, float time);
};

#endif