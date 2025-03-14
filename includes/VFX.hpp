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

	public:
		VFX();
		~VFX();

	//Getters & seters
	float &getJitterIntensity();
	void setJitterIntensity(float intensity);

	//Effects
	std::pair<int, int> jitter(std::pair<int, int> point);
};

#endif