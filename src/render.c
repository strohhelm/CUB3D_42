/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:34:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/09/30 15:27:54 by timschmi         ###   ########.fr       */
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
// void	background(t_game *game)
// {
// 	mlx_texture_t	*floortex;
// 	mlx_texture_t	*ceilingtex;
	
// 	t_point	ray0;
// 	t_point	rayX;
	
// 	double	step;
// 	t_point	floor;
	
// 	int		y;
// 	int		x;
// 	int		p;
// 	float	posZ;
// 	float	rowdist;
	
// 	floortex = game->map.textures[FLOOR];
// 	ceilingtex = game->map.textures[CEILING];
// 	y = 0;
// 	while (y < HEIGHT / 2)
// 	{
		
		
// 		x = WIDTH / 2; 
// 		while (x < WIDTH)
// 		{
// 			int texX = (int)(floortex->width * fmod(floor.x, 1.0)) & floortex->width - 1;
// 			int texY = (int)(floortex->height * fmod(floor.y, 1.0)) & floortex->height - 1;
// 			floor.x += floorstep.x;
// 			floor.y += floorstep.y;
			
// 			uint8_t *tex_pos = &floortex->pixels[(floortex->width * texY + texX) * 4];
// 			uint32_t colour;
// 			ft_memmove(&colour, tex_pos, 4);
// 			mlx_put_pixel(game->img, x, y + HEIGHT / 2, colour);
			
// 			// texX = (uint32_t)(ceilingtex->width * (floor.x - cellX)) & ceilingtex->width - 1;
// 			// texY = (uint32_t)(ceilingtex->height * (floor.y - cellY)) & ceilingtex->height - 1;
// 			// tex_pos = &ceilingtex->pixels[ceilingtex->width * texY + texX];
// 			// ft_memcpy(&colour, tex_pos, 4);
// 			// mlx_put_pixel(game->img, x, HEIGHT - y, game->map.ceiling);
// 			x++;
// 		}
// 		y++;
// 	}
// }
// }

void	backgroud(t_game *game)
{
	mlx_texture_t	*floortex;
	mlx_texture_t	*ceilingtex;
	
	t_point	ray0;
	t_point	rayX;
	t_point	floorstep;
	t_point	floor;
	
	int		y;
	int		x;
	int		p;
	float	posZ;
	float	rowdist;
	
	floortex = game->map.textures[FLOOR];
	ceilingtex = game->map.textures[CEILING];
	y = 0;
	while (y < HEIGHT / 2)
	{
		ray0.x = game->player.dir.x - game->player.scr.x;
		ray0.y = game->player.dir.y - game->player.scr.y;
		rayX.x = game->player.dir.x + game->player.scr.x;
		rayX.y = game->player.dir.y + game->player.scr.y;
		p = y - HEIGHT/ 2;
		posZ = 0.5 * HEIGHT;
		rowdist = posZ / p;

		
		floorstep.x = rowdist * (rayX.x - ray0.x) / (WIDTH);
		floorstep.y = rowdist * (rayX.y - ray0.y) / (WIDTH);

		floor.x = game->player.pos.x + rowdist * ray0.x;
		floor.y = game->player.pos.y + rowdist * ray0.y;
		
		
		x = WIDTH; 
		while (x < WIDTH)
		{
			// int texX = (int)(floortex->width * fmod(floor.x, 1.0)) & floortex->width - 1;
			// int texY = (int)(floortex->height * fmod(floor.y, 1.0)) & floortex->height - 1;
			// floor.x += floorstep.x;
			// floor.y += floorstep.y;
			
			// uint8_t *tex_pos = &floortex->pixels[(floortex->width * texY + texX) * 4];
			uint32_t colour;
			// ft_memmove(&colour, tex_pos, 4);
			// mlx_put_pixel(game->img, x, y + HEIGHT / 2, colour);
			
			int texX = (uint32_t)(ceilingtex->width * fmod(floor.x, 1.0)) & ceilingtex->width - 1;
			int texY = (uint32_t)(ceilingtex->height * fmod(floor.y, 1.0)) & ceilingtex->height - 1;
			uint8_t *tex_pos = &ceilingtex->pixels[ceilingtex->width * texY + texX];
			ft_memcpy(&colour, tex_pos, 4);
			mlx_put_pixel(game->img, x, y, colour);
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
		scr.x = (-player->pov)/10;
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

	game = (t_game*)param;
	ft_hook(game);
	// grid(game);
	blank(game);
	// draw_player(game);
	// player_dir_line(game);
	// backgroud(game);
	raycasting(game);
}
