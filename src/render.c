/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:34:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/10/01 16:43:36 by pstrohal         ###   ########.fr       */
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
	
// 	floortex = game->map.textures[FLOOR];
// 	ceilingtex = game->map.textures[CEILING];

// 	t_point far1;
// 	t_point far2;
// 	t_point near1;
// 	t_point near2;

// 	far1.x = game->player.pos
	
	
// 	y = 0;
// 	while (y < HEIGHT / 2)
// 	{
		
		
// 		x = WIDTH / 2; 
// 		while (x < WIDTH)
// 		{
// 			int texX = (int)(floortex->width * fmod(floor.x, 1.0)) & floortex->width - 1;
// 			int texY = (int)(floortex->height * fmod(floor.y, 1.0)) & floortex->height - 1;
// 			// floor.x += floorstep.x;
// 			// floor.y += floorstep.y;
			
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
	
	int		y;
	int		x;
	int		p;
	float	posZ;
	float	rowdist;
	
	floortex = game->map.textures[FLOOR];
	ceilingtex = game->map.textures[CEILING];
	y = HEIGHT / 2;
	while (y > 0)
	{
		raydirx0 = (game->player.dir.x - game->player.scr.x) * game->map.scale;
		raydiry0 = (game->player.dir.y - game->player.scr.y) * game->map.scale;
		raydirx1 = (game->player.dir.x + game->player.scr.x) * game->map.scale;
		raydiry1 = (game->player.dir.y + game->player.scr.y) * game->map.scale;
		
		
		p = y - HEIGHT/ 2;
		posZ = 0.5 * HEIGHT;
		rowdist = posZ / p;

		
		floorstepX = rowdist * (raydirx1 - raydirx0) / (WIDTH / 2);
		floorstepY = rowdist * (raydiry1 - raydiry0) / (WIDTH / 2);

		floorX = (- game->player.pos.x) + rowdist * raydirx0;
		floorY = (- game->player.pos.y) + rowdist * raydiry0;
		
		
		x = WIDTH; 
		while (x < WIDTH)
		{
			int texX = (int)((double)floortex->width * fmod(floorX, 1.0)) & floortex->width - 1;
			int texY = (int)((double)floortex->height * fmod(floorY, 1.0)) & floortex->height - 1;
			
			floorX += floorstepX;
			floorY += floorstepY;
			
			uint8_t *tex_pos = &floortex->pixels[(floortex->width * texY + texX) * 4];
			// uint32_t colour;
			// ft_memmove(&colour, tex_pos, sizeof(uint32_t));
			uint8_t *img_pos = &game->img->pixels[(WIDTH * (HEIGHT - y - 1) + x) * 4];
			ft_memmove(img_pos, tex_pos, sizeof(uint32_t));
			
			
			// mlx_put_pixel(game->img, WIDTH - x, HEIGHT - y - 1, colour & 255);
			
			// int texX = (uint32_t)(ceilingtex->width * fmod(floor.x, 1.0)) & ceilingtex->width - 1;
			// int texY = (uint32_t)(ceilingtex->height * fmod(floor.y, 1.0)) & ceilingtex->height - 1;
			// uint8_t *tex_pos = &ceilingtex->pixels[ceilingtex->width * texY + texX];
			// ft_memcpy(&colour, tex_pos, 4);
			// mlx_put_pixel(game->img, x, y, colour);
			x++;

		}
		y--;
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
