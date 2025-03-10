/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OrthographicProjection.hpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:16:42 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 13:16:37 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ORTOGRAPHICPROJECTION_HPP
# define ORTOGRAPHICPROJECTION_HPP

# include "IProjection.hpp"

class OrthographicProjection : public IProjection{
	public:
		~OrthographicProjection();
		virtual std::pair<int, int> project(int &x, int &y, int &z) const;
};

#endif