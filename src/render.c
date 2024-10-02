/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:34:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/02 16:36:00 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void blank(t_game *game)
{
	int x = 0;
	int y = 0;

	while (x < WIDTH)
	{
		y = 0;
		while (y <= (HEIGHT / 2))
			mlx_put_pixel(game->img, x, y++, game->map.ceiling);
		while (y < (HEIGHT))
			mlx_put_pixel(game->img, x, y++, game->map.floor);
		x++;
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
	
	y = HEIGHT / 2 - 1;
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
		rowdist = posZ / p;

		
		floorstepX = rowdist * ((raydirx1 - raydirx0) / (WIDTH));
		floorstepY = rowdist * ((raydiry1 - raydiry0) / (WIDTH));

		floorX = (game->player.pos.x) + rowdist * raydirx0;
		floorY = (game->player.pos.y) + rowdist * raydiry0;
		
		x = 0; 
		while (x < WIDTH)
		{
			uint32_t texX = (int)(floortex->width * fabs(fmod(floorX, 1.0))) % floortex->width;
			uint32_t texY = (int)(floortex->height * fabs(fmod(floorY, 1.0))) % floortex->height;
			
			// printf("w:%d | %f h:%d | %f\n", floortex->width, floorX, floortex->height, floorY);
			uint8_t *tex_pos = &floortex->pixels[(floortex->width * texY + texX) * 4];
			uint8_t *img_pos = &game->img->pixels[(WIDTH * (y - 1) + x) * 4];
			
			ft_memmove(img_pos, tex_pos, sizeof(uint32_t));

			
			
			texX = (int)((ceilingtex->width) * floorX ) % ceilingtex->width;
			texY = (int)((ceilingtex->height) * floorY) % ceilingtex->height;
			
			tex_pos = &ceilingtex->pixels[(ceilingtex->width * texY + texX) * 4];

			
			img_pos = &game->img->pixels[(WIDTH * (HEIGHT - y) + x) * 4];
			
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
	t_point dir;
	t_point scr;

	dir = player->dir;
	player->dir.x/= 10;
	player->dir.y /=10;
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

void render(void *param)
{
	t_game *game;
	double t;
	double ft;
	double time = 1.0 / 30.0;
	t =	mlx_get_time();
	// printf("time:%f\n", t);
	game = (t_game*)param;
	ft_hook(game);
	// grid(game);
	blank(game);
	// draw_player(game);
	// player_dir_line(game);
	backgroud(game);
	raycasting(game);
	ft = mlx_get_time() - t;
	// printf("frametime:%f\n", ft);
	if (ft < time)
	{
		// printf("sleep %d\n", (int)((time - ft) * 1000000));
		usleep((int)((time - ft) * 1000000));
	}
}
