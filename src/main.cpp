/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:13:14 by hmunoz-g          #+#    #+#             */
/*   Updated: 2025/03/12 14:29:48 by hmunoz-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mapHandler/MapBuilder.hpp"
#include "../includes/mapHandler/MapParser.hpp"
#include "../includes/projections/IsometricProjection.hpp"
#include "../includes/projections/OrthographicProjection.hpp"
#include "../includes/projections/PerspectiveProjection.hpp"
#include "../includes/projections/TrimetricProjection.hpp"
#include "../includes/projections/DimetricProjection.hpp"
#include "../includes/projections/CabinetProjection.hpp"
#include "../includes/projections/CavalierProjection.hpp"
#include "../includes/projections/MilitaryProjection.hpp"
#include "../includes/projections/FishEyeProjection.hpp"
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
	PerspectiveProjection *pers = NULL;
	OrthographicProjection *ortho = NULL;
	TrimetricProjection *trime = NULL;
	CabinetProjection *cabinet = NULL;
	DimetricProjection *dime = NULL;
	CavalierProjection *cava = NULL;
	MilitaryProjection *mili = NULL;
	FishEyeProjection *fish = NULL;
	
	FDF *fdf = NULL;
	
	try{	
		std::string input = std::string(argv[1]);
		builder = new MapBuilder(input);
		mlx = new MLXHandler(1920, 1080, "FDF++");
		iso = new IsometricProjection();
		pers = new PerspectiveProjection();
		ortho = new OrthographicProjection();
		trime = new TrimetricProjection();
		dime = new DimetricProjection();
		cabinet = new CabinetProjection();
		cava = new CavalierProjection();
		mili = new MilitaryProjection();
		fish = new FishEyeProjection();

		
		fdf = new FDF(builder->getMap(), fish, *mlx);
		parser = new MapParser(fdf->getMatrix());
		parser->parseMap();
		//fdf->printMatrix();

		fdf->draw();
		mlx_loop(mlx->getMLX());

		delete builder;
		delete mlx;
		delete parser;
		delete iso;
		delete pers;
		delete ortho;
		delete trime;
		delete dime;
		delete cabinet;
		delete cava;
		delete mili;
		delete fish;
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
		if (pers != NULL)
			delete pers;
		if (ortho != NULL)
			delete ortho;
		if (trime != NULL)
			delete trime;
		if (dime != NULL)
			delete dime;
		if (cabinet != NULL)
			delete cabinet;
		if (cava != NULL)
			delete cava;
		if (mili != NULL)
			delete mili;
		if (fish != NULL)
			delete fish;
		if (fdf != NULL)
			delete fdf;
		std::cout << "Exception caught: " << e.what() << std::endl;
		return (1);
	}
	
	return (0);
}