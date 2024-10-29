/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:34:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/29 17:57:51 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	blank(t_game *game)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (y < HEIGHT / 2 - game->y)
				mlx_put_pixel(game->img, x, y, game->map.ceiling);
			else
				mlx_put_pixel(game->img, x, y, game->map.floor);
		}
	}
}

void	backgroud(t_game *game)
{
	mlx_texture_t	*floortex;
	mlx_texture_t	*ceilingtex;
	
	float	raydirx0;
	float	raydiry0;
	float	raydirx1;
	float	raydiry1;
	float	floorstepX;
	float	floorstepY;
	float	floorX;
	float	floorY;
	static double t = 0;
	
	int		y;
	int		x;
	int		p;
	float	posZ;
	float	rowdist;
	
	floortex = game->map.textures[FLOOR];
	ceilingtex = game->map.textures[CEILING];
	
	y = HEIGHT / 2 - 1 - game->y;
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		t += 0.01;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		t -= 0.01;
	while (y <= HEIGHT)
	{
		raydirx0 = (game->player.dir.x - game->player.scr.x) * 10;
		raydiry0 = (game->player.dir.y - game->player.scr.y) * 10;
		raydirx1 = (game->player.dir.x + game->player.scr.x) * 10;
		raydiry1 = (game->player.dir.y + game->player.scr.y) * 10;
		p = y - HEIGHT / 2;
		posZ = HEIGHT / 2;
		rowdist = posZ / p ;
		floorstepX = rowdist * ((raydirx1 - raydirx0) / (WIDTH));
		floorstepY = rowdist * ((raydiry1 - raydiry0) / (WIDTH));
		floorX = (game->player.pos.x) + rowdist * raydirx0;
		floorY = (game->player.pos.y) + rowdist * raydiry0;
		x = 0; 
		while (x < WIDTH)
		{
			uint32_t texX = (int)(floortex->width * fabs(fmod(floorX, 1.0))) % floortex->width;
			uint32_t texY = (int)(floortex->height * fabs(fmod(floorY, 1.0))) % floortex->height;
			uint8_t *tex_pos = &floortex->pixels[(floortex->width * texY + texX) * 4];
			uint8_t *img_pos = &game->img->pixels[(WIDTH * (y - 1 - game->y) + x) * 4];
			ft_memmove(img_pos, tex_pos, sizeof(uint32_t));
			texX = (int)((ceilingtex->width) * floorX ) % ceilingtex->width;
			texY = (int)((ceilingtex->height) * floorY) % ceilingtex->height;
			tex_pos = &ceilingtex->pixels[(ceilingtex->width * texY + texX) * 4];
			img_pos = &game->img->pixels[(WIDTH * (HEIGHT - y + game->y) + x) * 4];
			ft_memmove(img_pos, tex_pos, sizeof(uint32_t));
			floorX += floorstepX;
			floorY += floorstepY;
			x++;
		}
		y++;
	}
}

void	screen_init(t_player *player)
{
	t_point	dir;
	t_point	scr;

	dir = player->dir;
	player->dir.x /= 10;
	player->dir.y /= 10;
	scr.x = 0;
	scr.y = 0;
	if (dir.y > 0)
		scr.x = (-player->pov) / 10;
	else if (dir.y < 0)
		scr.x = player->pov / 10;
	else if (dir.x > 0)
		scr.y = player->pov / 10;
	else if (dir.x < 0)
		scr.y = -player->pov / 10;
	player->scr = scr;
}

void	put_crosshair(t_game *game)
{
	// int	x;
	// int	y;
	
	game->cross = mlx_new_image(game->mlx, CROSSHAIR, CROSSHAIR);
	// x = CROSSHAIR / 2;
	// y = 1;
	// while (y < CROSSHAIR)
	// 	mlx_put_pixel(game->cross, x, y++, 0xFF0000FF);
	// y = CROSSHAIR / 2;
	// x = 0;
	// while (x < CROSSHAIR)
	// 	mlx_put_pixel(game->cross, x++, y, 0xFF0000FF);
	draw_circle(game->cross, 0X000000FF, CROSSHAIR / 2 - 6);
	draw_circle(game->cross, 0X000000FF, CROSSHAIR / 2 - 5);
	draw_circle(game->cross, 0xFFFF00FF, CROSSHAIR / 2 - 4);
	draw_circle(game->cross, 0xFFFF00FF, CROSSHAIR / 2 - 3);
	draw_circle(game->cross, 0X000000FF, CROSSHAIR / 2 - 2);
	draw_circle(game->cross, 0X000000FF, CROSSHAIR / 2 - 1);
	
	mlx_image_to_window(game->mlx, game->cross, WIDTH / 2 - game->cross->width/2, HEIGHT/2 - game->cross->height / 2);
}

void update_enemy_pos(t_ai **enemy, t_game *game)
{
	t_ai *e = *enemy;

	double dist;
	t_point move;

	while(e)
	{
		dist = sqrt(pow(game->player.pos.x - e->pos.x, 2.0) + pow(game->player.pos.y - e->pos.y, 2.0));
		double len = 0.03 / dist;
		move.x = e->pos.x + len * (game->player.pos.x - e->pos.x);
		move.y = e->pos.y + len * (game->player.pos.y - e->pos.y); 

		e->pos.x = move.x;
		e->pos.y = move.y;
		e = e->next;
	}
}

void render(void *param)
{
	t_game		*game;
	double		t;
	double		ft;
	double		time;
	static t_ai *e = NULL;
	static int	i = 0;

	time = 1.0 / FPS;
	game = (t_game *)param;
	t = mlx_get_time();
	if (i++ < 2)
	{
		mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
		mlx_get_mouse_pos(game->mlx, &game->x, &game->x);
		game->x = 0;
		if (i == 1)
			e = load_alien(game);
		return ;
	}
	ft_hook(game);
	blank(game);
	minumap(game);
	// backgroud(game);
	raycasting(game);
	update_enemy_pos(&e, game);
	enemy_dist(game, &e);
	ft = mlx_get_time() - t;
	if (ft < time)
		usleep((int)((time - ft) * 1000000));
}
