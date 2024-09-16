#ifndef CUB_H
#define CUB_H

#define WIDTH 800
#define HEIGHT 800

#include <math.h>
#include <stdio.h>
#include "include/libft/libft.h"
#include "include/MLX42/include/MLX42/MLX42.h"

enum e_identifyers
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	CEILING,
	FLOOR,
};
enum e_action
{
	GET,
	SET,
};

enum e_error
{
	FALSEIDENT = -3,
	DOUBLEIDENT = -2,
	EMPTYLINE = -1,
	NOUGHT,

};

typedef struct s_coordinate {
	double	x;
	double	y;
}	t_point;

typedef struct s_player
{
	int height;
	int width;
	t_point pos;
	t_point dir;
	t_point scr;
	int start;
	long color;
}	t_player;

typedef struct s_map
{
	int **map;
	int map_h;
	int map_w;
	mlx_texture_t north;
	mlx_texture_t south;
	mlx_texture_t east;
	mlx_texture_t west;
	long ceiling;
	long floor;
} t_map;

typedef struct s_game
{
	mlx_t *mlx;
	mlx_image_t *img;
	t_player player;
	t_map map;
} t_game;


//structure of values needed for putting pixels betwwen two points.
typedef struct s_algorythm {
	int		a;
	int		b;
	int		p;
	int		xdiff;
	int		ydiff;
	int		zdiff;
	int		zstep;
	long	col;
	t_point	p_a;
	t_point	p_b;
	t_point	p_t;
}	t_pixel_line;


void raycasting(t_game *game);
void	draw_line(t_point *p_a, t_point *p_b, t_game *game, int color);

/*		main.c				*/
void grid(t_game *game);
void draw_player(mlx_image_t *img, t_player *player);
int collision(t_player player, t_game *game, int mod);
void ft_hook(mlx_key_data_t keydata, void *param);
void rotate_dir_plane(t_point *dir, t_point *plane, double speed, double l_r);
void render(void *param);

/*		read_input.c		*/
int		comp_ident(char *str, int **idents);
int		check_identifyer(char **line, int *map_flag);
void	insert_map(t_map *map, char **str, int *map_flag);
void	get_info(int fd, t_player *player, t_map *map);
void	read_input(int argc, char **argv, t_player *player, t_map *map);

/*		read_map.c			*/



#endif