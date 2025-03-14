/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:13:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/14 09:36:09 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mapHandler/MapBuilder.hpp"
#include "../includes/mapHandler/MapParser.hpp"
#include "../includes/projections/Projector.hpp"
#include "../includes/VFX.hpp"
#include "../includes/FDF.hpp"

int main(int argc, char **argv){
	if (argc == 2){
		std::string help(argv[1]);
		if (help == "help"){
			std::cout << "Usage:" << std::endl
				<< "./FDF++ <string/map> <type>" << std::endl
				<< "To convert a string into a map, just input a string argument." << std::endl
				<< "To use an available map, use map path as argument." << std::endl
				<< "Projection types go from 1 to 9:" << std::endl
				<< "	1 - Isometric" << std::endl
				<< "	2 - Perspective" << std::endl
				<< "	3 - Orthographic" << std::endl
				<< "	4 - Trimetric" << std::endl
				<< "	5 - Dimetric" << std::endl
				<< "	6 - Cabinet" << std::endl
				<< "	7 - Cavalier" << std::endl
				<< "	8 - Military" << std::endl
				<< "	9 - FishEye" << std::endl;
			exit (0);
		} 
		std::cerr << "Bad arguments!!(Try ./FDF++ <string/map> <projection type: 1-9>, or run with 'help' argument for further instructions)" << std::endl;
		exit (1);
}
	
	if (argc < 3){
		std::cerr << "Bad arguments!!(Try ./FDF++ <string/map> <projection type: 1-9>, or run with 'help' argument for further instructions)" << std::endl;
		exit (1);
	}
	
	MapBuilder *builder = NULL;
	MLXHandler *mlx = NULL;
	MapParser *parser = NULL;
	Projector *projector = NULL;
	VFX *vfx;
	
	FDF *fdf = NULL;
	
	try{	
		std::string input = std::string(argv[1]);
		builder = new MapBuilder(input);
		mlx = new MLXHandler(1920, 1080, "FDF++");

		projector = new Projector();
		projector->setType(std::atoi(argv[2]));

		vfx = new VFX();
		
		fdf = new FDF(builder->getMap(), projector, *mlx, vfx);
		mlx->setFDF(fdf);
		
		parser = new MapParser(fdf->getMatrix());
		parser->parseMap();
		//fdf->printMatrix();

		fdf->draw();
		mlx->handleEvents();
		mlx_loop(mlx->getMLX());

		delete builder;
		delete mlx;
		delete parser;
		delete projector;
		delete vfx;
		delete fdf;
	} catch (const std::exception &e){
		if (builder != NULL)
			delete builder;
		if (mlx != NULL)
			delete mlx;
		if (parser != NULL)
			delete parser;
		if (projector != NULL)
			delete projector;
		if (vfx != NULL)
			delete vfx;
		if (fdf != NULL)
			delete fdf;
		std::cout << "Exception caught: " << e.what() << std::endl;
		return (1);
	}
	
	return (0);
}