/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:13:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 12:51:04 by hmunoz-g         ###   ########.fr       */
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
	
	MapBuilder *builder = NULL;
	MLXHandler *mlx = NULL;
	MapParser *parser = NULL;
	IsometricProjection *iso = NULL;
	FDF *fdf = NULL;
	
	try{	
		std::string input = std::string(argv[1]);
		builder = new MapBuilder(input);
		mlx = new MLXHandler(1920, 1080, "FDF++");
		iso = new IsometricProjection();

		
		fdf = new FDF(builder->getMap(), iso, *mlx);
		parser = new MapParser(fdf->getMatrix());
		parser->parseMap();
		//fdf->printMatrix();

		fdf->draw();
		mlx_loop(mlx->getMLX());

		delete builder;
		delete mlx;
		delete parser;
		delete iso;
		delete fdf;
	} catch (const std::exception &e){
		if (builder != NULL)
			delete builder;
		if (mlx != NULL)
			delete mlx;
		if (parser != NULL)
			delete parser;
		if (iso != NULL)
			delete iso;
		if (fdf != NULL)
			delete fdf;
		std::cout << "Exception caught: " << e.what() << std::endl;
		return (1);
	}
	
	return (0);
}