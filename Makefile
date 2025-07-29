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
				src/projections/ConicProjection.cpp \
				src/projections/SphericalConicProjection.cpp \

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

# -=-=-=-=-    DOCUMENTATION -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

DOXYGEN_VERSION = 1.10.0
DOXYGEN_DIR = $(HOME)/doxygen-$(DOXYGEN_VERSION)
DOXYGEN_BIN = $(DOXYGEN_DIR)/bin/doxygen

# Generate project documentation using Doxygen
# NOTE: This target will work with or without Graphviz installed:
#   - WITH Graphviz: Generates full docs including dependency graphs, call graphs,
#     class collaboration diagrams, and inheritance charts
#   - WITHOUT Graphviz: Generates complete documentation but without visual graphs
#
# To enable visual graphs, install Graphviz on your system:
#   Ubuntu/Debian: sudo apt-get install graphviz
#   macOS: brew install graphviz
#   Arch: sudo pacman -S graphviz
doxy: $(DOXYGEN_BIN)
	@if command -v dot >/dev/null 2>&1; then \
		echo "$(GREEN)Generating documentation with Graphviz support$(DEF_COLOR)"; \
	else \
		echo "$(YELLOW)Generating documentation without graphs (Graphviz not found)$(DEF_COLOR)"; \
		echo "$(CYAN)Tip: Install graphviz package to enable dependency graphs$(DEF_COLOR)"; \
	fi
	@$(DOXYGEN_BIN) Doxyfile
	@echo "$(GREEN)Documentation generated in docs/html/index.html$(DEF_COLOR)"

$(DOXYGEN_BIN):
	@echo "$(CYAN)Downloading Doxygen$(DEF_COLOR)"
	@wget -q https://www.doxygen.nl/files/doxygen-$(DOXYGEN_VERSION).linux.bin.tar.gz -O /tmp/doxygen.tar.gz
	@tar -xzf /tmp/doxygen.tar.gz -C $(HOME)
	@rm /tmp/doxygen.tar.gz
	@echo "$(GREEN)Doxygen installed successfully$(DEF_COLOR)"

doxyclean:
	@rm -rf docs/html/ docs/latex/ docs/xml/ docs/rtf/ docs/man/ docs/docbook/
	@echo "$(RED)Cleaned documentation files$(DEF_COLOR)"

clean:
	@$(RM) $(OBJ_DIR) $(DEP_DIR)
	@echo "$(RED)Cleaned object files and dependencies$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) MLX42/build
	@rm -rf libs/mlx42
	@echo "$(RED)Cleaned all binaries$(DEF_COLOR)"

re: fclean all

.PHONY: all clean fclean re directories doxy doxyclean