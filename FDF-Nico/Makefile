# -=-=-=-=-    NAME -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

NAME		:= 	fdf

# -=-=-=-=-    PATH -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

INCS		:=	includes

LIBFTDIR	:=	libft

MLXDIR		:= 	MLX42

# -=-=-=-=-    FILES -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

SRC			:=	srcs/fdf.c				\
				srcs/parser.c			\
				srcs/error.c			\
				srcs/matrix.c			\
				srcs/start.c			\
				srcs/matrix_utils.c		\
				srcs/drawing_utils.c	\
				srcs/hooks.c

CPP_SRC		:=	../Map_Builder/MapBuilder.cpp \
				../Map_Builder/map_builder_wrapper.cpp \
				#../Map_Builder/main.cpp

MLX_FLAG	:=	.mlx_flag

HEADER		:=	$(INCLUDES)/fdf.h
CPP_HEADER	:=	Map_Builder/MapBuilder.hpp Map_Builder/map_builder_wrapper.h

MAKE		:=	Makefile

OBJS		:=	$(SRC:%.c=%.o)
CPP_OBJS	:=	$(CPP_SRC:%.cpp=%.o)

LIBS		:=	$(LIBFTDIR)/libft.a $(MLXDIR)/build/libmlx42.a /usr/lib/x86_64-linux-gnu/libglfw.so \
				-lm -ldl -Ofast -pthread -lglfw -lstdc++

# -=-=-=-=-    FLAGS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= #

CC			:=	cc
CXX			:=	g++

CFLAGS		:=	-Werror -Wextra -Wall -Wunreachable-code -Ofast -fsanitize=address
CXXFLAGS	:=	-Werror -Wextra -Wall -Wunreachable-code -Ofast -fsanitize=address -std=c++11

INCLUDE		:=	-Iincludes -IMap_Builder

# -=-=-=-=-    TARGETS -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- #

all: make_libft libmlx $(NAME)

libmlx:
	@cmake -DDEBUG=1 $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

%.o: %.cpp $(CPP_HEADER) Makefile
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(CPP_OBJS) $(SRCS) Makefile includes/fdf.h
	$(CXX) $(CXXFLAGS) $(OBJS) $(CPP_OBJS) $(INCLUDE) $(LIBS) -o $(NAME)

make_libft:
	make -C libft

clean:
	/bin/rm -f $(OBJS) $(CPP_OBJS)

fclean: clean
	/bin/rm -f $(NAME)
	make fclean -C libft
	rm -fr MLX42/build

re: fclean all

.PHONY:  all clean fclean re make_libft libmlx