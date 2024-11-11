/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 16:55:17 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/11 21:25:53 by pstrohal         ###   ########.fr       */
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
# define ROTATE_AMOUNT NINETY * 0.9 / FPS

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "include/libft/src/libft.h"
# include "include/get_next_line/get_next_line.h"
# include "include/MLX42/include/MLX42/MLX42.h"

typedef unsigned long	u_l;
typedef	double db;


enum e_state
{
	ALIVE,
	DYING,
	DEAD,
};



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
	BULLET,
};

enum e_action
{
	GET,
	SET,
};
enum e_status
{
	OPEN,
	OPENING,
	CLOSED,
	CLOSING,
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

typedef struct s_sprites
{
	mlx_texture_t *tex;
	struct s_sprites *next;
} t_sprites;

typedef struct s_enemy
{
	t_point pos;
	mlx_texture_t **tex[2];
	double dist;
	struct s_enemy *next;
	int hit;
	int state;
	int hp;
	int i;
} t_ai;

typedef struct s_indiv_texture {
	mlx_texture_t	side[4];
	int				arr[4];
}	t_tex;

typedef struct s_circlehelp
{
	int	x;
	int	y;
	int	xcenter;
	int	ycenter;
	int r;
	int p;
}	t_circle_help;

typedef struct s_player
{
	int		height;
	int		width;
	t_point	pos;
	t_point	dir;
	t_point	scr;
	mlx_image_t *gun_img;
	mlx_texture_t **gun;
	double	pov;
	int		start;
	long	color;
	int		attack;
	int		hp;
}	t_player;

typedef struct s_door
{
	t_point			p1;
	t_point			p2;
	int				map_x;
	int				map_y;
	int				id;
	int				status;
	double			progress;
	int				dir;
	mlx_texture_t	*texture;
}	t_door;
typedef struct s_doorhelp
{
	t_point	door_intersect;
	t_point	sl;
	t_point	sr;
	t_point	dirvector;
	t_point	screenvector;
	t_point	screen_x;
	double	screenwidth;
	t_point	stepvector;
	double	doorwidth;
	t_point	pos;
	int		lineheight;
	int		start;
	int		end;
	t_point	tex_coords;
	double	door_x;
	uint8_t	*tex_pos;
	uint8_t	*img_pos;
	uint	test;
	double	tex_step;
	double	dist;
	double	tmpdist;
	double	buffdist;
	double	angle;
	t_door	*d;
}	t_doorhelp;

typedef struct s_dooralloc
{
	int	dir;
	int	x;
	int	y;
	int	id;
}	t_da;

typedef struct s_doorstuff
{
	t_list	*doors;
	int		nb;
	t_door	*current;
}	t_doorstuff;

typedef struct	s_minimap
{
	int				w;
	int				h;
	int				printh;
	double			x;
	double			y;
	double			step;
	unsigned int	wall;
	unsigned int	floor;
	double			min;
	double			max;
	t_point			pos;
}	t_minimap;

typedef struct s_map
{
	int				**map;
	char			**str_map;
	int				map_h;
	int				map_w;
	uint			ceiling;
	uint			floor;
	int				start[3];
	double			scale;
	mlx_texture_t	*textures[7];
	char			**tex_names;
	t_tex			**indiv;
	t_doorstuff		dstuff;
}	t_map;

typedef struct s_texture
{
	double		step;
	t_point		tex;
	uint8_t		*tex_pos;
	uint8_t		*img_pos;
	long		arr_pos;
	uint		pic_pos;
	uint		index;
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

typedef struct s_enemy_var
{
	t_point s;
	t_point proj;
	t_texture tex;
	double invcam;
	int height_offset;
	int spritescrx;
	int sheight;
	int starty;
	int endy;
	int swidth;
	int startx;
	int endx;
	int line;
	int y;
} t_enemy_var;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*minimap;
	double		scale;
	mlx_image_t	*circle;
	mlx_image_t	*cross;
	mlx_image_t	*hp;
	t_player	player;
	t_map		map;
	t_rays		ray;
	int			over;
	int			mouse;
	int			x;
	int			y;
	double		dist_arr[WIDTH];
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

/*		alienpls			*/
t_ai		*load_alien(t_game *game);
void		enemy_dist(t_game *game, t_ai **enemy, int frame);
void		draw_sprites(t_game *game, t_ai *enemy, int frame);
void		game_over_check(t_game *game);

/*		cast_textures		*/
void		draw_tex(t_game *game, int x, t_rays *ray);
void		tex_loop(t_game *game, t_rays *ray, t_texture *tex, int x);
int			return_orientation(int one, int two, int side);
int			get_direction(t_point pos, t_point hit, int side);
void		render_calc(t_game *game, t_rays *ray);



/*		UI		*/
void		health_bar(t_game *game);
void		load_gun(t_game *game);
void		gun_anim(t_game *game, int frame);


/*		draw_line		*/
void		draw_line(t_point *p_a, t_point *p_b, mlx_image_t *MLX_INVIMG, int color);

/*		enemy_dist_sort.c		*/
void		enemy_dist(t_game *game, t_ai **enemy, int frame);
void		sort_ai(t_ai **enemy);
void		swap(t_ai **head);

/*		ememy_coll.c		*/
void		update_enemy_pos(t_ai **enemy, t_game *game);
void		e_collision(t_point new_pos, t_game *game, t_ai *e);
void		set_e_index(t_point new_pos, t_ai *e, int *ix, int *iy);

/*		collision.c		*/
void		collision(t_point new_pos, t_game *game);
void		set_index(t_point new_pos, t_game *game, int *ix, int *iy);

/*		colour_stuff	*/
uint32_t	invert_colour(uint8_t *col);
uint32_t	colour(uint8_t *col);
void		change_colour(uint32_t col, unsigned int *wall, unsigned int *floor);
uint32_t	darken_colour(uint32_t col, int amount);

/*		doors			*/
void		draw_doors(t_game *game);

/*		door_mechanics	*/
void		door_move(t_game *game, t_door *d);
void		rotate_door(t_door *d);
void		doors(t_game *game);
void		minimap_door_hit(t_game *game, t_point hit, t_point *intersect);
void		draw_minimap_doors(t_game *game, uint32_t colour);

/*		door_mechanics_utils	*/
void		set_dir(t_door *d, t_door *p, db i, db j);
void		set_status(t_door *d, t_door *p, int i);
void		set_status_progress(t_door *d, int status, db progress);
int	intersection_with_door(t_game *game, t_point pos, t_point p);


/*		doors_utils		*/
t_point		intersection(t_point a, t_point b, t_point c, t_point d);
t_point		vector(t_point a, t_point b);
double		dist_points(t_point a, t_point b);
t_point		point_x_vector(t_point p, double x, t_point v);
double		vector_angle(t_point a, t_point b);
t_point		segment_intersection(t_point a, t_point b, t_point c, t_point d);

/*		draw_line		*/
void		draw_line(t_point *p_a, t_point *p_b, mlx_image_t *MLX_INVIMG, int color);

/*		movement		*/
void		mouse(mlx_key_data_t key, void* par);
void		ft_hook(t_game *game);
void		rotate_dir_plane(t_point *dir, t_point *plane, \
			double speed, double l_r);
void		update_pos(t_game *game, t_point new_pos);

/*		init_enemies.c		*/
t_ai		*load_alien(t_game *game);
mlx_texture_t	**allocate_textures_dying(void);
mlx_texture_t	**allocate_textures_idle(void);
void		append_node(t_ai **e, t_point pos, mlx_texture_t **idle, mlx_texture_t **dying);

/*		main				*/
void		init_game(t_game *game);
void		second_init(t_game *game);
void		screen_init(t_player *player);
int			leaks(void);

/*		minimap				*/
void		minimap(t_game * game);
void		cut_minimap(t_game *game, t_minimap *m);

/*		minimap_allocation	*/
void		circlePoints(t_circle_help *c, mlx_image_t *img, uint32_t col);
void		draw_circle(mlx_image_t *img, uint32_t col, uint32_t radius);
void		fill_outside_circle(mlx_image_t *img);
void		minimap_init(t_game *game);


/*		raycaster			*/
void		raycasting(t_game *game);
void		init_rays(t_game *game, t_rays *ray, int x);
void		step_and_dist(t_game *game, t_rays *ray);
void		ray_overflow(t_game *game, t_rays *ray);
void		hit_loop(t_game *game, t_rays *ray);


/*		read_input.c		*/
int			comp_ident(char *str, int *idents);
int			check_identifyer(char *line, int *map_flag);
void		insert_map(t_map *map, char **str);
void		get_info(int fd, t_map *map);
void		read_input(char **argv, t_player *player, t_map *map);

/*		read_input_utils.c	*/
void		get_start_pos(t_map *map, t_player *player);
int			comp_ident(char *str, int *idents);
int			check_identifyer(char *line, int *map_flag);

/*		read_map_utils.c	*/
int			**alloc_int_arr(int x, int y);

/*			read_map.c			*/
int			check_line(t_map *map, int i);
int			max_width(char **arr, int *y);
void		validate_map(t_map *map);

/*		read_settigns.c		*/
void		insert_info(t_map *map, char **str);

/*		error.c				*/
int			error(int e_action, int e_error);
void		err_check(void *p, char *msg);
void		error_print(char *msg);
void		check_error(int e);

/*		render		*/
void		render(void *param);
void		screen_init(t_player *player);
void		blank(t_game *game);
void		put_crosshair(t_game *game);

/*		textures			*/
t_tex		**allocate_textures(t_map *map);
void		draw_on_tex(t_game *game, t_texture *tex, int dir);
void		fill_text(t_tex *t, mlx_texture_t **tex, int (*arr)[4]);
void		fill_arr(t_map *map, int x, int y, int (*arr)[4]);
void		make_indi_tex(t_game *game, t_tex **t, t_texture *tex);

/*		utils.c				*/
int			arr_len(char **arr);
t_game		*game_pointer(int i, void *game);
int			mv_arr(char **src, char **dest);
void		free_game_end(t_game *game);
void		free_int_array(int **arr, int h);
void		free_string_array(char **str);
int			left_or_right(t_point a, t_point b, t_point p);

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

