/**
 * @file main.cpp
 * @brief Entry point of the FDF++ application.
 *
 * Initializes core components including the map parser, rendering window,
 * projector, visual effects, and user interface. Loads the map data, applies
 * projections, and starts the main render and event loop using MLX42.
 *
 * Expected usage:
 * @code
 * ./FDF++ <map_file_or_string>
 * @endcode
 */

#include "../includes/mapHandler/MapBuilder.hpp"
#include "../includes/mapHandler/MapParser.hpp"
#include "../includes/projections/Projector.hpp"
#include "../includes/VFX.hpp"
#include "../includes/FDF.hpp"
#include "../includes/UI.hpp"

/**
 * @brief Main entry point. Sets up the FDF++ rendering pipeline.
 *
 * Initializes and connects the following components:
 * - MapBuilder: Parses the map input (file or inline string).
 * - MLXHandler: Handles window creation and MLX42 interactions.
 * - Projector: Manages the type of projection used.
 * - VFX: Configures visual effects.
 * - FDF: Central renderer combining map, projection, and VFX.
 * - UI: Displays control interface and render info.
 * - MapParser: Extracts map metadata and normalizes values.
 *
 * Runs the main render loop and cleans up all allocated resources.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments. Expects one argument: the map input.
 * @return Exit code (0 on success, 1 on error).
 */
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