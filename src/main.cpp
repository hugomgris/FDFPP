/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:13:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/04/03 13:12:06 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mapHandler/MapBuilder.hpp"
#include "../includes/mapHandler/MapParser.hpp"
#include "../includes/projections/Projector.hpp"
#include "../includes/VFX.hpp"
#include "../includes/FDF.hpp"
#include "../includes/UI.hpp"

int main(int argc, char **argv){
	if (argc != 2){
		std::cerr << "Bad arguments!!(Try ./FDF++ <string/map>)" << std::endl;
		exit (1);
	}
	
	MapBuilder *builder = NULL;
	MLXHandler *mlx = NULL;
	MapParser *parser = NULL;
	Projector *projector = NULL;
	VFX *vfx;
	UI *ui;
	
	FDF *fdf = NULL;
	
	try{	
		std::string input = std::string(argv[1]);
		builder = new MapBuilder(input);
		mlx = new MLXHandler(1920, 1080, "FDF++");

		projector = new Projector();
		projector->setType(1);

		vfx = new VFX();
		
		
		fdf = new FDF(builder->getMap(), projector, *mlx, vfx);
		mlx->setFDF(fdf);

		ui = new UI(fdf->getHeightMap(), mlx, mlx->getUIWidth(), mlx->getUIHeight());
		ui->fillBackground();
		ui->outputControls();
		
		parser = new MapParser(fdf->getMatrix());
		parser->parseMap();

		fdf->draw();
		mlx->handleEvents();
		mlx_loop(mlx->getMLX());

		mlx->cleanup();
		delete builder;
		delete mlx;
		delete parser;
		delete projector;
		delete vfx;
		delete ui;
		delete fdf;
	} catch (const std::exception &e){
		if (builder != NULL)
			delete builder;
		if (ui != NULL)
			delete ui;
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