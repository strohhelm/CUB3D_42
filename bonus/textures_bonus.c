/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@42.heilbronn.de>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-10 12:05:31 by pstrohal          #+#    #+#             */
/*   Updated: 2024-10-10 12:05:31 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	draw_on_tex(t_game *game, t_texture * tex, int dir)
{
	int x;
	int y;
	uint32_t color;
	mlx_texture_t *current;
	uint8_t *pos;

	current = &game->map.indiv[tex->index]->side[dir];
	color = 0xFF000000;
	y = -0;
	pos = tex->tex_pos - 10 * 4 * current->width - 10 * 4;
	while (++y < 20)
	{
		x = -1;
		while (++x < 20)
		{
			ft_memcpy(pos + y * 4 * current->width + x * 4, &color, 4);
		}
	}
}

void	fill_text(t_tex *t, mlx_texture_t **tex)
{
	int	i;
	size_t	nb;

	i = NORTH;
	while (i < CEILING)
	{
		t->side[i].width = tex[i]->width;
		t->side[i].height = tex[i]->height;
		t->side[i].bytes_per_pixel = tex[i]->bytes_per_pixel;
		nb = sizeof(uint8_t) * t->side[i].width * t->side[i].height * 4;
		t->side[i].pixels = (uint8_t *)malloc(nb);
		if (!t->side[i].pixels)
			error_print("duuuude, get rekt malloc fucked up!");
		ft_memmove(t->side[i].pixels, tex[i]->pixels, nb);
		i++;
	}
}

t_tex **allocate_textures(int height, int width, mlx_texture_t **tex, int **map)
{
	t_tex	**text_arr;
	int		i;
	int		fu;
	int		x;
	int		y;

	text_arr = (t_tex **)malloc(sizeof(t_tex *) * height * width);
	if (!text_arr)
		error_print("bruuuh look at your shitty pc, cant even malloc!");
	i = -1;
	y = 0;
	x = 0;
	printf("loading w: %d, h:%d\n", width, height);
	while (++i < width * height)
	{
		y = i / width;
		x = i - y * width;
		// printf("x:%d, y:%d\n", x, y);
		text_arr[i] = (t_tex *)malloc(sizeof(t_tex));
		if (!text_arr[i])
			error_print("bruuuh look at your shitty pc, cant even malloc!");
		printf("[%d", i);
		if (map[y][x] == 0)
		{
			printf("X");
			fill_text(text_arr[i], tex);
				// printf("y:%d, x:%d\n", y,x);
		}
		printf("]");
	}
	printf("\n");
	return (text_arr);
}
