/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:55:17 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/04 21:27:19 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BONUS_H
# define CUB_BONUS_H

# define WIDTH 1920
# define HEIGHT 1080
# define MINIMAP_H HEIGHT / 3
# define MINIMAP_P 10
# define CROSSHAIR 30
# define EPSILON 1e-6
# define FPS 30.0
# define MAX_DOORS 20
# define PI 3.14159265358979323846
# define DEG 180.0 / PI
# define NINETY PI / 2.0

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "include/libft/src/libft.h"
# include "include/get_next_line/get_next_line.h"
# include "include/MLX42/include/MLX42/MLX42.h"

typedef unsigned long	u_l;

enum e_colors
{
	NO = 0x9B5DE5FF,
	WE = 0xFF6F61FF,
	SO = 0xDFFF00FF,
	EA = 0xFF0D0FFF,
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
enum e_status
{
	OPEN,
	CLOSED,
	CLOSING,
	OPENING,
};

enum e_error
{
	FALSEIDENT = -3,
	DOUBLEIDENT = -2,
	EMPTYLINE = -1,
	NOUGHT,
	MALLOC,
};

enum e_direction
{
	LEFT,
	RIGHT,
	OOPS,
};

typedef struct s_coordinate {
	double	x;
	double	y;
}	t_point;

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
}	t_player;

typedef struct s_doorhelp
{
	int		px_len;
	t_point	left_intersect;
	t_point	right_intersect;
	t_point	door_intersect;
	t_point	door_start;
	t_point	doorstepvector;
	t_point	sl;
	t_point	sr;
	t_point	dirvector;
	t_point	p1vector;
	t_point	p2vector;
	t_point	slvector;
	t_point	srvector;
	t_point	left_vector;
	t_point	right_vector;
	t_point	left_d_point;
	t_point	right_d_point;
	double	left_angle;
	double	right_angle;
	double	p1_angle;
	double	p2_angle;
	double	pov_angle;
	double	p1p2_angle;
	t_point	screenvector;
	double	screenwidth;
	t_point	stepvector;
	double	screenstep;
	double	doorwidth;
	double	doorstep;
	double	px_angle;
	int		left;
	int		right;
	int		lineheight;
	int		left_dir;
	int		right_dir;
	int		p1_dir;
	int		p2_dir;
	double	p1_dist;
	double	p2_dist;
	t_point	pos;
}	t_doorhelp;

typedef struct s_door
{
	t_point			p1;
	t_point			p2;
	int				status;
	float			progress;
	mlx_texture_t	*texture;
	t_doorhelp		hlp;
}	t_door;

typedef struct s_doorstuff
{
	t_list			*doors;
	int				nb;
}	t_doorstuff;

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
	t_doorstuff		dstuff;
	double			dist_buffer[WIDTH];
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
}	t_game;



//structure of values needed for putting pixels between two points.
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

/*		cast_textures.c		*/
void	draw_tex(t_game *game, int x, t_rays *ray);
void	tex_loop(t_game *game, t_rays *ray, t_texture *tex, int x);
int		return_orientation(int one, int two, int side);
int		get_direction(t_point pos, t_point hit, int side);
void	render_calc(t_game *game, t_rays *ray);

/*		collision.c		*/
void	collision(t_point new_pos, t_game *game);

/*		doors.c			*/
void	draw_doors(t_game *game);
int	left_or_right(t_game *game, t_doorhelp *hlp, t_point p);

/*		doors_utils		*/
t_point	intersection(t_point a, t_point b, t_point c, t_point d);
t_point	vector_between_two_points(t_point a, t_point b);
double	dist_between_two_points(t_point a, t_point b);
t_point	get_new_point(t_point p, t_point vector);
t_point	get_point_plus_x_times_vector(t_point p, double x, t_point v);

/*		doors_utils_2	*/
double	orth_distance(t_point a, t_point b, t_point c);
double	dot_prod(t_point a, t_point b);
double	magn(t_point a);
double	angle_between_vectors(t_point a, t_point b);
void	set_left_right_vectors(t_game *game, t_doorhelp *hlp, t_door *d);


/*		draw_line		*/
void	draw_line(t_point *p_a, t_point *p_b, mlx_image_t *MLX_INVIMG, int color);

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

/*		render		*/
void	render(void *param);
void	screen_init(t_player *player);
void	blank(t_game *game);
void	put_crosshair(t_game *game);

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

