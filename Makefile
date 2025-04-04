# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmunoz-g <hmunoz-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 13:48:05 by hmunoz-g          #+#    #+#              #
#    Updated: 2025/03/31 10:02:14 by hmunoz-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -=-=-=-=-    COLOURS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

DEF_COLOR   = \033[0;39m
YELLOW      = \033[0;93m
CYAN        = \033[0;96m
GREEN       = \033[0;92m
BLUE        = \033[0;94m
RED         = \033[0;91m

# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME        := FDF++

# -=-=-=-=-    FLAG -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CPP          = c++
FLAGS       = -Werror -Wall -Wextra -std=c++17 -pedantic -g -fsanitize=address
DEPFLAGS    = -MMD -MP

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

RM          = rm -fr
OBJ_DIR     = .obj
DEP_DIR     = .dep
MLXDIR		:= 	libs/mlx42

# -=-=-=-=-    LIBRARIES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #
LIBS		:=	$(MLXDIR)/build/libmlx42.a /usr/lib/x86_64-linux-gnu/libglfw.so \
				-lm -ldl -Ofast -pthread -lglfw

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC         := src/main.cpp \
				src/FDF.cpp \
				src/MLXHandler.cpp \
				src/VFX.cpp \
				src/Camera.cpp \
				src/HeightMap.cpp \
				src/ColorManager.cpp \
				src/Renderer.cpp \
				src/UI.cpp \
				src/mapHandler/Map.cpp \
				src/mapHandler/MapBuilder.cpp \
				src/mapHandler/MapParser.cpp \
				src/projections/Projector.cpp \
				src/projections/IsometricProjection.cpp \
				src/projections/OrthographicProjection.cpp \
				src/projections/PerspectiveProjection.cpp \
				src/projections/TrimectricProjection.cpp \
				src/projections/DimetricProjection.cpp \
				src/projections/CabinetProjection.cpp \
				src/projections/CavalierProjection.cpp \
				src/projections/MilitaryProjection.cpp \
				src/projections/RecursiveDepthProjection.cpp \
				src/projections/HyperbolicProjection.cpp \

OBJS        = $(addprefix $(OBJ_DIR)/, $(SRC:.cpp=.o))
DEPS        = $(addprefix $(DEP_DIR)/, $(SRC:.cpp=.d))

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: directories mlx $(NAME)

directories:
	@mkdir -p $(OBJ_DIR)/src/mapHandler
	@mkdir -p $(OBJ_DIR)/src/projections
	@mkdir -p $(DEP_DIR)/src/mapHandler
	@mkdir -p $(DEP_DIR)/src/projections

-include $(DEPS)

mlx:
	@if [ ! -d "$(MLXDIR)" ]; then \
		echo "MLX42 library not found, cloning from GitHub..."; \
		git clone https://github.com/42-Fundacion-Telefonica/MLX42.git $(MLXDIR); \
	fi
	@if [ ! -d "$(MLXDIR)/build/" ]; then \
		cmake -DDEBUG=1 $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4; \
	fi

$(OBJ_DIR)/%.o: %.cpp 
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	$(CPP) $(FLAGS) $(DEPFLAGS) -c $< -o $@ -MF $(DEP_DIR)/$*.d

$(NAME): $(OBJS) Makefile
	@echo "$(GREEN)Linking $(NAME)!$(DEF_COLOR)"
	$(CPP) $(FLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"
	@echo "$(RED)So preoccupied with whether or not I could, I didn't stop to think if I should.$(DEF_COLOR)"

doxy:
	doxygen Doxyfile
	@echo "$(GREEN)Doxy documentation generated in docs/index.html$< $(DEF_COLOR)"

doxyclean:
	rm -rf docs/html/ docs/latex/ docs/xml/ docs/rtf/ docs/man/ docs/docbook/
	@echo "$(RED)Cleaned doxy files and documentation$(DEF_COLOR)"

clean:
	@$(RM) $(OBJ_DIR) $(DEP_DIR)
	@echo "$(RED)Cleaned object files and dependencies$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) MLX42/build
	@rm -rf libs/mlx42
	@echo "$(RED)Cleaned all binaries$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re directories doxy index