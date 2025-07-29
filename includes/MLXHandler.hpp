/**
 * @file MLXHandler.hpp
 * @brief Declares the MLXHandler class for managing MLX42 window, images, and event hooks.
 *
 * MLXHandler provides the interface for window creation, image buffer management, event handling,
 * and connection to the FDF rendering pipeline. It exposes methods for event hooks, image clearing,
 * and resource cleanup.
 */
 
#ifndef MLXHANDLER_HPP
# define MLXHANDLER_HPP

# include <iostream>
# include <stdexcept>
# include <cstring> 
# include "../libs/mlx42/include/MLX42/MLX42.h"

class FDF;

class MLXHandler{
	private:
		MLXHandler();
		
		int	_width;
		int	_height;
		int _uiWidth;
		int _uiHeight;
		const char *_title;
		
		mlx_t *_mlx;
		mlx_image_t *_img;
		mlx_image_t *_ui;
		mlx_image_t *_text1;
		mlx_image_t *_text2;

		FDF *_fdf;
		bool _autoRotate;

		bool _leftMousePressed;
		bool _rightMousePressed;
		int _lastMouseX;
		int _lastMouseY;

	public:
		MLXHandler(int width, int height, const char* title);
		MLXHandler(const MLXHandler &other);
		~MLXHandler();

		MLXHandler &operator=(const MLXHandler &other);

		int &getHeight();
		int &getWidth();
		int &getUIHeight();
		int &getUIWidth();
		mlx_image_t *getImage() const;
		mlx_image_t *getUI() const;
		mlx_image_t *getText1() const;
		mlx_image_t *getText2() const;
		mlx_t *getMLX() const;
		FDF *getFDF() const;
		bool &getAutoRotate();

		void setAutoRotate(bool autoRotate);
		void setFDF(FDF *fdf);

		void render() const;
		void handleEvents();
		void clearImage(mlx_image_t *img);
		void cleanup();

		static void basicHooks(void *param);
		static void scrollHook(double xdelta, double ydelta, void *param);
		static void perspectiveHooks(void *param);

		static void mouseHook(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
};

#endif