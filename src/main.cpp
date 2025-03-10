/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:13:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/10 15:54:06 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mapHandler/MapBuilder.hpp"
#include "../includes/mapHandler/MapParser.hpp"
#include "../includes/projections/IsometricProjection.hpp"
#include "../includes/projections/OrthographicProjection.hpp"
#include "../includes/projections/PerspectiveProjection.hpp"
#include "../includes/FDF.hpp"

int main(int argc, char **argv){
	if (argc < 2){
		std::cerr << "Need arguments!!";
		exit (1);
	}
	
	MapBuilder *mapBuilder = NULL;
	
	try{	
		std::string input = std::string(argv[1]);
		mapBuilder = new MapBuilder(input);

		MapParser mapParser(mapBuilder->getMap());
		mapParser.parseMap();

		mapBuilder->mapPrinter();
		
		MLXHandler MLXHandler(1920, 1080, "FDF++");

		IsometricProjection iso;
		FDF fdf(mapBuilder->getMap(), &iso, MLXHandler);

		MLXHandler.render();

		delete mapBuilder;
	} catch (const std::exception &e){
		if (mapBuilder != NULL)
			delete mapBuilder;
		std::cout << "Exception caught: " << e.what() << std::endl;
		return (1);
	}
	
	return (0);
}