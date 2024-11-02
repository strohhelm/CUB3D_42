/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: h4ns <h4ns@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:55:17 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/02 17:17:58 by h4ns             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP_H HEIGHT / 3
# define MINIMAP_W MINIMAP_H
# define MINIMAP_P 10
# define CROSSHAIR 30
# define EPSILON 1e-6
 #define FPS 30.0

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "include/libft/src/libft.h"
# include "include/get_next_line/get_next_line.h"
# include "include/MLX42/include/MLX42/MLX42.h"

typedef struct s_coordinate {
	double	x;
	double	y;
}	t_point;

typedef struct s_sprites
{
	mlx_texture_t *tex;
	struct s_sprites *next;
} t_sprites;

enum e_state
{
	ALIVE,
	DYING,
	DEAD,
};

typedef struct s_enemy
{
	t_point pos;
	mlx_texture_t **tex[2];
	double dist;
	struct s_enemy *next;
	int state;
	int hp;
	int i;
} t_ai;

enum e_colors
{
	NO = 0x9B5DE5FF,
	WE = 0xFF6F61FF,
	SO = 0xDFFF00FF,
	EA = 0x3E00FFFF,
};
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
	MALLOC,
};

typedef unsigned long	u_l;


typedef struct s_indiv_texture {
	mlx_texture_t	side[4];
}	t_tex;

typedef struct s_player
{
	int		height;
	int		width;
	t_point	pos;
	t_point	dir;
	t_point	scr;
	double	pov;
	int		start;
	long	color;
	int		attack;
	int		hp;
}	t_player;

typedef struct s_map
{
	int				**map;
	char			**str_map;
	int				map_h;
	int				map_w;
	unsigned int	ceiling;
	unsigned int	floor;
	int				start[3];
	double			scale;
	mlx_texture_t	*textures[6];
	char			**tex_names;
	t_tex			**indiv;
}	t_map;

typedef struct s_texture
{
	double		step;
	t_point		tex;
	uint8_t		*tex_pos;
	uint8_t		*img_pos;
	int			arr_pos;
	int			pic_pos;
	u_l			index;
	uint32_t	test;
}	t_texture;

//structure of values needed raycasting.
typedef struct s_rays
{
	double		camx;
	double		ray_dir_x;
	double		ray_dir_y;
	int			mx;
	int			my;
	double		sdistx;
	double		sdisty;
	double		deldistx;
	double		deldisty;
	double		walldist;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			start;
	int			end;
	t_point		wallhit;
	t_point		hitp;
	t_point		minimap_hit;
	t_point		pos;
	int			dir;
	t_texture	tex;
}	t_rays;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*minimap;
	double		scale;
	mlx_image_t	*circle;
	mlx_image_t	*cross;
	t_player	player;
	t_map		map;
	t_rays		ray;
	int			mouse;
	int			x;
	int			y;
	double		dist_arr[WIDTH];
}	t_game;

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



/*		UI		*/
void health_bar(t_game *game);

/*		alien			*/
t_ai *load_alien(t_game *game);
void enemy_dist(t_game *game, t_ai **enemy, int frame);
void draw_sprites(t_game *game, t_ai *enemy, int frame);

/*		draw_line		*/
void	draw_line(t_point *p_a, t_point *p_b, mlx_image_t *MLX_INVIMG, int color);

/*		collision.c		*/
void	collision(t_point new_pos, t_game *game);

/*		render		*/
void	render(void *param);
void	screen_init(t_player *player);
void	blank(t_game *game);
void	put_crosshair(t_game *game);

/*		movement.c		*/
void	mouse(mlx_key_data_t key, void* par);
void	ft_hook(t_game *game);
void	rotate_dir_plane(t_point *dir, t_point *plane, \
		double speed, double l_r);
void	update_pos(t_game *game, t_point new_pos);

/*		minimap.c			*/
void	minimap(t_game * game);
void	minumap(t_game * game);
void	minimap_init(t_game *game);
uint32_t	darken_colour(uint32_t col, int amount);
void	draw_circle(mlx_image_t *img, uint32_t col, uint32_t radius);

/*		main.c				*/
void	init_game(t_game *game);
void	second_init(t_game *game);
int		leaks(void);

/*		raycaster.c			*/
void	raycasting(t_game *game);
void	init_rays(t_game *game, t_rays *ray, int x);
void	step_and_dist(t_game *game, t_rays *ray);
void	ray_overflow(t_game *game, t_rays *ray);
void	hit_loop(t_game *game, t_rays *ray);

/*		cast_textures.c		*/
void	draw_tex(t_game *game, int x, t_rays *ray);
void	tex_loop(t_game *game, t_rays *ray, t_texture *tex, int x);
int		return_orientation(int one, int two, int side);
int		get_direction(t_point pos, t_point hit, int side);
void	render_calc(t_game *game, t_rays *ray);

/*		read_input.c		*/
int		comp_ident(char *str, int *idents);
int		check_identifyer(char *line, int *map_flag);
void	insert_map(t_map *map, char **str);
void	get_info(int fd, t_map *map);
void	read_input(char **argv, t_player *player, t_map *map);

/*		read_input_utils.c	*/
void	get_start_pos(t_map *map, t_player *player);
int		comp_ident(char *str, int *idents);
int		check_identifyer(char *line, int *map_flag);

/*		read_map_utils.c	*/
int		**alloc_int_arr(int x, int y);

/*		read_map.c			*/
int		check_line(t_map *map, int i);
int		max_width(char **arr, int *y);
void	validate_map(t_map *map);

/*		read_settigns.c		*/
void	insert_info(t_map *map, char **str);

/*		error.c				*/
int		error(int e_action, int e_error);
void	err_check(void *p, char *msg);
void	error_print(char *msg);
void	check_error(int e);

/*		textures			*/
t_tex **allocate_textures(int height, int width, mlx_texture_t **tex, int **map);
void	draw_on_tex(t_game *game, t_texture *tex, int dir);

/*		utils.c				*/
int		arr_len(char **arr);
t_game	*game_pointer(int i, void *game);
int		mv_arr(char **src, char **dest);
void	free_game_end(t_game *game);
void	free_int_array(int **arr, int h);
void	free_string_array(char **str);

#endif

// Deep Amethyst
// Hex: #9B5DE5
// A rich purple with a soft, luxurious feel.

// Burnt Coral
// Hex: #FF6F61
// A warm, slightly muted coral, striking but not too bold.

// Electric Limoncello
// Hex: #DFFF00
// A zesty and vibrant yellow-green that stands out.

// Iridescent Indigo
// Hex: #3E00FF
// A deep, electric blue with a hint of indigo, giving a futuristic vibe.

