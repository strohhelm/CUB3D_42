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

void	fill_text(t_tex *t, mlx_texture_t **tex)
{
	int	i;
	size_t	nb;

	i = NORTH;
	while (i < CEILING)
	{
		// ft_memcpy(&t->side[i], &tex[i], sizeof(mlx_texture_t));
		t->side[i].width = tex[i]->width;
		t->side[i].height = tex[i]->height;
		t->side[i].bytes_per_pixel = tex[i]->bytes_per_pixel;
		nb = sizeof(uint8_t) * t->side[i].width * t->side[i].height * 4;
		t->side[i].pixels = (uint8_t *)malloc(nb);
		if (!t->side[i].pixels)
			error_print("duuuude, get rekt malloc fucked up!");
		ft_memmove(t->side[i].pixels, &tex[i]->pixels, nb);
		i++;
	}
}

t_tex **allocate_textures(int height, int width, mlx_texture_t **tex)
{
	t_tex	**text_arr;
	int				i;

	text_arr = (t_tex **)malloc(sizeof(t_tex *) * height * width);
	if (!text_arr)
		error_print("bruuuh look at your shitty pc, cant even malloc!");
	i = -1;
	printf("w: %d, h: %d\n", width, height);
	while (++i < width * height)
	{
		text_arr[i] = (t_tex *)malloc(sizeof(t_tex));
		if (!text_arr[i])
			error_print("bruuuh look at your shitty pc, cant even malloc!");
		fill_text(text_arr[i], tex);
	}
	return (text_arr);
}
