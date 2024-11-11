/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:05:31 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/11 14:15:26 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	draw_on_tex(t_game *game, t_texture * tex, int dir)
{
	uint x;
	uint y;
	uint8_t *new_tex_pos;
	mlx_texture_t *current;
	mlx_texture_t *new;
	uint8_t *pos;

	printf("index: %u\n", tex->index);
	current = &game->map.indiv[tex->index]->side[dir];
	new = game->map.textures[BULLET];
	y = 0;
	pos = tex->tex_pos - new->height / 2 * 4 * current->width - new->width / 2 * 4;
	while (++y < new->height)
	{
		x = -1;
		while (++x < new->width)
		{
			new_tex_pos = &new->pixels[y * new->width * 4 + x * 4];
			if (*((uint32_t *)new_tex_pos))
				ft_memcpy(pos + y * 4 * current->width + x * 4, new_tex_pos, 4);
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
	// int		fu;
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
		text_arr[i] = (t_tex *)malloc(sizeof(t_tex));
		err_check(text_arr[i], "bruuuh look at your shitty pc, cant even malloc!");
		if (map[y][x] == 1)
			fill_text(text_arr[i], tex);
	}
	printf("\n");
	return (text_arr);
}
